#include <stand/stivale2.h>
#include <stdint.h>

typedef struct stivale2_struct *standenv_t;

uintptr_t stivale2_get_tag(e, id) 
standenv_t e;
uint64_t id; {
    struct stivale2_tag *current_tag = (void *)e->tags;
    for (;;) {
        if (current_tag == 0) {
            return 0;
        }

        if (current_tag->identifier == id) {
            return (uintptr_t)current_tag;
        }

        current_tag = (uintptr_t)current_tag->next;
    }
}
/* eof */