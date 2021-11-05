/* @(#) io.h  4.2.2 */

#if !defined(_io_h)
#define _io_h

#include <libcarbon/core.h>
/* @(#) io.h */

#include <libc/stdint.h>
#include "printf.h"

/** outb:
 *  @param port port to send to
 *  @param data data
 */
void MLTX_API _io_outb(uint16_t port, uint16_t data);
#define outb _io_outb

/** outb:
 *  @param port port to read from
 *  @return received data
 */
unsigned char MLTX_API _io_inb(uint16_t port);
#define inb _io_inb

void MLTX_API
_trace_trace(
    char fmt[]);
#define trace _trace_trace

#endif /* _io_h */