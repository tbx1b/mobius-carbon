/*===---- serial_console.c - Serial console helper functions ---------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#include <chips/serial_defs.h>
#include <device/io.h>
#include <sys/defs.h>
#include <sys/types.h>

/**
 * @brief Configure the baud rate of the serial port
 *
 * @param com The com pot
 * @param div The divisor
 * @return 0 on success
 */
int spbaudrate(uint16_t com, uint16_t div) {
  // Enable DLAB
  outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);

  // Set the div (sends LO_BYTE and HI_BYTEs)
  outb(SERIAL_DATA_PORT(com), (div >> 8) & 0x00FF);
  outb(SERIAL_DATA_PORT(com), div & 0x00FF);

  // Nothing bad happened... return with succes code (0)
  RETURN;
}

/**
 * @brief Configure serial port line
 *
 * @param c The port
 * @return 0 on success
 */
int spln(uint16_t c) {
  /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
   * Content: | d | b | prty  | s | dl  |
   * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
   */
  outb(SERIAL_LINE_COMMAND_PORT(c), 0x03);
  RETURN;
}
// eof