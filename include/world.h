#ifndef _WORLD_H
#define _WORLD_H

#include <entity.h>

typedef struct _world {
	Entity **entities; size_t size_entities;
} World;

World *world_create(Entity **entities, size_t size_entities);
void world_add_entity(World *world, Entity *entity);
void world_destroy(World **world);

#endif
