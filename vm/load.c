#include <stand/stivale2.h>
#include <io/io.h>
#include <libc/stdlib.h>

#define MEMMAP_ID 0x2187f79e8612de07

load_mmap(env)
struct stivale2_struct *env; {
    memmap_t map;
    int i;
    map = (memmap_t)stivale2_get_tag(env, MEMMAP_ID);

    for (i=0; i<map->entries;i++) {

    switch(map->memmap[i].type) {
    
    default:
        break; /* unreachable */
    }}

    _io_printf("Amount of entries: %d\n", i);
    RETURN;
}