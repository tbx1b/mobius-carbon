#define BASE_IRQ_MASTER_BASE 32
#define BASE_IRQ_SLAVE_BASE 40
#define BASE_IRQ_LEAVE_MASKED 1
#define BASE_IRQ_SKIP_SOFTINT 2
#define BASE_IRQ_SOFTINT_CLEARED 128
#define BASE_IRQ_SOFTINT_DISABLED 64


#define GATE_INITTAB_BEGIN(name)	\
	.data	2			;\
name:			;\
	.text

/*
 * Interrupt descriptor table and code vectors for it.
 */
#define	GATE_ENTRY(n,entry,type) \
	.data	2			;\
	.long	entry			;\
	.word	n			;\
	.word	type			;\
	.text

/*
 * Terminator for the end of the table.
 */
#define GATE_INITTAB_END		\
	.data	2			;\
	.long	0			;\
	.text
