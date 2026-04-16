#ifndef _ENTITY_H
#define _ENTITY_H

#include <mesh.h>
#include <vmm/vec3.h>
#include <vmm/mat4.h>
#include <texture.h>

typedef struct _entity {
    Vec3 position, rotation, scale;
    Mat4 model;
    Mesh *mesh;
    Texture *texture;
} Entity;

Entity *entity_create(Vec3 position, Vec3 rotation, Vec3 scale, Mesh *mesh, Texture *texture);
Vec3 entity_position(Entity *entity);
Vec3 entity_rotation(Entity *entity);
Vec3 entity_scale(Entity *entity);
void entity_update_position(Entity *entity, Vec3 new_position);
void entity_update_rotation(Entity *entity, Vec3 new_rotation);
void entity_update_scale(Entity *entity, Vec3 new_scale);
void entity_update_model(Entity *entity);
void entity_destroy(Entity **entity);

#endif
