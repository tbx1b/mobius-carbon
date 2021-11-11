#include <chips/mmu.h>
#include <stddef.h>
#include <sys/defs.h>
#include <vm/paging.h>

int vminit1() {
  size_t i;

  for (i = 0; i < 0x400; i++) {
    // flags: supervisor (executive-only)
    //        read-write
    //        not present
    page_directory[i] = 0x00000002;
    // idem:
    page_table[i] = (i * 0x1000) | 3;
  }
  // make the first page table present
  page_directory[0] = ((unsigned int)page_table) | 3;
  RETURN;
}

int vminit2() {
  load_pdir(page_directory);
  enable_paging();
  RETURN;
}