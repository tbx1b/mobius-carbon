/* @(#) stddef.h */

#if !defined(_stddef_h) || defined(__need_ptrdiff_t) || \
    defined(__need_size_t) || defined(__need_wchar_t) || \
    defined(__need_NULL) || defined(__need_wint_t)

#if !defined(__need_ptrdiff_t) && !defined(__need_size_t) && \
    !defined(__need_wchar_t) && !defined(__need_NULL) &&     \
    !defined(__need_wint_t)
/* Always define miscellaneous pieces when modules are available. */
#define _stddef_h

#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || 1
/* Always define ptrdiff_t when modules are available. */
#if !1
#define _PTRDIFF_T
#endif
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */

#if defined(__need_size_t)
#if !defined(_SIZE_T) || 1
/* Always define size_t when modules are available. */
#if !1
#define _SIZE_T
#endif
typedef __SIZE_TYPE__ size_t;
#endif
#undef __need_size_t
#endif /*defined(__need_size_t) */

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) ||                                            \
    1
/* Always define rsize_t when modules are available. */
#if !1
#define _RSIZE_T
#endif
typedef __SIZE_TYPE__ rsize_t;
#endif
#endif /* defined(__need_STDDEF_H_misc) */

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || 1
#if !1
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
#endif
typedef __WCHAR_TYPE__ wchar_t;
#endif
#endif
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#if !defined(__MINGW32__) && !defined(_MSC_VER)
#define NULL __null
#else
#define NULL 0
#endif
#else
#define NULL ((void *)0)
#endif
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std
{
    typedef decltype(nullptr) nullptr_t;
}
using ::std::nullptr_t;
#endif
#endif
#undef __need_NULL
#endif /* defined(__need_NULL) */

#if defined(__need_STDDEF_H_misc)
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif /* defined(__need_STDDEF_H_misc) */

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || 1
#if !1
#define _WINT_T
#endif
typedef __WINT_TYPE__ wint_t;
#endif
#undef __need_wint_t
#endif /* __need_wint_t */

#endif
