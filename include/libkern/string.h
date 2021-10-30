/**
 *  @file string.h
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


#pragma once

#include <libkern/stdlib.h>

int mbtowc (wchar_t * __pwc, const char *s, size_t n);


void *memcpy(void *dst, const void *src, size_t n);

void *memmove(void *dst, const void *src, size_t n);

void *memset(void *s, int c, size_t n);

int memcmp(const void *s1, const void *s2, size_t n);

void *memchr(const void *s, int c, size_t n);

void *memrchr(const void *s, int c, size_t n);

void *memmem(const void *haystack, size_t hl, const void *needle, size_t nl);

void *memrmem(const void *haystack, size_t hl, const void *needle, size_t nl);

char_t *strcpy(char_t *dst, const char_t *src);

char_t *strncpy(char_t *dst, const char_t *src, size_t n);

char_t *strcat(char_t *dst, const char_t *src);

int strcmp(const char_t *s1, const char_t *s2);

char_t *strncat(char_t *dst, const char_t *src, size_t n);

int strncmp(const char_t *s1, const char_t *s2, size_t n);

char_t *strdup(const char_t *s);

char_t *strchr(const char_t *s, int c);

char_t *strrchr(const char_t *s, int c);

char_t *strstr(const char_t *haystack, const char_t *needle);

char_t *_strtok_r(char_t *s, const char_t *d, char_t **p);

char_t *strtok(char_t *s, const char_t *delim);

char_t *strtok_r(char_t *s, const char_t *delim, char_t **ptr);

size_t strlen (const char_t *__s);

char* itoa(uint64_t num, char* str, uint64_t base);
