/ =========------------------------- str5.s -------------------------=========/
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

/ str5.s
.text

/ critical_factorization: internal fn
.align 16
.type	critical_factorization, @function
critical_factorization:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$20, %esp
	movl	%edx, -20(%ebp)
	movl	%ecx, -28(%ebp)
	cmpl	$1, %edx
	jbe	.L15
	movl	$1, %edi
	xorl	%ebx, %ebx
	movl	$-1, %esi
	movl	$1, %ecx
	movl	%edi, -24(%ebp)
	movl	$1, %edx
	movl	%esi, %edi
	movl	%ebx, -16(%ebp)
	jmp	.L7
	.align 16
.L22:
	movl	%edx, %esi
	movl	%edx, -16(%ebp)
	movl	$1, %ecx
	movl	%edx, %ebx
	subl	%edi, %esi
	movl	%esi, -24(%ebp)
.L4:
	leal	(%ebx,%ecx), %edx
	cmpl	%edx, -20(%ebp)
	jbe	.L21
.L7:
	leal	(%eax,%edi), %esi
	movzbl	(%esi,%ecx), %ebx
	cmpb	%bl, (%eax,%edx)
	jb	.L22
	je	.L23
	movl	-16(%ebp), %ecx
	movl	$1, -24(%ebp)
	leal	1(%ecx), %esi
	movl	%ecx, %edi
	movl	$1, %ecx
	movl	%esi, %ebx
	movl	%esi, -16(%ebp)
	leal	(%ebx,%ecx), %edx
	cmpl	%edx, -20(%ebp)
	ja	.L7
.L21:
	movl	-28(%ebp), %esi
	movl	%edi, -32(%ebp)
	xorl	%ebx, %ebx
	movl	$1, %ecx
	movl	-24(%ebp), %edi
	movl	%ebx, -16(%ebp)
	movl	$1, %edx
	movl	$1, -24(%ebp)
	movl	%edi, (%esi)
	movl	$-1, %esi
	jmp	.L13
	.align 16
.L25:
	movl	%edx, %ebx
	movl	%edx, -16(%ebp)
	movl	$1, %ecx
	subl	%esi, %ebx
	movl	%ebx, -24(%ebp)
	movl	%edx, %ebx
.L10:
	leal	(%ebx,%ecx), %edx
	cmpl	%edx, -20(%ebp)
	jbe	.L24
.L13:
	leal	(%eax,%ecx), %edi
	movzbl	(%edi,%esi), %ebx
	cmpb	%bl, (%eax,%edx)
	ja	.L25
	je	.L26
	movl	-16(%ebp), %edi
	movl	$1, %ecx
	movl	$1, -24(%ebp)
	movl	%edi, %esi
	addl	$1, %edi
	movl	%edi, %ebx
	movl	%edi, -16(%ebp)
	leal	(%ebx,%ecx), %edx
	cmpl	%edx, -20(%ebp)
	ja	.L13
.L24:
	movl	-32(%ebp), %eax
	addl	$1, %esi
	addl	$1, %eax
	cmpl	%eax, %esi
	jb	.L1
.L2:
	movl	-28(%ebp), %eax
	movl	-24(%ebp), %edi
	movl	%edi, (%eax)
	movl	%esi, %eax
.L1:
	addl	$20, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 16
.L23:
	cmpl	-24(%ebp), %ecx
	je	.L6
	movl	-16(%ebp), %ebx
	addl	$1, %ecx
	jmp	.L4
	.align 16
.L26:
	cmpl	-24(%ebp), %ecx
	je	.L12
	movl	-16(%ebp), %ebx
	addl	$1, %ecx
	jmp	.L10
	.align 16
.L6:
	addl	%ecx, -16(%ebp)
	movl	$1, %ecx
	movl	-16(%ebp), %ebx
	jmp	.L4
	.align 16
.L12:
	addl	%ecx, -16(%ebp)
	movl	$1, %ecx
	movl	-16(%ebp), %ebx
	jmp	.L10
	.align 16
.L15:
	movl	$1, -24(%ebp)
	xorl	%esi, %esi
	jmp	.L2
	.size	critical_factorization, .-critical_factorization


