/* @(#) inout.S - 4.2.2 */

.globl _io_outb
.globl _io_inb

_io_outb:
    movb    8(%esp), %al
    movw    4(%esp), %dx
    outb    %al, %dx
    ret

_io_inb:
    movw    4(%esp), %dx
    inb     %dx, %al
    ret
/*! EOF */