/* @(#) _width.h - standard-width integer types for i386 */

#ifndef _SYS__STDINT_H_
#define _SYS__STDINT_H_

#include "_types.h"

#ifndef _INT8_T_DECLARED
typedef __int8_t i8;
#define _INT8_T_DECLARED
#endif

#ifndef _INT16_T_DECLARED
typedef __int16_t i16;
#define _INT16_T_DECLARED
#endif

#ifndef _INT32_T_DECLARED
typedef __int32_t i32;
#define _INT32_T_DECLARED
#endif

#ifndef _INT64_T_DECLARED
typedef __int64_t i64;
#define _INT64_T_DECLARED
#endif

#ifndef _UINT8_T_DECLARED
typedef __uint8_t u8;
#define _UINT8_T_DECLARED
#endif

#ifndef _UINT16_T_DECLARED
typedef __uint16_t u16;
#define _UINT16_T_DECLARED
#endif

#ifndef _UINT32_T_DECLARED
typedef __uint32_t u32;
#define _UINT32_T_DECLARED
#endif

#ifndef _UINT64_T_DECLARED
typedef __uint64_t u64;
#define _UINT64_T_DECLARED
#endif

#ifndef _INTPTR_T_DECLARED
typedef __intptr_t iptr;
#define _INTPTR_T_DECLARED
#endif
#ifndef _UINTPTR_T_DECLARED
typedef __uintptr_t uptr;
#define _UINTPTR_T_DECLARED
#endif
#ifndef _INTMAX_T_DECLARED
typedef __intmax_t imax;
#define _INTMAX_T_DECLARED
#endif
#ifndef _UINTMAX_T_DECLARED
typedef __uintmax_t umax;
#define _UINTMAX_T_DECLARED
#endif

#endif /* !_SYS__STDINT_H_ */