#include <stdint.h>
#include <stddef.h>

#include <libc/string.h>

#include <cpu.h>
#include <debug/trace.h>
#include <stand/stivale2.h>
#include <io/io.h>
 
static uint8_t stack[8192];

static struct stivale2_header_tag_terminal terminal_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = 0
    },
    .flags = 0
};
 
static struct stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (uint64_t)&terminal_hdr_tag
    },
    .framebuffer_width  = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp    = 0
};
 
__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header stivale_hdr = {
    .entry_point = 0,
    .stack = (uintptr_t)stack + sizeof(stack),
    .flags = (1 << 1) | (1 << 2) | (1 << 4),
    .tags = (uintptr_t)&framebuffer_hdr_tag
};

void (*termio)(char *str, size_t len);

void _start(struct stivale2_struct *env) 
{
    extern void halt();

    static void (*termout)(char *str, size_t len);

    struct stivale2_struct_tag_terminal *term_str_tag;
    term_str_tag = stivale2_get_tag(env, STIVALE2_STRUCT_TAG_TERMINAL_ID);

    if (term_str_tag == 0)
    {
        for (;;)
        {
            halt();
        }
    }
    void *term_write_ptr = (void *)term_str_tag->term_write;
    termio = term_write_ptr;
    termio("Done\n", strlen("Done\n"));

    //announce();

    _io_printf("Test\n");

    while(1) {}
}