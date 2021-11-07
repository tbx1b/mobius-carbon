#include <hali86pc/irq.h>

/*
 * The initial values of these variables
 * are the standard locations of the PICs on startup of a PC.
 * We will typically reprogram the PICs (see base_irq_init)
 * so that the master PIC doesn't conflict with processor exception vectors;
 * at that point these variables will be changed to reflect the new locations.
 */
int irq_master_base = 0x08;
int irq_slave_base = 0x70;

/*
 * Hardware interrupt nesting counter and software interrupt flag.
 */
unsigned char base_irq_nest = BASE_IRQ_SOFTINT_CLEARED;

/*
 * High-level IRQ handler function table;
 * all entries initially point to the unexpected interrupt handler.
 */
unsigned int (*base_irq_handlers[BASE_IRQ_COUNT])(struct trap_state *ts) = {
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler,
	base_irq_default_handler
};