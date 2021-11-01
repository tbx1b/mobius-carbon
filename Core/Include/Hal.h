#ifndef hal_h_
#define hal_h_

#include "Carbon.h"

/* GLOBAL FUNCTIONS ***********************************************************/

/*! --- 
 *
 * @interface   io
 * 
 * @brief       input/output to port
 * 
 */

extern void    hal_io_outb(word port, byte value);

extern byte    hal_io_inb(word port);

extern byte    hal_io_inw(word port);

/*! --- 
 *
 * @interface   tty
 * 
 * @brief       input/output to tty
 * 
 */


extern void    hal_tty_write(char *c);

extern void    hal_tty_clear();

extern void    hal_tty_put(char c);

#endif /* hal_h_ */