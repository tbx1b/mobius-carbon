// =========---------------------- csr_cnsl.c  -----------------------=========//
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

static const VGA_WIDTH = 80, VGA_HEIGHT = 25;
static int cnrow, cncolumn;
static unsigned char cncolor;
static unsigned short * cnbuffer;

static void 
cnmovcur(int x, int y)
{
	unsigned short pos = y * VGA_WIDTH + x;
 
	iooutb(0x3D4, 0x0F);
	iooutb(0x3D5, (unsigned char) (pos & 0xFF));
	iooutb(0x3D4, 0x0E);
	iooutb(0x3D5, (unsigned char) ((pos >> 8) & 0xFF));
}

static 
cnput(const char c, const unsigned char clr, const unsigned x, const unsigned y) 
{
  unsigned long long i;

  i = y * VGA_WIDTH + x;
  cnbuffer[i] = cnentry(c, clr);
  return 0;
}

static 
cnscroll(int line)
{
  int loop;
  char c;

  for (loop = line * (VGA_WIDTH * 2) + 0xB8000; loop < VGA_WIDTH * 2; loop++) {
    c = *(char*)loop;
		*(char*)(loop - (VGA_WIDTH * 2)) = c;
  }
  return 0;
}

static 
cndellastln()
{
  int x, *ptr;

  for(x = 0; x < VGA_WIDTH * 2; x++) {
		ptr = (int*)(0xB8000 + (VGA_WIDTH * 2) * (VGA_HEIGHT - 1) + x);
		*ptr = 0;
	}
  return 0;
}

cnputc(const char c)
{
  int line;
  cnput(c, cncolor, cncolumn, cnrow);
  if (++cncolumn == VGA_WIDTH) {
    cncolumn = 0;
    if (++cnrow == VGA_HEIGHT) {
      for(line = 1; line <= VGA_HEIGHT - 1; line++)
				cnscroll(line);

      cndellastln();
      cnrow = VGA_HEIGHT - 1;
    }
  }
  return 0;
}

cnsetcolor(const unsigned char clr) {
  cncolor = clr;
  return 0;
}

cnputs(const char str[])
{
  do {
    /* handle special characters */
    if (*str=='\n' || *str=='\r') {
      cnrow++;
      cncolumn = 0;
      continue;
    }
    /* print */
    cnputc(*str);
  } while(*str++);

  cnmovcur(cncolumn, cnrow);
  return 0;
}

unsigned char 
cnecolor(const enum vga_color fg, const enum vga_color bg) {
  return fg | bg << 4;
}

unsigned short 
cnentry(const unsigned char uc, const unsigned char color) {
  return (unsigned short)uc | (unsigned short)color << 8;
}

cninit(unsigned char clr) {
  unsigned y, x;
  unsigned long long i;

  /* vga fb base addr */
  cnrow = 0; 
  cncolumn = 1;
  cncolor = clr;
  cnbuffer = (unsigned short*)0xB8000;

  for (y = 0; y < VGA_HEIGHT ; y++) {
    for (x = 0; x < VGA_WIDTH; x++) {
      i = y * VGA_WIDTH + x;
      cnbuffer[i] = cnentry(' ', cncolor);
    }
  }
  cncursoron(0, 15);
  cnmovcur(0, 0);

  return 0;
}