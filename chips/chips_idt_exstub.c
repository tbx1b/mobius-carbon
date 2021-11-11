#include <stdint.h>
#include <stdio.h>

typedef struct {
  uint32_t ip;
  uint32_t cs;
  uint32_t flags;
  uint32_t sp;
  uint32_t ss;
} interrupt_frame_t;

__attribute__((interrupt)) void exstub(interrupt_frame_t * frame) {
  //printf_("Got interrupt: %d (errno: %d)\n");
  __asm__ volatile("iret");
  //__builtin_unreachable();
}
