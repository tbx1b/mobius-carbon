/* @(#) stdarg.h */

#ifndef _stardg_h
#define _stardg_h

#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST
#endif
#define initVaList(ap, param) __builtin_va_start(ap, param)
#define releaseVaList(ap)          __builtin_va_end(ap)
#define vaList(ap, type)    __builtin_va_arg(ap, type)

/* GCC */
#define __va_copy(d,s) __builtin_va_copy(d,s)

#if __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L || !defined(__STRICT_ANSI__)
#define vaListCopy(dest, src)  __builtin_va_copy(dest, src)
#endif

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST 1
typedef __builtin_va_list __gnuc_va_list;
#endif

#endif /* _stardg_h */