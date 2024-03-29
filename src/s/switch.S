.macro ctx_save base
    sw ra, 0(\base)
    sw sp, 4(\base)
    sw s0, 8(\base)
    sw s1, 12(\base)
    sw s2, 16(\base)
    sw s3, 20(\base)
    sw s4, 24(\base)
    sw s5, 28(\base)
    sw s6, 32(\base)
    sw s7, 36(\base)
    sw s8, 40(\base)
    sw s9, 44(\base)
    sw s10, 48(\base)
    sw s11, 52(\base)
.endm

.macro ctx_load base
    lw ra, 0(\base)
    lw sp, 4(\base)
    lw s0, 8(\base)
    lw s1, 12(\base)
    lw s2, 16(\base)
    lw s3, 20(\base)
    lw s4, 24(\base)
    lw s5, 28(\base)
    lw s6, 32(\base)
    lw s7, 36(\base)
    lw s8, 40(\base)
    lw s9, 44(\base)
    lw s10, 48(\base)
    lw s11, 52(\base)
.endm


.globl __sched_swtch
.align 4
__sched_swtch:
    ctx_save a0  # a0 => struct context *old
    ctx_load a1  # a1 => struct context *new
    ret          # pc=ra; swtch to new task (new->ra)