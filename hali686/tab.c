#include <carbon.h>
#include "tab.h"

extern void gdt_flush(dword);
extern void idt_flush(dword);

// Internal function prototypes.
static void init_gdt();
static void init_idt();
static void gdt_set_gate(int32,dword,dword,byte,byte);
static void idt_set_gate(byte, dword, word, byte);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

// Initialisation routine - zeroes all the interrupt service routines,
// initialises the GDT and IDT.
void 
hal_tab_init()
{

    // Initialise the global descriptor table.
    init_gdt();
    // Initialise the interrupt descriptor table.
    init_idt();

}

static void 
init_gdt()
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base  = (dword)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    gdt_flush((dword)&gdt_ptr);
}

// Set the value of one GDT entry.
static void 
gdt_set_gate(int32 num, dword base, dword limit, byte access, byte gran)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;
    
    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

static void 
init_idt()
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    idt_ptr.base  = (dword)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entry_t)*256);

    idt_set_gate( 0, (dword)isr0 , 0x08, 0x8E);
    idt_set_gate( 1, (dword)isr1 , 0x08, 0x8E);
    idt_set_gate( 2, (dword)isr2 , 0x08, 0x8E);
    idt_set_gate( 3, (dword)isr3 , 0x08, 0x8E);
    idt_set_gate( 4, (dword)isr4 , 0x08, 0x8E);
    idt_set_gate( 5, (dword)isr5 , 0x08, 0x8E);
    idt_set_gate( 6, (dword)isr6 , 0x08, 0x8E);
    idt_set_gate( 7, (dword)isr7 , 0x08, 0x8E);
    idt_set_gate( 8, (dword)isr8 , 0x08, 0x8E);
    idt_set_gate( 9, (dword)isr9 , 0x08, 0x8E);
    idt_set_gate(10, (dword)isr10, 0x08, 0x8E);
    idt_set_gate(11, (dword)isr11, 0x08, 0x8E);
    idt_set_gate(12, (dword)isr12, 0x08, 0x8E);
    idt_set_gate(13, (dword)isr13, 0x08, 0x8E);
    idt_set_gate(14, (dword)isr14, 0x08, 0x8E);
    idt_set_gate(15, (dword)isr15, 0x08, 0x8E);
    idt_set_gate(16, (dword)isr16, 0x08, 0x8E);
    idt_set_gate(17, (dword)isr17, 0x08, 0x8E);
    idt_set_gate(18, (dword)isr18, 0x08, 0x8E);
    idt_set_gate(19, (dword)isr19, 0x08, 0x8E);
    idt_set_gate(20, (dword)isr20, 0x08, 0x8E);
    idt_set_gate(21, (dword)isr21, 0x08, 0x8E);
    idt_set_gate(22, (dword)isr22, 0x08, 0x8E);
    idt_set_gate(23, (dword)isr23, 0x08, 0x8E);
    idt_set_gate(24, (dword)isr24, 0x08, 0x8E);
    idt_set_gate(25, (dword)isr25, 0x08, 0x8E);
    idt_set_gate(26, (dword)isr26, 0x08, 0x8E);
    idt_set_gate(27, (dword)isr27, 0x08, 0x8E);
    idt_set_gate(28, (dword)isr28, 0x08, 0x8E);
    idt_set_gate(29, (dword)isr29, 0x08, 0x8E);
    idt_set_gate(30, (dword)isr30, 0x08, 0x8E);
    idt_set_gate(31, (dword)isr31, 0x08, 0x8E);

    idt_flush((dword)&idt_ptr);
}

static void 
idt_set_gate(byte num, dword base, word sel, byte flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_entries[num].flags   = flags /* | 0x60 */;
    #warning FIXME uncomment the OR
}
/*! EOF */