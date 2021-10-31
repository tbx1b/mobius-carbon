/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Pause the CPU
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

#ifndef __HAL_POWER_H__
#define __HAL_POWER_H__

/* INCLUDES *****************************************************************/

#include <Hal.h>

/* GLOBALS ******************************************************************/

halapi _Noreturn any halhalt(void);

#endif /* __HAL_POWER_H__ */
/* EOF */ 