/ another internal function
.align 16
.type	two_way_long_needle, @function
two_way_long_needle:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	%ecx, %edi
	pushl	%esi
	leal	-1052(%ebp), %ecx
	pushl	%ebx
	subl	$1084, %esp
	movl	8(%ebp), %ebx
	movl	%eax, -1072(%ebp)
	movl	%edi, %eax
	movl	%edx, -1068(%ebp)
	movl	%ebx, %edx
	call	critical_factorization
	leal	-24(%ebp), %edx
	movl	%eax, -1084(%ebp)
	leal	-1048(%ebp), %eax
	.align 16
.L28:
	movl	%ebx, (%eax)
	addl	$4, %eax
	cmpl	%eax, %edx
	jne	.L28
	testl	%ebx, %ebx
	je	.L33
	leal	(%edi,%ebx), %edx
	movl	%edi, -1076(%ebp)
	movl	%edi, %eax
	leal	-1(%edi,%ebx), %esi
	movl	%edx, %edi
	.align 16
.L32:
	movzbl	(%eax), %edx
	movl	%esi, %ecx
	subl	%eax, %ecx
	addl	$1, %eax
	movl	%ecx, -1048(%ebp,%edx,4)
	cmpl	%eax, %edi
	jne	.L32
	movl	-1076(%ebp), %edi
.L33:
	movl	-1052(%ebp), %eax
	subl	$4, %esp
	pushl	-1084(%ebp)
	movl	%eax, -1092(%ebp)
	addl	%edi, %eax
	pushl	%eax
	pushl	%edi
	call	memcmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L90
	movl	$0, -1080(%ebp)
	movl	$1, %eax
	subl	-1084(%ebp), %eax
	movl	$0, -1076(%ebp)
	movl	%eax, -1096(%ebp)
	.align 16
.L30:
	movl	-1076(%ebp), %eax
	movl	-1068(%ebp), %ecx
	leal	(%eax,%ebx), %esi
	cmpl	%ecx, %esi
	jbe	.L45
	movl	-1072(%ebp), %eax
	subl	$8, %esp
	pushl	$512
	addl	%ecx, %eax
	pushl	%eax
	call	strnlen
	addl	%eax, -1068(%ebp)
	addl	$16, %esp
	movl	-1068(%ebp), %ecx
	cmpl	%ecx, %esi
	ja	.L89
.L45:
	movl	-1072(%ebp), %eax
	movzbl	-1(%eax,%esi), %eax
	movl	-1048(%ebp,%eax,4), %eax
	testl	%eax, %eax
	je	.L34
	movl	-1080(%ebp), %edx
	testl	%edx, %edx
	je	.L35
	movl	-1092(%ebp), %esi
	movl	%ebx, %edx
	cmpl	%eax, %esi
	seta	%cl
	subl	%esi, %edx
	testb	%cl, %cl
	cmovne	%edx, %eax
.L35:
	addl	%eax, -1076(%ebp)
	movl	$0, -1080(%ebp)
	jmp	.L30
	.align 16
.L34:
	movl	-1080(%ebp), %esi
	movl	-1084(%ebp), %eax
	leal	-1(%ebx), %edx
	movl	-1076(%ebp), %ecx
	cmpl	%eax, %esi
	cmovnb	%esi, %eax
	movl	-1072(%ebp), %esi
	addl	%esi, %ecx
	movl	%ebx, %esi
	cmpl	%edx, %eax
	jb	.L37
	jmp	.L38
	.align 16
.L39:
	addl	$1, %eax
	cmpl	%edx, %eax
	jnb	.L83
.L37:
	movzbl	(%ecx,%eax), %ebx
	cmpb	%bl, (%edi,%eax)
	je	.L39
	movl	-1076(%ebp), %edx
	addl	-1096(%ebp), %edx
	movl	%esi, %ebx
	movl	$0, -1080(%ebp)
	addl	%edx, %eax
	movl	%eax, -1076(%ebp)
	jmp	.L30
	.align 16
.L83:
	movl	%esi, %ebx
.L38:
	movl	-1084(%ebp), %edx
	movl	-1076(%ebp), %esi
	leal	-1(%edx), %eax
	leal	(%esi,%eax), %ecx
	leal	-1(%edi), %esi
	subl	%edx, %ecx
	addl	-1072(%ebp), %ecx
	cmpl	%edx, -1080(%ebp)
	jnb	.L41
	movl	%ebx, 8(%ebp)
	movl	-1080(%ebp), %ebx
	movl	%ebx, -1088(%ebp)
	jmp	.L57
	.align 16
