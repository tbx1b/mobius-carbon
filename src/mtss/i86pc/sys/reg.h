/* @(#) reg.h - IA-32 register struct */

#if !defined(_reg_h)
#define _reg_h

#include <std/stdint.h>

typedef struct
{
    u32 ds;                                           /* Data segment selector */
    u32 edi, esi, ebp, _reserved, ebx, edx, ecx, eax; /* Pushed by pusha. */
    u32 ino, errno;                                   /* Interrupt number and error code (if applicable) */
    u32 eip, cs, eflags, esp, ss;                     /* Pushed by the processor automatically */
} Register;

#endif