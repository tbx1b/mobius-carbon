/* @(#) stdint.h */

#if !defined(_string_h)
#define _string_h

#include <libcarbon/core.h>
#include <libc/stddef.h>

void * MLTX_API
_libkernel_memset(void *dst0, int c0, size_t length);
#define memset _libkernel_memset

#endif