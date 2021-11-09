/*===---- stdint.h - Standard-width integer types --------------------------===
 *
 * Part of the Carbon libc subset, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#ifndef __LIBC_STDINT_H
#define __LIBC_STDINT_H

#ifdef __kernel__
#include <sys/types.h>
#else
// Don't use the internal kernel header
# include_next <stdint.h>
#endif

#endif