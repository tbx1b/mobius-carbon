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
