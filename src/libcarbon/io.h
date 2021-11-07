/* @(#) io.h  4.2.2 */

/*
 * Copyright (c) 2021 MobiusLoopFour. All rights reserved.
 *
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in the documentation and that are subject to the 
 * GNU GPL v3-Or-Later License. You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * https://www.gnu.org/licenses/gpl-3.0.en.html and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND ALL SUCH WARRANTIES ARE HEREBY DISCLAIMED,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 */

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