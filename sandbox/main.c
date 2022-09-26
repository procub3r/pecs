#include <stdio.h>
#include "pecs.h"
#include "components.h"

struct registry reg = {
    COMPONENT_REG(Health),
    COMPONENT_REG(Tag),
    COMPONENT_REG(Position),
    COMPONENT_REG(BoxCollider),
    COMPONENT_REG(Texture),
};

entity_t make_obstacle(int x, int y, int w, int h) {
    entity_t e = entity_create(&reg);

    Position* pos = component_add(&reg, e, Position);
    pos->x = x;
    pos->y = y;

    Tag* t = component_add(&reg, e, Tag);
    t->name = "obstacle";

    BoxCollider* b = component_add(&reg, e, BoxCollider);
    b->x = x;
    b->y = y;
    b->w = w;
    b->h = h;

    return e;
}

void print_obstacle(entity_t obstacle) {
    Tag* t = component_get(&reg, obstacle, Tag);
    Position* p = component_get(&reg, obstacle, Position);
    BoxCollider* b = component_get(&reg, obstacle, BoxCollider);
    printf("tag: %s; pos: %d, %d; box collider: %d, %d, %d, %d\n", t->name, p->x, p->y, b->x, b->y, b->w, b->h);
}

int main() {
    registry_create(&reg);

    entity_t obstacle0 = make_obstacle(1337, 42, -255, 256);
    entity_t obstacle1 = make_obstacle(1, -1, 1, -1);
    entity_t obstacle2 = make_obstacle(-2, 2, -2, 2);

    print_obstacle(obstacle0);
    print_obstacle(obstacle1);
    print_obstacle(obstacle2);

    registry_free(&reg);
}
