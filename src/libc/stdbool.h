/* @(#) stdbool.h */

#ifndef _stdbool_h
#define _stdbool_h

/* Don't define bool, true, and false in C++, except as a GNU extension. */
#ifndef __cplusplus
#define bool _Bool
#define true 1
#define false 0
#elif defined(__GNUC__) && !defined(__STRICT_ANSI__)
/* Define _Bool as a GNU extension. */
#define _Bool bool
#if __cplusplus < 201103L
/* For C++98, define bool, false, true as a GNU extension. */
#define bool  bool
#define false false
#define true  true
#endif
#endif

#define __bool_true_false_are_defined 1

#endif /* _stdbool_h */