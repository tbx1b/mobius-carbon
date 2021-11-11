#ifndef __MMU_H_
#define __MMU_H_

#include <stdint.h>

// Maps the whole 4GiB address space.
extern uint32_t page_directory[0x400] __attribute__((aligned(0x1000)));
extern uint32_t page_table[0x400] __attribute__((aligned(0x1000)));

#endif // __MMU_H_