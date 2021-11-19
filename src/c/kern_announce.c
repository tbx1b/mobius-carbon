#include <bogus/bogus.h>
#include <uart.h>

void __kern_announce() {
  puts("[qemu] : <Ctrl+A>, <C>, \"q\"<Enter> to quit\n");
  puts("[krnl] : Initializing kernel\n");
  return;
}