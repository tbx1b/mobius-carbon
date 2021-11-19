#pragma once

#include "risc32/machine/arch.h"

extern void __sched_timer();
extern void __sched_swtch(context_t *ctx_old, context_t *ctx_new);

#define timer __sched_timer
#define swtch __sched_swtch