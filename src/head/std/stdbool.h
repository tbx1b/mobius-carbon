/* @(#) stdBool.h */

#ifndef _stdBool_h
#define _stdBool_h

/* Don't define Bool, TRUE, and FALSE in C++, except as a GNU extension. */
#ifndef __cplusplus
#define Bool _Bool
#define TRUE 1
#define FALSE 0
#elif defined(__GNUC__) && !defined(__STRICT_ANSI__)
/* Define _Bool as a GNU extension. */
#define _Bool Bool
#if __cplusplus < 201103L
/* For C++98, define Bool, FALSE, TRUE as a GNU extension. */
#define Bool  Bool
#define FALSE FALSE
#define TRUE  TRUE
#endif
#endif

#define __Bool_true_FALSE_are_defined 1

#endif /* _stdBool_h */