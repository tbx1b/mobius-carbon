/**
 *  @file kern_vm.c
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
 *  @brief Kernel virtual memory facilities. Please note that this is not a substitute
 *          for a memory mamanger
 *
 */

#include "libkern/tty.h"
#include "libsa/bateau.h"
#include <carbon/stdint.h>
#include <vm/vm.h>
#include <carbon/assert.h>

uint64_t
os_vm_get_mem_size(efi_descriptor_t *memmap, size_t entries, size_t desc_size)
{
    uint64_t result = 0;

    kprintf("&memmap = $\n", memmap);
    kprintf("entries = #\n", entries);
    kprintf("desc_size = #\n", desc_size);

    for (size_t i = 0; i < entries; i++) {
        efi_descriptor_t *desc = (efi_descriptor_t *)((uintptr_t)memmap + (i * desc_size));
        assert(desc->page_count > 0, "desc->page_count underflow (os_vm_get_size)");
        result += desc->page_count * 0x1000;
    }
    
    assert(result > 0, "The memory map appears to be null (result > 0)");

    kprintf("Got size successfully (#)\n", result);

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

static _Bool _pgfa_inited = 0;
static os_vm_bitset_t bitset;

static void
_init_bitmap(void *buffer_address, size_t size)
{
    bitset.size = size;
    bitset.buffer = buffer_address;
    bitset.id = 0x10000001;

    for (size_t i = 0; i < size; i ++) {
        *(uint8_t*)(bitset.buffer + i) = 0;
    }
}

os_vm_read_efi_memmmap(vm_alloc_t *vm_alloc, 
                        efi_descriptor_t *memmap, 
                        size_t memmap_size, 
                        size_t memmap_descriptor_size)
{
    if (_pgfa_inited != 0)
        return 0;
    else
        _pgfa_inited = 1;

    size_t memmap_entries       = memmap_size / memmap_descriptor_size;
    uintptr_t largest_free      = 0;
    size_t largest_free_size    = 0;

    kprintf("memmap_entries: #\n", memmap_entries);

    for (size_t i = 0; i < memmap_entries; i ++) {
        efi_descriptor_t *desc  = (efi_descriptor_t *)((uintptr_t)memmap + (i * memmap_descriptor_size));

        if (desc->type == 7) { // conventional memory
            if (desc->page_count * 0x1000 > largest_free_size) {

                largest_free        = (uintptr_t)desc->physical_address;
                kprintf("largest_free = $\n", largest_free);

                largest_free_size = desc->page_count * 0x1000;
                kprintf("largest_free_size = #\n", largest_free_size);

            }
        }
    }

    kprintf("pointer to largest_free: $\n", largest_free);

    size_t mem_size = os_vm_get_mem_size(memmap, memmap_entries, memmap_descriptor_size);
    vm_alloc->free = mem_size;

    uint64_t bitset_size = mem_size / 0x1000 / 0x0008 + 1;
    assert(mem_size != 0, "mem_size != 0");

    _init_bitmap((void *)largest_free, bitset_size);
    assert(bitset.id == 0x10000001, "Bitset ID was not set after setup");

    os_vm_lock_m(vm_alloc, (uintptr_t)(&bitset), bitset.size / 0x1000 + 1);

    for (size_t i = 0; i < memmap_entries; i++){
        efi_descriptor_t* desc = (efi_descriptor_t*)((uint64_t)memmap + (i * memmap_descriptor_size));
        if (desc->type != 7){ // not efiConventionalMemory
            os_vm_reserve_m(vm_alloc, (uintptr_t)desc->physical_address, desc->page_count);
        }
    }

    return 1;
}

uintptr_t os_vm_request(vm_alloc_t *self) 
{
    for (size_t index = 0; index < (bitset.size) * 8; index ++) {
        if (os_vm_get(&(bitset), index) == 0)
            return ((uintptr_t)(0));

        os_vm_lock(self, (uintptr_t)(index * 0x1000));
        return (uintptr_t)(index * 0x1000);
    }
    return ((uintptr_t)(0));
}

os_vm_free(vm_alloc_t *self, uintptr_t address)
{
    size_t index = address / 0x1000;
    if (os_vm_get(&(bitset), index) == 0) {
        return 0;
    }

    os_vm_set(&(bitset), index, 0);

    self->free += 0x1000;
    self->used -= 0x1000;

    return 1;
}

os_vm_free_m(vm_alloc_t *self, uintptr_t address, size_t page_count)
{
    for (size_t i = 0; i < page_count; i++) {
        auto r = os_vm_free(self, (address + (i * 0x1000)));
        if (r == 0) {
            return r;
        }
    }
    return 1;
}

os_vm_lock(vm_alloc_t *self, uintptr_t address) 
{
    size_t index = address / 0x1000;
    if (os_vm_get(&(bitset), index) == 1)
        return 0;

    os_vm_set(&(bitset), index, 1);

    self->free -= 0x1000;
    self->used += 0x1000;
    return 1;
}

os_vm_lock_m(vm_alloc_t *self, uintptr_t address, size_t page_count)
{
    for (size_t i = 0; i < page_count; i ++) {
        auto r = os_vm_lock(self, (address + (i * 0x1000)));
        if (r == 0) {
            return r;
        }
    }
    return 1;
}

os_vm_release(vm_alloc_t *self, uintptr_t address)
{
    size_t index = address / 0x1000;
    if (os_vm_get(&(bitset), index) == 0)
        return 0;
    
    os_vm_set(&(bitset), index, 0);

    self->free += 0x1000;
    self->reserved -= 0x1000;
    return 1;
}

os_vm_release_m(vm_alloc_t *self, uintptr_t address, size_t page_count)
{
    for (size_t i = 0; i < page_count; i++) {
        auto r = os_vm_release(self, (address + (i * 0x1000)));
        if (r == 0) {
            return r;
        }
    }
    return 1;
}

os_vm_reserve(vm_alloc_t *self, uintptr_t address)
{
    size_t index = address / 0x1000;
    if (os_vm_get(&(bitset), index) == 1) {
        return 0;
    }
    os_vm_set(&(bitset), index, 1);
    
    self->free -= 0x1000;
    self->reserved += 0x1000;
    return 1;
}

os_vm_reserve_m(vm_alloc_t *self, uintptr_t address, size_t page_count)
{
    for (size_t i = 0; i < page_count; i++) {
        auto r = os_vm_reserve(self, (address + (i * 0x1000)));
        if (r == 0) {
            return r;
        }
    }
    return 1;
}
