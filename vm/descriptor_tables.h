/*===---- descriptor_tables.c - DT data structures -------------------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#ifndef __CARBON_DESCRIPTOR_TABLES_H_
#define __CARBON_DESCRIPTOR_TABLES_H_

#include <stdint.h>
#include <sys/defs.h>

typedef struct {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr_struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) gdtptr_t;

__BEGIN_DECLS
extern void tabinit();
__END_DECLS

#endif /* __CARBON_DESCRIPTOR_TABLES_H_ */
       // eof