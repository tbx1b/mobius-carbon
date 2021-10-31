/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Main realtime kernel
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

/* INCLUDES *****************************************************************/

#include <Carbon.h>
#include "stivale2.h"

/* CARBON_MAIN ***************************************************************/

carbonapi
main(struct stivale2_struct * _Nonnull  stivale2_struct)
{
    puts_init(stivale2_struct);
    puts("Lol\n");

    return 0;
}
/* EOF*/