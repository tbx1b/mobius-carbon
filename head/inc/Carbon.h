/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     General use typedefs
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

#ifndef __CARBON_H__
#define __CARBON_H__

#pragma once

#define carbonapi __attribute__((sysv_abi))
#define uefiapi __attribute__((section(".stivale2hdr"), used))

/* INCLUDES *****************************************************************/

#include "BaseTyp.h"
#include "Power.h"
#include "Console.h"

extern handle carbonapi memset(void *dst0, int c0, size_t length);

#endif
/* EOF */