#ifndef _STD_H
#define _STD_H

#include "cplus.h"

/* convenience for successful return */
#define RETURN return(0)

EXPORT_C_START 

int reverse(char[]);
int itoa(int, char buffer[]);

EXPORT_C_END

#endif