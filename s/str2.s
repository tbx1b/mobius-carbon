/ str2.S, continuation of str1.S
.text

/ Copy a block of memory, handling overlap.
/ This is the routine that actually implements
/ (the portable versions of) bcopy, memcpy, and memmove.
/ C: void * memcpy(void *dst0, const void *src0, unsigned int len)
.globl	memcpy
.type	memcpy, @function

memcpy:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$4, %esp
	movl	12(%ebp), %eax
	movl	16(%ebp), %edi
	testl	%edi, %edi
	je	.L2
	cmpl	%eax, 8(%ebp)
	je	.L2
	movl	%eax, %ecx
	cmpl	%eax, 8(%ebp)
	jnb	.L3
	movl	%eax, %ebx
	orl	8(%ebp), %ebx
	movl	8(%ebp), %edx
	testb	$3, %bl
	je	.L4
	movl	%eax, %edx
	xorl	8(%ebp), %edx
	testb	$3, %dl
	jne	.L17
	cmpl	$3, %edi
	ja	.L26
.L17:
	movl	%edi, %esi
.L5:
	subl	%esi, %edi
	movl	%esi, %edx
	addl	8(%ebp), %edx
	movl	%eax, %ebx
	movl	8(%ebp), %ecx
	movl	%eax, 12(%ebp)
.L6:
	addl	$1, %ebx
	addl	$1, %ecx
	movzbl	-1(%ebx), %eax
	movb	%al, -1(%ecx)
	cmpl	%edx, %ecx
	jne	.L6
	movl	12(%ebp), %eax
	addl	%esi, %eax
.L4:
	cmpl	$3, %edi
	jbe	.L7
	movl	%edi, %esi
	shrl	$2, %esi
	movl	%eax, %ebx
	movl	%edx, %ecx
	movl	%eax, 12(%ebp)
.L8:
	movl	(%ebx), %eax
	movl	%eax, (%ecx)
	addl	$4, %ebx
	addl	$4, %ecx
	subl	$1, %esi
	jne	.L8
	movl	12(%ebp), %eax
	movl	%edi, %ecx
	andl	$-4, %ecx
	addl	%ecx, %eax
	addl	%ecx, %edx
.L7:
	andl	$3, %edi
	movl	%edi, %ebx
	je	.L2
	addl	%edx, %ebx
.L9:
	addl	$1, %eax
	addl	$1, %edx
	movzbl	-1(%eax), %ecx
	movb	%cl, -1(%edx)
	cmpl	%ebx, %edx
	jne	.L9
.L2:
	movl	8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.L26:
	andl	$3, %ecx
	movl	$4, %edx
	movl	%edx, %esi
	subl	%ecx, %esi
	jmp	.L5
.L3:
	addl	%edi, %eax
	movl	%edi, %ecx
	addl	8(%ebp), %ecx
	movl	%eax, %ebx
	movl	%ecx, %edx
	orl	%eax, %edx
	testb	$3, %dl
	je	.L10
	movl	%ecx, %edx
	xorl	%eax, %edx
	testb	$3, %dl
	jne	.L18
	andl	$3, %ebx
	cmpl	$4, %edi
	ja	.L11
.L18:
	movl	%edi, %ebx
.L11:
	subl	%ebx, %edi
	movl	%ebx, %edx
	movl	%ebx, %esi
	negl	%esi
	subl	%ebx, %eax
	movl	%ecx, -16(%ebp)
.L12:
	movl	-16(%ebp), %ebx
	addl	%esi, %ebx
	movzbl	-1(%eax,%edx), %ecx
	movb	%cl, -1(%ebx,%edx)
	subl	$1, %edx
	jne	.L12
	movl	%ebx, %ecx
.L10:
	cmpl	$3, %edi
	jbe	.L13
	movl	%edi, %edx
	shrl	$2, %edx
	movl	%edi, %ebx
	andl	$-4, %ebx
	subl	%ebx, %eax
	subl	%ebx, %ecx
.L14:
	movl	-4(%eax,%edx,4), %ebx
	movl	%ebx, -4(%ecx,%edx,4)
	subl	$1, %edx
	jne	.L14
.L13:
	andl	$3, %edi
	je	.L2
	movl	%edi, %edx
	movl	%edi, %ebx
	negl	%ebx
	subl	%edi, %eax
	movl	%ecx, %edi
.L15:
	leal	(%edi,%ebx), %esi
	movzbl	-1(%eax,%edx), %ecx
	movb	%cl, -1(%esi,%edx)
	subl	$1, %edx
	jne	.L15
	jmp	.L2

	.size	memcpy, .-memcpy


/ C: void * memmove(void *s1, const void *s2, unsigned int n)
.globl	memmove
.type	memmove, @function
memmove:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	pushl	16(%ebp)
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	memcpy
	leave
	ret
	.size	memmove, .-memmove


/ C: void bcopy(const void *s1, void *s2, unsigned int n)
.globl	bcopy
.type	bcopy, @function
bcopy:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	pushl	16(%ebp)
	pushl	8(%ebp)
	pushl	12(%ebp)
	call	memcpy
	addl	$16, %esp
	leave
	ret
	.size	bcopy, .-bcopy


/ C: char * strcpy(char * restrict dst, const char * restrict src)
.globl	strcpy
.type	strcpy, @function
strcpy:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %ebx
	movl	12(%ebp), %esi
	subl	$12, %esp
	pushl	%esi
	call	strlen
	addl	$12, %esp
	addl	$1, %eax
	pushl	%eax
	pushl	%esi
	pushl	%ebx
	call	memcpy
	movl	%ebx, %eax
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	strcpy, .-strcpy
