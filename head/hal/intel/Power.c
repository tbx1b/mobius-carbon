/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Pause the CPU
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

#include "HalPower.h"
#include <Carbon.h>

carbonapi _Noreturn any halhalt()
{
    for (;;) {
        __asm__("hlt");
    }
}
/* EOF */