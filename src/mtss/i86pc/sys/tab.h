/* @(#) tab.h - gdt and idt data structures */

#if !defined(_tab_h)
#define _tab_h

#include <std/stdint.h>
#include <core.h>

#include "reg.h"

typedef struct
{
    u16 li;
    u32 ba;
} pack(GlobalDescriptorTable);

typedef struct
{
    u16 llo;
    u16 blo;
    u8 bmd;
    u8 acc;
    u8 grn;
    u8 bhi;
} pack(GlobalDescriptorTableEntry);

typedef struct
{
    u16 blo;
    u16 sel;
    u8 zro;
    u8 flgs;
    u16 bhi;
} pack(IntDescriptorTableEntry);

typedef struct
{
    u16 li;
    u32 ba;
} pack(IntDescriptorTable);

extern MTSS_API void isr0();
extern MTSS_API void isr1();
extern MTSS_API void isr2();
extern MTSS_API void isr3();
extern MTSS_API void isr4();
extern MTSS_API void isr5();
extern MTSS_API void isr6();
extern MTSS_API void isr7();
extern MTSS_API void isr8();
extern MTSS_API void isr9();
extern MTSS_API void isr10();
extern MTSS_API void isr11();
extern MTSS_API void isr12();
extern MTSS_API void isr13();
extern MTSS_API void isr14();
extern MTSS_API void isr15();
extern MTSS_API void isr16();
extern MTSS_API void isr17();
extern MTSS_API void isr18();
extern MTSS_API void isr19();
extern MTSS_API void isr20();
extern MTSS_API void isr21();
extern MTSS_API void isr22();
extern MTSS_API void isr23();
extern MTSS_API void isr24();
extern MTSS_API void isr25();
extern MTSS_API void isr26();
extern MTSS_API void isr27();
extern MTSS_API void isr28();
extern MTSS_API void isr29();
extern MTSS_API void isr30();
extern MTSS_API void isr31();

extern MTSS_API void irq0 ();
extern MTSS_API void irq1 ();
extern MTSS_API void irq2 ();
extern MTSS_API void irq3 ();
extern MTSS_API void irq4 ();
extern MTSS_API void irq5 ();
extern MTSS_API void irq6 ();
extern MTSS_API void irq7 ();
extern MTSS_API void irq8 ();
extern MTSS_API void irq9 ();
extern MTSS_API void irq10();
extern MTSS_API void irq11();
extern MTSS_API void irq12();
extern MTSS_API void irq13();
extern MTSS_API void irq14();
extern MTSS_API void irq15();

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef void (*ISR)(Register);
void _os_register_irq_handler(u8 n, ISR handler);
#define register_irq_handler _os_register_irq_handler

#endif