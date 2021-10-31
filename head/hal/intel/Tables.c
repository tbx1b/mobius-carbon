/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Pause the CPU
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

/* INCLUDES *****************************************************************/

#include <Carbon.h>

/* GLOBALS ******************************************************************/

typedef struct {
    word        m_wOffset1;
    word        m_wSelector;
    byte        m_cInterruptStackTable;
    byte        m_fTypeAttributes;
    word        m_wOffset2;
    dword       m_wOffset3;
    dword       reserved;
} raw IDTEntry;

typedef struct {
    word        m_wLimit;
    long_ptr    m_pBase;
} raw IDTPointer;

extern void isr0(void);
// ...
extern void isr31(void);
// ...
extern any IDTFlush(void);

IDTEntry    pentries[256];
IDTPointer  idt_pointer;

fileprivate HalSetGate(byte num, dlongword base, word selector, byte flags)
{
    return HAL_ERR_UNIMPLEMENTED;
}

fileprivate HalInitIDT(void)
{
    idt_pointer.m_wLimit    = sizeof(IDTEntry) * 256 -1;
    idt_pointer.m_pBase     = (long_ptr)&pentries;

    memset(&pentries, 0, sizeof(IDTEntry)*256);


    #define setgate(x) HalSetGate(x, (dlongword)isr##x, 0x08, 0x8E)

    setgate(0);
    // ...
    setgate(31);

    #undef setgate//(x)

    IDTFlush();
    return HAL_ERR_UNIMPLEMENTED;
}
/* EOF */