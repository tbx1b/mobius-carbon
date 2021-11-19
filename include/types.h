#pragma once

typedef unsigned int i8   __attribute__ ((__mode__ (__QI__)));
typedef unsigned int i16  __attribute__ ((__mode__ (__HI__)));
typedef unsigned int i32  __attribute__ ((__mode__ (__SI__)));
typedef unsigned int i64  __attribute__ ((__mode__ (__DI__)));

typedef _Bool i1;

typedef i32 ptr;
typedef i64 size;

_Static_assert(sizeof(i8)    == 1, "i8 must be 1 byte wide"  );
_Static_assert(sizeof(i16)   == 2, "i16 must be 2 bytes wide");
_Static_assert(sizeof(i32)   == 4, "i32 must be 4 bytes wide");
_Static_assert(sizeof(i64)   == 8, "i64 must be 8 bytes wide");