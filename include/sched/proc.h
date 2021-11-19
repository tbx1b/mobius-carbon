#pragma once

#include <types.h>

#define STACK_SIZE 0x600

extern i64 __sched_top_task;
#define top_task __sched_top_task

// __sched_mk_task, __sched_init_task in a nice wrapper
extern i64 __sched_spawn(void (*task)(void));

extern i64 __sched_mk_task(void (*task)(void));
extern void __sched_init_task(i64 i);
extern void __sched_ret_to_k();

#define mk_task __sched_mk_task
#define init_task __sched_init_task
#define ret_to_k __sched_ret_to_k
#define spawn __sched_spawn