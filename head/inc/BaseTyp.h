/*
 * PROJECT:     Carbon
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Standard width integers and types
 * COPYRIGHT:   Copyright 2021 MobiusLoopFour
 */

#ifndef __BASETYP_H__
#define __BASETYP_H__

/* INCLUDES *****************************************************************/

#include <HalDefs.h>

/* TYPE-ALIASES *************************************************************/

#ifdef HALDEFS

    typedef __BYTE      byte;
    typedef __WORD      word;
    typedef __DWORD     dword;
    typedef __UINT64    dlongword;

    typedef __UINT32    ulong32;
    typedef __ULONG64   ulong64;

    typedef __INT8      int8;
    typedef __INT16     int16;
    typedef __INT32     int32;
    typedef __INT64     int64;

    typedef __UINT8     uint8;
    typedef __UINT16    uint16;
    typedef __UINT32    uint32;
    typedef __UINT64    uint64;
    typedef __UINT64    size_t;

    
    typedef __CCHAR     cchar;
    
#else /* !HALDEFS */
    typedef unsigned short Word;
    #error Include HalDefs.h
#endif /* !HALDEFS */

typedef void *          handle;

typedef int32           bool32;
typedef int8            bool;

#define FALSE ((bool)0)
#define TRUE ((bool)!FALSE)
#define NULL ((handle)0)

#define any void
#define fileprivate static

#if defined(CA64)
    typedef ulong64 long_ptr;
#else /* !CA64 */
    typedef unsigned long long long_ptr;
#endif /* !CA64 */

#endif /* !__BASETYP_H__ */
/* EOF */