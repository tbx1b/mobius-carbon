/ =========------------------------- str6.s -------------------------=========/
/                       Copyright 2021 MobiusLoopFour
/
/  Licensed under the Apache License, Version 2.0 (the "License");
/  you may not use this file except in compliance with the License.
/   You may obtain a copy of the License at
/
/  http:/www.apache.org/licenses/LICENSE-2.0
/ 
/  Unless required by applicable law or agreed to in writing, software
/  distributed under the License is distributed on an "AS IS" BASIS,
/  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/  See the License for the specific language governing permissions and
/  limitations under the License.
/ =========----------------------------------------------------------=========/ 

/ Memory and string operations

/ str6.s

.text

/ memset: The memset() function fills the first n bytes of the memory area 
/ pointed to by s with the constant byte c.
/ C: void *memset(void *s, int c, unsigned int n);
.align 16
.globl	memset
.type	memset, @function
memset:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	16(%ebp), %ebx
	movl	8(%ebp), %esi
	cmpl	$11, %ebx
	jbe	.L27
	movzbl	12(%ebp), %edi
	xorl	%eax, %eax
	movl	%esi, %ecx
	movl	%edi, %edx
	sall	$8, %edx
	orl	%edi, %edx
	testl	%edi, %edi
	cmove	%eax, %edx
	movl	%esi, %eax
	andl	$3, %ecx
	je	.L6
	movl	$4, %eax
	leal	-4(%ecx,%ebx), %ebx
	subl	%ecx, %eax
	movl	%eax, -28(%ebp)
	je	.L8
	xorl	%ecx, %ecx
.L7:
	movl	%edi, %eax
	movb	%al, (%esi,%ecx)
	addl	$1, %ecx
	cmpl	-28(%ebp), %ecx
	jb	.L7
.L8:
	movl	-28(%ebp), %eax
	addl	%esi, %eax
.L6:
	movl	%ebx, %ecx
	andl	$-4, %ecx
	addl	%eax, %ecx
	.align 16
.L9:
	movl	%edx, (%eax)
	addl	$4, %eax
	cmpl	%eax, %ecx
	jne	.L9
	andl	$3, %ebx
	je	.L16
	xorl	%eax, %eax
.L10:
	movl	%edi, %edx
	movb	%dl, (%ecx,%eax)
	addl	$1, %eax
	cmpl	%ebx, %eax
	jb	.L10
.L16:
	leal	-12(%ebp), %esp
	movl	%esi, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 16
.L27:
	testl	%ebx, %ebx
	je	.L16
	movzbl	12(%ebp), %eax
	subl	$4, %esp
	pushl	%ebx
	pushl	%eax
	pushl	%esi
	call	memset
	addl	$16, %esp
	leal	-12(%ebp), %esp
	movl	%esi, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	memset, .-memset


/ bzero: void bzero(void *s, unsigned int n);
.align 16
.globl	bzero
.type	bzero, @function
bzero:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	12(%ebp), %ebx
	movl	8(%ebp), %esi
	cmpl	$11, %ebx
	jbe	.L51
	movl	%esi, %eax
	andl	$3, %eax
	je	.L31
	movl	$4, %edx
	leal	-4(%eax,%ebx), %ebx
	subl	%eax, %edx
	je	.L33
	xorl	%eax, %eax
.L32:
	movb	$0, (%esi,%eax)
	addl	$1, %eax
	cmpl	%edx, %eax
	jb	.L32
.L33:
	addl	%edx, %esi
.L31:
	movl	%ebx, %edi
	subl	$4, %esp
	andl	$-4, %edi
	pushl	%edi
	pushl	$0
	pushl	%esi
	addl	%edi, %esi
	call	memset
	addl	$16, %esp
	andl	$3, %ebx
	je	.L28
	xorl	%eax, %eax
.L34:
	movb	$0, (%esi,%eax)
	addl	$1, %eax
	cmpl	%ebx, %eax
	jb	.L34
.L28:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 16
.L51:
	testl	%ebx, %ebx
	je	.L28
	subl	$4, %esp
	pushl	%ebx
	pushl	$0
	pushl	%esi
	call	memset
	addl	$16, %esp
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	bzero, .-bzero
