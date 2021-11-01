/*
 * MODULE:          Input/Output
 * LICENSE:         GPL-3.0-or-later
 * PURPOSE:         Print strings
 * COPYRIGHT:       Copyright MobiusLoopFour
 */

/* INCLUDES *******************************************************************/

#include <cdef.h>
#include <string.h>
#include "tty.h"

/* PRIVATE FUNCTIONS **********************************************************/

#define isdigit(d) ((d) >= '0' && (d) <= '9')
#define Ctod(c) ((c) - '0')

#define MAXBUF (sizeof(int) * 8)
static char digs[] = "0123456789abcdef";



static int
printnum(
	unsigned int  	u,      /* number to print */
	int             base,
	void                    (*putc)(int, void *),
	void                    *arg)
{
	char    buf[MAXBUF];    /* build number here */
	char *  p = &buf[MAXBUF - 1];
	int nprinted = 0;

	do {
		*p-- = digs[u % base];
		u /= base;
	} while (u != 0);

	while (++p != &buf[MAXBUF]) {
		(*putc)(*p, arg);
		nprinted++;
	}

	return nprinted;
}

boolean       _doprnt_truncates = FALSE;

static void putc(int c, void * arg)
{
	tty_put((char)c);
}

static int
__doprnt(
	const char      *fmt,
	va_list                 argp,
	/* character output routine */
	void                    *arg,
	int                     radix          /* default radix - for '%r' */)
{
	int             length;
	int             prec;
	boolean       ladjust;
	char            padc;
	int               n;
	unsigned int      u;
	int             plus_sign;
	int             sign_char;
	boolean       altfmt, truncate;
	int             base;
	char    c;
	int             capitals;
	int             long_long;
	enum {
		INT,
		SHORT,
		CHAR,
	} numeric_type = INT;
	int             nprinted = 0;

	if (radix < 2 || radix > 36) {
		radix = 10;
	}

	while ((c = *fmt) != '\0') {
		if (c != '%') {
			(*putc)(c, arg);
			nprinted++;
			fmt++;
			continue;
		}

		fmt++;

		long_long = 0;
		numeric_type = INT;
		length = 0;
		prec = -1;
		ladjust = FALSE;
		padc = ' ';
		plus_sign = 0;
		sign_char = 0;
		altfmt = FALSE;

		while (TRUE) {
			c = *fmt;
			if (c == '#') {
				altfmt = TRUE;
			} else if (c == '-') {
				ladjust = TRUE;
			} else if (c == '+') {
				plus_sign = '+';
			} else if (c == ' ') {
				if (plus_sign == 0) {
					plus_sign = ' ';
				}
			} else {
				break;
			}
			fmt++;
		}

		if (c == '0') {
			padc = '0';
			c = *++fmt;
		}

		if (isdigit(c)) {
			while (isdigit(c)) {
				length = 10 * length + Ctod(c);
				c = *++fmt;
			}
		} else if (c == '*') {
			length = va_arg(argp, int);
			c = *++fmt;
			if (length < 0) {
				ladjust = !ladjust;
				length = -length;
			}
		}

		if (c == '.') {
			c = *++fmt;
			if (isdigit(c)) {
				prec = 0;
				while (isdigit(c)) {
					prec = 10 * prec + Ctod(c);
					c = *++fmt;
				}
			} else if (c == '*') {
				prec = va_arg(argp, int);
				c = *++fmt;
			}
		}

		if (c == 'l') {
			c = *++fmt; /* need it if sizeof(int) < sizeof(long) */
			if (sizeof(int) < sizeof(long)) {
				long_long = 1;
			}
			if (c == 'l') {
				long_long = 1;
				c = *++fmt;
			}
		} else if (c == 'h') {
			c = *++fmt;
			numeric_type = SHORT;
			if (c == 'h') {
				numeric_type = CHAR;
				c = *++fmt;
			}
		} else if (c == 'q' || c == 'L') {
			long_long = 1;
			c = *++fmt;
		}

		if (c == 'z' || c == 'Z') {
			c = *++fmt;
			if (sizeof(size_t) == sizeof(unsigned int)) {
				long_long = 1;
			}
		}

		truncate = FALSE;
		capitals = 0;   /* Assume lower case printing */

		switch (c) {
		case 'b':
		case 'B':
		{
			char *p;
			boolean     any;
			int  i;

			if (long_long) {
				u = va_arg(argp, unsigned int);
			} else {
				u = va_arg(argp, unsigned int);
			}
			p = va_arg(argp, char *);
			base = *p++;
			nprinted += printnum(u, base, putc, arg);

			if (u == 0) {
				break;
			}

			any = FALSE;
			while ((i = *p++) != '\0') {
				if (*fmt == 'B') {
					i = 33 - i;
				}
				if (*p <= 32) {
					/*
					 * Bit field
					 */
					int j;
					if (any) {
						(*putc)(',', arg);
					} else {
						(*putc)('<', arg);
						any = TRUE;
					}
					nprinted++;
					j = *p++;
					if (*fmt == 'B') {
						j = 32 - j;
					}
					for (; (c = *p) > 32; p++) {
						(*putc)(c, arg);
						nprinted++;
					}
					nprinted += printnum((unsigned)((u >> (j - 1)) & ((2 << (i - j)) - 1)),
					    base, putc, arg);
				} else if (u & (1 << (i - 1))) {
					if (any) {
						(*putc)(',', arg);
					} else {
						(*putc)('<', arg);
						any = TRUE;
					}
					nprinted++;
					for (; (c = *p) > 32; p++) {
						(*putc)(c, arg);
						nprinted++;
					}
				} else {
					for (; *p > 32; p++) {
						continue;
					}
				}
			}
			if (any) {
				(*putc)('>', arg);
				nprinted++;
			}
			break;
		}

		case 'c':
			c = (char)va_arg(argp, int);
			(*putc)(c, arg);
			nprinted++;
			break;

		case 's':
		{
			const char *p;
			const char *p2;

			if (prec == -1) {
				prec = 0x7fffffff; /* MAXINT */
			}
			p = va_arg(argp, char *);

			if (p == NULL) {
				p = "";
			}

			if (length > 0 && !ladjust) {
				n = 0;
				p2 = p;

				for (; *p != '\0' && n < prec; p++) {
					n++;
				}

				p = p2;

				while (n < length) {
					(*putc)(' ', arg);
					n++;
					nprinted++;
				}
			}

			n = 0;

			while ((n < prec) && (!(length > 0 && n >= length))) {
				if (*p == '\0') {
					break;
				}
				(*putc)(*p++, arg);
				nprinted++;
				n++;
			}

			if (n < length && ladjust) {
				while (n < length) {
					(*putc)(' ', arg);
					n++;
					nprinted++;
				}
			}

			break;
		}

		case 'o':
			truncate = _doprnt_truncates;
		case 'O':
			base = 8;
			goto print_unsigned;

		case 'D': {
			unsigned char *up;
			char *q, *p;

			up = (unsigned char *)va_arg(argp, unsigned char *);
			p = (char *)va_arg(argp, char *);
			if (length == -1) {
				length = 16;
			}
			while (length--) {
				(*putc)(digs[(*up >> 4)], arg);
				(*putc)(digs[(*up & 0x0f)], arg);
				nprinted += 2;
				up++;
				if (length) {
					for (q = p; *q; q++) {
						(*putc)(*q, arg);
						nprinted++;
					}
				}
			}
			break;
		}

		case 'd':
		case 'i':
			truncate = _doprnt_truncates;
			base = 10;
			goto print_signed;

		case 'u':
			truncate = _doprnt_truncates;
		case 'U':
			base = 10;
			goto print_unsigned;

		case 'p':
			altfmt = TRUE;
			if (sizeof(int) < sizeof(void *)) {
				long_long = 1;
			}
		case 'x':
			truncate = _doprnt_truncates;
			base = 16;
			goto print_unsigned;

		case 'X':
			base = 16;
			capitals = 16;  /* Print in upper case */
			goto print_unsigned;

		case 'r':
			truncate = _doprnt_truncates;
		case 'R':
			base = radix;
			goto print_signed;

		case 'n':
			truncate = _doprnt_truncates;
		case 'N':
			base = radix;
			goto print_unsigned;

print_signed:
			if (long_long) {
				n = va_arg(argp, int);
			} else {
				n = va_arg(argp, int);
			}
			switch (numeric_type) {
			case SHORT:
				n = (short)n;
				break;
			case CHAR:
				n = (char)n;
				break;
			default:
				break;
			}
			if (n >= 0) {
				u = n;
				sign_char = plus_sign;
			} else {
				u = -n;
				sign_char = '-';
			}
			goto print_num;

print_unsigned:
			if (long_long) {
				u = va_arg(argp, unsigned int);
			} else {
				u = va_arg(argp, unsigned int);
			}
			switch (numeric_type) {
			case SHORT:
				u = (unsigned short)u;
				break;
			case CHAR:
				u = (unsigned char)u;
				break;
			default:
				break;
			}
			goto print_num;

print_num:
			{
				char        buf[MAXBUF];/* build number here */
				char *      p = &buf[MAXBUF - 1];
				static char digits[] = "0123456789abcdef0123456789ABCDEF";
				const char *prefix = NULL;

				if (truncate) {
					u = (int)((int)(u));
				}

				do {
					/* Print in the correct case */
					*p-- = digits[(u % base) + capitals];
					u /= base;
				} while (u != 0);

				length -= (int)(&buf[MAXBUF - 1] - p);
				if (sign_char) {
					length--;
				}
				if (prefix) {
					length -= (int)strlen(prefix);
				}

				if (padc == ' ' && !ladjust) {
					/* blank padding goes before prefix */
					while (--length >= 0) {
						(*putc)(' ', arg);
						nprinted++;
					}
				}
				if (sign_char) {
					(*putc)(sign_char, arg);
					nprinted++;
				}
				if (prefix) {
					while (*prefix) {
						(*putc)(*prefix++, arg);
						nprinted++;
					}
				}
				if (padc == '0') {
					/* zero padding goes after sign and prefix */
					while (--length >= 0) {
						(*putc)('0', arg);
						nprinted++;
					}
				}
				while (++p != &buf[MAXBUF]) {
					(*putc)(*p, arg);
					nprinted++;
				}

				if (ladjust) {
					while (--length >= 0) {
						(*putc)(' ', arg);
						nprinted++;
					}
				}
				break;
			}

		case '\0':
			fmt--;
			break;

		default:
			(*putc)(c, arg);
			nprinted++;
		}
		fmt++;
	}

	return nprinted;
}

/* GLOBAL FUNCTIONS ***********************************************************/

int
printf(const char *fmt, ...)
{
	int ret;

	va_list ap;
	va_start(ap, fmt);
	ret = __doprnt(fmt, ap, NULL, 0);
	va_end(ap);

	return ret;
}
/* EOF */