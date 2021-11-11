/*===---- gdt.S - Load the gdt ---------------------------------------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#include <sys/defs.h>

FSYM(gdtflush)
GLOB(gdtflush)
   movl 4(%esp),%eax
   lgdtl (%eax)

   movw $0x10, %ax
   movw %ax, %ds
   movw %ax, %es
   movw %ax, %fs
   movw %ax, %gs
   movw %ax, %ss
   jmpl $0x08,$flush

flush:
   retl
   nop
   nop
   nop

.section .note.GNU-stack,"",%progbits