#include <stdio.h>
#include <stdlib.h>
#include "pecs.h"

void registry_create(struct registry* reg) {
    reg->entity_count = 0;
    reg->destroyed_entities = (struct sset){.initial_capacity = 4};
    sset_create(&reg->destroyed_entities);

    for (int i = 0; i < sizeof(index_t) * 8; i++) {
        reg->component_arrays[i].map = (struct sset) {.initial_capacity = 4};
        // Make space for just 4 components of every component type for now.
        // How to manage this memory? Manually realloc if length exceeds capacity?
        // Abstract this functionality into a list struct? Stay tuned to find out!
        reg->component_arrays[i].components = malloc(4 * reg->component_sizes[i]);
        printf("[PECS]: MALLOC'D %u * %zu bytes for component array %d\n", 4, reg->component_sizes[i], i);
    }
}

void registry_free(struct registry* reg) {
    sset_free(&reg->destroyed_entities);
}

entity_t entity_create(struct registry* reg) {
    if (reg->destroyed_entities.length == 0) {
        printf("[PECS]: Entity %u created\n", reg->entity_count);
        return reg->entity_count++;
    }
    entity_t e = sset_pop(&reg->destroyed_entities);
    printf("[PECS]: Entity %u created\n", e);
    return e;
}

void entity_destroy(struct registry* reg, entity_t entity) {
    printf("[PECS]: Entity %u destroyed\n", entity);
    sset_add(&reg->destroyed_entities, entity);
}
