/*===---- asm.h - Runtime debugging facilities -----------------------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#ifndef __CARBON_ASSERT_H_
#define __CARBON_ASSERT_H_

#ifdef __debug__

#define assert(x)                                                              \
  do {                                                                         \
    if (!(x)) {                                                                \
      printf_("\033[1m\033[31m ASSERTION FAILED - %s - %d\033[0m\n", __FILE__, \
              __LINE__);                                                       \
      for (;;) {                                                               \
        __asm__ volatile("cli");                                               \
        __asm__ volatile("hlt");                                               \
      }                                                                        \
    }                                                                          \
  } while (0)

#define assert_nz(x)                                                           \
  do {                                                                         \
    if (((x) != 0)) {                                                          \
      printf_("\033[1m\033[31m ASSERTION FAILED - %s - %d\033[0m\n", __FILE__, \
              __LINE__);                                                       \
      for (;;) {                                                               \
        __asm__ volatile("cli");                                               \
        __asm__ volatile("hlt");                                               \
      }                                                                        \
    }                                                                          \
  } while (0)

#else

#define assert(x)
#define assert_nz(x)

#endif // debug

#endif /* __CARBON_ASSERT_H_ */
       // eof