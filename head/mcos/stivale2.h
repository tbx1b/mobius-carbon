/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Stivale 2 IDL
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

#ifndef __STIVALE__STIVALE2_H__
#define __STIVALE__STIVALE2_H__

//#include <stdint.h>
#include <Carbon.h>


#if (defined (_STIVALE2_SPLIT_64) && defined (__i386__)) || defined(_STIVALE2_SPLIT_64_FORCE)

#define _stivale2_split64(NAME) \
    union {                    \
        dword NAME;         \
        dword NAME##_lo;    \
    };                         \
    dword NAME##_hi

#else

#define _stivale2_split64(NAME) \
    dlongword NAME

#endif

// Anchor for non ELF kernels
struct stivale2_anchor {
    byte anchor[15];
    byte bits;
    _stivale2_split64(phys_load_addr);
    _stivale2_split64(phys_bss_start);
    _stivale2_split64(phys_bss_end);
    _stivale2_split64(phys_stivale2hdr);
};

struct stivale2_tag {
    dlongword identifier;
    _stivale2_split64(next);
};

/* --- Header --------------------------------------------------------------- */
/*  Information passed from the kernel to the bootloader                      */

struct stivale2_header {
    _stivale2_split64(entry_point);
    _stivale2_split64(stack);
    dlongword flags;
    _stivale2_split64(tags);
};

#define STIVALE2_HEADER_TAG_ANY_VIDEO_ID 0xc75c9fa92a44c4db

struct stivale2_header_tag_any_video {
    struct stivale2_tag tag;
    dlongword preference;
};

#define STIVALE2_HEADER_TAG_FRAMEBUFFER_ID 0x3ecc1bc43d0f7971

struct stivale2_header_tag_framebuffer {
    struct stivale2_tag tag;
    word framebuffer_width;
    word framebuffer_height;
    word framebuffer_bpp;
    word unused;
};

#define STIVALE2_HEADER_TAG_FB_MTRR_ID 0x4c7bb07731282e00

#define STIVALE2_HEADER_TAG_TERMINAL_ID 0xa85d499b1823be72

struct stivale2_header_tag_terminal {
    struct stivale2_tag tag;
    dlongword flags;
    _stivale2_split64(callback);
};

#define STIVALE2_TERM_CB_DEC 10
#define STIVALE2_TERM_CB_BELL 20
#define STIVALE2_TERM_CB_PRIVATE_ID 30
#define STIVALE2_TERM_CB_STATUS_REPORT 40
#define STIVALE2_TERM_CB_POS_REPORT 50
#define STIVALE2_TERM_CB_KBD_LEDS 60
#define STIVALE2_TERM_CB_MODE 70
#define STIVALE2_TERM_CB_LINUX 80

#define STIVALE2_TERM_CTX_SIZE ((dlongword)(-1))
#define STIVALE2_TERM_CTX_SAVE ((dlongword)(-2))
#define STIVALE2_TERM_CTX_RESTORE ((dlongword)(-3))
#define STIVALE2_TERM_FULL_REFRESH ((dlongword)(-4))

#define STIVALE2_HEADER_TAG_SMP_ID 0x1ab015085f3273df

struct stivale2_header_tag_smp {
    struct stivale2_tag tag;
    dlongword flags;
};

#define STIVALE2_HEADER_TAG_5LV_PAGING_ID 0x932f477032007e8f

#define STIVALE2_HEADER_TAG_UNMAP_NULL_ID 0x92919432b16fe7e7

/* --- Struct --------------------------------------------------------------- */
/*  Information passed from the bootloader to the kernel                      */

struct stivale2_struct {
#define STIVALE2_BOOTLOADER_BRAND_SIZE 64
    char bootloader_brand[STIVALE2_BOOTLOADER_BRAND_SIZE];

#define STIVALE2_BOOTLOADER_VERSION_SIZE 64
    char bootloader_version[STIVALE2_BOOTLOADER_VERSION_SIZE];

    dlongword tags;
};

#define STIVALE2_STRUCT_TAG_PMRS_ID 0x5df266a64047b6bd

#define STIVALE2_PMR_EXECUTABLE ((dlongword)1 << 0)
#define STIVALE2_PMR_WRITABLE   ((dlongword)1 << 1)
#define STIVALE2_PMR_READABLE   ((dlongword)1 << 2)

struct stivale2_pmr {
    dlongword base;
    dlongword length;
    dlongword permissions;
};

struct stivale2_struct_tag_pmrs {
    struct stivale2_tag tag;
    dlongword entries;
    struct stivale2_pmr pmrs[];
};

#define STIVALE2_STRUCT_TAG_KERNEL_BASE_ADDRESS_ID 0x060d78874a2a8af0

struct stivale2_struct_tag_kernel_base_address {
    struct stivale2_tag tag;
    dlongword physical_base_address;
    dlongword virtual_base_address;
};

#define STIVALE2_STRUCT_TAG_CMDLINE_ID 0xe5e76a1b4597a781

struct stivale2_struct_tag_cmdline {
    struct stivale2_tag tag;
    dlongword cmdline;
};

#define STIVALE2_STRUCT_TAG_MEMMAP_ID 0x2187f79e8612de07

#define STIVALE2_MMAP_USABLE                 1
#define STIVALE2_MMAP_RESERVED               2
#define STIVALE2_MMAP_ACPI_RECLAIMABLE       3
#define STIVALE2_MMAP_ACPI_NVS               4
#define STIVALE2_MMAP_BAD_MEMORY             5
#define STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE 0x1000
#define STIVALE2_MMAP_KERNEL_AND_MODULES     0x1001
#define STIVALE2_MMAP_FRAMEBUFFER            0x1002

