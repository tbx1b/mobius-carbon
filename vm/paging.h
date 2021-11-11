#ifndef __VM_PAGIN_H_
#define __VM_PAGIN_H_

#include <stdint.h>
#include <stddef.h>
#include <chips/mmu.h>

extern void load_pdir(uint32_t*);
extern void enable_paging();

extern int vminit1();
extern int vminit2();

#endif // __VM_PAGIN_H_
// eof