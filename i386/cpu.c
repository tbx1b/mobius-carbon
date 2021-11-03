void
halt()
{
    for (;;)
    __asm__("hlt");
}