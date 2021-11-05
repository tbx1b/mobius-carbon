/* @(#) vm.h - virtual memory */

#if !defined(_vm_h)
#define _vm_h

#include <core.h>

MTSS_API void _vm_loadg();
#define loadg _vm_loadg

/* should this even be here? */
MTSS_API void _vm_loadi();
#define loadi _vm_loadi

#endif