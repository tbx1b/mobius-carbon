/*
 * MODULE:          Input/Output
 * LICENSE:         GPL-3.0-or-later
 * PURPOSE:         Read/write to ports
 * COPYRIGHT:       Copyright MobiusLoopFour
 */

/* INCLUDES *******************************************************************/

#ifndef io_h_
#define io_h_

#include <cdef.h>

/* GLOBAL FUNCTIONS ***********************************************************/

void    outb(word port, byte value);
byte    inb(word port);
byte    inw(word port);

#endif /*! io_h */
/* EOF */