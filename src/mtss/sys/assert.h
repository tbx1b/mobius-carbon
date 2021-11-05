/* @(#) assert.h */

#if !defined(_assert_h)
#define _assert_h

#include <sys/io.h>
#include <core.h>

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
        if (!((x) != 0))                                                                        \
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