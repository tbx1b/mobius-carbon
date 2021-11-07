#include <hali86pc/seg.h>

INLINE void
fill_descriptor_base(struct x86_desc *desc, unsigned base)
{
	desc->base_low = base & 0xffff;
	desc->base_med = (base >> 16) & 0xff;
	desc->base_high = base >> 24;
}

INLINE void
fill_descriptor_limit(struct x86_desc *desc, unsigned limit)
{
	if (limit > 0xfffff)
	{
		limit >>= 12;
		desc->granularity |= SZ_G;
	}
	else
		desc->granularity &= ~SZ_G;
	desc->limit_low = limit & 0xffff;
	desc->limit_high = limit >> 16;
}


/* Fill a gate with particular values.  */
INLINE void
fill_gate(struct x86_gate *gate, unsigned offset, unsigned short selector,
	  unsigned char access, unsigned char word_count)
{
	gate->offset_low = offset & 0xffff;
	gate->selector = selector;
	gate->word_count = word_count;
	gate->access = access | ACC_P;
	gate->offset_high = (offset >> 16) & 0xffff;
}

INLINE void
fill_descriptor(struct x86_desc *desc, unsigned base, unsigned limit,
		unsigned char access, unsigned char sizebits)
{
	if (limit > 0xfffff)
	{
		limit >>= 12;
		sizebits |= SZ_G;
	}
	desc->limit_low = limit & 0xffff;
	desc->base_low = base & 0xffff;
	desc->base_med = (base >> 16) & 0xff;
	desc->access = access | ACC_P;
	desc->limit_high = limit >> 16;
	desc->granularity = sizebits;
	desc->base_high = base >> 24;
}