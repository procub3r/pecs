#ifndef PECS_H
#define PECS_H

#include <stdint.h>
#include "utils/sset.h"

// Generate Component ID from Component Type
#define COMPONENT_ID(T) PECS_COMPONENT_ID_##T
// Weird macro that registers a component in a registry. Look at example
// code (if it exists) to see how it is used.
#define COMPONENT_REG(T) .component_sizes[COMPONENT_ID(T)] = sizeof(T)

typedef index_t entity_t;

struct component_array {
    struct sset map; // Maps components to entities
    uint8_t* components;
};

struct registry {
    entity_t entity_count;
    struct sset destroyed_entities;
    size_t component_sizes[sizeof(index_t) * 8];
    struct component_array component_arrays[sizeof(index_t) * 8];
};

void registry_create(struct registry* reg);
void registry_free(struct registry* reg);

entity_t entity_create(struct registry* reg);
void entity_destroy(struct registry* reg, entity_t entity);

#endif
