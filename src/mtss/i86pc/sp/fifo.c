/* @(#) fifo.c */

#include <sys/io.h>
#include <std/stdint.h>
#include "_sp.h"

/*!
 * Check a com port
 * @param com The com port
 * @return 1 if ready
 */
_sp_fifo_ready(
    u32 c)
{
    return inb(SERIAL_LINE_STATUS_PORT(c)) & 0x20;
}