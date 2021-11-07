/* @(#) lmm_find_free.c */

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

void lmm_find_free(lmm_t *lmm, __uintptr_t *inout_addr,
		   __size_t *out_size, lmm_flags_t *out_flags)
{
	struct lmm_region *reg;
	__uintptr_t start_addr = (*inout_addr + ALIGN_MASK) & ~ALIGN_MASK;
	__uintptr_t lowest_addr = (__uintptr_t)-1;
	__size_t lowest_size = 0;
	unsigned lowest_flags = 0;

	for (reg = lmm->regions; reg; reg = reg->next)
	{
		struct lmm_node *node;

		if ((reg->nodes == 0)
		    || (reg->max <= start_addr)
		    || (reg->min > lowest_addr))
			continue;

		for (node = reg->nodes; node; node = node->next)
		{
			assert((__uintptr_t)node >= reg->min);
			assert((__uintptr_t)node < reg->max);

			if ((__uintptr_t)node >= lowest_addr)
				break;
			if ((__uintptr_t)node + node->size > start_addr)
			{
				if ((__uintptr_t)node > start_addr)
				{
					lowest_addr = (__uintptr_t)node;
					lowest_size = node->size;
				}
				else
				{
					lowest_addr = start_addr;
					lowest_size = node->size
						- (lowest_addr - (__uintptr_t)node);
				}
				lowest_flags = reg->flags;
				break;
			}
		}
	}

	*inout_addr = lowest_addr;
	*out_size = lowest_size;
	*out_flags = lowest_flags;
}

