#include <carbon.h>

typedef struct _register
{
    dword ds;                  // Data segment selector
    dword edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    dword int_no, err_code;    // Interrupt number and error code (if applicable)
    dword eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} register_t;