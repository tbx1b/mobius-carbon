/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Pause the CPU
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

/* INCLUDES *****************************************************************/

#include <Carbon.h>
#include <Hal.h>

halapi 
HalOnCall(HalCall call)
{
    switch (call) {
        case Main: {
            return HAL_ERR_UNIMPLEMENTED;
        }
        default: {
            return HAL_ERR_UNIMPLEMENTED;
        }
    }
}
/* EOF */