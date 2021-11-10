/*===---- kmain.c - Kernel main procedure ----------------------------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <gnu/multiboot.h>
#include <vm/descriptor_tables.h>

uint32_t kmain(uint32_t magic, uintptr_t addr) {
  assert(magic == MULTIBOOT_BOOTLOADER_MAGIC);
  tabinit();
  RETURN;
}
// eof