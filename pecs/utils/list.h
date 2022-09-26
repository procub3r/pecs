#ifndef PECS_LIST_H
#define PECS_LIST_H

#include <stdint.h>
#include <stdlib.h>

struct list {
    uint8_t* raw;
    size_t element_size;
    size_t length, capacity;
    size_t initial_capacity;
};

void list_create(struct list* list);
void list_free(struct list* list);
void* list_get(struct list* list, size_t index);
void* list_get_last(struct list* list);
void list_add(struct list* list, void* element);
void list_remove(struct list* list, size_t index);

#endif
