/* @(#) _types.h - standard-width integer types for i386 */

#if !defined(_std_types_h)
#define _std_types_h

#include <std/limits.h>

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
#if __SIZEOF_LONG__ == 8
typedef long __int64_t;
typedef unsigned long __uint64_t;
#elif __SIZEOF_LONG__ == 4
__extension__ typedef long long __int64_t;
__extension__ typedef unsigned long long __uint64_t;
#else
#error unsupported long size
#endif

typedef __int8_t __int_least8_t;
typedef __int16_t __int_least16_t;
typedef __int32_t __int_least32_t;
typedef __int64_t __int_least64_t;
typedef __int64_t __intmax_t;
typedef __uint8_t __uint_least8_t;
typedef __uint16_t __uint_least16_t;
typedef __uint32_t __uint_least32_t;
typedef __uint64_t __uint_least64_t;
typedef __uint64_t __uintmax_t;

typedef __int32_t __intptr_t;
typedef __int32_t __intfptr_t;
typedef __uint32_t __uintptr_t;
typedef __uint32_t __uintfptr_t;
typedef __uint32_t __vm_offset_t;
typedef __uint32_t __vm_size_t;

#if __SIZEOF_SIZE_T__ == 8
typedef __uint64_t __size_t; /* sizeof() */
typedef __int64_t __ssize_t; /* byte count or error */
#elif __SIZEOF_SIZE_T__ == 4
typedef __uint32_t __size_t;   /* sizeof() */
typedef __int32_t __ssize_t;   /* byte count or error */
#else
#error unsupported Int size
#endif

#if __SIZEOF_PTRDIFF_T__ == 8
typedef __int64_t __ptrdiff_t; /* ptr1 - ptr2 */
#elif __SIZEOF_PTRDIFF_T__ == 4
typedef __int32_t __ptrdiff_t; /* ptr1 - ptr2 */
#else
#error unsupported Int size
#endif

/*
 * Target-dependent type definitions.
 */
#define __NO_STRICT_ALIGNMENT

/*
 * Standard type definitions.
 */
#ifdef __LP64__
typedef __int32_t __clock_t; /* clock()... */
typedef __int64_t __critical_t;
#ifndef _STANDALONE
typedef double __double_t;
typedef float __float_t;
#endif
#else
typedef unsigned long __clock_t;
typedef __int32_t __critical_t;
#ifndef _STANDALONE
typedef long double __double_t;
typedef long double __float_t;
#endif
#endif
typedef __int32_t __int_fast8_t;
typedef __int32_t __int_fast16_t;
typedef __int32_t __int_fast32_t;
typedef __int64_t __int_fast64_t;
#ifdef __LP64__
typedef __int64_t __register_t;
typedef __int64_t __segsz_t; /* segment size (in pages) */
typedef __int64_t __time_t;	 /* time()... */
#else
typedef __int32_t __register_t;
typedef __int32_t __segsz_t;
typedef __int32_t __time_t;
#endif
typedef __uint32_t __uint_fast8_t;
typedef __uint32_t __uint_fast16_t;
typedef __uint32_t __uint_fast32_t;
typedef __uint64_t __uint_fast64_t;
#ifdef __LP64__
typedef __uint64_t __u_register_t;
typedef __uint64_t __vm_paddr_t;
#else
typedef __uint32_t __u_register_t;
typedef __uint64_t __vm_paddr_t;
#endif
typedef int ___wchar_t;

#define __WCHAR_MIN __INT_MIN /* min value for a wchar_t */
#define __WCHAR_MAX __INT_MAX /* max value for a wchar_t */

/*
 * Standard type definitions.
 */
typedef __int32_t __blksize_t; /* file block size */
typedef __int64_t __blkcnt_t;  /* file block count */
typedef __int32_t __clockid_t; /* clock_gettime()... */
typedef __uint32_t __fflags_t; /* file flags */
typedef __uint64_t __fsblkcnt_t;
typedef __uint64_t __fsfilcnt_t;
typedef __uint32_t __gid_t;
typedef __int64_t __id_t;	 /* can hold a gid_t, pid_t, or uid_t */
typedef __uint64_t __ino_t;	 /* inode number */
typedef long __key_t;		 /* IPC key (for Sys V IPC) */
typedef __int32_t __lwpid_t; /* Thread ID (a.k.a. LWP) */
typedef __uint16_t __mode_t; /* permissions */
typedef int __accmode_t;	 /* acc permissions */
typedef int __nl_item;
typedef __uint64_t __nlink_t; /* link count */
typedef __int64_t __off_t;	  /* file offset */
typedef __int64_t __off64_t;  /* file offset (alias) */
typedef __int32_t __pid_t;	  /* process [group] */
typedef __int64_t __rlim_t;	  /* resource limit - intentionally */
							  /* signed, because of legacy code */
							  /* that uses -1 for RLIM_INFINITY */
typedef __uint8_t __sa_family_t;
typedef __uint32_t __socklen_t;
typedef long __suseconds_t;		   /* microseconds (signed) */
typedef struct __timer *__timer_t; /* timer_gettime()... */
typedef struct __mq *__mqd_t;	   /* mq_open()... */
typedef __uint32_t __uid_t;
typedef unsigned int __useconds_t; /* microseconds (unsigned) */
typedef int __cpuwhich_t;		   /* which parameter for cpuset. */
typedef int __cpulevel_t;		   /* level parameter for cpuset. */
typedef int __cpusetid_t;		   /* cpuset identifier. */
typedef __int64_t __daddr_t;	   /* bwrite(3), FIOBMAP2, etc */

typedef int __ct_rune_t;	  /* arg type for ctype funcs */
typedef __ct_rune_t __rune_t; /* rune_t (see above) */
typedef __ct_rune_t __wint_t; /* wint_t (see above) */

/* Clang already provides these types as built-ins, but only in C++ mode. */
#if !defined(__clang__) || !defined(__cplusplus)
typedef __uint_least16_t __char16_t;
typedef __uint_least32_t __char32_t;
#endif
/* In C++11, char16_t and char32_t are built-in types. */
#if defined(__cplusplus) && __cplusplus >= 201103L
#define _CHAR16_T_DECLARED
#define _CHAR32_T_DECLARED
#endif

typedef struct
{
	long long __max_align1 __attribute__((__aligned__((_Alignof(long long)))));
#ifndef _STANDALONE
	long double __max_align2 __attribute__((__aligned__((_Alignof(long double)))));
#endif
} __max_align_t;

typedef __uint64_t __dev_t; /* device number */

typedef __uint32_t __fixpt_t; /* fixed point number */

typedef union
{
	char __mbstate8[128];
	__int64_t _mbstateL; /* for alignment */
} __mbstate_t;

typedef __uintmax_t __rman_res_t;
#endif