OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)

SECTIONS
{
    . = 0x1000;
    
    _k_start = .;
    
    .text : ALIGN(0x1000)
    {
        *(.text)
    }
    .rodata : ALIGN(0x1000)
    {
        *(.rodata)
    }
    .data : ALIGN(0x1000)
    {
        *(.data)
    }
    .bss : ALIGN(0x1000)
    {
        *(COMMON)
        *(.bss)
    }
    
    _k_end = .;
}
