/*===---- idt.c - Sets up the IDT ------------------------------------------===
 *
 * Part of libcarbon, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#include <sys/defs.h>
#include <stdint.h>
#include <stddef.h>

#define _I_MAX 256

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idt_t;

typedef struct {
  uint16_t offset_lo;
  uint16_t sel;
  uint8_t _res;
  uint8_t attrs;
  uint16_t offfset_hi;
} __attribute__((packed)) idte_t;

__attribute__((aligned(0x10))) static idte_t gates[_I_MAX];
static idt_t idt;

static _Bool vectors[_I_MAX];

extern void* stubs[];

_Noreturn void exstub() {
  printf_("Got an interrupt\n");
  while (1)
  __asm__ volatile ("cli; hlt");
}

void isetd(uint8_t vec, void * isr, uint8_t flags) {

  idte_t* d       = &gates[vec];
  d->offset_lo    = (uint32_t)isr & 0xffff;
  d->sel          = 0x08;
  d->attrs        = flags;
  d->_res         = 0;
  d->offfset_hi   = (uint32_t)isr >> 0x10;
}

int iinit() {

  __asm__ volatile ("cli");

  idt.base = (uintptr_t)&gates[0];
  idt.limit = (uint16_t)sizeof(idte_t) * _I_MAX - 1;
  for (uint8_t vector = 0; vector < 32; vector++) {
        isetd(vector, stubs[vector], 0x8E);
        vectors[vector] = 1;
    }

  __asm__ volatile ("lidtl %0" : : "m"(idt));
  __asm__ volatile ("sti");

  return(0);
}
