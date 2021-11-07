/* @(#) assert.h */

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

#if !defined(_assert_h)
#define _assert_h

#include <libcarbon/io.h>
#include <libcarbon/core.h>

/*
 * inline definition in header file
 *
 */

#ifdef __DEBUG__

#define fatalError(MSG)                               \
    do                                                \
    {                                                 \
        printf_("\033[1m\033[31m%s\033[0m\n", (MSG)); \
        while (1)                                     \
        {                                             \
            __asm__ volatile("cli");                  \
            __asm__ volatile("hlt");                  \
        }                                             \
    } while (0)

#define assert(x)                                                                               \
    do                                                                                          \
    {                                                                                           \
        if (!(x))                                                                               \
        {                                                                                       \
            printf_("\033[1m\033[31m ASSERTION FAILED - %s - %d\033[0m\n", __FILE__, __LINE__); \
            for (;;)                                                                            \
            {                                                                                   \
                __asm__ volatile("cli");                                                        \
                __asm__ volatile("hlt");                                                        \
            }                                                                                   \
        }                                                                                       \
    } while (0)

/* yellow */
#define warn(x)                                                                         \
    do                                                                                  \
    {                                                                                   \
        if (!(x))                                                                       \
            printf_("\033[1m\033[33m Warning: - %s - line %d\033[0m\n", __FILE__, __LINE__); \
    } while (0)

#define assertNonzero(x)                                                                          \
    do                                                                                          \
    {                                                                                           \
        if (((x) != 0))                                                                        \
        {                                                                                       \
            printf_("\033[1m\033[31m ASSERTION FAILED - %s - %d\033[0m\n", __FILE__, __LINE__); \
            for (;;)                                                                            \
            {                                                                                   \
                __asm__ volatile("cli");                                                        \
                __asm__ volatile("hlt");                                                        \
            }                                                                                   \
        }                                                                                       \
    } while (0)

#else
#error Debugging in release mode is undefined
#endif

#endif