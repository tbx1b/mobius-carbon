/*===---- io.S - Port I/O --------------------------------------------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#include <sys/defs.h>

FSYM(__outb)
GLOB(__outb)
  movb  8(%esp), %al
  movw  4(%esp), %dx
  outb  %al, %dx
  ret

FSYM(__inb)
GLOB(__inb)
  movw  4(%esp), %dx
  inb   %dx, %al
  ret
