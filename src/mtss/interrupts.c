/* @(#) isr.c */

#include <libcarbon/core.h>
#include <libcarbon/io.h>
#include <libcarbon/assert.h>
#include "reg.h"

static uint32_t li = 0xffffffff;

/* print the interrupt code */
#define _fatalError(MSG)                                                         \
    do                                                                           \
    {                                                                            \
        printf_("\033[1m\033[31mFatal error: %s (int $%x)\033[0m\n", (MSG), li); \
        while (1)                                                                \
        {                                                                        \
            __asm__ volatile("hlt");                                             \
        }                                                                        \
    } while (0)

/* print the errno */
#define _efatalError(MSG)                                                                                 \
    do                                                                                                    \
    {                                                                                                     \
        printf_("\033[1m\033[31mFatal error: %s (int $%x, errno $%x)\033[0m\n", (MSG), li, state->errno); \
        while (1)                                                                                         \
        {                                                                                                 \
            __asm__ volatile("hlt");                                                                      \
        }                                                                                                 \
    } while (0)

void MLTX_UNIX_API
_os_isr_handler(register_t *state)
{
    li = state->ino;
    assert(li < 32);

    switch (li)
    {
    case 0:
    {
        _fatalError("Zero division error");
    }
    /* ... */
    case 3:
    {
        _fatalError("Breakpoint exception");
    }
    case 4:
    {
        _fatalError("'Into detected overflow'");
    }
    case 5:
    {
        _fatalError("Out of bounds");
    }
    case 6:
    {
        _fatalError("Attempted to parse invalid instruction");
    }
    case 7:
    {
        _fatalError("No coprocessor");
    }
    case 8:
    {
        _efatalError("Double fault");
    }
    case 9:
    {
        _fatalError("Coprocessor segment overrun");
    }
    case 10:
    {
        _efatalError("Bad task state segment");
    }
    case 11:
    {
        _efatalError("Segment not present");
    }
    case 12:
    {
        _efatalError("Stack failure");
    }
    case 13:
    {
        _efatalError("Protection fault");
    }
    case 14:
    {
        _efatalError("Page fault");
    }
    case 15:
    {
        _fatalError("Unknown interrupt fault");
    }
    case 16:
    {
        _fatalError("Coprocessor fault");
    }
    case 17:
    {
        _fatalError("Alignment fault");
    }
    case 18:
    {
        _fatalError("Machine fault");
    }
    case 19:
    {
        _fatalError("Floating point fault");
    }
    case 20:
    {
        _fatalError("Virtualization fault");
    }
    case 21:
    {
        _fatalError("Control protection fault");
    }
        assert(li >= 22);

    default:
        warn(0); // unimplemented
        break;
    }
}

#undef fatalError

/* inline */ uint32_t MLTX_API
_os_get_last_interrupt(void)
{
    return li;
}