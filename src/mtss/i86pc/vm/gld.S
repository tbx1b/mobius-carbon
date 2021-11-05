/* @(#) gld.S - load the gdt */

.globl _vm_gld

_vm_gld:
    mov 4(%esp), %edx
    mov 8(%esp), %eax
    lgdt (%edx)
    mov %eax, %ds
    mov %eax, %es
    mov %eax, %gs
    mov %eax, %fs
    mov %eax, %ss

    pushl 12(%esp)
    push $.setcs
    ljmp *(%esp)

.setcs:
    add $8, %esp
    ret