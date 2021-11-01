/*
 * MODULE:          Tables
 * LICENSE:         GPL-3.0-or-later
 * PURPOSE:         Global Descriptor Table setup
 * COPYRIGHT:       Copyright MobiusLoopFour
 */

/* INCLUDES *******************************************************************/

#include <sys.h>
#include <carbon.h>
#include <hal.h>

/* PRIVATE DATA STRUCTURES ****************************************************/

#define i686_MAX_INTERRUPTS		256

//! must be in the format 0D110, where D is descriptor type
#define i686_IDT_DESC_BIT16		0x06	//00000110
#define i686_IDT_DESC_BIT32		0x0E	//00001110
#define i686_IDT_DESC_RING1		0x40	//01000000
#define i686_IDT_DESC_RING2		0x20	//00100000
#define i686_IDT_DESC_RING3		0x60	//01100000
#define i686_IDT_DESC_PRESENT	0x80	//10000000

typedef struct idt_descriptor {
	word			base_lo;
	word 			sel;
	byte			_ignore;
	byte 			flags;
	byte			base_hi;
} __attribute__((packed)) hal_idt_descriptor_t;

typedef struct {
	word			limit;
	dword			base;
} idt_r_t;
/*! EOF */