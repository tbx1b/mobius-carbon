#include <bogus/bogus.h>
#include <machine/arch.h>
#include <sched/pool.h>
#include <sched/switch.h>
#include <sched/user.h>
#include <types.h>
#include <uart.h>

#define STACK_SIZE 1024
i8 task0_stack[STACK_SIZE];
context_t ctx_os;
context_t ctx_task;

void user_task() {
  puts("Userland already!\n");
  while (1)
    ;
}

i32 kmain(void) {
  announce(); // print some bs on the screen

  user_init(); // load launch process(es)
  init_pool(); // start the scheduler

  while (1)
    ; // wait
  return 0;
}