#include "libkern/tty.h"
#include <carbon/stdint.h>
#include <carbon/assert.h>
#include <vm/vm.h>
#include <libsa/bateau.h>


vm_alloc_t universal_allocator;

extern uint64_t _k_start;
extern uint64_t _k_end;


os_kern_vm_init(bateau_info_struct_t *aBootTimeEnvironment)
{
    os_vm_read_efi_memmmap(&universal_allocator, aBootTimeEnvironment->memmap, aBootTimeEnvironment->memmap_size, aBootTimeEnvironment->memmap_descriptor_size);
    
    ptrdiff_t k_size    = (uintptr_t)&_k_end - (uintptr_t)&_k_start;
    size_t k_pages      = (uintptr_t)k_size / 0x1000 + 1;

    os_vm_lock_m(&universal_allocator, (uintptr_t)&_k_start, k_pages);

    assert(k_size > 0, "Kernel size must be greater than zero.");

    return 1;
}
