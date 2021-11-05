/* @(#) stdint.h */

#if !defined(_string_h)
#define _string_h

#include <core.h>
#include <std/stddef.h>

void * MTSS_API
_libkernel_memset(void *dst0, int c0, Int length);
#define memset _libkernel_memset

#endif