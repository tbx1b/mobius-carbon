/* @(#) io.h  4.2.2 */

#if !defined(_io_h)
#define _io_h

#include <core.h>
/* @(#) io.h */

#include <std/stdint.h>
#include "printf.h"

/** outb:
 *  @param port port to send to
 *  @param data data
 */
MTSS_API void _io_outb(u16 port, u16 data);
#define outb _io_outb

/** outb:
 *  @param port port to read from
 *  @return received data
 */
unsigned char MTSS_API _io_inb(u16 port);
#define inb _io_inb

MTSS_API void
_trace_trace(
    char fmt[]);
#define trace _trace_trace

#endif /* _io_h */