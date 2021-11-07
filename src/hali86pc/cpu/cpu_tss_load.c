#include <hali86pc/tss.h>
#include <hali86pc/gdt.h>

void base_tss_load(void)
{
	/* Make sure the TSS isn't marked busy.  */
	base_gdt[BASE_TSS / 8].access &= ~ACC_TSS_BUSY;

	/* Load the TSS.  */
	set_tr(BASE_TSS);
}