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

extern void __kern_delay(reg_t r);
#define delay __kern_delay

extern void __kern_core_id(reg_t r);
#define core_id __kern_core_id

extern void __kern_rmstatus(reg_t r);
#define rmstatus __kern_rmstatus

extern void __kern_wmstatus(reg_t r);
#define wmstatus __kern_wmstatus

extern void __kern_wmpec(reg_t r);
#define wmpec __kern_wmpec

extern void __kern_wmscratch(reg_t r);
#define wmscratch __kern_wmscratch

extern void __kern_mtvec(reg_t r);
#define mtvec __kern_mtvec

extern void __kern_rmie(reg_t r);
#define rmie __kern_rmie

extern void __kern_wmie(reg_t r);
#define wmie __kern_wmie

