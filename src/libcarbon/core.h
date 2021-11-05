/* @(#) core.h */

#if !defined(_BASE_API)
#define _BASE_API 1

#define _KERNEL
#define MLTX_API __attribute__((__cdecl__))

/* needed for some assebly calls */
#define MLTX_UNIX_API __attribute__((sysv_abi))

extern void MLTX_API _os_announce();
#define announce _os_announce

#endif