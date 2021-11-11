/*===---- bcmp.S - ---------------------------------------------------------===
 *
 * Part of the Carbon libc subset, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#include <sys/defs.h>

FSYM(bcmp)
GLOB(bcmp)
	pushl	%edi
	pushl	%esi
	movl	12(%esp),%edi
	movl	16(%esp),%esi
	cld				// set compare direction forward

	movl	20(%esp),%ecx		// compare by words
	shrl	$2,%ecx
	repe
	cmpsl
	jne	L1

	movl	20(%esp),%ecx		// compare remainder by bytes
	andl	$3,%ecx
	repe
	cmpsb
L1:
	setne	%al
	movsbl	%al,%eax
	popl	%esi
	popl	%edi
	ret

.section .note.GNU-stack,"",%progbits