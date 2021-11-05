/* #(@) announce.c - simple bootup message */

#include <sys/io.h>
#include <core.h>

// ugly code, pretty announce().
MTSS_API void
_os_announce()
{
    printf("\033[1m\033[32m--------------------------------------------------------------------------------------------------------------------\n\n");
    printf("\t\tBOOT SUCCEEDED\n");
    printf("\t\tThe source code can be read at: \033[34mhttps://github.com/mobiusloopfour/mobius-carbon\033[1m\033[32m\n");
    printf("\t\tThe system software is licensed under GPLv3-OR-LATER\n\n");
    printf("--------------------------------------------------------------------------------------------------------------------\n\n\033[0m");
    return;
}