struct stivale2_mmap_entry {
    dlongword base;
    dlongword length;
    dword type;
    dword unused;
};

struct stivale2_struct_tag_memmap {
    struct stivale2_tag tag;
    dlongword entries;
    struct stivale2_mmap_entry memmap[];
};

#define STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID 0x506461d2950408fa

#define STIVALE2_FBUF_MMODEL_RGB 1

struct stivale2_struct_tag_framebuffer {
    struct stivale2_tag tag;
    dlongword framebuffer_addr;
    word framebuffer_width;
    word framebuffer_height;
    word framebuffer_pitch;
    word framebuffer_bpp;
    byte  memory_model;
    byte  red_mask_size;
    byte  red_mask_shift;
    byte  green_mask_size;
    byte  green_mask_shift;
    byte  blue_mask_size;
    byte  blue_mask_shift;
    byte  unused;
};

#define STIVALE2_STRUCT_TAG_EDID_ID 0x968609d7af96b845

struct stivale2_struct_tag_edid {
    struct stivale2_tag tag;
    dlongword edid_size;
    byte  edid_information[];
};

#define STIVALE2_STRUCT_TAG_TEXTMODE_ID 0x38d74c23e0dca893

struct stivale2_struct_tag_textmode {
    struct stivale2_tag tag;
    dlongword address;
    word unused;
    word rows;
    word cols;
    word bytes_per_char;
};

#define STIVALE2_STRUCT_TAG_FB_MTRR_ID 0x6bc1a78ebe871172

#define STIVALE2_STRUCT_TAG_TERMINAL_ID 0xc2b3f4c3233b0974

struct stivale2_struct_tag_terminal {
    struct stivale2_tag tag;
    dword flags;
    word cols;
    word rows;
    dlongword term_write;
    dlongword max_length;
};

#define STIVALE2_STRUCT_TAG_MODULES_ID 0x4b6fe466aade04ce

struct stivale2_module {
    dlongword begin;
    dlongword end;

#define STIVALE2_MODULE_STRING_SIZE 128
    char string[STIVALE2_MODULE_STRING_SIZE];
};

struct stivale2_struct_tag_modules {
    struct stivale2_tag tag;
    dlongword module_count;
    struct stivale2_module modules[];
};

#define STIVALE2_STRUCT_TAG_RSDP_ID 0x9e1786930a375e78

struct stivale2_struct_tag_rsdp {
    struct stivale2_tag tag;
    dlongword rsdp;
};

#define STIVALE2_STRUCT_TAG_EPOCH_ID 0x566a7bed888e1407

struct stivale2_struct_tag_epoch {
    struct stivale2_tag tag;
    dlongword epoch;
};

#define STIVALE2_STRUCT_TAG_FIRMWARE_ID 0x359d837855e3858c

#define STIVALE2_FIRMWARE_BIOS (1 << 0)

struct stivale2_struct_tag_firmware {
    struct stivale2_tag tag;
    dlongword flags;
};

#define STIVALE2_STRUCT_TAG_EFI_SYSTEM_TABLE_ID 0x4bc5ec15845b558e

struct stivale2_struct_tag_efi_system_table {
    struct stivale2_tag tag;
    dlongword system_table;
};

#define STIVALE2_STRUCT_TAG_KERNEL_FILE_ID 0xe599d90c2975584a

struct stivale2_struct_tag_kernel_file {
    struct stivale2_tag tag;
    dlongword kernel_file;
};

#define STIVALE2_STRUCT_TAG_KERNEL_FILE_V2_ID 0x37c13018a02c6ea2

struct stivale2_struct_tag_kernel_file_v2 {
    struct stivale2_tag tag;
    dlongword kernel_file;
    dlongword kernel_size;
};

#define STIVALE2_STRUCT_TAG_KERNEL_SLIDE_ID 0xee80847d01506c57

struct stivale2_struct_tag_kernel_slide {
    struct stivale2_tag tag;
    dlongword kernel_slide;
};

#define STIVALE2_STRUCT_TAG_SMBIOS_ID 0x274bd246c62bf7d1

struct stivale2_struct_tag_smbios {
    struct stivale2_tag tag;
    dlongword flags;
    dlongword smbios_entry_32;
    dlongword smbios_entry_64;
};

#define STIVALE2_STRUCT_TAG_SMP_ID 0x34d1d96339647025

struct stivale2_smp_info {
    dword processor_id;
    dword lapic_id;
    dlongword target_stack;
    dlongword goto_address;
    dlongword extra_argument;
};

struct stivale2_struct_tag_smp {
    struct stivale2_tag tag;
    dlongword flags;
    dword bsp_lapic_id;
    dword unused;
    dlongword cpu_count;
    struct stivale2_smp_info smp_info[];
};

#define STIVALE2_STRUCT_TAG_PXE_SERVER_INFO 0x29d1e96239247032

struct stivale2_struct_tag_pxe_server_info {
    struct stivale2_tag tag;
    dword server_ip;
};

#define STIVALE2_STRUCT_TAG_MMIO32_UART 0xb813f9b8dbc78797

struct stivale2_struct_tag_mmio32_uart {
    struct stivale2_tag tag;
    dlongword addr;
};

#define STIVALE2_STRUCT_TAG_DTB 0xabb29bd49a2833fa

struct stivale2_struct_tag_dtb {
    struct stivale2_tag tag;
    dlongword addr;
    dlongword size;
};

#define STIVALE2_STRUCT_TAG_VMAP 0xb0ed257db18cb58f

struct stivale2_struct_vmap {
    struct stivale2_tag tag;
    dlongword addr;
};

#undef _stivale2_split64

extern carbonapi long_ptr stivale2_get_tag(struct stivale2_struct * _Nonnull stivale2_struct, dlongword id);

#endif
/* EOF*/