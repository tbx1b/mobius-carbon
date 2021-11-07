void
memcpy(void *dst, const void *src, unsigned len)
{
    const char *s = src;
    char *d = dst;

    while (len--)
        *d++ = *s++;
}