#include <chips/mmu.h>

uint32_t page_directory[0x400] __attribute__((aligned(0x1000)));
// eof