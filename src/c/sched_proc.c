#include "machine/arch.h"
#include "sched/switch.h"
#include <bogus/bogus.h>
#include <sched/proc.h>
#include <types.h>

i64 __sched_top_task = 0;
i8 __sched_task_stk[MAX_TASKS][STACK_SIZE];

context_t __sched_ctx_tasks[MAX_TASKS];
context_t __sched_osctx;
context_t *__sched_cctx; // ptr to current context

i64 __sched_mk_task(void (*task)(void)) {

  i64 i = top_task++;
  __sched_ctx_tasks[i].ra = (reg_t)task;
  __sched_ctx_tasks[i].sp = (reg_t)&__sched_task_stk[i][STACK_SIZE - 1];

  return i;
}

void __sched_init_task(i64 i) {
  __sched_cctx = &__sched_ctx_tasks[i];
  __sched_swtch(&__sched_osctx, &__sched_ctx_tasks[i]);
}

void __sched_ret_to_k() {
  context_t *ctx = __sched_cctx;
  __sched_cctx = &__sched_osctx;
  __sched_swtch(ctx, &__sched_osctx);
}