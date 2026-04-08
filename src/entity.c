#include <entity.h>

Entity *entity_create(Vec3 pos, Vec3 rot, Vec3 scale, Mesh *mesh, Texture *tex) {
    Entity *ent = calloc(1, sizeof(Entity));
    ent->model = mat4_make_model(pos, rot, scale);
    ent->position = pos;
    ent->rotation = rot;
    ent->scale = scale;
    if(mesh) ent->mesh = mesh;
    if(tex) ent->tex = tex;
    return ent;
}

void entity_destroy(Entity **ent) {
    if(!ent) return;
    if(!*ent) return;
    if((*ent)->mesh) mesh_destroy(&((*ent)->mesh));
    if((*ent)->tex) texture_destroy(&((*ent)->tex));
    free(*ent);
    *ent = NULL;
}
