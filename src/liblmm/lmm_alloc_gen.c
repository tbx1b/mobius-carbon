/* @(#) lmm_alloc_gen.c */

/*
 * Copyright (c) 2021 MobiusLoopFour. All rights reserved.
 *
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in the documentation and that are subject to the 
 * GNU GPL v3-Or-Later License. You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * https://www.gnu.org/licenses/gpl-3.0.en.html and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND ALL SUCH WARRANTIES ARE HEREBY DISCLAIMED,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 */

#include <liblmm/lmm.h>

void *lmm_alloc_gen(lmm_t *lmm, __size_t size, lmm_flags_t flags,
		    int align_bits, __uintptr_t align_ofs,
		    __uintptr_t in_min, __size_t in_size)
{
	__uintptr_t in_max = in_min + in_size;
	struct lmm_region *reg;

#if !1
	printf("lmm_alloc_gen %08x\n", size);
	lmm_dump(lmm);
#endif

	assert(lmm != 0);
	assert(size > 0);

	for (reg = lmm->regions; reg; reg = reg->next)
	{
		struct lmm_node **nodep, *node;

		CHECKREGPTR(reg);

		/* First trivially reject the entire region if possible.  */
		if ((flags & ~reg->flags) 
		    || (reg->min >= in_max)
		    || (reg->max <= in_min))
			continue;

		for (nodep = &reg->nodes;
		     (node = *nodep) != 0;
		     nodep = &node->next)
		{
			__uintptr_t addr;
			struct lmm_node *anode;
			int i;

			assert(((__uintptr_t)node & ALIGN_MASK) == 0);
			assert(((__uintptr_t)node->size & ALIGN_MASK) == 0);
			assert((node->next == 0) || (node->next > node));
			assert((__uintptr_t)node < reg->max);

			/* Now make a first-cut trivial elimination check
			   to skip chunks that are _definitely_ too small.  */
			if (node->size < size)
				continue;

			/* Now compute the address at which
			   the allocated chunk would have to start.  */
			addr = (__uintptr_t)node;
			if (addr < in_min)
				addr = in_min;
			for (i = 0; i < align_bits; i++)
			{
				__uintptr_t bit = (__uintptr_t)1 << i;
				if ((addr ^ align_ofs) & bit)
					addr += bit;
			}

			/* See if the block at the adjusted address
			   is still entirely within the node.  */
			if ((addr - (__uintptr_t)node + size) > node->size)
				continue;

			/* If the block extends past the range constraint,
			   then all of the rest of the nodes in this region
			   will extend past it too, so stop here. */
			if (addr + size > in_max)
				break;

			/* OK, we can allocate the block from this node.  */

			/* If the allocation leaves at least ALIGN_SIZE
			   space before it, then split the node.  */
			anode = (struct lmm_node*)(addr & ~ALIGN_MASK);
			assert(anode >= node);
			if (anode > node)
			{
				__size_t split_size = (__uintptr_t)anode
							- (__uintptr_t)node;
				assert((split_size & ALIGN_MASK) == 0);
				anode->next = node->next;
				anode->size = node->size - split_size;
				node->size = split_size;
				nodep = &node->next;
			}

			/* Now use the first part of the anode
			   to satisfy the allocation,
			   splitting off the tail end if necessary.  */
			size = ((addr & ALIGN_MASK) + size + ALIGN_MASK)
				& ~ALIGN_MASK;
			if (anode->size > size)
			{
				struct lmm_node *newnode;

				/* Split the node and return its head.  */
				newnode = (struct lmm_node*)
						((void*)anode + size);
				newnode->next = anode->next;
				newnode->size = anode->size - size;
				*nodep = newnode;
			}
			else
			{
				/* Remove and return the entire node.  */
				*nodep = anode->next;
			}

			/* Adjust the region's free memory counter.  */
			assert(reg->free >= size);
			reg->free -= size;

#if 0
			printf("lmm_alloc_gen returning %08x\n", addr);
			lmm_dump(lmm);
#endif

			return (void*)addr;
		}
	}

#if 0
	printf("lmm_alloc_gen failed\n");
#endif

	return 0;
}

