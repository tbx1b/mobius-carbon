#include "libkern/tty.h"

#include <vm/ptab.h>
#include <vm/vm.h>
#include <vm/mgr.h>
#include <vm/index.h>

#include <carbon/stdint.h>

#include <libkern/string.h>

//extern vm_alloc_t universal_allocator;

vm_mk_page_tab_mgr(vptm_t *self, vm_page_table_t *pml4_address)
{
    self->pml4_address = pml4_address;
    return 1;
}

void os_vm_raw_map(vptm_t *self, uintptr_t virtual, uintptr_t physical)
{
    vm_page_map_index_t indexer;
    vm_mk_page_map_index(&indexer, virtual);
    vm_page_dir_entry_t PDE;

    PDE = self->pml4_address->entries[indexer.page_dir_ptr_index];
    vm_page_table_t* PDP;
    if (!PDE.present){
        PDP = (vm_page_table_t*)os_vm_alloc();
        memset(PDP, 0, 0x1000);
        PDE.address = (uint64_t)PDP >> 12;
        PDE.present = true;
        PDE.rw = true;
        self->pml4_address->entries[indexer.page_dir_ptr_index] = PDE;
    }
    else
    {
        PDP = (vm_page_table_t*)((uint64_t)PDE.address << 12);
    }
    
    
    PDE = PDP->entries[indexer.page_dir_index];
    vm_page_table_t* PD;
    if (!PDE.present){
        PD = (vm_page_table_t*)os_vm_alloc();
        memset(PD, 0, 0x1000);
        PDE.address = (uint64_t)PD >> 12;
        PDE.present = true;
        PDE.rw = true;
        PDP->entries[indexer.page_dir_index] = PDE;
    }
    else
    {
        PD = (vm_page_table_t*)((uint64_t)PDE.address << 12);
    }

    PDE = PD->entries[indexer.page_table_index];
    vm_page_table_t* PT;
    if (!PDE.present){
        PT = (vm_page_table_t*)os_vm_alloc();
        memset(PT, 0, 0x1000);
        PDE.address = (uint64_t)PT >> 12;
        PDE.present = true;
        PDE.rw = true;
        PD->entries[indexer.page_table_index] = PDE;
    }
    else
    {
        PT = (vm_page_table_t*)((uint64_t)PDE.address << 12);
    }

    PDE = PT->entries[indexer.page_index];
    PDE.address = (uint64_t)physical >> 12;
    PDE.present = true;
    PDE.rw = true;
    PT->entries[indexer.page_index] = PDE;
}
