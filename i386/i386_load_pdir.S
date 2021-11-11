#include <machine/asm.h>

FSYM(load_pdir)
GLOB(load_pdir)
  push %ebp
  mov %esp, %ebp
  mov 8(%esp), %eax
  mov %eax, %cr3
  mov %ebp, %esp
  pop %ebp
  ret