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
