#ifndef PECS_H
#define PECS_H

#include "utils/sset.h"

typedef index_t entity_t;

struct registry {
    entity_t entity_count;
    struct sset destroyed_entities;
};

void registry_create(struct registry* reg);
void registry_free(struct registry* reg);

entity_t entity_create(struct registry* reg);
void entity_destroy(struct registry* reg, entity_t entity);

#endif
