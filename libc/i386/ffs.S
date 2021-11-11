/*===---- ffs.S - ----------------------------------------------------------===
 *
 * Part of the Carbon libc subset, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#include <sys/defs.h>

FSYM(ffs)
GLOB(ffs)
 	bsfl	4(%esp),%eax
	jz	L1	 		// ZF is set if all bits are 0
	incl	%eax			// bits numbered from 1, not 0
	ret

	.align 2
L1:	xorl	%eax,%eax		/* clear result */
	ret

.section .note.GNU-stack,"",%progbits