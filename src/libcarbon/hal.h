/* @(#) hal.h - hardware abstraction layer */

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

#include <libcarbon/core.h>

#if !defined(_hal_h)
#define _hal_h

#include "libcarbon/pic.h"
#include "libcarbon/io.h"
/* i86pc/sys */

extern MLTX_API _hal_init(void);
extern MLTX_API _hal_shutdown(void);

extern MLTX_API void _hal_enable(void);
extern MLTX_API void _hal_disable(void);

typedef void (*vect_t)(void);

extern MLTX_API void _hal_set_vect(uint32_t intno, vect_t vect);
extern MLTX_API vect_t _hal_get_vect(uint32_t intno);

extern MLTX_API _Bool _hal_interrupt_mask(uint8_t intno, _Bool enable);
extern MLTX_API void _hal_interrupt_done(uint32_t intno);

extern MLTX_API void _hal_sound(uint64_t frequency);

extern MLTX_API const char * const _hal_request_cpu_vendor(void);
extern MLTX_API uint32_t _hal_request_tick_count(void);

extern MLTX_API void _os_pic_init(uint8_t b00, uint8_t b01);
#define pic_init _os_pic_init

#endif