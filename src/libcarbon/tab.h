/* @(#) tab.h - gdt and idt data structures */

#if !defined(_tab_h)
#define _tab_h

#include <libc/stdint.h>
#include <libcarbon/core.h>

#define Pack(x) __attribute__((packed)) (x)

typedef struct
{
    uint16_t li;
    uint32_t ba;
} Pack(gdt_t);

typedef struct
{
    uint16_t llo;
    uint16_t blo;
    uint8_t bmd;
    uint8_t acc;
    uint8_t grn;
    uint8_t bhi;
} Pack(gdt_entry_t);

typedef struct
{
    uint16_t blo;
    uint16_t sel;
    uint8_t zro;
    uint8_t flgs;
    uint16_t bhi;
} Pack(idt_entry_t);

typedef struct
{
    uint16_t li;
    uint32_t ba;
} Pack(idt_t);

#undef Pack //(x)

extern MLTX_API void isr0();
extern MLTX_API void isr1();
extern MLTX_API void isr2();
extern MLTX_API void isr3();
extern MLTX_API void isr4();
extern MLTX_API void isr5();
extern MLTX_API void isr6();
extern MLTX_API void isr7();
extern MLTX_API void isr8();
extern MLTX_API void isr9();
extern MLTX_API void isr10();
extern MLTX_API void isr11();
extern MLTX_API void isr12();
extern MLTX_API void isr13();
extern MLTX_API void isr14();
extern MLTX_API void isr15();
extern MLTX_API void isr16();
extern MLTX_API void isr17();
extern MLTX_API void isr18();
extern MLTX_API void isr19();
extern MLTX_API void isr20();
extern MLTX_API void isr21();
extern MLTX_API void isr22();
extern MLTX_API void isr23();
extern MLTX_API void isr24();
extern MLTX_API void isr25();
extern MLTX_API void isr26();
extern MLTX_API void isr27();
extern MLTX_API void isr28();
extern MLTX_API void isr29();
extern MLTX_API void isr30();
extern MLTX_API void isr31();

#endif