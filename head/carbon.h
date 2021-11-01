#ifndef carbon_h_
#define carbon_h_

#include "sys.h"
#include "stdio.h"
#include "hal.h"

#define _cdecl __attribute__((__cdecl__))
size_t strlen(const char *str);
void *memset(void *dst0, int c0, size_t length);

#endif /* string_h_ */