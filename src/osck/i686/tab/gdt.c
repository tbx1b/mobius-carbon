/*
 * MODULE:          Tables
 * LICENSE:         GPL-3.0-or-later
 * PURPOSE:         Global Descriptor Table setup
 * COPYRIGHT:       Copyright MobiusLoopFour
 */

/* INCLUDES *******************************************************************/

#include <cdef.h>
#include <string.h>
#include <hal.h>

/* PRIVATE DATA STRUCTURES ****************************************************/

typedef struct gdt_descriptor {
    word		limit;
	word		base_lo;
	byte			base_mid;
	byte			flags;
	byte			grand;
	byte			base_hi;
} __attribute__((packed)) hal_i686_gdt_descriptor_t;

typedef struct gdt_r {
    word    limit;
    dword    base;
} __attribute__((packed)) hal_i686_gdt_r_t;

#define MAX_DESCRIPTORS					3
#define i686_GDT_DESC_ACCESS			0x0001			//00000001
#define i686_GDT_DESC_READWRITE			0x0002			//00000010
#define i686_GDT_DESC_EXPANSION			0x0004			//00000100
#define i686_GDT_DESC_EXEC_CODE			0x0008			//00001000
#define i686_GDT_DESC_CODEDATA			0x0010			//00010000
#define i686_GDT_DESC_DPL			    0x0060			//01100000
#define i686_GDT_DESC_MEMORY			0x0080			//10000000
#define i686_GDT_GRAND_LIMITHI_MASK		0x0f			//00001111
#define i686_GDT_GRAND_OS			    0x10			//00010000
#define i686_GDT_GRAND_32BIT			0x40			//01000000
#define i686_GDT_GRAND_4K			    0x80			//10000000

static hal_i686_gdt_descriptor_t _gdt[3];

static hal_i686_gdt_r_t   _gdtr;

/* PRIVATE FUNCTIONS **********************************************************/

static void 
hal_i686_gdt_install()
{
    __asm volatile("lgdt (%0)" :: "r" (&_gdtr));
}

static void
hal_i686_gdt_set_descr(
    dword i, 
    unsigned long long base,
    unsigned long long limit,
    byte access,
    byte gr)
{
    if (i > MAX_DESCRIPTORS)
        return;

    /* null the desc */
    memset((void*)&_gdt[i], 0, sizeof(hal_i686_gdt_descriptor_t));

#define gi _gdt[i]
    /* limit & base addrs */
    gi.base_lo      = base & 0xffff;
    gi.base_mid     = (base >> 16) & 0xff;
    gi.base_hi	    = (base >> 24) & 0xff;
    gi.limit        = limit & 0xffff;
    /* flags & granularity */
    gi.flags        = access;
    gi.grand        = (limit >> 16) & 0x0f;
    gi.grand       |= gr & 0xf0;
#undef gi
}

/* GLOBAL FUNCTIONS ***********************************************************/

hal_i686_gdt_init()
{
    _gdtr.limit     = (sizeof(hal_i686_gdt_descriptor_t) * MAX_DESCRIPTORS) - 1;
    _gdtr.base      = (dword)&_gdt[0];

#define set(a,b,c,d,e) hal_i686_gdt_set_descr(a,b,c,d,e)
    /* null descriptor */
    set(0, 0, 0, 0, 0);

    /* code descriptor */
    set(
        1, 0, 0xffffffff,
        i686_GDT_DESC_READWRITE|i686_GDT_DESC_EXEC_CODE|i686_GDT_DESC_CODEDATA|i686_GDT_DESC_MEMORY,
        i686_GDT_GRAND_4K|i686_GDT_GRAND_32BIT|i686_GDT_GRAND_LIMITHI_MASK
    );

    /* data descriptor */
    set(
        2, 0, 0xffffffff,
        i686_GDT_DESC_READWRITE|i686_GDT_DESC_CODEDATA|i686_GDT_DESC_MEMORY,
        i686_GDT_GRAND_4K|i686_GDT_GRAND_32BIT|i686_GDT_GRAND_LIMITHI_MASK
    );
#undef set

    hal_i686_gdt_install();
    return 0;
}
/* ! EOF */