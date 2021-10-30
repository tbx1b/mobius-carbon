/**
 *  @file boot_stald.c
 *  @author MOBIUSLOOPFOUR <scratch.joint-0i@icloud.com>
 *
 *  Copyright MOBIUSLOOPFOUR 2021
 *  All rights reserved.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @brief Static elf loader
 *
 */

#include <uefi.h>
#include "bateau.h"

/*** ELF64 defines and structs ***/
#define ELFMAG      "\177ELF"
#define SELFMAG     4
#define EI_CLASS    4       /* File class byte index */
#define ELFCLASS64  2       /* 64-bit objects */
#define EI_DATA     5       /* Data encoding byte index */
#define ELFDATA2LSB 1       /* 2's complement, little endian */
#define ET_EXEC     2       /* Executable file */
#define PT_LOAD     1       /* Loadable program segment */
#ifdef __x86_64__
#define EM_MACH     62      /* AMD x86-64 architecture */
#endif
#ifdef __aarch64__
#define EM_MACH     183     /* ARM aarch64 architecture */
#endif

typedef struct
{
    uint8_t  e_ident[16];   /* Magic number and other info */
    uint16_t e_type;        /* Object file type */
    uint16_t e_machine;     /* Architecture */
    uint32_t e_version;     /* Object file version */
    uint64_t e_entry;       /* Entry point virtual address */
    uint64_t e_phoff;       /* Program header table file offset */
    uint64_t e_shoff;       /* Section header table file offset */
    uint32_t e_flags;       /* Processor-specific flags */
    uint16_t e_ehsize;      /* ELF header size in bytes */
    uint16_t e_phentsize;   /* Program header table entry size */
    uint16_t e_phnum;       /* Program header table entry count */
    uint16_t e_shentsize;   /* Section header table entry size */
    uint16_t e_shnum;       /* Section header table entry count */
    uint16_t e_shstrndx;    /* Section header string table index */
} elf64_ehdr_t;

typedef struct
{
    uint32_t p_type;        /* Segment type */
    uint32_t p_flags;       /* Segment flags */
    uint64_t p_offset;      /* Segment file offset */
    uint64_t p_vaddr;       /* Segment virtual address */
    uint64_t p_paddr;       /* Segment physical address */
    uint64_t p_filesz;      /* Segment size in file */
    uint64_t p_memsz;       /* Segment size in memory */
    uint64_t p_align;       /* Segment alignment */
} elf64_phdr_t;

/**
 * Load an ELF executable
 */

#include "bootf.h"

int 
stald(char *path, bateau_info_struct_t *argv)
{
    FILE *f;
    char *buff;
    long int size;
    elf64_ehdr_t *elf;
    elf64_phdr_t *phdr;
    uintptr_t  entry;
    int i;

    /* load the file */
    if((f = fopen(path, "r"))) {
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        buff = malloc(size + 1);
        if(!buff) {
            printf("Unable to allocate memory\n");
            boot_failure_feedback();
            return 1;
        }
        fread(buff, size, 1, f);
        fclose(f);
    } else {
        printf("Unable to open file\n");
        disk_failure_feedback();
        return 0;
    }

    /* is it a valid ELF executable for this architecture? */
    elf = (elf64_ehdr_t *)buff;
    if(!memcmp(elf->e_ident, ELFMAG, SELFMAG) &&    /* magic match? */
        elf->e_ident[EI_CLASS] == ELFCLASS64 &&     /* 64 bit? */
        elf->e_ident[EI_DATA] == ELFDATA2LSB &&     /* LSB? */
        elf->e_type == ET_EXEC &&                   /* executable object? */
        elf->e_machine == EM_MACH &&                /* architecture match? */
        elf->e_phnum > 0) {                         /* has program headers? */
            /* load segments */
            for(phdr = (elf64_phdr_t *)(buff + elf->e_phoff), i = 0;
                i < elf->e_phnum;
                i++, phdr = (elf64_phdr_t *)((uint8_t *)phdr + elf->e_phentsize)) {
                    if(phdr->p_type == PT_LOAD) {
                        printf("ELF segment %p %d bytes (bss %d bytes)\n", phdr->p_vaddr, phdr->p_filesz,
                            phdr->p_memsz - phdr->p_filesz);
                        memcpy((void*)phdr->p_vaddr, buff + phdr->p_offset, phdr->p_filesz);
                        memset((void*)(phdr->p_vaddr + phdr->p_filesz), 0, phdr->p_memsz - phdr->p_filesz);
                    }
                }
            entry = elf->e_entry;
    } else {
        printf("Not a valid ELF executable for this architecture\n");
        boot_failure_feedback();
        return 0;
    }
    /* free resources */
    free(buff);

    printf("ELF entry point %p\n", entry);
    printf("ENV ptr: %p\n", argv);
    
    printf("ELF entry point %p\n", entry);

    exit_bs();
    i = (*((int(* __attribute__((sysv_abi)))(bateau_info_struct_t*))(entry)))(argv);
    printf("You shouldn't see this\n");

    boot_failure_feedback();
    return 0;
}
