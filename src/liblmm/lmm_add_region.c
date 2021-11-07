/* @(#) lmm_add_region.c */

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

void lmm_add_region(lmm_t *lmm, lmm_region_t *reg,
		    void *addr, __size_t size,
		    lmm_flags_t flags, lmm_pri_t pri)
{
	__uintptr_t min = (__uintptr_t)addr;
	__uintptr_t max = min + size;
	struct lmm_region **rp, *r;

	/* Align the start and end addresses appropriately.  */
	min = (min + ALIGN_MASK) & ~ALIGN_MASK;
	max &= ~ALIGN_MASK;

	/* If there's not enough memory to do anything with,
	   then just drop the region on the floor.
	   Since we haven't put it on the lmm's list,
	   we'll never see it again.  */
	if (max <= min)
		return;

	/* Initialize the new region header.  */
	reg->nodes = 0;
	reg->min = min;
	reg->max = max;
	reg->flags = flags;
	reg->pri = pri;
	reg->free = 0;

	/* Add the region to the lmm's region list in descending priority order.
	   For regions with the same priority, sort from largest to smallest
	   to reduce the average amount of list traversing we need to do.  */
	for (rp = &lmm->regions;
	     (r = *rp) && ((r->pri > pri) ||
	     		   ((r->pri == pri) &&
			    (r->max - r->min > reg->max - reg->min)));
	     rp = &r->next)
	{
		assert(r != reg);
		assert((reg->max <= r->min) || (reg->min >= r->max));
	}
	reg->next = r;
	*rp = reg;
}

