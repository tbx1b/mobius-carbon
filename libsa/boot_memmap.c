/**
 *  @file boot_memmap.c
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
 *  @brief Basic impl. of the POSIX libc string functions. strdup will not be implemented
 *          in kernel space. (malloc)
 *
 */

#include <uefi.h>
#include "bootf.h"
#include "bateau.h"

const char *memmap_types[] = 
{
        "EfiReservedMemoryType",
        "EfiLoaderCode",
        "EfiLoaderData",
        "EfiBootServicesCode",
        "EfiBootServicesData",
        "EfiRuntimeServicesCode",
        "EfiRuntimeServicesData",
        "EfiConventionalMemory",
        "EfiUnusableMemory",
        "EfiACPIReclaimMemory",
        "EfiACPIMemoryNVS",
        "EfiMemoryMappedIO",
        "EfiMemoryMappedIOPortSpace",
        "EfiPalCode"
};

bateau_memmap_result_t
make_memmap(void)
{
    bateau_memmap_result_t          result;
    efi_status_t                    status;
    efi_memory_descriptor_t         *memmap;
    uint64_t                         memmap_size, memmap_key, memmap_desc_size;

    memmap = NULL;
    memmap_size = 0;
    memmap_desc_size = 0;
    memmap_key = 0;

    /* first run: checks */
    status = BS->GetMemoryMap(&memmap_size, NULL, &memmap_key, &memmap_desc_size, NULL);

    if (status != EFI_BUFFER_TOO_SMALL || !memmap_size) {
        printf("Unable to retrieve the EFI Memory Map\n");
        boot_failure_feedback();
    }

    /* in worst case malloc allocates two blocks, and each block might split a record into three, that's 4 additional records */
    memmap_size += (4 * memmap_desc_size);


    /* allocate memmap */
    memmap = (efi_memory_descriptor_t*)malloc(memmap_size + 1);

    if (!memmap) {
        printf("Unable to allocate memory for the EFI Memory Map (the irony!)\n");
        //boot_failure_feedback();
    }

    /* populate */
    status = BS->GetMemoryMap(&memmap_size, memmap, &memmap_key, &memmap_desc_size, NULL);
    


    if (EFI_ERROR(status)) {
        printf("Unable to write the EFI Memory Map to memory (the irony!)\n");
        //boot_failure_feedback();
    }

    result.memmap = memmap;
    result.memmap_descriptor_size = memmap_desc_size;
    result.memmap_size = memmap_size;

    printf("result.memmap = 0x%x\n", result.memmap);
    printf("result.memmap_descriptor_size = %d\n", result.memmap_descriptor_size);
    printf("result.memmap_size = %d\n", result.memmap_size);

    return result;
}
