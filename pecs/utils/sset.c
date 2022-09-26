#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "sset.h"

void sset_create(struct sset* sset) {
    assert(sset->initial_capacity != 0);
    sset->capacity = sset->initial_capacity;
    sset->length = 0;
    sset->dense = malloc(sset->capacity * sizeof(index_t));
    sset->sparse = malloc(sset->capacity * sizeof(index_t));
}

void sset_free(struct sset* sset) {
    sset->length = 0;
    sset->capacity = 0;
    free(sset->dense);
    free(sset->sparse);
    sset->dense = NULL;
    sset->sparse = NULL;
}

char sset_has(struct sset* sset, index_t element) {
    return sset->sparse[element] < sset->length && sset->dense[sset->sparse[element]] == element;
}

void sset_add(struct sset* sset, index_t element) {
    assert(!sset_has(sset, element));
    if (element >= sset->capacity) {
        while (element >= sset->capacity) {
            sset->capacity *= 2;
        }
        sset->dense = realloc(sset->dense, sset->capacity * sizeof(index_t));
        sset->sparse = realloc(sset->sparse, sset->capacity * sizeof(index_t));
        printf("[PECS]: REALLOC'D SSET\n");
    }
    sset->dense[sset->length] = element;
    sset->sparse[element] = sset->length;
    sset->length++;
}

void sset_remove(struct sset* sset, index_t element) {
    assert(sset_has(sset, element));
    sset->length--;
    sset->dense[sset->sparse[element]] = sset->dense[sset->length];
    sset->sparse[sset->dense[sset->length]] = sset->sparse[element];
}

index_t sset_pop(struct sset* sset) {
    assert(sset->length != 0);
    sset->length--;
    return sset->dense[sset->length];
}

void sset_print(struct sset* sset) {
    printf(" dense: ");
    for (index_t i = 0; i < sset->capacity; i++) {
        printf("%u, ", sset->dense[i]);
    }
    printf("\nsparse: ");
    for (index_t i = 0; i < sset->capacity; i++) {
        printf("%u, ", sset->sparse[i]);
    }
    puts("\n");
}
