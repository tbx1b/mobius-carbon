/* @(#) tabs.c  - set up gdt and idt */

#include <core.h>
#include <std/stdint.h>
#include <std/string.h>
#include <sys/io.h>
#include "tab.h"

/* load gd table */
extern MTSS_API void _vm_gld(
    GlobalDescriptorTable *gdt_ptr,
    u32 ds,
    u32 cs);

/* load id table */
extern MTSS_API void _vm_ild(u32);

/* fileprivate gdt & idt entries */
static GlobalDescriptorTable gdt_ptr;
static GlobalDescriptorTableEntry gdt_ent[0x005];
static IntDescriptorTable idt_ptr;
static IntDescriptorTableEntry idt_ent[0x100];

static MTSS_API void
gdt_set_gate(
    u32 n,
    u32 base,
    u32 limit,
    u8 acc,
    u8 gran)
{
    gdt_ent[n].blo = (base & 0xffff);
    gdt_ent[n].bmd = (base >> 16) & 0xff;
    gdt_ent[n].bhi = (base >> 24) & 0xff;

    gdt_ent[n].llo = (limit & 0xffff);
    gdt_ent[n].grn = (limit >> 16) & 0x0f;

    gdt_ent[n].grn |= gran & 0xf0;
    gdt_ent[n].acc = acc;

    return;
}

static MTSS_API void
idt_set_gate(
    u8 n,
    u32 base,
    u16 sel,
    u8 flgs)
{
    idt_ent[n].blo = base & 0xffff;
    idt_ent[n].bhi = (base >> 0x10) & 0xffff;

    idt_ent[n].sel = sel;
    idt_ent[n].zro = 0; /* always zero */

    idt_ent[n].flgs = flgs /* | 0x60 */;
#warning FIXME: Uncomment when switching rings
    return;
}

MTSS_API void
_vm_loadg()
{
    gdt_ptr.li = (sizeof(GlobalDescriptorTableEntry) * 5) - 1;

    gdt_ptr.ba = (uptr)&gdt_ent;

    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    _vm_gld((GlobalDescriptorTable *)&gdt_ptr, 0x10, 0x08);

    return;
}

MTSS_API void
_vm_loadi()
{
    idt_ptr.li = sizeof(IntDescriptorTableEntry) * 0x100 - /* really, intel? - 1?? */ 1;
    idt_ptr.ba = (uptr)&idt_ent;

    memset(&idt_ent, 0, sizeof(IntDescriptorTableEntry) * 0x100);

    /* IRQ */

    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    /* handlers ... */

    idt_set_gate(0, (u32)isr0, 0x08, 0x8E);
    idt_set_gate(1, (u32)isr1, 0x08, 0x8E);
    idt_set_gate(2, (u32)isr2, 0x08, 0x8E);
    idt_set_gate(3, (u32)isr3, 0x08, 0x8E);
    idt_set_gate(4, (u32)isr4, 0x08, 0x8E);
    idt_set_gate(5, (u32)isr5, 0x08, 0x8E);
    idt_set_gate(6, (u32)isr6, 0x08, 0x8E);
    idt_set_gate(7, (u32)isr7, 0x08, 0x8E);
    idt_set_gate(8, (u32)isr8, 0x08, 0x8E);
    idt_set_gate(9, (u32)isr9, 0x08, 0x8E);
    idt_set_gate(10, (u32)isr10, 0x08, 0x8E);
    idt_set_gate(11, (u32)isr11, 0x08, 0x8E);
    idt_set_gate(12, (u32)isr12, 0x08, 0x8E);
    idt_set_gate(13, (u32)isr13, 0x08, 0x8E);
    idt_set_gate(14, (u32)isr14, 0x08, 0x8E);
    idt_set_gate(15, (u32)isr15, 0x08, 0x8E);
    idt_set_gate(16, (u32)isr16, 0x08, 0x8E);
    idt_set_gate(17, (u32)isr17, 0x08, 0x8E);
    idt_set_gate(18, (u32)isr18, 0x08, 0x8E);
    idt_set_gate(19, (u32)isr19, 0x08, 0x8E);
    idt_set_gate(20, (u32)isr20, 0x08, 0x8E);
    idt_set_gate(21, (u32)isr21, 0x08, 0x8E);
    idt_set_gate(22, (u32)isr22, 0x08, 0x8E);
    idt_set_gate(23, (u32)isr23, 0x08, 0x8E);
    idt_set_gate(24, (u32)isr24, 0x08, 0x8E);
    idt_set_gate(25, (u32)isr25, 0x08, 0x8E);
    idt_set_gate(26, (u32)isr26, 0x08, 0x8E);
    idt_set_gate(27, (u32)isr27, 0x08, 0x8E);
    idt_set_gate(28, (u32)isr28, 0x08, 0x8E);
    idt_set_gate(29, (u32)isr29, 0x08, 0x8E);
    idt_set_gate(30, (u32)isr30, 0x08, 0x8E);
    idt_set_gate(31, (u32)isr31, 0x08, 0x8E);
    idt_set_gate(32, (u32)irq0, 0x08, 0x8E);
    idt_set_gate(33, (u32)irq1, 0x08, 0x8E);
    idt_set_gate(34, (u32)irq2, 0x08, 0x8E);
    idt_set_gate(35, (u32)irq3, 0x08, 0x8E);
    idt_set_gate(36, (u32)irq4, 0x08, 0x8E);
    idt_set_gate(37, (u32)irq5, 0x08, 0x8E);
    idt_set_gate(38, (u32)irq6, 0x08, 0x8E);
    idt_set_gate(39, (u32)irq7, 0x08, 0x8E);
    idt_set_gate(40, (u32)irq8, 0x08, 0x8E);
    idt_set_gate(41, (u32)irq9, 0x08, 0x8E);
    idt_set_gate(42, (u32)irq10, 0x08, 0x8E);
    idt_set_gate(43, (u32)irq11, 0x08, 0x8E);
    idt_set_gate(44, (u32)irq12, 0x08, 0x8E);
    idt_set_gate(45, (u32)irq13, 0x08, 0x8E);
    idt_set_gate(46, (u32)irq14, 0x08, 0x8E);
    idt_set_gate(47, (u32)irq15, 0x08, 0x8E);
    _vm_ild((uptr)&idt_ptr);

    return;
}

ISR interrupt_handlers[256];

void _os_register_irq_handler(u8 n, ISR handler)
{
    printf("&addr = %p\n", &handler);
    interrupt_handlers[n] = handler;
}

void _os_irq_handler(Register regs)
{
    printf("What\n");
    if (regs.ino >= 40)
    {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);

    if (interrupt_handlers[regs.ino] != 0)
    {
        ISR handler = interrupt_handlers[regs.ino];
        handler(regs);
    }
}
