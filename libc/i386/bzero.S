/*===---- bzero.S - --------------------------------------------------------===
 *
 * Part of the Carbon libc subset, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#include <sys/defs.h>

FSYM(bzero)
GLOB(bzero)
	pushl	%edi
	pushl	%ebx
	movl	12(%esp),%edi
	movl	16(%esp),%ecx

	cld				/* set fill direction forward */
	xorl	%eax,%eax		/* set fill data to 0 */

	cmpl	$0x0f,%ecx
	jle	L1

	movl	%edi,%edx		/* compute misalignment */
	negl	%edx
	andl	$3,%edx
	movl	%ecx,%ebx
	subl	%edx,%ebx

	movl	%edx,%ecx		/* zero until word aligned */
	rep
	stosb

	movl	%ebx,%ecx		/* zero by words */
	shrl	$2,%ecx
	rep
	stosl

	movl	%ebx,%ecx
	andl	$3,%ecx			/* zero remainder by bytes */
L1:	rep
	stosb

	popl	%ebx
	popl	%edi
	ret
.section .note.GNU-stack,"",%progbits