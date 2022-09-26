#include <stdio.h>
#include "pecs.h"

int main() {
    struct registry reg;
    registry_create(&reg);

    entity_t e0 = entity_create(&reg);
    entity_t e1 = entity_create(&reg);
    entity_t e2 = entity_create(&reg);
    entity_t e3 = entity_create(&reg);

    entity_destroy(&reg, e2);
    entity_destroy(&reg, e0);
    entity_t e4 = entity_create(&reg);
    entity_t e5 = entity_create(&reg);
    entity_t e6 = entity_create(&reg);

    registry_free(&reg);
}
