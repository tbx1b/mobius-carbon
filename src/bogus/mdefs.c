#include <libc/stddef.h>
#include <libc/stdint.h>
#include <libcarbon/core.h>
#include <hali86pc/paging.h>
#include <hali86pc/vm.h>
#include <hali86pc/machine/proc_reg.h>
#include <hali86pc/_internal.h>

INLINE pt_entry_t *pdir_find_pte(uintptr_t pdir_pa, uintptr_t la)
{
	pd_entry_t *pde = pdir_find_pde(pdir_pa, la);
	if (!(*pde & INTEL_PDE_VALID))
		return 0;
	return ptab_find_pte(pde_to_pa(*pde), la);
}

INLINE pt_entry_t pdir_get_pte(uintptr_t pdir_pa, uintptr_t la)
{
	pt_entry_t *pte = pdir_find_pte(pdir_pa, la);
	return pte ? *pte : 0;
}

INLINE void paging_disable(void)
{
	/* Turn paging off.  */
	__asm__ volatile(
	"	movl	%0,%%cr0\n"
	"	jmp	1f\n"
	"1:\n"
	: : "r" (get_cr0() & ~CR0_PG));

	/* Flush the TLB.  */
	set_cr3(0);
}

#undef get_eflags
#undef set_eflags

/* __inline */ unsigned get_eflags(void)
{
	unsigned eflags;
	__asm__ volatile(
	"	pushfl\n"
	"	popl %0" : "=r" (eflags));
	return eflags;
}

/* __inline */ void set_eflags(unsigned eflags)
{
	__asm__ volatile(
	"	pushl %0\n"
	"	popfl" : : "r" (eflags));
}

