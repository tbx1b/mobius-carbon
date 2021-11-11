#ifndef __LIBC_STRING_H_
#define __LIBC_STRING_H_

#include <stddef.h>

void * memset(void *b, int c, size_t len);
int memcmp(void *b1, void *b2, size_t len);
void * memmove(void * destination, const void * source, size_t num);

void bzero(void *s, size_t n);
int bcmp(void *b1, void *b2, size_t len);
void bcopy(const void *src, void *dest, size_t n);


#endif