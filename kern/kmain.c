/*===---- kmain.c - Kernel main procedure ----------------------------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

// uint32_t
#include <stdint.h>
// printf
#include <stdio.h>
// assert()
#include <assert.h>

// MULTIBOOT_BOOTLOADER_MAGIC
#include <gnu/multiboot.h>

uint32_t kmain(uint32_t magic, uintptr_t addr) {
  assert(magic == MULTIBOOT_BOOTLOADER_MAGIC);
  printf("Hello, World!\n");
  RETURN;
}
// eof