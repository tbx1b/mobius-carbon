/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Pause the CPU
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

/* INCLUDES *****************************************************************/

#include <Carbon.h>

#define	wsize	sizeof(unsigned int)
#define	wmask	(wsize - 1)

// n.b. this must be compiled with -fno-builtin or it might get optimized into
// a recursive call to bzero.
fileprivate carbonapi void
bzero(void *dst0, size_t length)
{
    return (void)memset(dst0, 0, length);
}

#define	RETURN	return (dst0)
#define	VAL	c0
#define	WIDEVAL	c

/* GLOBALS *****************************************************************/

handle carbonapi
memset(void *dst0, int c0, size_t length)
{
	size_t t;
	unsigned int c;
	unsigned char *dst;

	dst = dst0;
	/*
	 * If not enough words, just fill bytes.  A length >= 2 words
	 * guarantees that at least one of them is `complete' after
	 * any necessary alignment.  For instance:
	 *
	 *	|-----------|-----------|-----------|
	 *	|00|01|02|03|04|05|06|07|08|09|0A|00|
	 *	          ^---------------------^
	 *		 dst		 dst+length-1
	 *
	 * but we use a minimum of 3 here since the overhead of the code
	 * to do word writes is substantial.
	 */
	if (length < 3 * wsize) {
		while (length != 0) {
			*dst++ = VAL;
			--length;
		}
		RETURN;
	}

	if ((c = (unsigned char)c0) != 0) {	/* Fill the word. */
		c = (c << 32) | c;	/* u_int is 64 bits. */
	}
	/* Align destination by filling in bytes. */
	if ((t = (long)dst & wmask) != 0) {
		t = wsize - t;
		length -= t;
		do {
			*dst++ = VAL;
		} while (--t != 0);
	}

	/* Fill words.  Length was >= 2*words so we know t >= 1 here. */
	t = length / wsize;
	do {
		*(unsigned int *)dst = WIDEVAL;
		dst += wsize;
	} while (--t != 0);

	/* Mop up trailing bytes, if any. */
	t = length & wmask;
	if (t != 0)
		do {
			*dst++ = VAL;
		} while (--t != 0);
	RETURN;
}
/* EOF */