/* @(#) init.c - hal init */

#include <libcarbon/core.h>
#include <libcarbon/hal.h>

#include <libc/stdint.h>

#include <libcarbon/core.h>
#include <libcarbon/io.h>
#include <libcarbon/vm.h>
#include <libcarbon/assert.h>
#include <libcarbon/hal.h>

MLTX_API _hal_init(void) {

	/* announce() should go first */
	announce();
	trace("HAL initialised for platform IA-32");
	trace("HAL vendor: <stock>");

    loadg();
    loadi();

    return 0;
}