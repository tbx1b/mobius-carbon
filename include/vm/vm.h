/**
 *  @file vm.h
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
 *  @brief Basic paging facilities.
 *
 */

#pragma once 

#include <libsa/bateau.h>
#include <carbon/stdint.h>

#define OS_VM_BITSET_ID 0x10000001
typedef struct {
    uint32_t    id;
    size_t      size;
    uint8_t     *buffer;
} os_vm_bitset_t;

#define OS_VM_PAGE_FRAME_ALLOC_ID

typedef struct os_vm_page_frame_alloc_t {
    uint32_t    id; // OS_VM_PAGE_FRAME_ALLOC_ID

    size_t      free;
    size_t      reserved;
    size_t      used;

    os_vm_bitset_t bitset;
} vm_alloc_t;

os_vm_get(os_vm_bitset_t *b, uint64_t index);

os_vm_set(os_vm_bitset_t *b, uint64_t index, uint8_t value);

os_vm_read_efi_memmmap(vm_alloc_t *vm_alloc, 
                        efi_descriptor_t *memmap, 
                        size_t memmap_size, 
                        size_t memmap_descriptor_size);

uintptr_t os_vm_request(vm_alloc_t *self);

os_vm_free(vm_alloc_t *self, uintptr_t address);

os_vm_free_m(vm_alloc_t *self, uintptr_t address, size_t page_count);

os_vm_lock(vm_alloc_t *self, uintptr_t address);

os_vm_lock_m(vm_alloc_t *self, uintptr_t address, size_t page_count);

os_vm_release(vm_alloc_t *self, uintptr_t address);

os_vm_release_m(vm_alloc_t *self, uintptr_t address, size_t page_count);

os_vm_reserve(vm_alloc_t *self, uintptr_t address);

os_vm_reserve_m(vm_alloc_t *self, uintptr_t address, size_t page_count);

os_kern_vm_init(bateau_info_struct_t *aBootTimeEnvironment);
