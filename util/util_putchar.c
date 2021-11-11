/*===---- putchar.c - Display a character on the serial port ---------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#include <sys/types.h>
#include <device/io.h>

#define PORT 0x3f8

/**
 * @brief Log a character on the serial port
 * 
 * @param c The character
 * @return uint 0 on success
 */
uint putc(const char c) {
  outb(PORT, c);
  return 0;
}
