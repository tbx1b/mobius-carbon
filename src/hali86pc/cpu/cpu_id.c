#include <hali86pc/machine/eflags.h>
#include <hali86pc/machine/proc_reg.h>

#include <libc/string.h>
#include <hali86pc/_internal.h>

static void get_cache_config(struct cpu_info *id)
{
	unsigned ci[4];
	unsigned cicount = 0;
	unsigned ccidx = 0;

	do
	{
		unsigned i;

		cicount++;
		__asm__ volatile(
		"	cpuid\n"
		: "=a" (ci[0]), 
		  "=b" (ci[1]),
		  "=c" (ci[2]),
		  "=d" (ci[3])
		: "a" (2));

		for (i = 0; i < 4; i++)
		{
			unsigned reg = ci[i];
			if ((reg & (1 << 31)) == 0)
			{
				/* The low byte of EAX isn't a descriptor.  */
				if (i == 0)
					reg >>= 8;
				while (reg != 0)
				{
					if ((reg & 0xff) &&
					    (ccidx < sizeof(id->cache_config)))
					{
						id->cache_config[ccidx++] =
							reg & 0xff;
					}
					reg >>= 8;
				}
			}
		}
	}
	while (cicount < (ci[0] & 0xff));
}

void cpuid(struct cpu_info *out_id)
{
	int orig_eflags = get_eflags();

	memset(out_id, 0, sizeof(*out_id));

	/* Check for a dumb old 386 by trying to toggle the AC flag.  */
	set_eflags(orig_eflags ^ EFL_AC);
	if ((get_eflags() ^ orig_eflags) & EFL_AC)
	{
		/* It's a 486 or better.  Now try toggling the ID flag.  */
		set_eflags(orig_eflags ^ EFL_ID);
		if ((get_eflags() ^ orig_eflags) & EFL_ID)
		{
			int highest_val;

			/*
			 * CPUID is supported, so use it.
			 * First get the vendor ID string.
			 */
			__asm__ volatile(
			"	cpuid\n"
			: "=a" (highest_val),
			  "=b" (*((int*)(out_id->vendor_id+0))),
			  "=d" (*((int*)(out_id->vendor_id+4))),
			  "=c" (*((int*)(out_id->vendor_id+8)))
			: "a" (0));

			/* Now the feature information.  */
			if (highest_val >= 1)
			{
				__asm__ volatile(
				"	cpuid\n"
				: "=a" (*((int*)out_id)),
				  "=d" (out_id->feature_flags)
				: "a" (1)
				: "ebx", "ecx");
			}

			/* Cache and TLB information.  */
			if (highest_val >= 2)
				get_cache_config(out_id);
		}
		else
		{
			/* No CPUID support - it's an older 486.  */
			out_id->family = CPU_FAMILY_486;

			/* XXX detect FPU */
		}
	}
	else
	{
		out_id->family = CPU_FAMILY_386;

		/* XXX detect FPU */
	}

	set_eflags(orig_eflags);
}

