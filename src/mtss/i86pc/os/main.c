/* @(#) main.c */

#include <core.h>
#include <std/stdint.h>
#include <std/stdbool.h>
#include <sys/io.h>
#include <sys/vm.h>
#include <sys/assert.h>
#include "tab.h"

#include "annouce.h"

extern ISR interrupt_handlers[256];

MTSS_API void
kernelMain(void)
{
    announce();
    loadg();
    trace("GDT loaded with no fault");
    loadi();
    trace("IDT loaded with no fault");

    /* unexpected end of kerne */
    assert(FALSE);
    return;
}