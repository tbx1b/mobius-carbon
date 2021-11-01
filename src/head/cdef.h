#ifndef CarbonDef_h_
#define CarbonDef_h_

/* general use */
typedef unsigned int    uint32;
typedef          int    int32;
typedef unsigned short  uint16;
typedef          short  int16;
typedef unsigned char   uint8;
typedef          char   int8;

/* hw */
typedef uint32          dword;
typedef uint16          word;
typedef uint8           byte;

/* sizeof */
typedef uint32          size_t;

/* pointers */
typedef uint32          uint_ptr;
typedef int32           int_ptr;
typedef uint_ptr        lparam;
typedef int_ptr         wparam;
typedef void *          handle;
typedef handle          pvoid;
typedef int_ptr         ptr_diff;

/* bool */

typedef int32           bool32;
typedef int16           bool16;
typedef int8            bool8;
typedef bool8           bool;

typedef enum  {
    FALSE = 0,
    TRUE = !FALSE
} boolean;

#define YES TRUE
#define NO FALSE

#define NULL ((void*)0)

typedef __builtin_va_list va_list;

#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST
#endif
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap)          __builtin_va_end(ap)
#define va_arg(ap, type)    __builtin_va_arg(ap, type)

/* GCC always defines __va_copy, but does not define va_copy unless in c99 mode
 * or -ansi is not specified, since it was not part of C90.
 */
#define __va_copy(d,s) __builtin_va_copy(d,s)

#if __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L || !defined(__STRICT_ANSI__)
#define va_copy(dest, src)  __builtin_va_copy(dest, src)
#endif

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST 1
typedef __builtin_va_list __gnuc_va_list;
#endif


#endif /* CarbonDef_h_ */
/* EOF */