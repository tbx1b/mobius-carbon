#include <stddef.h>
#include <stdarg.h>

#include <stand/stivale2.h>
#include <libc/string.h>
#include <libc/stdlib.h>

#define RETURN return(0)

#define PRINTF_BUFFER 20
static _ready = 0;
extern void (*termio)(char *str, size_t len);
void *t = 0;

sprintf(c, len)
char c[]; {
    if (!_ready) return;
    termio(c, len);
    RETURN;
}

#define itod(x) ((char)x+'0')
#define H(FUNCTOR,to) \
    do {        \
        tmp[0] = FUNCTOR(va_arg(args, to)); \
        termio(&tmp[0], 1); \
    } while (0);

#define Hxtox(FUNCTOR,to) \
    do { \
        char tmp2[PRINTF_BUFFER]; \
        FUNCTOR(va_arg(args, to), tmp2);\
        termio(tmp2, PRINTF_BUFFER); \
    } while (0)

_io_printf(char fmt[], ...) {
    int cnt;
    char c;
    char tmp[1];
    va_list args;
    extern void halt();

    if (!termio) return; /* null test, else we'll triple fault ;) */
    
    cnt=0;
    va_start(args, fmt);
    
    do {
        if (*fmt!='%') {termio(&fmt[0], 1); continue;}
        fmt++;
        switch (*fmt) {
        case 'd' : {
            Hxtox(itoa, int);
            break;
        }
        case '%' :
        case '\0' : {
            termio("%", 1);
            break;
        }
        default:
            break; /* user did not format well */
        }
    } while(*fmt++);

    va_end(args);
    RETURN;
}
#undef H
/* eof */