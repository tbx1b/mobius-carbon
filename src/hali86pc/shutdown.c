/* @(#) shutdown.c - hal shutdown */

#include <libcarbon/core.h>
#include <libcarbon/hal.h>

#include <libc/stdint.h>

#include <libcarbon/core.h>
#include <libcarbon/io.h>
#include <libcarbon/vm.h>
#include <libcarbon/assert.h>
#include <libcarbon/hal.h>

MLTX_API _hal_shutdown(void) {

	trace("HAL shutting down...");

	__asm__ volatile("cli");
	return 0;
}