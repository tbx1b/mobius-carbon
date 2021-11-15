/Platform specific wrappers to call from C

.text
.globl	insl
.type	insl, @function
insl:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%ebx
	movl	8(%ebp), %edx
	movl	12(%ebp), %ecx
	movl	16(%ebp), %eax
	movl	%ecx, %ebx
	movl	%ebx, %edi
	movl	%eax, %ecx

	cld; rep insl

	movl	%ecx, %eax
	movl	%edi, %ebx
	movl	%ebx, 12(%ebp)
	movl	%eax, 16(%ebp)
	nop
	popl	%ebx
	popl	%edi
	popl	%ebp
	ret
	.size	insl, .-insl
	.globl	outw
	.type	outw, @function
outw:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movw	%dx, -4(%ebp)
	movw	%ax, -8(%ebp)
	movzwl	-8(%ebp), %eax
	movzwl	-4(%ebp), %edx

	out %ax,%dx

	nop
	leave
	ret
	.size	outw, .-outw
	.globl	outsl
	.type	outsl, @function
outsl:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %edx
	movl	12(%ebp), %ecx
	movl	16(%ebp), %eax
	movl	%ecx, %ebx
	movl	%ebx, %esi
	movl	%eax, %ecx

	cld; rep outsl

	movl	%ecx, %eax
	movl	%esi, %ebx
	movl	%ebx, 12(%ebp)
	movl	%eax, 16(%ebp)
	nop
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	outsl, .-outsl
	.globl	stosb
	.type	stosb, @function
stosb:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%ebx
	movl	8(%ebp), %ecx
	movl	16(%ebp), %edx
	movl	12(%ebp), %eax
	movl	%ecx, %ebx
	movl	%ebx, %edi
	movl	%edx, %ecx

	cld; rep stosb

	movl	%ecx, %edx
	movl	%edi, %ebx
	movl	%ebx, 8(%ebp)
	movl	%edx, 16(%ebp)
	nop
	popl	%ebx
	popl	%edi
	popl	%ebp
	ret
	.size	stosb, .-stosb
	.globl	stosl
	.type	stosl, @function
stosl:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%ebx
	movl	8(%ebp), %ecx
	movl	16(%ebp), %edx
	movl	12(%ebp), %eax
	movl	%ecx, %ebx
	movl	%ebx, %edi
	movl	%edx, %ecx

	cld; rep stosl

	movl	%ecx, %edx
	movl	%edi, %ebx
	movl	%ebx, 8(%ebp)
	movl	%edx, 16(%ebp)
	nop
	popl	%ebx
	popl	%edi
	popl	%ebp
	ret
	.size	stosl, .-stosl
	.globl	lgdt
	.type	lgdt, @function
lgdt:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	12(%ebp), %eax
	subl	$1, %eax
	movw	%ax, -6(%ebp)
	movl	8(%ebp), %eax
	movw	%ax, -4(%ebp)
	movl	8(%ebp), %eax
	shrl	$16, %eax
	movw	%ax, -2(%ebp)
	leal	-6(%ebp), %eax

	lgdt (%eax)

	nop
	leave
	ret
	.size	lgdt, .-lgdt
	.globl	lidt
	.type	lidt, @function
lidt:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	12(%ebp), %eax
	subl	$1, %eax
	movw	%ax, -6(%ebp)
	movl	8(%ebp), %eax
	movw	%ax, -4(%ebp)
	movl	8(%ebp), %eax
	shrl	$16, %eax
	movw	%ax, -2(%ebp)
	leal	-6(%ebp), %eax

	lidt (%eax)

	nop
	leave
	ret
	.size	lidt, .-lidt
	.globl	ltr
	.type	ltr, @function
ltr:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	8(%ebp), %eax
	movw	%ax, -4(%ebp)
	movzwl	-4(%ebp), %eax

	ltr %ax

	nop
	leave
	ret
	.size	ltr, .-ltr
	.globl	readeflags
	.type	readeflags, @function
readeflags:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp

	pushfl; popl %eax

	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	ret
	.size	readeflags, .-readeflags
	.globl	loadgs
	.type	loadgs, @function
loadgs:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	8(%ebp), %eax
	movw	%ax, -4(%ebp)
	movzwl	-4(%ebp), %eax

	movw %ax, %gs

	nop
	leave
	ret
	.size	loadgs, .-loadgs
	.globl	cli
	.type	cli, @function
cli:
	pushl	%ebp
	movl	%esp, %ebp

	cli

	nop
	popl	%ebp
	ret
	.size	cli, .-cli
	.globl	sti
	.type	sti, @function
sti:
	pushl	%ebp
	movl	%esp, %ebp

	sti

	nop
	popl	%ebp
	ret
	.size	sti, .-sti
	.globl	xchg
	.type	xchg, @function
xchg:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx

	lock; xchgl (%edx), %eax

	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	ret
	.size	xchg, .-xchg
	.globl	rcr2
	.type	rcr2, @function
rcr2:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp

	movl %cr2,%eax

	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	ret
	.size	rcr2, .-rcr2
	.globl	lcr3
	.type	lcr3, @function
lcr3:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax

	movl %eax,%cr3

	nop
	popl	%ebp
	ret
	.size	lcr3, .-lcr3
