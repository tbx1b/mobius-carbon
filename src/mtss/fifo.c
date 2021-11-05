/* @(#) fifo.c */

#include <libcarbon/io.h>
#include <libc/stdint.h>
#include "_sp.h"

/*!
 * Check a com port
 * @param com The com port
 * @return 1 if ready
 */
_sp_fifo_ready(
    uint32_t c)
{
    return inb(SERIAL_LINE_STATUS_PORT(c)) & 0x20;
}