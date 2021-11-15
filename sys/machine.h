// =========---------------------- machine.h  ------------------------=========//
//                       Copyright 2021 MobiusLoopFour
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
// 
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
// =========----------------------------------------------------------=========// 

/* Routines to let C code use special x86 instructions. */

void
insl(int port, void *addr, int cnt)
;

void
outw(unsigned short port, unsigned short data)
;

void
outsl(int port, const void *addr, int cnt)
;

void
stosb(void *addr, int data, int cnt)
;

void
stosl(void *addr, int data, int cnt)
;

struct sdesc;

void
lgdt(struct sdesc *p, int size)
;

struct gatedesc;

void
lidt(struct gatedesc *p, int size)
;

void
ltr(unsigned short sel)
;

unsigned
readeflags(void)
;

void
loadgs(unsigned short v)
;

void
cli(void)
;

void
sti(void)
;

unsigned
xchg(volatile unsigned *addr, unsigned newval)
;

unsigned
rcr2(void)
;

void
lcr3(unsigned val)
;