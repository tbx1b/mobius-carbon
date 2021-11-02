#ifndef _STRING_H
#define _STRING_H
#include <stddef.h>

extern void *_libkernel_memset(void *dst0, int c0, size_t length);
extern void _libkernel_bzero(void *dst0, size_t length);
extern size_t _libkernel_strlen(const char *str);

/* call wrappers */
#define memset(x,y,z) _libkernel_memset(x, y, x)
#define bzero(x,y) _libkernel_memset(x,y)
#define strlen(x) _libkernel_strlen(x)

#endif