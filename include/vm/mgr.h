#pragma once

#include "ptab.h"
#include <vm/index.h>
#include <vm/vm.h>
#include <vm/ptab.h>

#define VM_PAGE_TAB_MGR_ID 0x10201001
typedef struct {
    uint64_t id;
    vm_page_table_t *pml4_address;
} vm_page_tab_mgr_t;

typedef vm_page_tab_mgr_t vptm_t; // brevity

vm_mk_page_tab_mgr(vptm_t *self, vm_page_table_t *pml4_address);

void os_vm_raw_map(vptm_t *self, uintptr_t virtual, uintptr_t physical);

