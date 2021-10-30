/**
 *  @file libk_memmove.c
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
 *  @brief Virtual memory facilities.
 *
 */

#pragma once

#include "libkern/tty.h"
#include "libsa/bateau.h"
#include <carbon/stdint.h>
#include <carbon/assert.h>

#define bool _Bool
#define false 0
#define true !false
#define NULL 0

#define OS_VM_BITSET_ID 0x10000001
typedef struct {
    uint32_t    id;
    size_t      size;
    uint8_t     *buffer;
} __attribute__((packed)) os_vm_bitset_t;

#define OS_VM_PAGE_FRAME_ALLOC_ID 0x10000002

typedef struct os_vm_page_frame_alloc_t {
    uint32_t    id; // OS_VM_PAGE_FRAME_ALLOC_ID

    size_t      free;
    size_t      reserved;
    size_t      used;

    os_vm_bitset_t bitset;
} vm_alloc_t;

void os_vm_read_memmap(efi_descriptor_t* memmap, size_t memmap_size, size_t memmap_desc_size);

void _init_bmp(size_t bmp_size, uintptr_t buffer_address);

uintptr_t os_vm_alloc();

void os_vm_free(uintptr_t address);

void os_vm_free_m(uintptr_t address, uint64_t page_count);

void os_vm_lock(uintptr_t address);

void os_vm_lock_m(uintptr_t address, uint64_t page_count);

void os_vm_release(uintptr_t address);

void os_vm_release_m(uintptr_t address, uint64_t page_count);

void os_vm_reserve(uintptr_t address);

void os_vm_reserve_m(uintptr_t address, uint64_t page_count);

uint64_t vm_free();
uint64_t vm_used();
uint64_t vm_reserved();
