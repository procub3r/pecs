#include <stdio.h>
#include "pecs.h"

int main() {
    struct sset s = {.initial_capacity = 4};
    sset_create(&s);
    sset_print(&s);

    sset_add(&s, 3);
    sset_print(&s);

    sset_add(&s, 0);
    sset_print(&s);

    sset_add(&s, 4);
    sset_print(&s);

    sset_add(&s, 1);
    sset_print(&s);

    sset_remove(&s, 0);
    sset_print(&s);

    sset_remove(&s, 1);
    sset_print(&s);

    sset_add(&s, 0);
    sset_print(&s);

    sset_add(&s, 1);
    sset_print(&s);

    sset_free(&s);
}
