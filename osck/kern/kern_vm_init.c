#include <vm/mgr.h>
#include <libkern/tty.h>

#include <carbon/stdint.h>
#include <carbon/assert.h>

#include <libkern/string.h>
#include <vm/vm.h>
#include <vm/ptab.h>
#include <vm/index.h>

#include <libsa/bateau.h>


extern vm_alloc_t universal_allocator;

extern uint64_t _k_start;
extern uint64_t _k_end;

extern uint64_t os_vm_get_mem_size(efi_descriptor_t *memmap, size_t entries, size_t desc_size);


os_kern_vm_init(bateau_info_struct_t *aBootTimeEnvironment)
{
    uint64_t entries = aBootTimeEnvironment->memmap_size / aBootTimeEnvironment->memmap_descriptor_size;
    os_vm_read_memmap(aBootTimeEnvironment->memmap, aBootTimeEnvironment->memmap_size, aBootTimeEnvironment->memmap_descriptor_size);

    ptrdiff_t kernel_size = (uintptr_t)&_k_end - (uintptr_t)&_k_start;
    size_t kernel_p = (uintptr_t)kernel_size / 0x1000 + 1; // amount of kernel pages to be alloc'd

    os_vm_lock_m((uintptr_t)&_k_start, kernel_p);

    vm_page_table_t *pml4 = (vm_page_table_t *)os_vm_alloc();
    memset(pml4, 0, 0x1000);

    vm_page_tab_mgr_t page_tab_mgr;
    vm_mk_page_tab_mgr(&page_tab_mgr, pml4);

    for (uint64_t t = 0; t < os_vm_get_mem_size(aBootTimeEnvironment->memmap, entries, aBootTimeEnvironment->memmap_descriptor_size); t+= 0x1000){
        os_vm_raw_map(&page_tab_mgr, t, t);
    }

    uint64_t fbBase = (uint64_t)aBootTimeEnvironment->frame_buffer->base;
    uint64_t fbSize = (uint64_t)aBootTimeEnvironment->frame_buffer->size + 0x1000;
    for (uint64_t t = fbBase; t < fbBase + fbSize; t += 0x1000){
        os_vm_raw_map(&page_tab_mgr, t, t);
    }

    #pragma INTEL64_SPECIFIC
    __asm__("mov %0, %%cr3" : : "r" (pml4)); // load the page table into the control register. (x86_64)

    os_vm_raw_map(&page_tab_mgr, 0x600000000, 0x80000);

    // trivial test
    uint64_t* test = (uint64_t*)0x600000000;
    *test = 10;
    assert(*test == 10, "Paging was not set up correctly or is corrupted");

    return 1;
}
