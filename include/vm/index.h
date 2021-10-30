#pragma once
#include <carbon/stdint.h>

typedef struct {
    size_t page_dir_ptr_index;
    size_t page_dir_index;
    size_t page_table_index;
    size_t page_index;
} vm_page_map_index_t;

vm_mk_page_map_index(vm_page_map_index_t *self, uintptr_t  virtual_address);

