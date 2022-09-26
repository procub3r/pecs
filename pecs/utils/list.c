#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

void list_create(struct list* list) {
    assert(list->initial_capacity != 0);
    list->capacity = list->initial_capacity;
    list->length = 0;
    list->raw = malloc(list->capacity * list->element_size);
}

void list_free(struct list* list) {
    list->length = 0;
    list->capacity = 0;
    free(list->raw);
    list->raw = NULL;
}

void* list_get(struct list* list, size_t index) {
    return list->raw + index * list->element_size;
}

void* list_get_last(struct list* list) {
    return list_get(list, list->length - 1);
}

void list_add(struct list* list, void* element) {
    if (list->length == list->capacity) {
        list->capacity *= 2;
        list->raw = realloc(list->raw, list->capacity * list->element_size);
        printf("[PECS]: REALLOC'D LIST\n");
    }
    memcpy(list_get(list, list->length), element, list->element_size);
    list->length++;
}

void list_remove(struct list* list, size_t index) {
    assert(index < list->length);
    list->length--;
    // Don't bother memcpy'ing if the element to remove is the last one
    if (index == list->length) {
        memcpy(list_get(list, index), list_get(list, list->length), list->element_size);
    }
}

void list_remove_last(struct list* list) {
    list_remove(list, list->length - 1);
}
