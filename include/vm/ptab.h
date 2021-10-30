#pragma once

#include <carbon/stdint.h>


typedef struct {
    _Bool present       : 1;
    _Bool rw            : 1;
    _Bool su            : 1;
    _Bool wt            : 1; // write-through
    _Bool cache_ds      : 1; // cache disabled
    _Bool dirty         : 1;
    _Bool nop_00        : 1;
    _Bool larger_p      : 1;
    _Bool nop_01        : 1;
    uint8_t avaialble   : 3; // anything
    uintptr_t  address   : 52;
} vm_page_dir_entry_t;

typedef vm_page_dir_entry_t pd_entry_t; // shorthand

typedef struct {
    pd_entry_t entries[512];
} __attribute__((aligned(0x1000))) vm_page_table_t;

