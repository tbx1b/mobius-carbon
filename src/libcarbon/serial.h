/* @(#) serial.h */

#if !defined(_serial_h)
#define _serial_h

#include <libcarbon/core.h>

MLTX_API _sp_fifo_ready(unsigned c);
#define fifo_ready _sp_fifo_ready

void MLTX_API
_sp_cfbaud_rate(
    unsigned short com,
    unsigned short divisor);
#define cfbaud_rate _sp_cfbaud_rate

void MLTX_API
_sp_cfln(
    unsigned short c);
#define cfln _sp_cfln

#endif