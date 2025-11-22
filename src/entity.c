#include <entity.h>

Entity *init_entity(Vector3 pos, Vector3 rot, Vector3 scale, Mesh *mesh, Texture *tex) {
    Entity *ent = calloc(1, sizeof(Entity));
    ent->model = mat4_make_model(pos, rot, scale);
    ent->position = pos;
    ent->rotation = rot;
    ent->scale = scale;
    if(mesh) ent->mesh = mesh;
    if(tex) ent->tex = tex;
    return ent;
}

void destroy_entity(Entity **ent) {
    if(!ent) return;
    if(!*ent) return;
    if((*ent)->mesh) mesh_destroy(&((*ent)->mesh));
    if((*ent)->tex) texture_destroy(&((*ent)->tex));
    free(*ent);
    *ent = NULL;
}
