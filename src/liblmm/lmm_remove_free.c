/* @(#) lmm_remove_free.c */

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

void lmm_remove_free(lmm_t *lmm, void *block, __size_t block_size)
{
	__uintptr_t rstart = (__uintptr_t)block;
	__uintptr_t rend = rstart + block_size;
	assert(rend > rstart);

	while (rstart < rend)
	{
		__uintptr_t size;
		lmm_flags_t flags;
		void *ptr;

		lmm_find_free(lmm, &rstart, &size, &flags);
		assert(rstart >= (__uintptr_t)block);
		if ((size == 0) || (rstart >= rend))
			break;
		if (rstart + size > rend)
			size = rend - rstart;
		ptr = lmm_alloc_gen(lmm, size, flags, 0, 0,
				    rstart, size);
		assert((__uintptr_t)ptr == rstart);
	}
}

