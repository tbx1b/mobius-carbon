/* @(#) core.h */

#include <libc/stddef.h>
#include <libc/stdint.h>
#include <libc/limits.h>
#include <libcarbon/core.h>

#define wsize sizeof(uint32_t)
#define wmask (wsize - 1)

void *MLTX_API
_libkernel_memset(void *dst0, int c0, size_t length);

/* gcc */
inline void *MLTX_API
memset(void *dst0, int c0, size_t length)
{
	return _libkernel_memset(dst0, c0, length);
}

// n.b. this must be compiled with -fno-builtin or it might get optimized into
// a recursive call to bzero.
void MLTX_API
_libkernel_bzero(void *dst0, size_t length)
{
	return (void)_libkernel_memset(dst0, 0, length);
}

#define RETURN return (dst0)
#define VAL c0
#define WIDEVAL c

void *MLTX_API
_libkernel_memset(void *dst0, int c0, size_t length)
{
	size_t t;
	uint32_t c;
	uint8_t *dst;

	if (length < 3 * wsize)
	{
		while (length != 0)
		{
			*dst++ = VAL;
			--length;
		}
		RETURN;
	}

	if ((c = (uint8_t)c0) != 0)
	{					  /* Fill the word. */
		c = (c << 8) | c; /* u_int is 16 bits. */
#if __UINT_MAX > 0xffff
		c = (c << 16) | c; /* u_int is 32 bits. */
#endif
#if __UINT_MAX > 0xffffffff
		c = (c << 32) | c; /* u_int is 64 bits. */
#endif
	}
	/* Align destination by filling in bytes. */
	if ((t = (long)dst & wmask) != 0)
	{
		t = wsize - t;
		length -= t;
		do
		{
			*dst++ = VAL;
		} while (--t != 0);
	}

	/* Fill words.  Length was >= 2*words so we know t >= 1 here. */
	t = length / wsize;
	do
	{
		*(uint8_t *)dst = WIDEVAL;
		dst += wsize;
	} while (--t != 0);

	/* Mop up trailing bytes, if any. */
	t = length & wmask;
	if (t != 0)
	{
		do
		{
			*dst++ = VAL;
		} while (--t != 0);
	}
	RETURN;
}