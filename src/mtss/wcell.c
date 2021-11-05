/* @(#) wcell.c - 4.2.1 */

#include <libcarbon/cell.h>
#include <libcarbon/core.h>
#include <libcarbon/io.h>

#include <libc/stdint.h>

static int8_t *fb = (int8_t *)0x000B8000;

void MLTX_API
_io_write_cell(
    uint32_t i,
    int8_t c,
    uint8_t fg,
    uint8_t bg)
{
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}