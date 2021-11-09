/*===---- stdarg.h - Standard arguments interface --------------------------===
 *
 * Part of the Carbon libc subset, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#ifndef __LIBC_STDARG_H
#define __LIBC_STDARG_H

#ifdef __kernel__

#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST
#endif

#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) __builtin_va_arg(ap, type)

#define __va_copy(d, s) __builtin_va_copy(d, s)

#if __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L ||                   \
    !defined(__STRICT_ANSI__)
#define va_copy(dest, src) __builtin_va_copy(dest, src)
#endif

#ifndef __GNUC_VA_LIST
// clang
#define __GNUC_VA_LIST 1
typedef __builtin_va_list __gnuc_va_list;
#endif

#else
// Don't use the internal kernel header
#include_next <stdarg.h>
#endif

#endif // __LIBC_STDARG_H
       // eof