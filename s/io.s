/ =========-------------------------- io.s  -------------------------=========/
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

// Send a byte
/ C prototype: void iooutb(unsigned short port, unsigned short data);
.globl iooutb
.type iooutb,@function

iooutb:
  movb  8(%esp), %al
  movw  4(%esp), %dx
  outb  %al, %dx
  retl
.size iooutb, . - iooutb


/ Receive a byte (in %eax)
/ C prototype: unsigned char ioinb(unsigned short port);
.globl ioinb
.type ioinb,@function

ioinb:
  movw  4(%esp), %dx
  inb   %dx, %al
  retl
.size ioinb, . - iooutb

/ EOF
.section .note.GNU-stack,"",%progbits