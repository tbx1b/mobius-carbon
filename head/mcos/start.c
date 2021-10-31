/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Bootstrap
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

/* INCLUDES *****************************************************************/

#include "stivale2.h"
#include <Carbon.h>

/* FILEPRIVATE ***************************************************************/

fileprivate byte stack[8192];
 
fileprivate struct stivale2_header_tag_terminal terminal_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = 0
    },
    .flags = 0
};
 
fileprivate struct stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (long_ptr)&terminal_hdr_tag
    },
    .framebuffer_width  = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp    = 0
};
 
uefiapi fileprivate struct 
stivale2_header stivale_hdr = {
    .entry_point = 0,
    .stack = (long_ptr)stack + sizeof(stack),
    .flags = (1 << 1) | (1 << 2),
    .tags = (long_ptr)&framebuffer_hdr_tag
};
 

/* GLOBALS *******************************************************************/

extern carbonapi main(struct stivale2_struct * _Nonnull  stivale2_struct);

struct stivale2_struct *g_stivale2_struct;

any carbonapi
_start( struct stivale2_struct * _Nonnull stivale2_struct) 
{
    g_stivale2_struct = stivale2_struct;
    main(stivale2_struct);
    pause();
}
/* EOF */