#include "libkern/tty.h"
/**
 *  @file assert.c
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
 *  @brief Provide a basic assertion fn
 *
 */

#include <carbon/stdint.h>

extern void kprintf(const char *s, ...);

assert(_Bool condition, const char *s)
{
    if (!condition) {

        tty_dbg_color(0xFF0000); // red

        kprintf("\nAssertion failed: ");
        kprintf(s);
        kprintf("\n");
        kprintf("-> Continuing\n");

        tty_dbg_color(0xFFFFFF); 
        __asm__("cli");
        halt: __asm__("hlt"); goto halt;
        return 0;
    }
    return 1;
}
