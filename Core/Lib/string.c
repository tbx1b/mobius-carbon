#include <Carbon.h>
/* Magic numbers for the algorithm */
static const unsigned long mask01 = 0x01010101;
static const unsigned long mask80 = 0x80808080;


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

size_t
strlen(const char *str)
{
	const char *p;
	const unsigned long *lp;

	/* Skip the first few bytes until we have an aligned p */
	for (p = str; (uint_ptr)p & LONGPTR_MASK; p++)
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
	    }

	/* NOTREACHED */
	return (0);
}
