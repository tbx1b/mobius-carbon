#if !defined(_paging_h)
#define _paging_h

#include <libc/stddef.h>
#include <libc/stdint.h>
#include <libcarbon/core.h>
#include <hali86pc/paging.h>
#include <hali86pc/vm.h>
#include <hali86pc/machine/proc_reg.h>

#include <hali86pc/_internal.h>

#define INTEL_OFFMASK	0xfff	/* offset within page */
#define PDESHIFT	22	/* page descriptor shift */
#define PDEMASK		0x3ff	/* mask for page descriptor index */
#define PTESHIFT	12	/* page table shift */
#define PTEMASK		0x3ff	/* mask for page table index */

/*
 *	Convert linear offset to page descriptor/page table index
 */
#define lin2pdenum(a)	(((a) >> PDESHIFT) & PDEMASK)
#define lin2ptenum(a)	(((a) >> PTESHIFT) & PTEMASK)

/*
 *	Convert page descriptor/page table index to linear address
 */
#define pdenum2lin(a)	((uintptr_t)(a) << PDESHIFT)
#define ptenum2lin(a)	((uintptr_t)(a) << PTESHIFT)

/*
 *	Number of ptes/pdes in a page table/directory.
 */
#define NPTES	(ptoa(1)/sizeof(pt_entry_t))
#define NPDES	(ptoa(1)/sizeof(pt_entry_t))

/*
 *	Hardware pte bit definitions (to be used directly on the ptes
 *	without using the bit fields).
 */
#define INTEL_PTE_VALID		0x00000001
#define INTEL_PTE_WRITE		0x00000002
#define INTEL_PTE_USER		0x00000004
#define INTEL_PTE_WTHRU		0x00000008
#define INTEL_PTE_NCACHE 	0x00000010
#define INTEL_PTE_REF		0x00000020
#define INTEL_PTE_MOD		0x00000040
#define INTEL_PTE_GLOBAL	0x00000100
#define INTEL_PTE_AVAIL		0x00000e00
#define INTEL_PTE_PFN		0xfffff000

#define INTEL_PDE_VALID		0x00000001
#define INTEL_PDE_WRITE		0x00000002
#define INTEL_PDE_USER		0x00000004
#define INTEL_PDE_WTHRU		0x00000008
#define INTEL_PDE_NCACHE 	0x00000010
#define INTEL_PDE_REF		0x00000020
#define INTEL_PDE_MOD		0x00000040	/* only for superpages */
#define INTEL_PDE_SUPERPAGE	0x00000080
#define INTEL_PDE_GLOBAL	0x00000100	/* only for superpages */
#define INTEL_PDE_AVAIL		0x00000e00
#define INTEL_PDE_PFN		0xfffff000

/*
 *	Macros to translate between page table entry values
 *	and physical addresses.
 */
#define	pa_to_pte(a)		((a) & INTEL_PTE_PFN)
#define	pte_to_pa(p)		((p) & INTEL_PTE_PFN)
#define	pte_increment_pa(p)	((p) += INTEL_OFFMASK+1)

#define	pa_to_pde(a)		((a) & INTEL_PDE_PFN)
#define	pde_to_pa(p)		((p) & INTEL_PDE_PFN)
#define	pde_increment_pa(p)	((p) += INTEL_OFFMASK+1)

/*
 *	Superpage-related macros.
 */
#define SUPERPAGE_SHIFT		PDESHIFT
#define SUPERPAGE_SIZE		(1 << SUPERPAGE_SHIFT)
#define SUPERPAGE_MASK		(SUPERPAGE_SIZE - 1)

#define round_superpage(x)	((uintptr_t)((((uintptr_t)(x))	\
				+ SUPERPAGE_MASK) & ~SUPERPAGE_MASK))
#define trunc_superpage(x)	((uintptr_t)(((uintptr_t)(x))	\
				& ~SUPERPAGE_MASK))

#define	superpage_aligned(x)	((((uintptr_t)(x)) & SUPERPAGE_MASK) == 0)

#include <libcarbon/core.h>
#include <libc/stddef.h>
#include <libc/stdint.h>
#include <hali86pc/machine/proc_reg.h>

/*
 *	i386/i486/i860 Page Table Entry
 */
typedef unsigned int	pt_entry_t;
#define PT_ENTRY_NULL	((pt_entry_t *) 0)

typedef unsigned int	pd_entry_t;
#define PD_ENTRY_NULL	((pt_entry_t *) 0)

/*
 * Read and write the page directory base register (PDBR).
 */
#define set_pdbr(pdir)	set_cr3(pdir)
#define get_pdbr()	get_cr3()

/*
 * Invalidate the entire TLB.
 */
#define inval_tlb()	set_pdbr(get_pdbr())

INLINE void paging_enable(uintptr_t pdir);
INLINE void paging_disable(void);

/*
 * Load page directory 'pdir' and turn paging on.
 * Assumes that 'pdir' equivalently maps the physical memory
 * that contains the currently executing code,
 * the currently loaded GDT and IDT, etc.
 */
INLINE void paging_enable(uintptr_t pdir);

