/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Get any stivale 2 tag
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

/* INCLUDES *****************************************************************/

#include <Carbon.h>
#include "stivale2.h"

/* GLOBALS *****************************************************************/

carbonapi long_ptr 
stivale2_get_tag(struct stivale2_struct * _Nonnull stivale2_struct, dlongword id) 
{
    struct stivale2_tag *current_tag = (handle) stivale2_struct->tags;
    for (;;) {
        if (current_tag == 0) {
            return 0;
        }
        if (current_tag->identifier == id) {
            return (long_ptr)current_tag;
        }
        current_tag = (void *)current_tag->next;
    }
}
/* EOF*/