// =========------------------------- defs.h  ------------------------=========//
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

#ifndef defs_h_
#define defs_h_

/* other header files */

#include <chips/mmu.h>
#include <sys/machine.h>

/* misc */

#define PORT 0x3f8

/* cn.S */

void            cncursoroff(void);
void            cncursoron(unsigned char cursor_start, unsigned char cursor_end);

/* cnsl.c */

enum vga_color {
  BLACK = 0,
  BLUE = 1,
  GREEN = 2,
  CYAN = 3,
  RED = 4,
  MAGENTA = 5,
  BROWN = 6,
  LIGHT_GREY = 7,
  DARK_GREY = 8,
  LIGHT_BLUE = 9,
  LIGHT_GREEN = 10,
  LIGHT_CYAN = 11,
  LIGHT_RED = 12,
  LIGHT_MAGENTA = 13,
  LIGHT_BROWN = 14,
  WHITE = 15,
};

int             cninit(unsigned char clr);
int             cnsetcolor(const unsigned char clr);
unsigned short  cnentry(const unsigned char uc, const unsigned char color);
unsigned char   cnecolor(const enum vga_color fg, const enum vga_color bg);
int             cnputs(const char str[]);

/* gdt.S */



/* io.S */

void            iooutb(const unsigned short port, const unsigned short data);
unsigned char   ioinb(const unsigned short port);

/* strN.s */

int             strlen(const char *str);
int             memcmp(const void *s1, const void *s2, unsigned n);
void *          memcpy(void *dst0, const void *src0, unsigned int len);
void *          memmove(void *s1, const void *s2, unsigned int n);
void            bcopy(const void *s1, void *s2, unsigned int n);
char *          strcpy(char * restrict dst, const char * restrict src);
char *          strcat(char *dest, const char *src);
unsigned int    strnlen(const char *str, unsigned int maxlen);
char *          strncat(char *s1, const char *s2, unsigned int n);
void *          memchr(void const *s, int c_in, unsigned int n);
char *          strchr(const char *s, int c_in);
char *          strstr(const char *haystack, const char *needle);
void *          memset(void *s, int c, unsigned int n);
void            bzero(void *s, unsigned int n);

/* mascotte.c */

void            announce();

/* serial.c */

#define         SERIAL_COM1_BASE 0x3F8 /* COM1 base port */
#define         SERIAL_DATA_PORT(base) (base)
#define         SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define         SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define         SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define         SERIAL_LINE_STATUS_PORT(base) (base + 5)
#define         SERIAL_LINE_ENABLE_DLAB 0x80

int             spln(unsigned short c);
int             spbaudrate(unsigned short com, unsigned short div);
int             init_serialp(void);

/* tty.c */

int             ttyup(int broadcast, int side);
int             ttyinit();
int             ttyputs(const char str[]);

/* vm.c */

int             seginit(void);

extern struct sdesc gdt[6];

#endif /* defs_h_ */