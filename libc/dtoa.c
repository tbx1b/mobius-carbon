#include <libc/string.h>

#define ITOA_BUFFER 20
#define RETURN return(0)


reverse(s)
char s[]; {
    int i, j;
    char c;
 
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    RETURN;
}

itoa(n, s)
char s[]; {
    int i, j, sign;

    for (j = 0; j < ITOA_BUFFER; j++) {
        s[j] = '\0';
    }

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