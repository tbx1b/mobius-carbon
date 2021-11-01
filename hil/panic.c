#include <carbon.h>

#define dbg(x) printf("[EXCEPTION OCCURED]: %s\n", x)

hil_tab_on_panic(void)
{
    #warning TODO: crash dump
    dbg("Your social credit score appears to be > 0. (Abort trap 31)"); /* int $31 */
    return 0;
}

#undef dbg/*(x)*/