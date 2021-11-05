/* @(#) reg.h - IA-32 register struct */

#if !defined(_reg_h)
#define _reg_h

#include <libc/stdint.h>

typedef struct
{
    uint32_t ds;                                           /* Data segment selector */
    uint32_t edi, esi, ebp, _reserved, ebx, edx, ecx, eax; /* Pushed by pusha. */
    uint32_t ino, errno;                                   /* Interrupt number and error code (if applicable) */
    uint32_t eip, cs, eflags, esp, ss;                     /* Pushed by the processor automatically */
} register_t;

#endif