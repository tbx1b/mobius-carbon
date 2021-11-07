/* __inline */ unsigned short get_ds(void)
{
	unsigned short ds;
	__asm__ volatile("movw %%ds,%w0" : "=r" (ds));
	return ds;
}

/* __inline */ void set_ds(unsigned short ds)
{
	__asm__ volatile("movw %w0,%%ds" : : "r" (ds));
}