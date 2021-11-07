/* @(#) ild.S - load the idt */

.globl _vm_ild

_vm_ild:
    mov 4(%esp), %eax
    lidt (%eax)
    ret

/*! EOF */