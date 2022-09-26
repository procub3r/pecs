#ifndef ECS_H
#define ECS_H

#include "pecs.h"

typedef struct health {
    int hp;
} Health;

typedef struct tag {
    char* name;
} Tag;

typedef struct position {
    int x, y;
} Position;

typedef struct boxcollider {
    int x, y, w, h;
} BoxCollider;

typedef struct texture {
    char* file;
    int scale_x, scale_y;
} Texture;

enum component_id {
    COMPONENT_ID(Health),
    COMPONENT_ID(Tag),
    COMPONENT_ID(Position),
    COMPONENT_ID(BoxCollider),
    COMPONENT_ID(Texture),
};

#endif