.L42:
	leal	-1(%eax), %edx
	cmpl	%eax, -1088(%ebp)
	je	.L60
	movl	%edx, %eax
.L57:
	movzbl	1(%eax,%ecx), %ebx
	leal	1(%eax), %edx
	cmpb	%bl, 1(%esi,%eax)
	je	.L42
	movl	8(%ebp), %ebx
.L41:
	movl	-1080(%ebp), %eax
	addl	$1, %eax
	cmpl	%eax, %edx
	jb	.L91
	movl	-1092(%ebp), %esi
	movl	%ebx, %eax
	addl	%esi, -1076(%ebp)
	subl	%esi, %eax
	movl	%eax, -1080(%ebp)
	jmp	.L30
.L89:
	xorl	%eax, %eax
.L27:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.L60:
	movl	8(%ebp), %ebx
	movl	-1080(%ebp), %edx
	jmp	.L41
.L90:
	movl	-1084(%ebp), %edx
	movl	%ebx, %eax
	leal	-1(%ebx), %ecx
	movl	%ebx, 8(%ebp)
	movl	%ecx, %ebx
	subl	%edx, %eax
	cmpl	%edx, %eax
	cmovb	%edx, %eax
	xorl	%esi, %esi
	addl	$1, %eax
	movl	%eax, -1092(%ebp)
	leal	-1(%edx), %eax
	movl	%eax, -1088(%ebp)
	movl	$1, %eax
	subl	%edx, %eax
	movl	%eax, -1080(%ebp)
	.align 16
.L46:
	movl	8(%ebp), %edx
	movl	-1068(%ebp), %ecx
	addl	%esi, %edx
	cmpl	%ecx, %edx
	jbe	.L56
	movl	-1072(%ebp), %eax
	subl	$8, %esp
	movl	%edx, -1076(%ebp)
	pushl	$512
	addl	%ecx, %eax
	pushl	%eax
	call	strnlen
	movl	-1076(%ebp), %edx
	addl	%eax, -1068(%ebp)
	addl	$16, %esp
	movl	-1068(%ebp), %eax
	cmpl	%eax, %edx
	ja	.L89
.L56:
	movl	-1072(%ebp), %eax
	movzbl	-1(%eax,%edx), %eax
	movl	-1048(%ebp,%eax,4), %eax
	testl	%eax, %eax
	je	.L47
	addl	%eax, %esi
	jmp	.L46
	.align 16
.L47:
	movl	-1084(%ebp), %ecx
	movl	-1072(%ebp), %edx
	movl	%ecx, %eax
	addl	%esi, %edx
	cmpl	%ecx, %ebx
	ja	.L49
	jmp	.L50
	.align 16
.L51:
	addl	$1, %eax
	cmpl	%eax, %ebx
	jbe	.L50
.L49:
	movzbl	(%edx,%eax), %ecx
	cmpb	%cl, (%edi,%eax)
	je	.L51
	addl	-1080(%ebp), %esi
	addl	%eax, %esi
	jmp	.L46
	.align 16
.L50:
	movl	-1088(%ebp), %eax
	leal	(%esi,%eax), %edx
	cmpl	$-1, %eax
	je	.L53
	subl	-1084(%ebp), %edx
	movl	%ebx, -1076(%ebp)
	leal	-1(%edi), %ecx
	addl	-1072(%ebp), %edx
	jmp	.L58
	.align 16
.L54:
	subl	$1, %eax
	jb	.L53
.L58:
	movzbl	1(%eax,%edx), %ebx
	cmpb	%bl, 1(%ecx,%eax)
	je	.L54
	movl	-1076(%ebp), %ebx
	addl	-1092(%ebp), %esi
	jmp	.L46
.L91:
	movl	-1072(%ebp), %eax
	addl	-1076(%ebp), %eax
	jmp	.L27
.L53:
	movl	-1072(%ebp), %eax
	addl	%esi, %eax
	jmp	.L27
	.size	two_way_long_needle, .-two_way_long_needle
	

/ memchr: Locate character in block of memory
/ C: void * memchr (void const *s, int c_in, unsigned int n)
.align 16
.globl	memchr	
.type	memchr, @function
memchr:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	16(%ebp), %edx
	movl	8(%ebp), %eax
	pushl	%esi
	pushl	%ebx
	movzbl	12(%ebp), %ebx
	testl	%edx, %edx
	jne	.L109
	jmp	.L104
	.align 16
