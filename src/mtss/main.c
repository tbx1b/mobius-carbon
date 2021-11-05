/* @(#) main.c */

#include <libc/stdint.h>

#include <libcarbon/core.h>
#include <libcarbon/io.h>
#include <libcarbon/vm.h>
#include <libcarbon/assert.h>
#include <libcarbon/hal.h>


void MLTX_API
kernel_main(void)
{
    /* start up the HAL */
    assertNonzero(_hal_init());

#if 0
    __asm__("int $24"); // trigger ISR warning
#endif

    /* unexpected eof */
    assertNonzero(_hal_shutdown());

    return;
}