/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Pause the CPU
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

#ifndef __POWER_H__
#define __POWER_H__

#pragma once

/* INCLUDES *****************************************************************/

#include <HalPower.h>

/* GLOBALS ******************************************************************/

extern void halhalt();
#define pause(x) halhalt()

#endif /* __POWER_H__ */
/* EOF*/