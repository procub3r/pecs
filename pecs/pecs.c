#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pecs.h"

index_t initial_entity_count = 4;

void registry_create(struct registry* reg) {
    reg->entity_count = 0;
    reg->destroyed_entities = (struct sset){.initial_capacity = initial_entity_count};
    sset_create(&reg->destroyed_entities);

    reg->entity_signatures = (struct list){
        .element_size = sizeof(index_t),
        .initial_capacity = initial_entity_count
    };
    list_create(&reg->entity_signatures);

    for (int i = 0; i < sizeof(index_t) * 8; i++) {
        if (reg->component_sizes[i] == 0) {
            continue;
        }
        reg->component_arrays[i].map = (struct sset){.initial_capacity = initial_entity_count};
        sset_create(&reg->component_arrays[i].map);
        reg->component_arrays[i].components = (struct list){
            .element_size = reg->component_sizes[i],
            .initial_capacity = initial_entity_count
        };
        list_create(&reg->component_arrays[i].components);
        printf("[PECS]: MALLOC'D %u * %zu bytes for component array %d\n", initial_entity_count, reg->component_sizes[i], i);
    }
}

void registry_free(struct registry* reg) {
    sset_free(&reg->destroyed_entities);
}

// TODO: Update entity_{create,destroy}() to account for components
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

char component_has_(struct registry* reg, entity_t entity, index_t component_id) {
    index_t* signature = list_get(&reg->entity_signatures, entity);
    return (*signature & (1 << component_id)) != 0;
}

void* component_add_(struct registry* reg, entity_t entity, index_t component_id) {
    assert(!component_has_(reg, entity, component_id));
    index_t* signature = list_get(&reg->entity_signatures, entity);
    *signature |= 1 << component_id;

    sset_add(&reg->component_arrays[component_id].map, entity);
    reg->component_arrays[component_id].components.length++;
    return list_get_last(&reg->component_arrays[component_id].components);
}

void* component_get_(struct registry* reg, entity_t entity, index_t component_id) {
    return list_get(&reg->component_arrays[component_id].components, reg->component_arrays[component_id].map.sparse[entity]);
}

void component_remove_(struct registry* reg, entity_t entity, index_t component_id) {
    assert(component_has_(reg, entity, component_id));
    index_t* signature = list_get(&reg->entity_signatures, entity);
    *signature &= ~(1 << component_id);

    list_remove(&reg->component_arrays[component_id].components, reg->component_arrays[component_id].map.sparse[entity]);
    sset_remove(&reg->component_arrays[component_id].map, entity);
}
