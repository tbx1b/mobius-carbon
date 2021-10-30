/**
 *  @file tty.c
 *  @author MOBIUSLOOPFOUR <scratch.joint-0i@icloud.com>
 *
 *  Copyright MOBIUSLOOPFOUR 2021
 *  All rights reserved.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @brief Basic printing services
 *
 */

#include "carbon/stdint.h"
#include <libkern/tty.h>
#include <carbon/carbon.h>
#include <libkern/string.h>

#include <stdarg.h>

static struct tty_t __pinfo;
static int __init = 0;
static size_t X, Y;

static uint32_t color;

static void 
putc(struct tty_t pinfo, int x, int y, const char *s)
{
    unsigned char *ptr, *chr, *frg;
    unsigned int c;
    uintptr_t o, p;
    int i, j, k, l, m, n;
    //while(*s) {
        c = 0; s += mbtowc((wchar_t*)&c, (const char*)s, 4);
        //if(c == '\r') { x = 0; return; } else
        //if(c == '\n') { x = 0; y += pinfo.font->height; return; }
        for(ptr = (unsigned char*)(pinfo.font) + (pinfo.font)->characters_offs, chr = 0, i = 0; i < 0x16400; i++) {
            if(ptr[0] == 0xFF) { i += 65535; ptr++; }
            else if((ptr[0] & 0xC0) == 0xC0) { j = (((ptr[0] & 0x3F) << 8) | ptr[1]); i += j; ptr += 2; }
            else if((ptr[0] & 0xC0) == 0x80) { j = (ptr[0] & 0x3F); i += j; ptr++; }
            else { if((unsigned int)i == c) { chr = ptr; break; } ptr += 6 + ptr[1] * (ptr[0] & 0x40 ? 6 : 5); }
        }
        if(!chr) return;
        ptr = chr + 6; o = (uintptr_t)(pinfo.lfb) + y * (pinfo.pitch) + x * 4;
        for(i = n = 0; i < chr[1]; i++, ptr += chr[0] & 0x40 ? 6 : 5) {
            if(ptr[0] == 255 && ptr[1] == 255) continue;
            frg = (unsigned char*)(pinfo.font) + (chr[0] & 0x40 ? ((ptr[5] << 24) | (ptr[4] << 16) | (ptr[3] << 8) | ptr[2]) :
                ((ptr[4] << 16) | (ptr[3] << 8) | ptr[2]));
            if((frg[0] & 0xE0) != 0x80) continue;
            o += (int)(ptr[1] - n) * (pinfo.pitch); n = ptr[1];
            k = ((frg[0] & 0x1F) + 1) << 3; j = frg[1] + 1; frg += 2;
            for(m = 1; j; j--, n++, o += (pinfo.pitch))
                for(p = o, l = 0; l < k; l++, p += 4, m <<= 1) {
                    if(m > 0x80) { frg++; m = 1; }
                    if(*frg & m) *((unsigned int*)p) = color;
                }
        }
        //x += chr[4]+1; y += chr[5];
    //}
}

void
kprintf(const char *s, ...)
{
    va_list arg;
    va_start(arg, s);


    if (__init != 1) {
        return;
    }

    if (s[0] == '\0') {
        return;
    }
    for (size_t i = 0; i < strlen(s); i++) {

        if (s[i] == '\n' || s[i] == '\r') {
            Y += 16;
            X = 0;
            continue;
        }

        if (s[i] == '$') { // HEX
            char buf[12];
            uint64_t n = va_arg(arg, uint64_t);

            itoa(n, buf, 16);
            kprintf("0x");
            kprintf(buf);
            continue;
        }

        if (s[i] == '#') { // DEC
            char buf[12];
            uint64_t n = va_arg(arg, uint64_t);

            itoa(n, buf, 10);
            kprintf(buf);
            continue;
        }

        if (s[i] == '@') { // BIN
            char buf[12];
            uint64_t n = va_arg(arg, uint64_t);

            kprintf("0b");
            itoa(n, buf, 2);
            kprintf(buf);
            continue;
        }

        if (s[i] == '%') { // STR
            char buf[12];
            const char *n = va_arg(arg, const char *);
            kprintf(n);
            kprintf(buf);
            continue;
        }

        if (X >= __pinfo.width) {
            Y += 16;
            X = 0;
        }

        putc(__pinfo, X, Y, &(s[i]));
        X += 8;
    }
}

tty_dbg_init(struct tty_t t) {
    if (__init == 1) {
        return 1;
    }
    __pinfo = t;
    __init = 1;

    X = 0;
    Y = 0;

    color = 0xFFFFFFFF;

    return 1;
}

tty_dbg_color(uint32_t c)
{
    color = c;
    return 1;
}

tty_dbg_screen_color(uint32_t c, frame_buffer_t *fb) 
{
    X ^= X;
    Y ^= Y;

    memset((void*)fb->base, c, fb->size);
    return 1;
}
