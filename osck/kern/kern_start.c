/**
 *  @file kern_start.c
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
 *  @brief Kernel entry point
 *
 */

#include "vm/vm.h"
#include <carbon/carbon.h>

#include <libkern/stdlib.h>
#include <libsa/bateau.h>
#include <libkern/tty.h>

#include <carbon/stdint.h>
#include <carbon/assert.h>

int 
_start(bateau_info_struct_t *aBootTimeEnvironment) 
{   
    {
        struct tty_t pinfo = {
            .width = aBootTimeEnvironment->width,
            .height = aBootTimeEnvironment->height,
            .font = aBootTimeEnvironment->font,
            .lfb = aBootTimeEnvironment->lfb,
            .pitch = aBootTimeEnvironment->pitch
        };

        tty_dbg_screen_color(0x00000000, (aBootTimeEnvironment->frame_buffer)); // black
        tty_dbg_init(pinfo);
        tty_dbg_color(0xFFFFFFFF); // white
    }

    os_kern_vm_init(aBootTimeEnvironment);

    halt: __asm__("hlt"); goto halt;
    return 0;
}
