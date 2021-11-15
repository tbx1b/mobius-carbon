// =========-------------------------- mmu.h  ------------------------=========//
//                       Copyright 2021 MobiusLoopFour
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
// 
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
// =========----------------------------------------------------------=========// 

#ifndef mmu_h_
#define mmu_h_

#define FL_IF           0x00000200
#define DPL_USER        0x3

/* control register */
#define CR0_PE          0x00000001      /* protection enable */
#define CR0_WP          0x00010000      /* write protect */
#define CR0_PG          0x80000000      /* paging */
#define CR4_PSE         0x00000010      /* PAE */

/* segments */
#define SEG_KCODE       1               /* kernel code */
#define SEG_KDATA       2               /* kernel data+stack */
#define SEG_UCODE       3               /* user code */
#define SEG_UDATA       4               /* user data+stack */
#define SEG_TSS         5               /* task state */
#define SEGAMNT         6               /* amount of segments */

#ifndef __ASSEMBLER__   /* C */

struct sdesc {
  unsigned int limi_lo  : 16;           /* low limit */
  unsigned int base_lo  : 16;           /* low base */
  unsigned int base_md  : 8;            /* mid base */
  unsigned int type     : 4;            /* type of segment */
  unsigned int rootless : 1;            /* is executive (0), is user (1) */
  unsigned int dpl      : 2;            /* priviledge level */
  unsigned int present  : 1;            /* is present */
  unsigned int limi_hi  : 4;            /* limit high bits */
  unsigned int store    : 1;            /* for the system to store anything in */
  unsigned int resv     : 1;            /* for Intel to store anything in */
  unsigned int i32      : 1;            /* is 32 bit */
  unsigned int gran     : 1;            /* granularity */
  unsigned int base_hi  : 8;            /* high base */
};

#define SEG(type, base, lim, dpl) (struct sdesc)    \
{ ((lim) >> 12) & 0xffff, (unsigned int)(base) & 0xffff,      \
  ((unsigned int)(base) >> 16) & 0xff, type, 1, dpl, 1,       \
  (unsigned int)(lim) >> 28, 0, 0, 1, 1, (unsigned int)(base) >> 24 }

#endif /* __ASSEMBLER__ */

/* app seg type bits */
#define ASBX            0x8             /* executable */
#define ASBW            0x2             /* writable/not executable */
#define ASBR            0x2             /* readable/executable */

/* sys seg type bits */

#define SSBX            0x9             /* 32 bit TSS */
#define SSBI            0xe             /* int gate */
#define SSBT            0xf             /* trap gate */

/* pagedir index */
#define PDX(va)         (((unsigned int)(va) >> PDXSHIFT) & 0x3FF)

/* pagetab index */
#define PTX(va)         (((unsigned int)(va) >> PTXSHIFT) & 0x3FF)

/* construct virtual address from indexes and offset */
#define PGADDR(d, t, o) ((unsigned int)((d) << PDXSHIFT | (t) << PTXSHIFT | (o)))

#ifndef __ASSEMBLER__
typedef unsigned int pte_t;
typedef pte_t pde_t;

struct taskstate {
  unsigned int link;         /* Old ts selector */
  unsigned int esp0;         /* Stack pointers and segment selectors */
  unsigned short ss0;        /*   after an increase in privilege level */
  unsigned short padding1;
  unsigned int *esp1;
  unsigned short ss1;
  unsigned short padding2;
  unsigned int *esp2;
  unsigned short ss2;
  unsigned short padding3;
  void *cr3;         /* Page directory base */
  unsigned int *eip;         /* Saved state from last task switch */
  unsigned int eflags;
  unsigned int eax;          /* More saved state (registers) */
  unsigned int ecx;
  unsigned int edx;
  unsigned int ebx;
  unsigned int *esp;
  unsigned int *ebp;
  unsigned int esi;
  unsigned int edi;
  unsigned short es;         /* Even more saved state (segment selectors) */
  unsigned short padding4;
  unsigned short cs;
  unsigned short padding5;
  unsigned short ss;
  unsigned short padding6;
  unsigned short ds;
  unsigned short padding7;
  unsigned short fs;
  unsigned short padding8;
  unsigned short gs;
  unsigned short padding9;
  unsigned short ldt;
  unsigned short padding10;
  unsigned short t;          /* Trap on task switch */
  unsigned short iomb;       /* I/O map base address */
};

struct gatedesc {
  unsigned int off_lo   : 16;   /* low 16 bits of offset in segment */
  unsigned int cs       : 16;   /* code segment selector*/
  unsigned int args     : 5;    /* # args, 0 for interrupt/trap gates*/
  unsigned int rsv1     : 3;    /* reserved(should be zero I guess)*/
  unsigned int type     : 4;    /* type(STS_{IG32,TG32})*/
  unsigned int s        : 1;    /* must be 0 (system)*/
  unsigned int dpl      : 2;    /* descriptor(meaning new) privilege level*/
  unsigned int p        : 1;    /* Present*/
  unsigned int off_hi   : 16;   /* high bits of offset in segment*/
} __attribute__((packed)) ;

/* Set up a normal interrupt/trap gate descriptor.
   - istrap: 1 for a trap (= exception) gate, 0 for an interrupt gate.
     interrupt gate clears FL_IF, trap gate leaves FL_IF alone
   - sel: Code segment selector for interrupt/trap handler
   - off: Offset in code segment for interrupt/trap handler
   - dpl: Descriptor Privilege Level -
          the privilege level required for software to invoke
          this interrupt/trap gate explicitly using an int instruction. */
#define SETGATE(gate, istrap, sel, off, d)                \
{                                                         \
  (gate).off_15_0 = (unsigned int)(off) & 0xffff;                 \
  (gate).cs = (sel);                                      \
  (gate).args = 0;                                        \
  (gate).rsv1 = 0;                                        \
  (gate).type = (istrap) ? STS_TG32 : STS_IG32;           \
  (gate).s = 0;                                           \
  (gate).dpl = (d);                                       \
  (gate).p = 1;                                           \
  (gate).off_31_16 = (unsigned int)(off) >> 16;                   \
}
#endif /* __ASSEMBLER__ */

#endif /* mmu_h_ */