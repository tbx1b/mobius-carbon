/* @(#) lmm.h */

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

#include <assert.h>

#ifndef _OSKIT_LMM_H_
#define _OSKIT_LMM_H_

#include <libcarbon/core.h>
#include <libc/limits.h>
#include <libc/stdint.h>

typedef __uint32_t lmm_flags_t;
typedef __uint32_t lmm_pri_t;

/* The contents of these structures are opaque to users.  */
typedef struct lmm_region
{
	struct lmm_region *next;

	/* List of free memory blocks in this region.  */
	struct lmm_node *nodes;

	/* Virtual addresses of the start and end of the memory region.  */
	uintptr_t min;
	uintptr_t max;

	/* Attributes of this memory.  */
	lmm_flags_t flags;

	/* Allocation priority of this region with respect to other regions.  */
	lmm_pri_t pri;

	/* Current amount of free space in this region in bytes.  */
	__size_t free;
} lmm_region_t;

typedef struct lmm
{
	struct lmm_region *regions;
} lmm_t;

#define LMM_INITIALIZER { 0 }

_CARBON_BEGIN_DECLS

void lmm_init(lmm_t *lmm);

void lmm_add_region(lmm_t *lmm, lmm_region_t *lmm_region,
		    void *addr, __size_t size,
		    lmm_flags_t flags, lmm_pri_t pri);

void lmm_add_free(lmm_t *lmm, void *block, __size_t size);
void lmm_remove_free(lmm_t *lmm, void *block, __size_t size);
void *lmm_alloc(lmm_t *lmm, __size_t size, lmm_flags_t flags);
void *lmm_alloc_aligned(lmm_t *lmm, __size_t size, lmm_flags_t flags,
			int align_bits, uintptr_t align_ofs);
void *lmm_alloc_page(lmm_t *lmm, lmm_flags_t flags);
void *lmm_alloc_gen(lmm_t *lmm, __size_t size, lmm_flags_t flags,
		    int align_bits, uintptr_t align_ofs,
		    uintptr_t bounds_min, uintptr_t bounds_max);
__size_t lmm_avail(lmm_t *lmm, lmm_flags_t flags);
void lmm_find_free(lmm_t *lmm, uintptr_t *inout_addr,
		   __size_t *out_size, lmm_flags_t *out_flags);
void lmm_free(lmm_t *lmm, void *block, __size_t size);
void lmm_free_page(lmm_t *lmm, void *block);

/* Only available if debugging turned on.  */
void lmm_dump(lmm_t *lmm);
void lmm_stats(lmm_t *lmm);
_CARBON_BEGIN_DECLS

struct lmm_node
{
	struct lmm_node *next;
	__size_t size;
};

#define ALIGN_SIZE	sizeof(struct lmm_node)
#define ALIGN_MASK	(ALIGN_SIZE - 1)

#define CHECKREGPTR(p)	do { \
	assert((reg->nodes == 0 && reg->free == 0) \
	       || (uintptr_t)reg->nodes >= reg->min); \
	assert(reg->nodes == 0 || (uintptr_t)reg->nodes < reg->max); \
	assert(reg->free >= 0); \
	assert(reg->free <= reg->max - reg->min); \
} while(0);
#endif /* _OSKIT_LMM_H_ */