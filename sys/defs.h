/*===----- types.h - Standard header For sized integer types --------------===*\
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
\*===----------------------------------------------------------------------===*/

#ifndef __CARBON_DEFS_H_
#define __CARBON_DEFS_H_

#ifdef __assembler__
#   define LOC(x) x:
#   define GLOB(x) .globl x; x:
#   define FSYM(x) .section .text; .type x,@function;
#   define DSYM(x) .section .data; .type x,@object;
#   define AUOUT_SYM(x) _##x:
#else

#include <sys/types.h>
typedef __SIZE_TYPE__ size_t;
#define RETURN return(0)

#ifndef __cplusplus
# define __BEGIN_DECLS
# define __END_DECLS
#else
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#endif

#endif // assembler

#endif /* __CARBON_DEFS_H_ */
