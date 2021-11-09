/*===---- io.c - I/O ports helper functions --------------------------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#ifndef __CARBON_IO_H_
#define __CARBON_IO_H_

#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/defs.h>

__BEGIN_DECLS

/**
 * @brief Send a byte
 * 
 * @param port to
 * @param data
 */
extern void __outb(uint16_t port, uint16_t data);

/**
 * @brief Get a byte
 * 
 * @param port from
 * @return data 
 */
extern uint8_t __inb(uint16_t port);

__END_DECLS

// Don't use ugly leading underscores, define something more normal.
// Used throughout this porject to avoid namespace collision, and
// impose good #include practices
#define inb __inb
#define outb __outb

#endif /* __CARBON_IO_H_ */
// eof