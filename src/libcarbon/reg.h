/* @(#) reg.h - IA-32 register struct */

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