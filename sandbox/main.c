#include <stdio.h>
#include "pecs.h"

// TODO: Maybe move steps 1 - 3 into
// their own set of .h and .c files
// so more than one translation unit
// can access the registry.

// 1. Define component structs
typedef struct {
    char* name;
} Tag;

typedef struct {
    int x, y;
} Position;

typedef struct {
    int x, y, w, h;
} BoxCollider;

// 2. Create enum with Component IDs of structs.
//    This will set the Component ID of every
//    struct to a unique integer.
enum component_type_id {
    COMPONENT_ID(Tag),
    COMPONENT_ID(Position),
    COMPONENT_ID(BoxCollider),
};

// 3. Make a registry, and register all component
//    types in it using the COMPONENT_REG macro.
struct registry reg = {
    COMPONENT_REG(Position),
    COMPONENT_REG(BoxCollider),
    COMPONENT_REG(Tag),
};

int main() {
    // 4. Create the registry and initialize it
    registry_create(&reg);

    // 5. Free the registry when it is no longer in use
    registry_free(&reg);
}
