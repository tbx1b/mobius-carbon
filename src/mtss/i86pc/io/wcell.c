/* @(#) wcell.c - 4.2.1 */

#include "cell.h"
#include <core.h>
#include <sys/io.h>
#include <std/stdint.h>

static i8 *fb = (i8 *)0x000B8000;

MTSS_API void
_io_write_cell(
    u32 i,
    i8 c,
    u8 fg,
    u8 bg)
{
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}