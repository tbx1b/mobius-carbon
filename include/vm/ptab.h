/**
 *  @file libk_memmove.c
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
 *  @brief Page table interfacing with the CPU
 *
 */

#pragma once

#include <carbon/stdint.h>

#pragma mark This is x86_64 specific code.

typedef struct {
    _Bool present       : 1;
    _Bool rw            : 1;
    _Bool su            : 1;
    _Bool wt            : 1; // write-through
    _Bool cache_ds      : 1; // cache disabled
    _Bool dirty         : 1;
    _Bool nop_00        : 1;
    _Bool larger_p      : 1;
    _Bool nop_01        : 1;
    uint8_t avaialble   : 3; // anything
    uintptr_t  address   : 52;
} vm_page_dir_entry_t;

typedef vm_page_dir_entry_t pd_entry_t; // shorthand

typedef struct {
    pd_entry_t entries[512];
} __attribute__((aligned(0x1000))) vm_page_table_t;