/*
 * Turn paging off.
 * Assumes that the currently loaded page directory
 * equivalently maps the physical memory
 * that contains the currently executing code,
 * the currently loaded GDT and IDT, etc.
 */
INLINE void paging_disable(void);

/*
 * Find the entry in a page directory or page table
 * for a particular linear address.
 */
#define pdir_find_pde(pdir_pa, la)					\
	(&((pd_entry_t*)phystokv(pdir_pa))[lin2pdenum(la)])
#define ptab_find_pte(ptab_pa, la)					\
	(&((pt_entry_t*)phystokv(ptab_pa))[lin2ptenum(la)])

/*
 * Find a page table entry given a page directory and a linear address.
 * Returns NULL if there is no page table covering that address.
 * Assumes that if there is a valid PDE, it's a page table, _not_ a 4MB page.
 */
INLINE pt_entry_t *pdir_find_pte(uintptr_t pdir_pa, uintptr_t la);

/*
 * Get the value of a page table entry,
 * or return zero if no such entry exists.
 * As above, doesn't check for 4MB pages.
 */
INLINE pt_entry_t pdir_get_pte(uintptr_t pdir_pa, uintptr_t la);

/*
 * Functions called by the following routines to allocate a page table.
 * Supplies a single page of CLEARED memory, by its physical address.
 * Returns zero if successful, nonzero on failure.
 * The default implementation simply allocates a page from the malloc_lmm,
 * returning -1 if the LMM runs out of memory.
 * This implementation can be overridden, of course.
 */
int ptab_alloc(uintptr_t *out_ptab_pa);

/*
 * A Page Directory looks just like a Page Table, on this machine!
 */
#define pdir_alloc(out_pa)	ptab_alloc(out_pa)
#define pdir_free(ptab_pa)	ptab_free(ptab_pa)

/*
 * Free a page table allocated using ptab_alloc().
 * The caller must ensure that it is not still in use in any page directories.
 */
void ptab_free(uintptr_t ptab_pa);


/*
 * Map a 4KB page into a page directory.
 * Calls ptab_alloc if a new page table needs to be allocated.
 * If ptab_alloc returns nonzero, pdir_map_page aborts with that value.
 * Otherwise, inserts the mapping and returns zero.
 * Doesn't check for 4MB pages.
 */
int pdir_map_page(uintptr_t pdir_pa, uintptr_t la, pt_entry_t mapping);

/*
 * Unmap a 4KB page from a page directory.
 * Invalidates the page table entry for the page containing the indicated
 * virtual address.  May call ptab_free to release page table resources.
 * Doesn't check for 4MB pages.
 */
void pdir_unmap_page(uintptr_t pdir_pa, uintptr_t la);


/*
 * Map a continuous range of virtual addresses
 * to a continuous range of physical addresses.
 * If the processor supports 4MB pages, uses them if possible.
 * Assumes that there are no valid mappings already in the specified range.
 * The 'mapping_bits' parameter must include INTEL_PTE_VALID,
 * and may include other permissions as desired.
 */
int pdir_map_range(uintptr_t pdir_pa, uintptr_t la, uintptr_t pa,
		   __size_t size, pt_entry_t mapping_bits);

/*
 * Change the permissions on an existing mapping range.
 * The 'new_mapping_bits' parameter must include INTEL_PTE_VALID,
 * and may include other permissions as desired.
 * Assumes that the mappings being changed were produced
 * by a previous call to pdir_map_range()
 * with identical linear address and size parameters.
 */
void pdir_prot_range(uintptr_t pdir_pa, uintptr_t la, __size_t size,
		     pt_entry_t new_mapping_bits);

/*
 * Unmap a continuous range of virtual addresses.
 * Assumes that the mappings being unmapped were produced
 * by a previous call to pdir_map_range()
 * with identical linear address and size parameters.
 */
void pdir_unmap_range(uintptr_t pdir_pa, uintptr_t la, __size_t size);

/*
 * Frees any unused page table pages associated with the indicated
 * page-aligned range in the given PDIR; the size is rounded up to whole pages.
 * Unused pages are those containing only invalid PTEs (resulting from
 * calls to unmap_page and unmap_range).  Used to reclaim page table resources.
 */
void pdir_clean_range(uintptr_t pdir_pa, uintptr_t la, __size_t size);

/*
 * These functions are primarily for debugging VM-related code:
 * they pretty-print a dump of a page directory or page table
 * and all their mappings.
 */
void pdir_dump(uintptr_t pdir_pa);
void ptab_dump(uintptr_t ptab_pa, uintptr_t base_la);

/*
 * Initialize a basic paged environment.
 * Sets up the base_pdir (see below) which direct maps
 * all physical memory from 0 to (at least) phys_mem_max.
 * The client can then modify this page directory or create others as needed.
 * The base physical memory mappings are accessible from user mode by default.
 */
void base_paging_init(void);

/*
 * Enable the basic paged environment on the current processor
 * using the base_pdir_pa.
 * Also enables superpages if appropriate.
 */
void base_paging_load(void);

/*
 * Physical address of the base page directory,
 * set up by base_paging_init().
 */
extern uintptr_t base_pdir_pa;

#endif