#include <sched/proc.h>
#include <sched/switch.h>

void __sched_init_pool() {
  int current_task = 0;
  while (1) {
    __sched_init_task(current_task);
    current_task = (current_task + 1) % __sched_top_task;
  }
}