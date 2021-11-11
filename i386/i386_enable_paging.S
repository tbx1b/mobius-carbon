
#include <machine/asm.h>

FSYM(enable_paging)
GLOB(enable_paging)
  push %ebp
  mov %esp, %ebp
  mov %cr0, %eax
  or $0x80000000, %eax
  mov %eax, %cr0
  mov %ebp, %esp
  pop %ebp
  ret

//DONE: .asciz "Done\n"