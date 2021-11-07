#include <hali86pc/trap.h>
#include <hali86pc/gate_init.h>
#include <hali86pc/gdt.h>
#include <hali86pc/idt.h>

void base_trap_init(void)
{
	gate_init(base_idt, base_trap_inittab, KERNEL_CS);
}