#include <hali86pc/trap.h>
#include <hali86pc/machine/eflags.h>
#include <hali86pc/machine/proc_reg.h>
#include <libcarbon/io.h>

void trap_dump(const struct trap_state *st)
{
	int from_user = (st->cs & 3) || (st->eflags & EFL_VM);
	int i;

	printf("Dump of trap_state at %p:\n", st);
	printf("EAX %08x EBX %08x ECX %08x EDX %08x\n",
		st->eax, st->ebx, st->ecx, st->edx);
	printf("ESI %08x EDI %08x EBP %08x ESP %08x\n",
		st->esi, st->edi, st->ebp,
		from_user ? st->esp : (unsigned)&st->esp);
	printf("EIP %08x EFLAGS %08x\n", st->eip, st->eflags);
	printf("CS %04x SS %04x DS %04x ES %04x FS %04x GS %04x\n",
		st->cs & 0xffff, from_user ? st->ss & 0xffff : get_ss(),
		st->ds & 0xffff, st->es & 0xffff,
		st->fs & 0xffff, st->gs & 0xffff);
	if (st->eflags & EFL_VM)
		printf("v86:            DS %04x ES %04x FS %04x GS %04x\n",
			st->v86_ds & 0xffff, st->v86_es & 0xffff,
			st->v86_gs & 0xffff, st->v86_gs & 0xffff);
	printf("trapno %d, error %08x, from %s mode\n",
		st->trapno, st->err, from_user ? "user" : "kernel");
	if (st->trapno == T_PAGE_FAULT)
		printf("page fault linear address %08x\n", st->cr2);

	/* Dump the top of the stack too.  */
	if (!from_user)
	{
		for (i = 0; i < 32; i++)
		{
			printf("%08x%c", (&st->esp)[i],
				((i & 7) == 7) ? '\n' : ' ');
		}
	}
}