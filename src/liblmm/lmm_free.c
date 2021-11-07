/* @(#) lmm_free.c */

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

void lmm_free(lmm_t *lmm, void *block, __size_t size)
{
	struct lmm_region *reg;
	struct lmm_node *node = (struct lmm_node*)
				((__uintptr_t)block & ~ALIGN_MASK);
	struct lmm_node *prevnode, *nextnode;

	assert(lmm != 0);
	assert(block != 0);
	assert(size > 0);

	size = (((__uintptr_t)block & ALIGN_MASK) + size + ALIGN_MASK)
		& ~ALIGN_MASK;

	/* First find the region to add this block to.  */
	for (reg = lmm->regions; ; reg = reg->next)
	{
		assert(reg != 0);
		CHECKREGPTR(reg);

		if (((__uintptr_t)node >= reg->min)
		    && ((__uintptr_t)node < reg->max))
			break;
	}

	/* Record the newly freed space in the region's free space counter.  */
	reg->free += size;
	assert(reg->free <= reg->max - reg->min);

	/* Now find the location in that region's free list
	   at which to add the node.  */
	for (prevnode = 0, nextnode = reg->nodes;
	     (nextnode != 0) && (nextnode < node);
	     prevnode = nextnode, nextnode = nextnode->next);

	/* Coalesce the new free chunk into the previous chunk if possible.  */
	if ((prevnode) &&
	    ((__uintptr_t)prevnode + prevnode->size >= (__uintptr_t)node))
	{
		assert((__uintptr_t)prevnode + prevnode->size
		       == (__uintptr_t)node);

		/* Coalesce prevnode with nextnode if possible.  */
		if (((__uintptr_t)nextnode)
		    && ((__uintptr_t)node + size >= (__uintptr_t)nextnode))
		{
			assert((__uintptr_t)node + size
			       == (__uintptr_t)nextnode);

			prevnode->size += size + nextnode->size;
			prevnode->next = nextnode->next;
		}
		else
		{
			/* Not possible -
			   just grow prevnode around newly freed memory.  */
			prevnode->size += size;
		}
	}
	else
	{
		/* Insert the new node into the free list.  */
		if (prevnode)
			prevnode->next = node;
		else
			reg->nodes = node;

		/* Try coalescing the new node with the nextnode.  */
		if ((nextnode) &&
		    (__uintptr_t)node + size >= (__uintptr_t)nextnode)
		{
			node->size = size + nextnode->size;
			node->next = nextnode->next;
		}
		else
		{
			node->size = size;
			node->next = nextnode;
		}
	}
}

