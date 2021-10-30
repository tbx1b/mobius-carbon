/**
 *  @file vm_paging.c
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
 *  @brief Basic allocation and freeing of memory pages.
 *
 */

#include "libkern/tty.h"
#include "libsa/bateau.h"
#include <carbon/stdint.h>
#include <vm/vm.h>
#include <carbon/assert.h>


static uint64_t __private_free_mem;
static uint64_t __private_reserved_mem;
static uint64_t __private_used_mem;
static bool __private_initliazed = false;
struct os_vm_page_frame_alloc_t universal_allocator;
static os_vm_bitset_t __private_bmp;

uint64_t
os_vm_get_mem_size(efi_descriptor_t *memmap, size_t entries, size_t desc_size)
{
    uint64_t result = 0;

    //kprintf("&memmap = $\n", memmap);
    //kprintf("entries = #\n", entries);
    //kprintf("desc_size = #\n", desc_size);

    for (size_t i = 0; i < entries; i++) {
        efi_descriptor_t *desc = (efi_descriptor_t *)((uintptr_t )memmap + (i * desc_size));
        //assert(desc->page_count > 0, "desc->page_count underflow (os_vm_get_size)");
        result += desc->page_count * 0x1000;
    }
    
    //assert(result > 0, "The memory map appears to be null (result > 0)");

    //kprintf("Got size successfully (#)\n", result);

    return result;
}

os_vm_get(os_vm_bitset_t *b, uint64_t index)
{   
    assert(b->id == 0x10000001, "os_vm_get: Not a bitset");

    uint64_t byte_index = index / 8;
    uint8_t bit_index = index % 8;
    uint8_t bit_indexer = 0x80 >> bit_index;

    if (((b->buffer)[byte_index] & bit_indexer) > 0){
        return 1;
    }
    return 0;
}

os_vm_set(os_vm_bitset_t *b, uint64_t index, uint8_t value)
{
    assert(b->id == 0x10000001, "os_vm_set: Not a bitset");

    uint64_t byte_index = index / 8;
    uint8_t bit_index = index % 8;
    uint8_t bit_indexer = 0x80 >> bit_index;

    (b->buffer)[byte_index] &= ~bit_indexer;

    if (value){
        (b->buffer)[byte_index] |= bit_indexer;
    }
    return 1;
}

void os_vm_read_memmap(efi_descriptor_t* memmap, size_t memmap_size, size_t memmap_desc_size)
{
    if (__private_initliazed) return;

    __private_initliazed = true;

    uint64_t entries = memmap_size / memmap_desc_size;

    uintptr_t largestFreeMemSeg = NULL;
    size_t largestFreeMemSegSize = 0;

    for (int i = 0; i < entries; i++){
        efi_descriptor_t* desc = (efi_descriptor_t*)((uint64_t)memmap + (i * memmap_desc_size));
        if (desc->type == 7){ // type = EfiConventionalMemory
            if (desc->page_count * 0x1000 > largestFreeMemSegSize)
            {
                largestFreeMemSeg = (uintptr_t)(desc->physical_address);
                largestFreeMemSegSize = desc->page_count * 0x1000;
            }
        }
    }

    uint64_t memorySize = os_vm_get_mem_size(memmap, entries, memmap_desc_size);
    __private_free_mem = memorySize;
    uint64_t bmp_size = memorySize / 0x1000 / 8 + 1;

    _init_bmp(bmp_size, largestFreeMemSeg);

    os_vm_lock_m((uintptr_t)&__private_bmp, __private_bmp.size / 0x1000 + 1);

    for (int i = 0; i < entries; i++){
        efi_descriptor_t* desc = (efi_descriptor_t*)((uint64_t)memmap + (i * memmap_desc_size));
        if (desc->type != 7){ // not efiConventionalMemory
            os_vm_reserve_m((uintptr_t)desc->physical_address, desc->page_count);
        }
    }
}

void _init_bmp(size_t bmp_size, uintptr_t buffer_address)
{
    __private_bmp.size = bmp_size;
    __private_bmp.buffer = (uint8_t*)buffer_address;
    __private_bmp.id = 0x10000001;
    for (int i = 0; i < bmp_size; i++){
        *(uint8_t*)(__private_bmp.buffer + i) = 0;
    }
}

uintptr_t os_vm_alloc(void)
{
    for (uint64_t index = 0; index < __private_bmp.size * 8; index++){
        if (os_vm_get(&__private_bmp, index) == true) continue;
        os_vm_lock(index * 0x1000);
        return (index * 0x1000);
    }

    return NULL; // Page Frame Swap to file
}

void os_vm_free(uintptr_t address)
{
    uint64_t index = (uint64_t)address / 0x1000;
    if (os_vm_get(&__private_bmp, index) == false) return;
    os_vm_set(&__private_bmp, index, false);
    __private_free_mem += 0x1000;
    __private_used_mem -= 0x1000;
}

void os_vm_free_m(uintptr_t address, uint64_t page_count)
{ // free multiple pages
    for (int t = 0; t < page_count; t++) {
        os_vm_free((uintptr_t)address + (t * 0x1000));
    }
}

void os_vm_lock(uintptr_t address)
{
    uint64_t index = (uint64_t)address / 0x1000;

    if (os_vm_get(&__private_bmp, index) == true) return;
    os_vm_set(&__private_bmp, index, true);

    __private_free_mem -= 0x1000;
    __private_used_mem += 0x1000;
}

void os_vm_lock_m(uintptr_t address, uint64_t page_count)
{
    for (int t = 0; t < page_count; t++) {
        os_vm_lock((uintptr_t)address + (t * 0x1000));
    }
}

void os_vm_release(uintptr_t address)
{
    uint64_t index = (uint64_t)address / 0x1000;

    if (os_vm_get(&__private_bmp, index) == false) return;
    os_vm_set(&__private_bmp, index, false);

    __private_free_mem += 0x1000;
    __private_reserved_mem -= 0x1000;
}

void os_vm_release_m(uintptr_t address, uint64_t page_count)
{
    for (int t = 0; t < page_count; t++) {
        os_vm_release((uintptr_t)address + (t * 0x1000));
    }
}

void os_vm_reserve(uintptr_t address)
{
    uint64_t index = (uint64_t)address / 0x1000;

    if (os_vm_get(&__private_bmp, index) == true) return;
    os_vm_set(&__private_bmp, index, true);

    __private_free_mem -= 0x1000;
    __private_reserved_mem += 0x1000;
}

void os_vm_reserve_m(uintptr_t address, uint64_t page_count)
{
    for (int t = 0; t < page_count; t++) {
        os_vm_reserve((uintptr_t)address + (t * 0x1000));
    }
}

uint64_t vm_free()
{
    return __private_free_mem;
}
uint64_t vm_used()
{
    return __private_used_mem;
}
uint64_t vm_reserved()
{
    return __private_reserved_mem;
}
