/*===---- asm.h - Standard-width integer types -----------------------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */


#ifndef __MACHINE_INT_TYPES_H_
#define __MACHINE_INT_TYPES_H_

typedef unsigned int uint;

#define INT_FAST_DEFINED

typedef signed char int_fast8_t;
typedef short int_fast16_t;
typedef long int_fast32_t;
typedef long long int_fast64_t;

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short int __int16_t;
typedef unsigned short int __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
#ifdef __COMPILER_INT64__
typedef __COMPILER_INT64__ __int64_t;
typedef __COMPILER_UINT64__ __uint64_t;
#else
/* LONGLONG */
typedef long long int __int64_t;
/* LONGLONG */
typedef unsigned long long int __uint64_t;
#endif

typedef unsigned long long __uintmax_t;

#if !defined(__kernel__)
#   define __BIT_TYPES_DEFINED__
#endif /* !defined(__kernel__) */

#ifdef __lint__
    typedef char *__va_list;
#else 
    typedef __builtin_va_list __va_list;
#endif

/* 7.18.1.4 Integer types capable of holding object pointers */

typedef int __intptr_t;
typedef unsigned int __uintptr_t;
#endif /*__MACHINE_INT_TYPES_H_ */
