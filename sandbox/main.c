#include <stdio.h>
#include "pecs.h"

struct component {
    int x, y, w, h;
    char* name;
};

int main() {
    struct list list = {
        .element_size = sizeof(struct component),
        .initial_capacity = 4
    };
    list_create(&list);
    list_add(&list, &(struct component){.x = 1, .y = 2, .w = 3, .h = 4, .name = "FIRST"});
    list_add(&list, &(struct component){.x = 2, .y = 3, .w = 4, .h = 5, .name = "SECON"});
    list_add(&list, &(struct component){.x = 3, .y = 4, .w = 5, .h = 6, .name = "THIRD"});
    list_add(&list, &(struct component){.x = 4, .y = 5, .w = 6, .h = 7, .name = "FOURT"});
    list_add(&list, &(struct component){.x = 5, .y = 6, .w = 7, .h = 8, .name = "FIFTH"});
    list_remove(&list, 2);

    for (int i = 0; i < list.length; i++) {
        struct component* c = list_get(&list, i);
        printf("%d, %d, %d, %d, %s\n", c->x, c->y, c->w, c->h, c->name);
    }
    list_free(&list);
}
