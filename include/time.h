#pragma once

#include <types.h>

void __kern_delay(volatile size count);
#define delay __kern_delay

#define MPP_MASK (3 << 11)
#define MPP_M (3 << 11)
#define MPP_S (1 << 11)
#define MPP_U (0 << 11)
#define MIE (1 << 3)
#define MIE_MEIE (1 << 11) // extern
#define MIE_MTIE (1 << 7)  // timer
#define MIE_MSIE (1 << 3)  // sw
#define NCPU 8             // maximum number of CPUs
#define CLINT 0x2000000
#define CLINT_MTIMECMP(hartid) (CLINT + 0x4000 + 4*(hartid))
#define CLINT_MTIME (CLINT + 0xBFF8) // cycles since boot.

extern void sys_timer();