/* @(#) core.h */

/*
 * Copyright (c) 2021 MobiusLoopFour. All rights reserved.
 *
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in the documentation and that are subject to the 
 * GNU GPL v3-Or-Later License. You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * https://www.gnu.org/licenses/gpl-3.0.en.html and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND ALL SUCH WARRANTIES ARE HEREBY DISCLAIMED,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 */

#if !defined(_BASE_API)
#define _BASE_API 1

#define _KERNEL
#define MLTX_API __attribute__((__cdecl__))

/* needed for some assebly calls */
#define MLTX_UNIX_API __attribute__((sysv_abi))

extern void MLTX_API _os_announce();
#define announce _os_announce

#if defined(__cplusplus)
#define _CARBON_BEGIN_DECLS extern "C" {
#define _CARBON_END_DECLS }
#else 
#define _CARBON_BEGIN_DECLS
#define _CARBON_END_DECLS 
#endif

#define INLINE extern /* __inline */

#endif