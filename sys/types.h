/*===----- types.h - Standard header For sized integer types --------------===*\
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
\*===----------------------------------------------------------------------===*/

#ifndef __CARBON_TYPES_H_
#define __CARBON_TYPES_H_

#include <machine/int_types.h>

typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;

typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;

typedef __int8_t uint_least8_t;
typedef __int16_t uint_least16_t;
typedef __int32_t uint_least32_t;
typedef __int64_t uint_least64_t;

typedef __uintmax_t intmax_t;
typedef __intptr_t intptr_t;
typedef __uintptr_t uintptr_t;

#define INT8_MIN (-0x7F - 1)
#define INT16_MIN (-0x7FFF - 1)
#define INT32_MIN (-0x7FFFFFFF - 1)
#define INT64_MIN (-0x7FFFFFFFFFFFFFFF - 1)

#define INT_LEAST8_MIN (-0x7F - 1)
#define INT_LEAST16_MIN (-0x7FFF - 1)
#define INT_LEAST32_MIN (-0x7FFFFFFF - 1)
#define INT_LEAST64_MIN (-0x7FFFFFFFFFFFFFFF - 1)

#define UINT8_MAX 0xFF
#define UINT16_MAX 0xFFFF
#define UINT32_MAX 0xFFFFFFFF
#define UINT64_MAX 0xFFFFFFFFFFFFFFFF

#define INT_LEAST8_MAX 0x7F
#define INT_LEAST16_MAX 0x7FFF
#define INT_LEAST32_MAX 0x7FFFFFFF
#define INT_LEAST64_MAX 0x7FFFFFFFFFFFFFFF

#define UINT_LEAST8_MAX 0xFF
#define UINT_LEAST16_MAX 0xFFFF
#define UINT_LEAST32_MAX 0xFFFFFFFF
#define UINT_LEAST64_MAX 0xFFFFFFFFFFFFFFFF

#define INT_FAST8_MIN (-0x7F - 1)
#define INT_FAST16_MIN (-0x7FFF - 1)
#define INT_FAST32_MIN (-0x7FFFFFFF - 1)
#define INT_FAST64_MIN (-0x7FFFFFFFFFFFFFFF - 1)

#define INT_FAST8_MAX 0x7F
#define INT_FAST16_MAX 0x7FFF
#define INT_FAST32_MAX 0x7FFFFFFF
#define INT_FAST64_MAX 0x7FFFFFFFFFFFFFFF

#define UINT_FAST8_MAX 0xFF
#define UINT_FAST16_MAX 0xFFFF
#define UINT_FAST32_MAX 0xFFFFFFFF
#define UINT_FAST64_MAX 0xFFFFFFFFFFFFFFFF

#define INTPTR_MIN (-0x7FFFFFFF - 1)
#define INTPTR_MAX 0x7FFFFFFF
#define UINTPTR_MAX 0xFFFFFFFF

#define INT8_C(x) (x)
#define INT16_C(x) (x)
#define INT32_C(x) ((x) + (INT32_MAX - INT32_MAX))
#define INT64_C(x) ((x) + (INT64_MAX - INT64_MAX))

#define UINT8_C(x) (x)
#define UINT16_C(x) (x)
#define UINT32_C(x) ((x) + (UINT32_MAX - UINT32_MAX))
#define UINT64_C(x) ((x) + (UINT64_MAX - UINT64_MAX))

#define INTMAX_C(x) ((x) + (INT64_MAX - INT64_MAX))
#define UINTMAX_C(x) ((x) + (UINT64_MAX - UINT64_MAX))

#define PTRDIFF_MIN INT32_MIN
#define PTRDIFF_MAX INT32_MAX

#define SIG_ATOMIC_MIN INT32_MIN
#define SIG_ATOMIC_MAX INT32_MAX

#define SIZE_MAX UINT32_MAX

#define WCHAR_MIN 0
#define WCHAR_MAX UINT16_MAX

#define WINT_MIN 0
#define WINT_MAX UINT16_MAX

#define INTMAX_MIN (-0x7fffffffffffffff - 1)
#define INTMAX_MAX 0x7fffffffffffffff
#define UINTMAX_MAX 0xffffffffffffffff

// Boolean type

typedef _Bool boolean_t;
#ifndef FALSE
#   define FALSE 0
#endif
#ifndef TRUE
#   define TRUE 1
#endif

// VA_LIST

typedef __va_list va_list;

#endif /* __CARBON_TYPES_H_ */
