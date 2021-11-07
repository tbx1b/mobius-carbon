#include <hali86pc/anno/anno.h>
#include <hali86pc/trap.h>
#include <libcarbon/assert.h>

struct anno_table anno_intr;
struct anno_table anno_trap;

#define HZ 100

int
copy_recover(struct anno_entry *anno, struct trap_state *tstate)
{
	assert(tstate->eip == anno->val1);

	tstate->eip = anno->val3;
	return 0;
}

volatile unsigned int loop_intrs;
unsigned int loop_counts[128];
extern int loop_start[], loop_end[];

void
loop_recover(struct anno_entry *anno, struct trap_state *tstate)
{
	assert(tstate->eip >= anno->val1);
	assert(tstate->eip >= (unsigned)loop_start &&
	       tstate->eip < (unsigned)loop_end);

	if (loop_intrs >= 10*HZ) {
		tstate->eax = 0;
		return;
	}
	loop_counts[tstate->eip - (unsigned)loop_start]++;
}