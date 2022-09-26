#include <stdio.h>
#include "pecs.h"
#include "components.h"

// Make a registry, and register all component
// types in it using the COMPONENT_REG macro.
struct registry reg = {
    COMPONENT_REG(Health),
    COMPONENT_REG(Tag),
    COMPONENT_REG(Position),
    COMPONENT_REG(BoxCollider),
    COMPONENT_REG(Texture),
};

int main() {
    // Create the registry and initialize it.
    registry_create(&reg);

    // Free the registry when it is no longer in use
    registry_free(&reg);
}
