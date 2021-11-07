/* __inline */ unsigned short get_cs(void)
{
	unsigned short cs;
	__asm__ volatile("movw %%cs,%w0" : "=r" (cs));
	return cs;
}