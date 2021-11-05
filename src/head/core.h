/* @(#) core.h */

#if !defined(_BASE_API)
#define _BASE_API 1

#define _KERNEL
#define MTSS_API __attribute__((__cdecl__))

/* needed for some assebly calls */
#define unix_function __attribute__((sysv_abi))

/* readability */
#define pack(x) __attribute__((packed)) (x)

#endif