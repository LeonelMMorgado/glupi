#include <entity.h>
#include <stdlib.h>

Entity *init_entity(Vector3 pos) {
    Entity *ent = calloc(1, sizeof(Entity));
    ent->model = mat4_make_model(pos, (Vector3){0}, (Vector3){{1, 1, 1}});
    ent->position = pos;
    return ent;
}

