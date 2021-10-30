/**
 *  @file _types_.h
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
 *  @brief Architecture specific types
 *
 */

#pragma once

#ifdef __GNUC__
typedef __signed char           __carbon_int8_t;
#else   /* !__GNUC__ */
typedef char                    __carbon_int8_t;
#endif  /* !__GNUC__ */

typedef unsigned char           __carbon_uint8_t;
typedef short                   __carbon_int16_t;
typedef unsigned short          __carbon_uint16_t;
typedef int                     __carbon_int32_t;
typedef unsigned int            __carbon_uint32_t;
typedef long long               __carbon_int64_t;
typedef unsigned long long      __carbon_uint64_t;

typedef long                    __carbon_intptr_t;
typedef unsigned long long      __carbon_uintptr_t ;
typedef unsigned int            __carbon_natural_t;

typedef long                    __carbon_ptrdiff_t;

#if defined(__SIZE_TYPE__)
typedef __SIZE_TYPE__           __carbon_size_t;        /* sizeof() */
#else
typedef unsigned long           __carbon_size_t;        /* sizeof() */
#endif

#if (__GNUC__ > 2)
typedef __builtin_va_list       __carbon_va_list;       /* va_list */
#else
typedef void *                  __carbon_va_list;       /* va_list */
#endif

#if defined(__WINT_TYPE__)
typedef __WINT_TYPE__           __carbon_wint_t;        /* wint_t */
#else
typedef wchar_t                 __carbon_wint_t;        /* wint_t */
#endif
