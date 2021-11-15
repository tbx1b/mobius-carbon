#include <sys/defs.h>
#include "mmu.h"

struct sdesc gdt[6];

int
seginit(void)
{  
  gdt[SEG_KCODE] = SEG(ASBX|ASBR, 0, 0xffffffff, 0);
  gdt[SEG_KDATA] = SEG(ASBW, 0, 0xffffffff, 0);
  gdt[SEG_UCODE] = SEG(ASBX|ASBR, 0, 0xffffffff, DPL_USER);
  gdt[SEG_UDATA] = SEG(ASBW, 0, 0xffffffff, DPL_USER);
  lgdt(gdt, sizeof(gdt));

  return 0;
}