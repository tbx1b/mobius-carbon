#include <stand/stivale2.h>
#include <stddef.h>
#include <libc/string.h>

#define RETURN return(0)

typedef (*termbuf_t)(char *str, size_t len);
static _ready = 0;
static termbuf_t termio;

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

sprintf(c, len)
char c[];
int len; {
    if (!_ready) return;
    termio(c, len);
    RETURN;
}

#define itod(x) ((char)x+'0')
#define H(FUNCTOR) \
    do {        \
        tmp[0] = FUNCTOR(x1); \
        termio(&tmp[0], 1); \
    } while (0);

#define Hxtox(FUNCTOR) \
    do { \
        char tmp2[10]; \
        FUNCTOR(x1, tmp2);\
        termio(tmp2, 10); \
    } while (0)

itoa(n, s)
char s[]; {
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    RETURN;
}

reverse(s)
char s[]; {
    int i, j;
    char c;
 
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    return(0);
}

printf(fmt, x1, x2, x3, x4, x5, x6)
char fmt[]; {
    int cnt;
    char c;
    char tmp[1];
    cnt=0;
    if (!_ready) return;
    do {
        if (*fmt!='%') {termio(&fmt[0], 1); continue;}
        fmt++;
        switch (*fmt) {
        case 'd' : {
            Hxtox(itoa);
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

    RETURN;
}
#undef H