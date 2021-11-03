#include <stddef.h>
#include <stdarg.h>
#include <stand/stivale2.h>
#include <libc/string.h>
#include <libc/stdlib.h>

#define RETURN return(0)

#define PRINTF_BUFFER 20

static _ready = 0;

sprintf(c, len)
char c[]; {
    if (!_ready) return 1;
    //termio(c, len);
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

struct stivale2_struct *t; 

init_tty(__t) 
struct stivale2_struct *__t; {
    t = __t;
    return 1;
}

_io_printf(char fmt[], ...) {
    int cnt;
    char c;
    char tmp[1];
    va_list args;

    // this is incredibly slow.
    struct stivale2_struct_tag_terminal *term_str_tag;
    term_str_tag = stivale2_get_tag(t, STIVALE2_STRUCT_TAG_TERMINAL_ID);

    void *term_write_ptr = (void *)term_str_tag->term_write;
    void (*termio)(const char *string, size_t length) = term_write_ptr;
    
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