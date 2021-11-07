/* @(#) serial.h */

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

#if !defined(_serial_h)
#define _serial_h

#include <libcarbon/core.h>

MLTX_API _sp_fifo_ready(unsigned c);
#define fifo_ready _sp_fifo_ready

void MLTX_API
_sp_cfbaud_rate(
    unsigned short com,
    unsigned short divisor);
#define cfbaud_rate _sp_cfbaud_rate

void MLTX_API
_sp_cfln(
    unsigned short c);
#define cfln _sp_cfln

#endif