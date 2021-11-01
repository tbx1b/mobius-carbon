#include <carbon.h>
#include "register.h"

static last_int = -1;

void _cdecl
isr_handler(register_t regs)
{
    #define dbg(x) hal_termio_write(x) /* printf has a bug which makes it unavailable */

    dbg("-------------------------------------\n"); 
    last_int = regs.int_no;

    switch (regs.int_no)
    {
        case 0 : {
            dbg("ERR_DIV_BY_ZERO (Abort trap $0)\n");
            return;
        }

        /***************  FATAL   ******************/
        case 31 : {
            hil_tab_on_panic();
            while (1) { __asm__("hlt"); } 
            #warning TODO: shutdown
            return;
        }
        default : {
            dbg("UNHANDLED EXCEPTION\n");
            while (1) { __asm__("hlt"); }
        }
    }
    return;
}

hal_idt_get_last()
{
    return last_int;
}
#undef dbg/*(x)*/
/*! EOF */