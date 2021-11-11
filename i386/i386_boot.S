/*===---- boot.S - Kernel entry point assembly stub ---0--------------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#include <sys/defs.h>

.section multiboot, "ax"

#define MB_MAGIC 0x1badb002
#define MB_FLAGS 0x0
#define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)

.align 4
	.int MB_MAGIC
	.int MB_FLAGS
	.int MB_CHECKSUM

.section .text, "ax"

.extern init

FSYM(_start)
GLOB(_start)
	movl $kernel_stack, %esp

	// reset eflags
	pushl   $0
	popf

	// Push the pointer to the Multiboot information structure
	pushl   %ebx
	// Push the magic value
	pushl   %eax

	calll kmain
	// Nothing to do...
	orl			%eax,%eax
	jnz			2f
	pushl 	$hanging
	calll		printf_
1:
	cli
	hlt
	jmp 1b
2:
	pushl $something_went_wrong
	calll printf_

something_went_wrong: 
	.asciz "Something went wrong. You may now turn off your computer and restart\n"

hanging:
	.asciz "You may turn off your computer\n"

.section .bss, "aw"
.space 8192 * 2
kernel_stack:

.section .note.GNU-stack,"",%progbits
// eof