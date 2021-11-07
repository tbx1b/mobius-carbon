/* @(#) lmm_avail.c */

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

__size_t lmm_avail(lmm_t *lmm, lmm_flags_t flags)
{
	struct lmm_region *reg;
	__size_t count;

	count = 0;
	for (reg = lmm->regions; reg; reg = reg->next)
	{
		CHECKREGPTR(reg);

		/* Don't count inapplicable regions.  */
		if (flags & ~reg->flags)
			continue;

		count += reg->free;
	}
	return count;
}

