/* @(#) _limits.h */

#if !defined(_machine_limits_h)
#define _machine_limits_h

#define CHAR_BIT 8 /* number of bits in a char */

#define SCHAR_MAX 0x7f		  /* max value for a signed char */
#define SCHAR_MIN (-0x7f - 1) /* min value for a signed char */

#define UCHAR_MAX 0xff /* max value for an unsigned char */

#define USHRT_MAX 0xffff	   /* max value for an unsigned short */
#define SHRT_MAX 0x7fff		   /* max value for a short */
#define SHRT_MIN (-0x7fff - 1) /* min value for a short */

#define UINT_MAX 0xffffffff		  /* max value for an unsigned int */
#define INT_MAX 0x7fffffff		  /* max value for an int */
#define INT_MIN (-0x7fffffff - 1) /* min value for an int */

#ifdef LP64
#define ULONG_MAX 0xffffffffffffffff	   /* max for an unsigned long */
#define LONG_MAX 0x7fffffffffffffff		   /* max for a long */
#define LONG_MIN (-0x7fffffffffffffff - 1) /* min for a long */
#else
#define ULONG_MAX 0xffffffffUL
#define LONG_MAX 0x7fffffffL
#define LONG_MIN (-0x7fffffffL - 1)
#endif

/* max value for an unsigned long long */
#define ULLONG_MAX 0xffffffffffffffffULL
#define LLONG_MAX 0x7fffffffffffffffLL		  /* max value for a long long */
#define LLONG_MIN (-0x7fffffffffffffffLL - 1) /* min for a long long */

#ifdef LP64
#define SSIZE_MAX LONG_MAX	 /* max value for a ssize_t */
#define SIZE_T_MAX ULONG_MAX /* max value for a size_t */
#define OFF_MAX LONG_MAX	 /* max value for an off_t */
#define OFF_MIN LONG_MIN	 /* min value for an off_t */
/* Quads and longs are the same on the amd64.  Ensure they stay in sync. */
#define UQUAD_MAX ULONG_MAX /* max value for a uquad_t */
#define QUAD_MAX LONG_MAX	/* max value for a quad_t */
#define QUAD_MIN LONG_MIN	/* min value for a quad_t */
#define LONG_BIT 64
#else
#define SSIZE_MAX INT_MAX
#define SIZE_T_MAX UINT_MAX
#define OFF_MAX LLONG_MAX
#define OFF_MIN LLONG_MIN
#define UQUAD_MAX ULLONG_MAX
#define QUAD_MAX LLONG_MAX
#define QUAD_MIN LLONG_MIN
#define LONG_BIT 32
#endif

#define WORD_BIT 32

/* Minimum signal stack size. */
#define MINSIGSTKSZ (512 * 4)

#endif /* !_machine_limits_h */