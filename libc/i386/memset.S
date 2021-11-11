/*===---- memset.S - -------------------------------------------------------===
 *
 * Part of the Carbon libc subset, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#include <sys/defs.h>
  
FSYM(memset)
GLOB(memset)
  pushl	%edi
	pushl	%ebx
	movl	12(%esp),%edi
	movzbl	16(%esp),%eax		/* unsigned char, zero extend */
	movl	20(%esp),%ecx
	pushl	%edi			/* push address of buffer */

	cld				/* set fill direction forward */

	cmpl	$0x0f,%ecx
	jle	L1

	movb	%al,%ah			/* copy char to all bytes in word */
	movl	%eax,%edx
	sall	$16,%eax
	orl	%edx,%eax

	movl	%edi,%edx		/* compute misalignment */
	negl	%edx
	andl	$3,%edx
	movl	%ecx,%ebx
	subl	%edx,%ebx

	movl	%edx,%ecx		/* set until word aligned */
	rep
	stosb

	movl	%ebx,%ecx
	shrl	$2,%ecx			/* set by words */
	rep
	stosl

	movl	%ebx,%ecx		/* set remainder by bytes */
	andl	$3,%ecx
L1:	rep
	stosb

	popl	%eax			/* pop address of buffer */
	popl	%ebx
	popl	%edi
	ret
.section .note.GNU-stack,"",%progbits