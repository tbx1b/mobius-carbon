/* @(#) lmm_alloc.c */

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

void *lmm_alloc(lmm_t *lmm, __size_t size, lmm_flags_t flags)
{
	struct lmm_region *reg;

	assert(lmm != 0);
	assert(size > 0);

	size = (size + ALIGN_MASK) & ~ALIGN_MASK;

	for (reg = lmm->regions; reg; reg = reg->next)
	{
		struct lmm_node **nodep, *node;

		CHECKREGPTR(reg);

		if (flags & ~reg->flags)
			continue;

		for (nodep = &reg->nodes;
		     (node = *nodep) != 0;
		     nodep = &node->next)
		{
			assert(((__uintptr_t)node & ALIGN_MASK) == 0);
			assert(((__uintptr_t)node->size & ALIGN_MASK) == 0);
			assert((node->next == 0) || (node->next > node));
			assert((__uintptr_t)node < reg->max);

			if (node->size >= size)
			{
				if (node->size > size)
				{
					struct lmm_node *newnode;

					/* Split the node and return its head */
					newnode = (struct lmm_node*)
							((void*)node + size);
					newnode->next = node->next;
					newnode->size = node->size - size;
					*nodep = newnode;
				}
				else
				{
					/* Remove and return the entire node. */
					*nodep = node->next;
				}

				/* Adjust the region's free memory counter.  */
				assert(reg->free >= size);
				reg->free -= size;

				return (void*)node;
			}
		}
	}

	return 0;
}

