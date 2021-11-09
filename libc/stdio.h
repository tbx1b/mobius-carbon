/*===---- stdio.h - Standard input/output operations + carbon specifics ----===
 *
 * Part of the Carbon libc subset, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

#ifndef __LIBC_STDIO_H_
#define __LIBC_STDIO_H_

#ifndef __kernel__
# include_next <stdio.h>
#else
# include <carbon/printf.h>
# include <device/io.h>
#endif

#endif // __LIBC_STDIO_H_
// eof