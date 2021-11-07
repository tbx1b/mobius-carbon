/* __inline */ unsigned short get_fs(void)
{
	unsigned short fs;
	__asm__ volatile("movw %%fs,%w0" : "=r" (fs));
	return fs;
}

/* __inline */ void set_fs(unsigned short fs)
{
	__asm__ volatile("movw %w0,%%fs" : : "r" (fs));
}