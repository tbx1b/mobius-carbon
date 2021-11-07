/* __inline */ unsigned short get_es(void)
{
	unsigned short es;
	__asm__ volatile("movw %%es,%w0" : "=r" (es));
	return es;
}

/* __inline */ void set_es(unsigned short es)
{
	__asm__ volatile("movw %w0,%%es" : : "r" (es));
}