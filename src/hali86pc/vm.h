#if !defined(_vm_h)
#define _vm_h

#include <libc/stdint.h>


/* This variable is expected always to contain
   the kernel virtual address at which physical memory is mapped.
   It may change as paging is turned on or off.  */
extern uintptr_t phys_mem_va;


/* Calculate a kernel virtual address from a physical address.  */
#define phystokv(pa)	((uintptr_t)(pa) + (__uintptr_t)(&phys_mem_va))

/* Same, but in reverse.
   This only works for the region of kernel virtual addresses
   that directly map physical addresses.  */
#define kvtophys(va)	((uintptr_t)(va) - (__uintptr_t)(&phys_mem_va))


/* This variable contains the kernel virtual address
   corresponding to linear address 0.
   In the absence of paging,
   linear addresses are always the same as physical addresses.  */
extern uintptr_t linear_base_va;

/* Convert between linear and kernel virtual addresses.  */
#define lintokv(la)	((uintptr_t)(la) + linear_base_va)
#define kvtolin(va)	((uintptr_t)(va) - linear_base_va)


/* If the kernel was started from real mode,
   this variable contains our original real-mode code segment.  */
extern unsigned short real_cs;

#endif