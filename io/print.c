#include <stddef.h>
#include <stdarg.h>

#include <stand/stivale2.h>
#include <libc/string.h>
#include <libc/stdlib.h>

#define RETURN return(0)

#define PRINTF_BUFFER 20

typedef (*termbuf_t)(char *str, size_t len);
static _ready = 0;
static termbuf_t termio;

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

init_tty(t) 
struct stivale2_struct *t; {
    extern void halt();

    struct stivale2_struct_tag_terminal *term_str_tag;
    term_str_tag = stivale2_get_tag(t, STIVALE2_STRUCT_TAG_TERMINAL_ID);

    if (term_str_tag == 0)
    {
        for (;;)
        {
            halt();
        }
    }

    void *term_write_ptr = (void *)term_str_tag->term_write;

    termio = term_write_ptr;

    _ready = 1;
    RETURN;
}

_io_printf(char fmt[], ...) {
    int cnt;
    char c;
    char tmp[1];
    va_list args;
    
    cnt=0;
    va_start(args, fmt);
    if (!_ready) return;
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