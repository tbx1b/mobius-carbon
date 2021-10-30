/**
 *  @file stdint.h
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
 *  @brief Standard-width integer types
 *
 */

#pragma once

#include <x86_64/_types_.h>

typedef __carbon_int8_t            int8_t;


typedef __carbon_uint8_t           uint8_t;
typedef __carbon_int16_t           int16_t;
typedef __carbon_uint16_t          uint16_t;
typedef __carbon_int32_t           int32_t;
typedef __carbon_uint32_t          uint32_t;
typedef __carbon_int64_t           int64_t;
typedef __carbon_uint64_t          uint64_t;

typedef __carbon_intptr_t          intptr_t;
typedef __carbon_uintptr_t         uintptr_t;
typedef __carbon_natural_t         natural_t;
typedef __carbon_ptrdiff_t         ptrdiff_t;

typedef __carbon_size_t            size_t;              /* sizeof */
typedef __carbon_va_list           va_list;

typedef __carbon_wint_t            wint_t;
