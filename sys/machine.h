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