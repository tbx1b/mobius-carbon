#include <hali86pc/gdt.h>
#include <hali86pc/tss.h>
#include <hali86pc/machine/proc_reg.h>

void base_tss_init(void)
{
	/* Only initialize once.  */
	if (!base_tss.ss0)
	{
		base_tss.ss0 = KERNEL_DS;
		base_tss.esp0 = get_esp(); /* only temporary */
		base_tss.io_bit_map_offset = sizeof(base_tss);
	}
}