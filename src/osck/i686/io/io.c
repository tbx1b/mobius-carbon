/*
 * MODULE:          Input/Output
 * LICENSE:         GPL-3.0-or-later
 * PURPOSE:         Read/write bytes
 * COPYRIGHT:       Copyright MobiusLoopFour
 */

/* INCLUDES *******************************************************************/

#include <cdef.h>

/* GLOBAL FUNCTIONS ***********************************************************/

// Write a byte out to the specified port.
void outb(word port, byte value)
{
    __asm__ volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

byte inb(word port)
{
   byte ret;
   __asm__ volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

word inw(word port)
{
   word ret;
   __asm__ volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}
/* EOF */