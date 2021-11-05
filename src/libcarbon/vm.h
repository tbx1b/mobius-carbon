/* @(#) vm.h - virtual memory */

#if !defined(_vm_h)
#define _vm_h

#include <libcarbon/core.h>

void MLTX_API _vm_loadg();
#define loadg _vm_loadg

/* should this even be here? */
void MLTX_API _vm_loadi();
#define loadi _vm_loadi

#endif