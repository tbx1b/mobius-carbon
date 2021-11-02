#include "trace.h"

#include <libc/string.h>

extern sprintf(char[], int);

trace(x) 
char x[]; {
    sprintf("[trace]: ", 10);
    sprintf(x, strlen(x));
    sprintf("\n ", 1);
}
