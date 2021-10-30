/**
 *  @file libk_str.c
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
 *  @brief Basic impl. of the POSIX libc string functions. strdup will not be implemented
 *          in kernel space. (malloc)
 *
 */

#include <libkern/string.h>
#include <carbon/stdint.h>

int mbtowc (wchar_t * __pwc, const char *s, size_t n)
{
    wchar_t arg;
    int ret = 1;
    if(!s || !*s) return 0;
    arg = (wchar_t)*s;
    if((*s & 128) != 0) {
        if((*s & 32) == 0 && n > 0) { arg = ((*s & 0x1F)<<6)|(*(s+1) & 0x3F); ret = 2; } else
        if((*s & 16) == 0 && n > 1) { arg = ((*s & 0xF)<<12)|((*(s+1) & 0x3F)<<6)|(*(s+2) & 0x3F); ret = 3; } else
        if((*s & 8) == 0 && n > 2) { arg = ((*s & 0x7)<<18)|((*(s+1) & 0x3F)<<12)|((*(s+2) & 0x3F)<<6)|(*(s+3) & 0x3F); ret = 4; }
        else return -1;
    }
    if(__pwc) *__pwc = arg;
    return ret;
}

char_t *strcpy(char_t *dst, const char_t *src)
{
    if(src && dst) {
        while(*src) {*dst++=*src++;} *dst=0;
    }
    return dst;
}

char_t *strncpy(char_t *dst, const char_t *src, size_t n)
{
    const char_t *e = src+n;
    if(src && dst && n>0) {
        while(*src && src<e) {*dst++=*src++;} *dst=0;
    }
    return dst;
}

char_t *strcat(char_t *dst, const char_t *src)
{
    if(src && dst) {
        dst += strlen(dst);
        while(*src) {*dst++=*src++;} *dst=0;
    }
    return dst;
}

int strcmp(const char_t *s1, const char_t *s2)
{
    if(s1 && s2 && s1!=s2) {
        do{if(*s1!=*s2){return *s1-*s2;}s1++;s2++;}while(*s1!=0);
        return *s1-*s2;
    }
    return 0;
}

char_t *strncat(char_t *dst, const char_t *src, size_t n)
{
    const char_t *e = src+n;
    if(src && dst && n>0) {
        dst += strlen(dst);
        while(*src && src<e) {*dst++=*src++;} *dst=0;
    }
    return dst;
}

int strncmp(const char_t *s1, const char_t *s2, size_t n)
{
    const char_t *e = s1+n;
    if(s1 && s2 && s1!=s2 && n>0) {
        do{if(*s1!=*s2){return *s1-*s2;}s1++;s2++;}while(*s1!=0 && s1<e);
        return *s1-*s2;
    }
    return 0;
}

char_t *strdup(const char_t *s)
{
    halt:
    __asm__("hlt");
    goto halt;
}

char_t *strchr(const char_t *s, int c)
{
    if(s) {
        while(*s) {
            if(*s == (char_t)c) return (char_t*)s;
            s++;
        }
    }
    return NULL;
}

char_t *strrchr(const char_t *s, int c)
{
    char_t *e;
    if(s) {
        e = (char_t*)s + strlen(s) - 1;
        while(s < e) {
            if(*e == (char_t)c) return e;
            s--;
        }
    }
    return NULL;
}

char_t *strstr(const char_t *haystack, const char_t *needle)
{
    return memmem(haystack, strlen(haystack) * sizeof(char_t), needle, strlen(needle) * sizeof(char_t));
}

char_t *_strtok_r(char_t *s, const char_t *d, char_t **p)
{
    int c, sc;
    char_t *tok, *sp;

    if(d == NULL || (s == NULL && (s=*p) == NULL)) return NULL;

    c = *s++;
    for(sp = (char_t *)d; (sc=*sp++)!=0;) {
        if(c == sc) { *p=s; *(s-1)=0; return s-1; }
    }

    if (c == 0) { *p=NULL; return NULL; }
    tok = s-1;
    while(1) {
        c = *s++;
        sp = (char_t *)d;
        do {
            if((sc=*sp++) == c) {
                if(c == 0) s = NULL;
                else *(s-1) = 0;
                *p = s;
                return tok;
            }
        } while(sc != 0);
    }
    return NULL;
}

char_t *strtok(char_t *s, const char_t *delim)
{
    char_t *p = s;
    return _strtok_r (s, delim, &p);
}

char_t *strtok_r(char_t *s, const char_t *delim, char_t **ptr)
{
    return _strtok_r (s, delim, ptr);
}

size_t strlen (const char_t *__s)
{
    size_t ret;

    if(!__s) return 0;
    for(ret = 0; __s[ret]; ret++);
    return ret;
}
