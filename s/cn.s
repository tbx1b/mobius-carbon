/ Disable the hardware cursor
/ C prototype: void cncursoroff(void);
.globl cncursoroff
.type cncursoroff,@function

cncursoroff:
  pushf
  pushl %eax
  pushl %edx
  movw $0x3D4, %dx
  / low cursor shape register
  movb $0xA, %al
  outb %al, %dx
  addw $1, %dx
  / bits 6-7 unused, bit 5 disables the cursor, bits 0-4 control the cursor shape
  movb $0x20, %al
  outb %al, %dx
  popl %edx
  popl %eax
  popf
  retl
.size cncursoroff, . - cncursoroff

.globl	cncursoron
.type	cncursoron, @function

/ Enable the hardware cursor
/ C prototype: void cncursoron(unsigned char cursor_start, unsigned char cursor_end);
cncursoron:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	subl	$8, %esp
	pushl	$10
	pushl	$980
	call	iooutb
	movl	$981, (%esp)
	call	ioinb
	popl	%edx
	popl	%ecx
	andl	$-64, %eax
	orl	%esi, %eax
	movzbl	%al, %eax
	pushl	%eax
	pushl	$981
	call	iooutb
	popl	%esi
	popl	%eax
	pushl	$11
	pushl	$980
	call	iooutb
	movl	$981, (%esp)
	call	ioinb
	movl	$981, 8(%ebp)
	addl	$16, %esp
	andl	$-32, %eax
	orl	%ebx, %eax
	movzbl	%al, %eax
	movl	%eax, 12(%ebp)
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	jmp	iooutb

.size	cncursoron, .-cncursoron
/ eof