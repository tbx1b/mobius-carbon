#include <machine/arch.h>
#include <time.h>
#include <types.h>

void __kern_delay(volatile size count) {
  count *= 50000;
  while (count--)
    ;
}

/* get the core */
reg_t core_id() {
  reg_t r;
  __asm__ volatile("csrr %0, mhartid" : "=r"(r));
  return r;
}

reg_t __kern_rmstatus() {
  reg_t r;
  __asm__ volatile("csrr %0, mstatus" : "=r"(r));
  return r;
}

void __kern_wmstatus(reg_t x) { __asm__ volatile("csrw mstatus, %0" : : "r"(x)); }

void __kern_wmpec(reg_t r) { __asm__ volatile("csrw mepc, %0" : : "r"(r)); }

reg_t __kern_rmpec() {
  reg_t r;
  __asm__ volatile("csrr %0, mepc" : "=r"(r));
  return r;
}

void __kern_wmscratch(reg_t r) { asm volatile("csrw mscratch, %0" : : "r"(r)); }

void __kern_mtvec(reg_t x) { asm volatile("csrw mtvec, %0" : : "r"(x)); }

reg_t __kern_rmie() {
  reg_t r;
  asm volatile("csrr %0, mie" : "=r"(r));
  return r;
}

void __kern_wmie(reg_t r) { asm volatile("csrw mie, %0" : : "r"(r)); }

static i64 timer_count = 0;
static const i64 interval = 10000000;

void timer_init()
{
  int id = core_id();
  *(reg_t*)CLINT_MTIMECMP(id) = *(reg_t*)CLINT_MTIME + interval;
  __kern_mtvec((reg_t)sys_timer);
  __kern_wmstatus(__kern_rmstatus() | MIE);
  __kern_wmie(__kern_rmie() | MIE_MTIE);
}

reg_t timer_handler(reg_t epc, reg_t cause)
{
  reg_t return_pc = epc;

  __kern_wmie(~((~__kern_rmie()) | (1 << 7)));

  int id = core_id();
  *(reg_t *)CLINT_MTIMECMP(id) = *(reg_t *)CLINT_MTIME + interval;

  __kern_wmie(__kern_rmie() | MIE_MTIE);
  return return_pc;
}