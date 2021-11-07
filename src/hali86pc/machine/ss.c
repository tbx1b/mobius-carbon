/* __inline */ unsigned short get_ss(void)
{
	unsigned short ss;
	__asm__ volatile("movw %%ss,%w0" : "=r" (ss));
	return ss;
}

/* __inline */ void set_ss(unsigned short ss)
{
	__asm__ volatile("movw %w0,%%ss" : : "r" (ss));
}