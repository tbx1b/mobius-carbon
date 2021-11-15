/ Send a byte
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