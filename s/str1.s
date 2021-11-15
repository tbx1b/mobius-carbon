/ =========------------------------- str1.s -------------------------=========/
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

/ strlen: Get the length of an .asciz string
/ C: int strlen(const char *str);
.text
.align 16
.globl	strlen
.type	strlen, @function
strlen:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%ebx
	movl	8(%ebp), %ebx
	cmpb	$0, (%ebx)
	je	.L1
	xorl	%edx, %edx
	.align 16
.L3:
	addl	$1, %eax
	adcl	$0, %edx
	cmpb	$0, (%ebx,%eax)
	jne	.L3
.L1:
	movl	-4(%ebp), %ebx
	leave
	ret
	.size	strlen, .-strlen

/ Compare two memory regions
/ C: int memcmp(const void *s1, const void *s2, unsigned n);
.align 16
.globl	memcmp
.type	memcmp, @function
memcmp:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%esi
	movl	16(%ebp), %esi
	movl	8(%ebp), %edx
	pushl	%ebx
	movl	12(%ebp), %ecx
	testl	%esi, %esi
	je	.L8
	addl	%edx, %esi
	jmp	.L11
	.align 16
.L10:
	cmpl	%esi, %edx
	je	.L16
.L11:
	movzbl	(%edx), %eax
	movzbl	(%ecx), %ebx
	addl	$1, %edx
	addl	$1, %ecx
	cmpb	%bl, %al
	je	.L10
	subl	%ebx, %eax
.L8:
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 16
.L16:
	popl	%ebx
	xorl	%eax, %eax
	popl	%esi
	popl	%ebp
	ret
	.size	memcmp, .-memcmp
