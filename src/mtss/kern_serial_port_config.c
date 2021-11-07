/* @(#) spcf.c  4.3.2 */

/*
 * Configure the serial port
 */

#include <libcarbon/io.h>
#include <libcarbon/core.h>
#include <libc/stdint.h>

#define SERIAL_COM1_BASE 0x3F8 /* COM1 base port */

#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)
#define SERIAL_LINE_ENABLE_DLAB 0x80

/*!
 * Configure a serial port
 * @param com The com port to configure
 */
void MLTX_API
_sp_cfbaud_rate(
    uint16_t com,
    uint16_t divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com),
         SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com),
         (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com),
         divisor & 0x00FF);
}

/*!
 * Configure a serial port line
 * @param com The com port to configure
 */
void MLTX_API
_sp_cfln(
    uint16_t c)
{
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    outb(SERIAL_LINE_COMMAND_PORT(c), 0x03);
}