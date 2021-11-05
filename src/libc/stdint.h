/* @(#) stdint.h */

#if !defined(_std_stdint_h)
#define _std_stdint_h

#include "_types.h"
#include "_width.h"

typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;

typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;

typedef __int_fast8_t int_fast8_t;
typedef __int_fast16_t int_fast16_t;
typedef __int_fast32_t int_fast32_t;
typedef __int_fast64_t int_fast64_t;

typedef __uint_fast8_t uint_fast8_t;
typedef __uint_fast16_t uint_fast16_t;
typedef __uint_fast32_t uint_fast32_t;
typedef __uint_fast64_t uint_fast64_t;

#if defined(UINTPTR_MAX) && defined(UINT64_MAX) && (UINTPTR_MAX == UINT64_MAX)
#define __WORDSIZE 64
#else
#define __WORDSIZE 32
#endif

#define WCHAR_MIN __WCHAR_MIN
#define WCHAR_MAX __WCHAR_MAX

#if __EXT1_VISIBLE
/* ISO/IEC 9899:2011 K.3.4.4 */
#ifndef RSIZE_MAX
#define RSIZE_MAX (SIZE_MAX >> 1)
#endif
#endif /* __EXT1_VISIBLE */

#endif /* !_std_stdint_h */