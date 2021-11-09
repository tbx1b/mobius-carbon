/*===---- serial_defs.c - Serial console helper functions ------------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#ifndef __CARBON_SERIAL_H_
#define __CARBON_SERIAL_H_

#include <sys/defs.h>
#include <sys/types.h>

// Generic serial port "magic" numbers
#define SERIAL_COM1_BASE 0x3F8 /* COM1 base port */
#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)
#define SERIAL_LINE_ENABLE_DLAB 0x80

__BEGIN_DECLS

int spbaudrate(uint16_t com, uint16_t div);

__END_DECLS

#endif /* __CARBON_SERIAL_H_ */
