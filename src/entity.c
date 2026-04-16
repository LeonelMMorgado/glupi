#include <entity.h>

Entity *entity_create(Vec3 position, Vec3 rotation, Vec3 scale, Mesh *mesh, Texture *texture) {
    Entity *ent = calloc(1, sizeof(Entity));
    ent->position = position;
    ent->rotation = rotation;
    ent->scale = scale;
	entity_update_model(ent);
    if(mesh) ent->mesh = mesh;
    if(texture) ent->texture = texture;
    return ent;
}

Vec3 entity_position(Entity *entity) {
	return entity->position;
}

Vec3 entity_rotation(Entity *entity) {
	return entity->rotation;
}

Vec3 entity_scale(Entity *entity) {
	return entity->scale;
}

void entity_update_position(Entity *entity, Vec3 new_position) {
	entity->position = new_position;
	entity_update_model(entity);
}

void entity_update_rotation(Entity *entity, Vec3 new_rotation) {
	entity->rotation = new_rotation;
	entity_update_model(entity);
}

void entity_update_scale(Entity *entity, Vec3 new_scale) {
	entity->scale = new_scale;
	entity_update_model(entity);
}

void entity_update_model(Entity *entity) {
	entity->model = mat4_make_model(entity->position, entity->rotation, entity->scale);
}

void entity_destroy(Entity **entity) {
    if(!entity) return;
    if(!*entity) return;
    if((*entity)->mesh) mesh_destroy(&((*entity)->mesh));
    if((*entity)->texture) texture_destroy(&((*entity)->texture));
    free(*entity);
    *entity = NULL;
}
