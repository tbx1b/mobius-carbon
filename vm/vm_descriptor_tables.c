/*===---- descriptor_tables.c - DT init code -------------------------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#include <stdint.h>
#include <vm/descriptor_tables.h>

extern void __attribute__((optnone)) gdtflush(uint32_t); // gdt.S
static void ginit();
static void gsetg(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

gdt_entry_t _gdt_[5];
gdtptr_t gdt_ptr;

/**
 * @brief Initialize global * tables (for x86: GDT and IDT)
 * 
 */
void tabinit() {
  ginit();
}

/* clang will optimise these functions into oblivion...
 * do take notes from gcc ;)
 */

/**
 * @brief Initialise the GDT
 * 
 */
__attribute__((optnone)) 
static void ginit() {
  gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
  gdt_ptr.base = (uint32_t)&_gdt_;

  gsetg(0, 0, 0, 0, 0);                // Null segment
  gsetg(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
  gsetg(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
  gsetg(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
  gsetg(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

  gdtflush((uint32_t)&gdt_ptr);
}

/**
 * @brief Set a GDT descriptor entry
 * 
 */
__attribute__((optnone)) 
static void gsetg(int32_t n, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
   _gdt_[n].base_low    = (base & 0xFFFF);
   _gdt_[n].base_middle = (base >> 16) & 0xFF;
   _gdt_[n].base_high   = (base >> 24) & 0xFF;

   _gdt_[n].limit_low   = (limit & 0xFFFF);
   _gdt_[n].granularity = (limit >> 16) & 0x0F;

   _gdt_[n].granularity |= gran & 0xF0;
   _gdt_[n].access      = access;
}