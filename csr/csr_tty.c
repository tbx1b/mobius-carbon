// =========---------------------- csr_tty.c  -----=------------------=========//
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