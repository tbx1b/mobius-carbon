/* @(#) lmm_add_free.c */

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

void lmm_add_free(lmm_t *lmm, void *block, __size_t size)
{
	struct lmm_region *reg;
	__uintptr_t min = (__uintptr_t)block; 
	__uintptr_t max = min + size;

	/* Restrict the min and max further to be properly aligned.
	   Note that this is the opposite of what lmm_free() does,
	   because lmm_free() assumes the block was allocated with lmm_alloc()
	   and thus would be a subset of a larger, already-aligned free block.
	   Here we can assume no such thing.  */
	min = (min + ALIGN_MASK) & ~ALIGN_MASK;
	max &= ~ALIGN_MASK;
	assert(max >= min);

	/* If after alignment we have nothing left, we're done.  */
	if (max == min)
		return;

	/* Add the block to the free list(s) of whatever region(s) it overlaps.
	   If some or all of the block doesn't fall into any existing region,
	   then that memory is simply dropped on the floor.  */
	for (reg = lmm->regions; reg; reg = reg->next)
	{
		assert(reg->min < reg->max);
		assert((reg->min & ALIGN_MASK) == 0);
		assert((reg->max & ALIGN_MASK) == 0);

		if ((max > reg->min) && (min < reg->max))
		{
			__uintptr_t new_min = min, new_max = max;

			/* Only add the part of the block
			   that actually falls within this region.  */
			if (new_min < reg->min)
				new_min = reg->min;
			if (new_max > reg->max)
				new_max = reg->max;
			assert(new_max > new_min);

			/* Add the block.  */
			lmm_free(lmm, (void*)new_min, new_max - new_min);
		}
	}
}

