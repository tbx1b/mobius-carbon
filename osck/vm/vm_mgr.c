/**
 *  @file vm_mgr.c
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
 *  @brief Virtual memory remapping
 *
 */

#include "libkern/tty.h"

#include <vm/ptab.h>
#include <vm/vm.h>
#include <vm/mgr.h>
#include <vm/index.h>

#include <carbon/stdint.h>

#include <libkern/string.h>

//extern vm_alloc_t universal_allocator;

vm_mk_page_tab_mgr(vptm_t *self, vm_page_table_t *pml4_address)
{
    self->pml4_address = pml4_address;
    return 1;
}

void os_vm_raw_map(vptm_t *self, uintptr_t virtual, uintptr_t physical)
{
    vm_page_map_index_t indexer;
    vm_mk_page_map_index(&indexer, virtual);
    vm_page_dir_entry_t pde;

    pde = self->pml4_address->entries[indexer.page_dir_ptr_index];
    vm_page_table_t* pdp;
    if (!pde.present) {
        pdp = (vm_page_table_t*)os_vm_alloc();
        memset(pdp, 0, 0x1000);
        pde.address = (uint64_t)pdp >> 12;
        pde.present = true;
        pde.rw = true;
        self->pml4_address->entries[indexer.page_dir_ptr_index] = pde;
    } else {
        pdp = (vm_page_table_t*)((uint64_t)pde.address << 12);
    }
    
    
    pde = pdp->entries[indexer.page_dir_index];
    vm_page_table_t* pd;
    if (!pde.present) {
        pd = (vm_page_table_t*)os_vm_alloc();
        memset(pd, 0, 0x1000);
        pde.address = (uint64_t)pd >> 12;
        pde.present = true;
        pde.rw = true;
        pdp->entries[indexer.page_dir_index] = pde;
    } else {
        pd = (vm_page_table_t*)((uint64_t)pde.address << 12);
    }

    pde = pd->entries[indexer.page_table_index];
    vm_page_table_t* pt;
    if (!pde.present) {
        pt = (vm_page_table_t*)os_vm_alloc();
        memset(pt, 0, 0x1000);
        pde.address = (uint64_t)pt >> 12;
        pde.present = true;
        pde.rw = true;
        pd->entries[indexer.page_table_index] = pde;
    } else {
        pt = (vm_page_table_t*)((uint64_t)pde.address << 12);
    }

    pde = pt->entries[indexer.page_index];
    pde.address = (uint64_t)physical >> 12;
    pde.present = true;
    pde.rw = true;
    pt->entries[indexer.page_index] = pde;
}
