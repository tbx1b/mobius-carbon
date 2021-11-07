/* @(#) lmm_stats.c */

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

#ifndef DEBUG
#define DEBUG
#endif

#include <libcarbon/io.h>
#include <liblmm/lmm.h>

void lmm_stats(lmm_t *lmm)
{
	struct lmm_region *reg;
	unsigned int regions, nodes, memfree;

	regions = nodes = memfree = 0;
	for (reg = lmm->regions; reg; reg = reg->next)
	{
		struct lmm_node *node;
		__size_t free_check;

		CHECKREGPTR(reg);

		regions++;

		free_check = 0;
		for (node = reg->nodes; node; node = node->next)
		{
			assert(((__uintptr_t)node & ALIGN_MASK) == 0);
			assert((node->size & ALIGN_MASK) == 0);
			assert(node->size >= sizeof(*node));
			assert((node->next == 0) || (node->next > node));
			assert((__uintptr_t)node < reg->max);

			nodes++;

			free_check += node->size;
		}
		assert(reg->free == free_check);

		memfree += reg->free;
	}

	printf("LMM=%p: %u bytes in %u regions, %d nodes\n",
	       lmm, memfree, regions, nodes);
}

