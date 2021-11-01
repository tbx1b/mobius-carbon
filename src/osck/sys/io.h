#ifndef io_h_
#define io_h_

#include <CarbonDef.h>

void    outb(word port, byte value);
byte    inb(word port);
byte    inw(word port);

#endif /*! io_h */
/* EOF */