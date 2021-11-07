#include <assert.h>
#include <hali86pc/paging.h>
#include <hali86pc/_internal.h>


int pdir_map_range(__uintptr_t pdir_pa, __uintptr_t la, __uintptr_t pa,
		   __size_t size, pt_entry_t mapping_bits)
{
	assert(mapping_bits & INTEL_PTE_VALID);
	assert(!(mapping_bits & INTEL_PTE_PFN));

	while (size > 0)
	{
		pd_entry_t *pde = pdir_find_pde(pdir_pa, la);

		/* Use a 4MB page if we can.  */
		if (superpage_aligned(la) && superpage_aligned(pa)
		    && (size >= SUPERPAGE_SIZE)
		    && (base_cpuid.feature_flags & CPUF_4MB_PAGES))
		{
			assert(!(*pde & INTEL_PDE_VALID));
			/* XXX what if an empty page table exists
			   from previous finer-granularity mappings? */
			*pde = pa | mapping_bits | INTEL_PDE_SUPERPAGE;
			la += SUPERPAGE_SIZE;
			pa += SUPERPAGE_SIZE;
			size -= SUPERPAGE_SIZE;
		}
		else
		{
			pt_entry_t *pte;

			/* Find the page table, creating one if necessary.  */
			if (!(*pde & INTEL_PDE_VALID))
			{
				__uintptr_t ptab_pa;
				int rc;

				/* Allocate a new page table.  */
				rc = ptab_alloc(&ptab_pa);
				if (rc)
					return rc;

				/* Set the pde to point to it.  */
				*pde = pa_to_pte(ptab_pa)
					| INTEL_PDE_VALID | INTEL_PDE_USER
					| INTEL_PDE_WRITE;
			}
			assert(!(*pde & INTEL_PDE_SUPERPAGE));
			pte = ptab_find_pte(pde_to_pa(*pde), la);

			/* Use normal 4KB page mappings.  */
			do
			{
				assert(!(*pte & INTEL_PTE_VALID));

				/* Insert the mapping.  */
				*pte = pa | mapping_bits;

				/* Advance to the next page.  */
				pte++;
				la += PAGE_SIZE;
				pa += PAGE_SIZE;
				size -= PAGE_SIZE;
			}
			while ((size > 0) && !superpage_aligned(la));
		}
	}

	return 0;
}
