/*
 * MODULE:          Input/Output
 * LICENSE:         GPL-3.0-or-later
 * PURPOSE:         Write to the tty
 * COPYRIGHT:       Copyright MobiusLoopFour
 */

/* INCLUDES *******************************************************************/

#include <sys.h>
#include "ioctl.h"

static dword cursor_y;
static dword cursor_x;
static word *video_memory = (word *)0xB8000;

/* PRIVATE FUNCTIONS **********************************************************/

static void 
move_cursor()
{
   word cursor_location = cursor_y * 80 + cursor_x;
   hal_io_outb(0x3D4, 14);
   hal_io_outb(0x3D5, cursor_location >> 8);
   hal_io_outb(0x3D4, 15);
   hal_io_outb(0x3D5, cursor_location);
}

static void 
scroll()
{

   byte attribute = (0 << 4) | (15  & 0x0F);
   word blank = 0x20 | (attribute << 8);

   if(cursor_y >= 25)
   {
       int i;
       for (i = 0*80; i < 24*80; i++)
       {
           video_memory[i] = video_memory[i+80];
       }
       for (i = 24*80; i < 25*80; i++)
       {
           video_memory[i] = blank;
       }
       cursor_y = 24;
   }
}

/* GLOBAL FUNCTIONS ***********************************************************/

void 
hal_termio_put(char c)
{
   byte bg_color = 0;
   byte fg_color = 15;

   byte  battribute = (bg_color << 4) | (fg_color & 0x0F);
   word  attribute = battribute << 8;
   word *location;
   if (c == 0x08 && cursor_x)
   {
       cursor_x--;
   }
   else if (c == 0x09)
   {
       cursor_x = (cursor_x+8) & ~(8-1);
   }
   else if (c == '\r')
   {
       cursor_x = 0;
   }
   else if (c == '\n')
   {
       cursor_x = 0;
       cursor_y++;
   }
   else if(c >= ' ')
   {
       location = video_memory + (cursor_y*80 + cursor_x);
       *location = c | attribute;
       cursor_x++;
   }
   if (cursor_x >= 80)
   {
       cursor_x = 0;
       cursor_y ++;
   }
   scroll();
   move_cursor();
}

void 
hal_termio_clear()
{
   byte attribute = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   word blank = 0x20 /* space */ | (attribute << 8);

   int i;
   for (i = 0; i < 80*25; i++)
   {
       video_memory[i] = blank;
   }

   cursor_x = 0;
   cursor_y = 0;
   move_cursor();
}

void 
hal_termio_write(char *c)
{
   int i = 0;
   while (c[i])
    {
        hal_termio_put(c[i++]);
    }
}
/* EOF */