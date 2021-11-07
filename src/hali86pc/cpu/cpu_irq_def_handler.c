#include <hali86pc/trap.h>

unsigned int base_irq_default_handler(struct trap_state *ts)
{
	printf_("Unexpected interrupt %d\n", ts->err);
	return 0;
}