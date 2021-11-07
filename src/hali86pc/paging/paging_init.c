#include <hali86pc/paging.h>
#include <libcarbon/assert.h>
#include <hali86pc/phys_lmm.h>
#include <hali86pc/paging.h>

void base_paging_init(void)
{
	if (ptab_alloc(&base_pdir_pa))
		fatalError("Can't allocate kernel page directory");

	if (pdir_map_range(base_pdir_pa, 0, 0, round_superpage(phys_mem_max),
		INTEL_PDE_VALID | INTEL_PDE_WRITE | INTEL_PDE_USER))
		fatalError("Can't direct-map physical memory");
}