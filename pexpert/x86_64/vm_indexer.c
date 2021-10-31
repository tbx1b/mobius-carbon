/**
 *  @file vm_i.c
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
 *  @brief Virtual memory indexing utilities
 *
 */

#include <vm/vm.h>
#include <vm/ptab.h>
#include <vm/index.h>

vm_mk_page_map_index(vm_page_map_index_t *self, uintptr_t  virtual_address)
{
    virtual_address         >>= 12;
    self->page_index        = virtual_address & 0x1FF;

    virtual_address         >>= 9;
    self->page_table_index  = virtual_address & 0x1FF;

    virtual_address         >>= 9;
    self->page_dir_index   = virtual_address & 0x1FF;

    virtual_address         >>= 9;
    self->page_dir_ptr_index = virtual_address & 0x1FF;
    
    return 1;
}
