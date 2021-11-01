/*
 * MODULE:          Kernel
 * LICENSE:         GPL-3.0-or-later
 * PURPOSE:         Entry point
 * COPYRIGHT:       Copyright MobiusLoopFour
 */

/* INCLUDES *******************************************************************/

#include <carbon.h>

/* ENTRY POINT ****************************************************************/

extern void announce(void);

void kernel_main(void) 
{
	/* 1.1 Print a welcome message */
	announce();


	hal_tab_init();
	printf("fmt: 0x%X\n", 0x1BADB002);

	__asm__("int $31");

	printf("fmt: 0x%X\n", hal_idt_get_last());

	return;
}
/* EOF */