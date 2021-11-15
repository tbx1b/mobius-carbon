#include <sys/defs.h>

extern cnputc(const char c);

struct ttystate_t {
  int initialized, broadcast, side;
};

static struct ttystate_t _context;

static 
sideputs(const char str[])
{
  if (!_context.initialized)
    return -1;
  do {
    iooutb(PORT, *str);
  } while (*str++);
  return 0;
}

ttyputs(const char str[])
{
  if (!_context.initialized)
    return -1;
  if (_context.broadcast)
    cnputs(str);
  if (_context.side)
    sideputs(str);
  return 0;
}

ttyup(broadcast, side)
{
  if (!_context.initialized)
    return -1;
  _context.broadcast = broadcast;
  _context.side = side;
  return 0;
}

ttyinit()
{
  _context.broadcast = 1;
  _context.side = 1;

  cninit(cnecolor(LIGHT_GREEN, BLACK));

  _context.initialized = 1;
  return 0;
}