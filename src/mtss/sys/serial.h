/* @(#) serial.h */

#if !defined(_serial_h)
#define _serial_h

#include <core.h>

MTSS_API _sp_fifo_ready(unsigned c);
#define fifo_ready _sp_fifo_ready

MTSS_API void
_sp_cfbaud_rate(
    unsigned short com,
    unsigned short divisor);
#define configureBaudRate _sp_cfbaud_rate

MTSS_API void
_sp_cfln(
    unsigned short c);
#define configureLine _sp_cfln

#endif