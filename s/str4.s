/ str4.s

.text

/ C: int strcmp(const char *p1, const char *p2);
	.align 16
	.globl	strcmp
	.type	strcmp, @function

strcmp:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%esi
	movl	8(%ebp), %esi
	pushl	%ebx
	movl	12(%ebp), %ebx
	jmp	.L4
	.align 16
.L2:
	addl	$1, %eax
	cmpb	%cl, %dl
	jne	.L8
.L4:
	movzbl	(%esi,%eax), %edx
	movzbl	(%ebx,%eax), %ecx
	testb	%dl, %dl
	jne	.L2
	movzbl	%cl, %eax
	popl	%ebx
	popl	%esi
	negl	%eax
	popl	%ebp
	ret
	.align 16
.L8:
	movzbl	%dl, %eax
	popl	%ebx
	popl	%esi
	subl	%ecx, %eax
	popl	%ebp
	ret
	.size	strcmp, .-strcmp



/ C: int strncmp(const char *s1, const char *s2, unsigned int n)
.align 16
.globl	strncmp
.type	strncmp, @function

strncmp:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	16(%ebp), %edi
	movl	8(%ebp), %edx
	pushl	%esi
	movl	12(%ebp), %ecx
	pushl	%ebx
	cmpl	$3, %edi
	jbe	.L25
	movl	%edi, %esi
	andl	$-4, %esi
	addl	%edx, %esi
	.align 16
.L20:
	movzbl	(%edx), %eax
	movzbl	(%ecx), %ebx
	testb	%al, %al
	je	.L21
	cmpb	%bl, %al
	jne	.L21
	movzbl	1(%edx), %eax
	movzbl	1(%ecx), %ebx
	testb	%al, %al
	je	.L21
	cmpb	%bl, %al
	jne	.L21
	movzbl	2(%edx), %eax
	movzbl	2(%ecx), %ebx
	testb	%al, %al
	je	.L21
	cmpb	%bl, %al
	jne	.L21
	movzbl	3(%edx), %eax
	addl	$4, %edx
	addl	$4, %ecx
	movzbl	-1(%ecx), %ebx
	testb	%al, %al
	je	.L21
	cmpb	%bl, %al
	jne	.L21
	cmpl	%edx, %esi
	jne	.L20
	andl	$3, %edi
	jmp	.L10
	.align 16
.L25:
	xorl	%ebx, %ebx
	xorl	%eax, %eax
.L10:
	testl	%edi, %edi
	je	.L21
	movzbl	(%edx), %eax
	movzbl	(%ecx), %ebx
	cmpb	%al, %bl
	jne	.L21
	testb	%al, %al
	je	.L21
	subl	$1, %edi
	je	.L21
	movzbl	1(%edx), %eax
	movzbl	1(%ecx), %ebx
	cmpb	%al, %bl
	jne	.L21
	testb	%al, %al
	je	.L21
	cmpl	$1, %edi
	je	.L21
	movzbl	2(%edx), %eax
	movzbl	2(%ecx), %ebx
.L21:
	subl	%ebx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	strncmp, .-strncmp
