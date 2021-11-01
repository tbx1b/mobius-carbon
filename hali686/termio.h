/*
 * MODULE:          Kernel
 * LICENSE:         GPL-3.0-or-later
 * PURPOSE:         Read/write to the tty
 * COPYRIGHT:       Copyright MobiusLoopFour
 */

#ifndef termio_h_
#define termio_h_

/* GLOBAL FUNCTIONS ***********************************************************/

void    hal_termio_write(char *c);
void    hal_termio_clear();
void    hal_termio_put(char c);
#endif /*! termio_h_ */
/* EOF */