/* @(#) tabs.c  - set up gdt and idt */

#include <libcarbon/core.h>
#include <libcarbon/io.h>
#include <libc/stdint.h>
#include <libc/string.h>
#include "tab.h"

/* load gd table */
extern MLTX_API void _vm_gld(
    gdt_t *gdt_ptr,
    uint32_t ds,
    uint32_t cs);

/* load id table */
extern MLTX_API void _vm_ild(uint32_t);

/* fileprivate gdt & idt entries */
static gdt_t gdt_ptr;
static gdt_entry_t gdt_ent[0x005];
static idt_t idt_ptr;
static idt_entry_t idt_ent[0x100];

static void MLTX_API
gdt_set_gate(
    uint32_t n,
    uint32_t base,
    uint32_t limit,
    uint8_t acc,
    uint8_t gran)
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

static void MLTX_API
idt_set_gate(
    uint8_t n,
    uint32_t base,
    uint16_t sel,
    uint8_t flgs)
{
    idt_ent[n].blo = base & 0xffff;
    idt_ent[n].bhi = (base >> 0x10) & 0xffff;

    idt_ent[n].sel = sel;
    idt_ent[n].zro = 0; /* always zero */

    idt_ent[n].flgs = flgs /* | 0x60 */;
#warning FIXME: Uncomment when switching rings
    return;
}

void MLTX_API
_vm_loadg()
{
    gdt_ptr.li = (sizeof(gdt_entry_t) * 5) - 1;

    gdt_ptr.ba = (uintptr_t)&gdt_ent;

    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    _vm_gld((gdt_t *)&gdt_ptr, 0x10, 0x08);

    trace("GDT loaded with no fault");

    return;
}

void MLTX_API
_vm_loadi()
{
    idt_ptr.li = sizeof(idt_entry_t) * 0x100 - /* really, intel? - 1?? */ 1;
    idt_ptr.ba = (uintptr_t)&idt_ent;

    memset(&idt_ent, 0, sizeof(idt_entry_t) * 0x100);

    /* handlers ... */

    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
    idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8E);
    idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8E);
    idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8E);
    idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8E);
    idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8E);
    idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8E);
    idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
    idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8E);
    idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);
    _vm_ild((uintptr_t)&idt_ptr);

    trace("IDT loaded with no fault");

    return;
}
