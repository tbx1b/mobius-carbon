#ifndef hal_h_
#define hal_h_

#include "carbon.h"

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

extern word    hal_io_inw(word port);

/*! --- 
 *
 * @interface   tty
 * 
 * @brief       input/output to tty
 * 
 */


extern void    hal_termio_write(char *c);

extern void    hal_termio_clear();

extern void    hal_termio_put(char c);

#endif /* hal_h_ */