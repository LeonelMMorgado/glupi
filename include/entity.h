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
    Texture *tex;
} Entity;

Entity *entity_create(Vec3 pos, Vec3 rot, Vec3 scale, Mesh *mesh, Texture *tex);
void entity_destroy(Entity **ent);

#endif
