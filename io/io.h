#ifndef _IO_H
#define _IO_H

#include <stdint.h>

typedef uint64_t io_id_t;

extern _io_printf(char fmt[], ...);

extern init_tty(void *tty);

extern sprintf(char c[], int len);

extern uintptr_t stivale2_get_tag(struct stivale2_struct *e, io_id_t id); 

#endif