/ str3.s
/ C: char *strcat(char *dest, const char *src);
.text
.globl	strcat
.type	strcat, @function

strcat:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %ebx
	pushl	%ebx
	call	strlen
	addl	$8, %esp
	pushl	12(%ebp)
	addl	%ebx, %eax
	pushl	%eax
	call	strcpy
	movl	%ebx, %eax
	movl	-4(%ebp), %ebx
	leave
	ret
	.size	strcat, .-strcat

/ C: unsigned int strnlen(const char *str, unsigned int maxlen);
.globl	strnlen
.type	strnlen, @function

strnlen:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %esi
	movl	12(%ebp), %ecx
	movl	%ecx, %eax
	testl	%ecx, %ecx
	je	.L3
	addl	%esi, %ecx
	testl	$3, %esi
	je	.L14
	movl	%esi, %eax
.L7:
	cmpb	$0, (%eax)
	je	.L19
	addl	$1, %eax
	testb	$3, %al
	jne	.L7
.L5:
	cmpl	%eax, %ecx
	ja	.L12
	movl	%eax, %ebx
	jmp	.L8
.L19:
	cmpl	%eax, %ecx
	cmovbe	%ecx, %eax
	subl	%esi, %eax
	jmp	.L3
.L14:
	movl	%esi, %eax
	jmp	.L5
.L21:
	leal	-3(%eax), %ebx
	jmp	.L8
.L22:
	leal	-2(%eax), %ebx
	jmp	.L8
.L9:
	cmpl	%eax, %ecx
	jbe	.L20
.L12:
	movl	%eax, %ebx
	addl	$4, %eax
	movl	-4(%eax), %edx
	subl	$16843009, %edx
	testl	$-2139062144, %edx
	je	.L9
	cmpb	$0, -4(%eax)
	je	.L8
	cmpb	$0, -3(%eax)
	je	.L21
	cmpb	$0, -2(%eax)
	je	.L22
	cmpb	$0, -1(%eax)
	jne	.L9
	leal	-1(%eax), %ebx
	jmp	.L8
.L20:
	movl	%ecx, %ebx
.L8:
	cmpl	%ecx, %ebx
	movl	%ecx, %eax
	cmovbe	%ebx, %eax
	subl	%esi, %eax
.L3:
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	strnlen, .-strnlen

/ C: char *strncat(char *s1, const char *s2, unsigned int n);
.globl	strncat
.type	strncat, @function

strncat:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$24, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	pushl	%esi
	call	strlen
	addl	$8, %esp
	leal	(%esi,%eax), %ebx
	pushl	16(%ebp)
	pushl	%edi
	call	strnlen
	addl	$12, %esp
	movb	$0, (%ebx,%eax)
	pushl	%eax
	pushl	%edi
	pushl	%ebx
	call	memcpy
	movl	%esi, %eax
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	strncat, .-strncat
