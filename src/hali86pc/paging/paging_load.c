/* @(#) hal_paging_load.c */

#include <hali86pc/_internal.h>
#include <hali86pc/paging.h>
#include <hali86pc/vm.h>

INLINE void paging_enable(uintptr_t pdir)
{
	/* Load the page directory.  */
	set_cr3(pdir);

	/* Turn on paging.  */
	__asm__ volatile(
	"	movl	%0,%%cr0\n"
	"	jmp	1f\n"
	"1:\n"
	: : "r" (get_cr0() | CR0_PG));
}

void base_paging_load(void)
{
	/* Enable superpage support if we have it.  */
	/* Note from 2021: I think we have it...
	 * Always enabled...
	 */
	set_cr4(get_cr4() | CR4_PSE);


	/* Turn on paging.  */
	paging_enable(base_pdir_pa);
}