.L110:
	cmpb	%bl, (%eax)
	je	.L92
	addl	$1, %eax
	subl	$1, %edx
	je	.L104
.L109:
	testb	$3, %al
	jne	.L110
	movzbl	12(%ebp), %ecx
	movl	%ecx, %esi
	sall	$8, %esi
	orl	%esi, %ecx
	movl	%ecx, %edi
	sall	$16, %edi
	orl	%ecx, %edi
	cmpl	$3, %edx
	ja	.L97
	jmp	.L99
	.align 16
.L112:
	subl	$4, %edx
	addl	$4, %eax
	cmpl	$3, %edx
	jbe	.L111
.L97:
	movl	(%eax), %ecx
	xorl	%edi, %ecx
	leal	-16843009(%ecx), %esi
	notl	%ecx
	andl	%ecx, %esi
	andl	$-2139062144, %esi
	je	.L112
.L99:
	addl	%eax, %edx
	jmp	.L98
	.align 16
.L113:
	addl	$1, %eax
	cmpl	%edx, %eax
	je	.L104
.L98:
	cmpb	%bl, (%eax)
	jne	.L113
.L92:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 16
.L111:
	testl	%edx, %edx
	jne	.L99
.L104:
	popl	%ebx
	xorl	%eax, %eax
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	memchr, .-memchr
	

/ strchr: Locate first occurrence of character in string
/ C: char * strchr (const char *s, int c_in)
.align 16
.globl	strchr
.type	strchr, @function

strchr:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movzbl	12(%ebp), %ecx
	testb	$3, %al
	jne	.L117
	jmp	.L115
	.align 16
.L136:
	testb	%dl, %dl
	je	.L126
	addl	$1, %eax
	testb	$3, %al
	je	.L115
.L117:
	movzbl	(%eax), %edx
	cmpb	%cl, %dl
	jne	.L136
	movl	%eax, %esi
.L114:
	addl	$4, %esp
	movl	%esi, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 16
.L115:
	movzbl	12(%ebp), %edx
	movl	%edx, %ebx
	sall	$8, %ebx
	orl	%ebx, %edx
	movl	%edx, %ebx
	sall	$16, %ebx
	orl	%edx, %ebx
	movl	%ebx, -16(%ebp)
	.align 16
.L131:
	movl	%eax, %esi
	movl	-16(%ebp), %edi
	movl	(%eax), %ebx
	leal	4(%eax), %eax
	xorl	%ebx, %edi
	leal	2130640639(%ebx), %edx
	xorl	%ebx, %edx
	leal	2130640639(%edi), %ebx
	xorl	%edi, %ebx
	andl	%ebx, %edx
	orl	$2130640639, %edx
	cmpl	$-1, %edx
	je	.L131
	movzbl	-4(%eax), %edx
	cmpb	%cl, %dl
	je	.L114
	testb	%dl, %dl
	je	.L126
	movzbl	-3(%eax), %edx
	cmpb	%cl, %dl
	je	.L137
	testb	%dl, %dl
	je	.L126
	movzbl	-2(%eax), %edx
	cmpb	%cl, %dl
	je	.L138
	testb	%dl, %dl
	je	.L126
	movzbl	-1(%eax), %edx
	cmpb	%cl, %dl
	je	.L139
	testb	%dl, %dl
	jne	.L131
.L126:
	addl	$4, %esp
	xorl	%esi, %esi
	popl	%ebx
	movl	%esi, %eax
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.L137:
	addl	$1, %esi
	jmp	.L114
.L138:
	addl	$2, %esi
	jmp	.L114
.L139:
	addl	$3, %esi
	jmp	.L114
	.size	strchr, .-strchr


