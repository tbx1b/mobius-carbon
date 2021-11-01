/*
 * MODULE:          Input/Output
 * LICENSE:         GPL-3.0-or-later
 * PURPOSE:         Read/write to ports
 * COPYRIGHT:       Copyright MobiusLoopFour
 */

/* INCLUDES *******************************************************************/

#ifndef io_h_
#define io_h_

#include <Carbon.h>

/* GLOBAL FUNCTIONS ***********************************************************/

void    hal_io_outb(word port, byte value);
byte    hal_io_inb(word port);
byte    hal_io_inw(word port);

#endif /*! io_h */
/* EOF */