#include <stdio.h>
#include "pecs.h"

void registry_create(struct registry* reg) {
    reg->entity_count = 0;
    reg->destroyed_entities = (struct sset){.initial_capacity = 4};
    sset_create(&reg->destroyed_entities);
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
