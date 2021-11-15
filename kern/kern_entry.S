#include <sys/offset.h>
#include <chips/mmu.h>

.code32

.p2align 2
.text
.globl multiboot_header
multiboot_header:
  #define magic 0x1badb002
  #define flags 0
  .long magic
  .long flags
  .long (-magic-flags)

.globl _start
_start = entry

.globl entry
entry:
  # Turn on page size extension for 4Mbyte pages
  movl    %cr4, %eax
  orl     $(CR4_PSE), %eax
  movl    %eax, %cr4

  # Set up stacl
  movl $kernel_stack, %esp

  calll kmain

1:
  cli
  hlt
  jmp 1b

.section .bss, "aw"
.space 8192 * 2
kernel_stack: