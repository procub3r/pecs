#ifndef PECS_SSET_H
#define PECS_SSET_H

#include <stdint.h>
#include <stddef.h>

typedef uint32_t index_t;

struct sset {
    index_t* dense;
    index_t* sparse;
    size_t length, capacity;
    size_t initial_capacity;
};

void sset_create(struct sset* sset);
void sset_free(struct sset* sset);
char sset_has(struct sset* sset, index_t element);
void sset_add(struct sset* sset, index_t element);
void sset_remove(struct sset* sset, index_t element);
index_t sset_pop(struct sset* sset);
void sset_print(struct sset* sset);

#endif
