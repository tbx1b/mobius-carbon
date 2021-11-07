#ifndef _OSKIT_CONFIG_H_
#define _OSKIT_CONFIG_H_

/* Define to compile the OSKit for use with Knit.  */
#undef KNIT

/* Define if your assembler supports the %cr4 register. */
#define HAVE_CR4

/* Define if your assembler supports the debug registers. */
#undef HAVE_DEBUG_REGS

/* Define if your assembler supports the .p2align pseudo-op. */
#undef HAVE_P2ALIGN

/* Define if your assembler supports the .code16 pseudo-op. */
#define HAVE_CODE16

/* Define if your assembler supports the .code16gcc pseudo-op. */
#define HAVE_CODE16GCC

/* Define to the prefix your assembler requires in .code16 mode
   before an instruction that uses a 32-bit address. */
#define ADDR32 .code32

/* Define to the prefix your assembler requires in .code16 mode
   before an instruction that uses a 32-bit datum.  */
#define DATA32 .data32

/* Define if your assembler allows .space within .bss segments. */
#define HAVE_WORKING_BSS

/* Define if your compiler groks __attribute__((packed)) on structs. */
#define HAVE_PACKED_STRUCTS

/* Define if your compiler groks __attribute__((pure)). */
#define HAVE_PURE

/* Define if your compiler groks __attribute__((noreturn)). */
#define HAVE_NORETURN

/* Define if your compiler groks __attribute__((stdcall)). */
#define HAVE_STDCALL

/* Define if your compiler groks __attribute__((constructor)). */
#define HAVE_CONSTRUCTOR

#endif /* _OSKIT_CONFIG_H_ */