/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Debug using print
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

/* INCLUDES *****************************************************************/

#include <Carbon.h>
#include "stivale2.h"
#include <stdarg.h>

/* FILEPRIVATE ***************************************************************/

fileprivate any (*term_write)(const cchar *string, size_t length);
fileprivate bool32 _initialized;

extern handle g_stivale2_struct;

/* STRLEN ********************************************************************/

/* Magic numbers for the algorithm */

fileprivate const unsigned long mask01 = 0x0101010101010101;
fileprivate const unsigned long mask80 = 0x8080808080808080;


#define	LONGPTR_MASK (sizeof(long) - 1)

/*
 * Helper macro to return string length if we caught the zero
 * byte.
 */
#define testbyte(x)				\
	do {					\
		if (p[x] == '\0')		\
		    return (p - str + x);	\
	} while (0)

carbonapi fileprivate size_t
strlen(const char * _Nullable str)
{
	const char *p;
	const unsigned long *lp;

	/* Skip the first few bytes until we have an aligned p */
	for (p = str; (long_ptr)p & LONGPTR_MASK; p++)
	    if (*p == '\0')
		return (p - str);

	/* Scan the rest of the string using word sized operation */
	for (lp = (const unsigned long *)p; ; lp++)
	    if ((*lp - mask01) & mask80) {
            p = (const char *)(lp);
            testbyte(0);
            testbyte(1);
            testbyte(2);
            testbyte(3);

            testbyte(4);
            testbyte(5);
            testbyte(6);
            testbyte(7);
	    }

	/* NOTREACHED */
	return (0);
}

#undef testbyte//(x)

/* GLOBALS *****************************************************************/

carbonapi
puts_init(handle _Nonnull stivale2_struct)
{
    if (_initialized) {
        return _initialized;
    }

    struct stivale2_struct_tag_terminal *term_str_tag;
    term_str_tag = (struct stivale2_struct_tag_terminal *) stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);
    if (term_str_tag == NULL) {
        _initialized = 0;
        goto puts_init_end;
    }

    void *term_write_ptr = (void *)term_str_tag->term_write;
    term_write = term_write_ptr;
    _initialized = 1;

    puts_init_end:
        return _initialized;
}

carbonapi any 
puts(const cchar * _Nullable format, ...)
{
    while (!_initialized) {
        continue;
    }
    if (*format == '\0') {
        return;
    }
    term_write(format, strlen(format));
}
/* EOF */