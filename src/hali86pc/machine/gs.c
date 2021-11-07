/* __inline */ unsigned short get_gs(void)
{
	unsigned short gs;
	__asm__ volatile("movw %%gs,%w0" : "=r" (gs));
	return gs;
}

/* __inline */ void set_gs(unsigned short gs)
{
	__asm__ volatile("movw %w0,%%gs" : : "r" (gs));
}
