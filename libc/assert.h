/*===---- assert.h - Basic assert macros -----------------------------------===
 *
 * Part of the Carbon libc subset, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#ifndef __LIBC_ASSERT_H_
#define __LIBC_ASSERT_H_

#ifndef __kernel__

# include_next <assert.h>

#else

#define _SYS_ASSERT
#include <sys/assert.h>

#endif // __kernel__

#endif // __LIBC_ASSERT_H_