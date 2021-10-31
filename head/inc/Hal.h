/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     HAL interface
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

#pragma once

/* INCLUDES *****************************************************************/

#include <Carbon.h>

/* GLOBALS ******************************************************************/

#define halapi carbonapi
#define raw __attribute__((packed))
#define call(x) HalOnCall((HalCall)x)

typedef enum {

    Main,
    Custom_Init,        /* Hardware specific setup */

    #pragma mark x86

    Ld_Idt,
    Ld_Gdt,
    Ld_Pag,

    #pragma mark End

} HalCall;

extern halapi HalOnCall(HalCall call);

#define HAL_ERR_UNIMPLEMENTED -1
/* EOF */