/ strstr: Locate substring
/ C: char * strstr (const char *haystack, const char *needle)
.align 16
.globl	strstr
.type	strstr, @function
strstr:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$76, %esp
	movl	12(%ebp), %esi
	movl	8(%ebp), %edx
	movsbl	(%esi), %eax
	testb	%al, %al
	je	.L172
	pushl	%eax
	pushl	%edx
	call	strchr
	popl	%ebx
	popl	%edi
	movl	%eax, -44(%ebp)
	movl	%eax, %edi
	testl	%eax, %eax
	je	.L140
	cmpb	$0, 1(%esi)
	je	.L140
	subl	$12, %esp
	pushl	%esi
	call	strlen
	popl	%edx
	popl	%ecx
	movl	%eax, %ebx
	leal	256(%eax), %eax
	pushl	%eax
	pushl	%edi
	call	strnlen
	addl	$16, %esp
	movl	%eax, -48(%ebp)
	movl	%eax, %edi
	cmpl	%eax, %ebx
	ja	.L173
	subl	$4, %esp
	pushl	%ebx
	pushl	%esi
	pushl	-44(%ebp)
	call	memcmp
	addl	$16, %esp
	testl	%eax, %eax
	je	.L140
	cmpl	$31, %ebx
	jbe	.L203
	movl	%ebx, 8(%ebp)
	movl	-44(%ebp), %eax
	leal	-12(%ebp), %esp
	movl	%esi, %ecx
	popl	%ebx
	movl	%edi, %edx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	two_way_long_needle
	.align 16
.L172:
	movl	%edx, -44(%ebp)
.L140:
	movl	-44(%ebp), %eax
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.L203:
	leal	-28(%ebp), %ecx
	movl	%ebx, %edx
	movl	%esi, %eax
	call	critical_factorization
	movl	-28(%ebp), %ecx
	subl	$4, %esp
	pushl	%eax
	movl	%eax, %edi
	movl	%eax, -56(%ebp)
	leal	(%esi,%ecx), %eax
	pushl	%eax
	pushl	%esi
	movl	%ecx, -76(%ebp)
	call	memcmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L195
	movl	$1, %eax
	movl	$0, -52(%ebp)
	xorl	%ecx, %ecx
	subl	%edi, %eax
	movl	%eax, -64(%ebp)
	.align 16
.L143:
	movl	-56(%ebp), %eax
	movl	-44(%ebp), %edi
	movl	-52(%ebp), %edx
	cmpl	%ecx, %eax
	cmovb	%ecx, %eax
	addl	%edi, %edx
	movl	%ecx, %edi
	cmpl	%eax, %ebx
	ja	.L145
	jmp	.L146
	.align 16
.L147:
	addl	$1, %eax
	cmpl	%eax, %ebx
	je	.L199
.L145:
	movzbl	(%edx,%eax), %ecx
	cmpb	%cl, (%esi,%eax)
	je	.L147
	movl	%edi, %ecx
	cmpl	%eax, %ebx
	jbe	.L146
	movl	-52(%ebp), %edx
	addl	-64(%ebp), %edx
	xorl	%ecx, %ecx
	addl	%edx, %eax
	movl	%eax, -52(%ebp)
.L154:
	movl	-52(%ebp), %eax
	movl	-48(%ebp), %edx
	leal	(%ebx,%eax), %edi
	cmpl	%edx, %edi
	jbe	.L143
	movl	-44(%ebp), %eax
	subl	$8, %esp
	movl	%ecx, -60(%ebp)
	pushl	$512
	addl	%edx, %eax
	pushl	%eax
	call	strnlen
	addl	%eax, -48(%ebp)
	movl	-48(%ebp), %edx
	addl	$16, %esp
	movl	-60(%ebp), %ecx
	cmpl	%edx, %edi
	jbe	.L143
.L173:
	movl	$0, -44(%ebp)
	movl	-44(%ebp), %eax
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.L195:
	movzbl	(%esi,%edi), %eax
	movl	%esi, -52(%ebp)
	movb	%al, -64(%ebp)
	movl	%ebx, %eax
	subl	%edi, %eax
	cmpl	%edi, %eax
	cmovb	%edi, %eax
	xorl	%ecx, %ecx
	movl	%ecx, %esi
	addl	$1, %eax
	movl	%eax, -76(%ebp)
	leal	1(%edi), %eax
	movl	%eax, -60(%ebp)
	leal	-1(%edi), %eax
	movl	%eax, -72(%ebp)
	movl	$1, %eax
	subl	%edi, %eax
	movl	%eax, -68(%ebp)
	.align 16
.L156:
	movl	-56(%ebp), %eax
	movl	-44(%ebp), %edi
	movzbl	-64(%ebp), %ecx
	addl	%esi, %eax
	addl	%edi, %eax
	leal	1(%eax), %edx
	cmpb	(%eax), %cl
	je	.L157
	subl	$8, %esp
	movzbl	%cl, %eax
	pushl	%eax
	pushl	%edx
	call	strchr
	addl	$16, %esp
	movl	%eax, %edx
	testl	%eax, %eax
	je	.L173
	movl	-56(%ebp), %eax
	movl	%edx, %esi
	addl	$1, %edx
	addl	%edi, %eax
	subl	%eax, %esi
