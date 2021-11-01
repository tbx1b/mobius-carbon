/*
 * MODULE:          Input/Output
 * LICENSE:         GPL-3.0-or-later
 * PURPOSE:         Read/write bytes
 * COPYRIGHT:       Copyright MobiusLoopFour
 */

/* INCLUDES *******************************************************************/

#include <carbon.h>

/* GLOBAL FUNCTIONS ***********************************************************/

// Write a byte out to the specified port.
void hal_io_outb(word port, byte value)
{
    __asm__ volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

byte hal_io_inb(word port)
{
   byte ret;
   __asm__ volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

word hal_io_inw(word port)
{
   word ret;
   __asm__ volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}
/* EOF */