#ifndef _ENTITY_H
#define _ENTITY_H

#include <mesh.h>
#include <vmm/vec3.h>
#include <vmm/mat4.h>


typedef struct _entity {
    Vector3 position;
    Mat4 model;
} Entity;

Entity *init_entity(Vector3 pos);
void destroy_entity(Entity *ent);

#endif