.L157:
	movl	-60(%ebp), %eax
	cmpl	%eax, %ebx
	jbe	.L158
	movl	-52(%ebp), %edi
	addl	$1, %edi
	jmp	.L161
	.align 16
.L159:
	addl	$1, %eax
	cmpl	%eax, %ebx
	jbe	.L158
.L161:
	addl	$1, %edx
	movzbl	-1(%edx), %ecx
	cmpb	%cl, -1(%edi,%eax)
	je	.L159
	testb	%cl, %cl
	je	.L173
	movl	-44(%ebp), %ecx
	addl	-48(%ebp), %ecx
	cmpl	%ecx, %edx
	jbe	.L162
.L170:
	subl	-44(%ebp), %edx
	movl	%edx, -48(%ebp)
.L162:
	cmpl	%eax, %ebx
	jbe	.L171
	movl	-68(%ebp), %edi
	leal	(%edi,%esi), %edx
	leal	(%edx,%eax), %esi
.L169:
	movl	-48(%ebp), %ecx
	leal	(%ebx,%esi), %edi
	cmpl	%edi, %ecx
	jnb	.L156
	movl	-44(%ebp), %eax
	subl	$8, %esp
	pushl	$512
	addl	%ecx, %eax
	pushl	%eax
	call	strnlen
	addl	%eax, -48(%ebp)
	movl	-48(%ebp), %ecx
	addl	$16, %esp
	cmpl	%ecx, %edi
	jbe	.L156
	jmp	.L173
	.align 16
.L158:
	movl	-44(%ebp), %ecx
	addl	-48(%ebp), %ecx
	cmpl	%ecx, %edx
	ja	.L170
.L171:
	movl	-72(%ebp), %eax
	leal	(%eax,%esi), %ecx
	cmpl	$-1, %eax
	je	.L164
	movl	-52(%ebp), %edi
	subl	-56(%ebp), %ecx
	addl	-44(%ebp), %ecx
	subl	$1, %edi
	jmp	.L167
	.align 16
.L165:
	subl	$1, %eax
	jb	.L164
.L167:
	movzbl	1(%ecx,%eax), %edx
	cmpb	%dl, 1(%edi,%eax)
	je	.L165
	testb	%dl, %dl
	je	.L173
	addl	-76(%ebp), %esi
	jmp	.L169
	.align 16
.L199:
	movl	%edi, %ecx
.L146:
	movl	-56(%ebp), %eax
	movl	-52(%ebp), %edi
	subl	$1, %eax
	leal	(%eax,%edi), %edx
	subl	-56(%ebp), %edx
	leal	-1(%esi), %edi
	addl	-44(%ebp), %edx
	movl	%edx, -60(%ebp)
	movl	-56(%ebp), %edx
	cmpl	%ecx, -56(%ebp)
	jbe	.L150
	movl	%esi, -68(%ebp)
	movl	-60(%ebp), %esi
	movl	%ebx, -72(%ebp)
	jmp	.L149
	.align 16
.L151:
	leal	-1(%eax), %edx
	cmpl	%eax, %ecx
	je	.L175
	movl	%edx, %eax
.L149:
	movzbl	1(%eax,%esi), %ebx
	leal	1(%eax), %edx
	cmpb	%bl, 1(%edi,%eax)
	je	.L151
	movl	-68(%ebp), %esi
	movl	-72(%ebp), %ebx
.L150:
	leal	1(%ecx), %eax
	cmpl	%edx, %eax
	ja	.L204
	movl	-76(%ebp), %edi
	movl	%ebx, %ecx
	addl	%edi, -52(%ebp)
	subl	%edi, %ecx
	jmp	.L154
	.align 16
.L164:
	addl	%esi, -44(%ebp)
	movl	-44(%ebp), %eax
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 16
.L175:
	movl	-68(%ebp), %esi
	movl	-72(%ebp), %ebx
	movl	%ecx, %edx
	jmp	.L150
.L204:
	movl	-52(%ebp), %esi
	addl	%esi, -44(%ebp)
	jmp	.L140
	.size	strstr, .-strstr
