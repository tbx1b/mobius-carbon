/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Pause the CPU
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

#ifndef __CONSOLE_H_
#define __CONSOLE_H_

#pragma once

/* INCLUDES *****************************************************************/

#include <Carbon.h>

/* GLOBALS ******************************************************************/

carbonapi puts_init(handle _Nonnull stivale2_struct);
carbonapi any puts(const cchar * _Nullable format, ...);

#endif /* __CONSOLE_H_ */
/* EOF*/