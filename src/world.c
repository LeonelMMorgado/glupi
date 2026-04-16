#include <world.h>
#include <entity.h>
#include <strcts.h>

World *world_create(Entity **entities, size_t size_entities) {
	printf("Creating World\n");
	World *w = malloc(sizeof(World));
	w->entities = entities;
	w->size_entities = size_entities;
	return w;
}

void world_add_entity(World *world, Entity *entity) {
	array_push(world->entities, entity);
	world->size_entities++;
}

void world_destroy(World **world) {
	if(!world || !*world) return;
	for(size_t i = 0; i < (*world)->size_entities; i++) entity_destroy(&((*world)->entities[i]));
	array_destroy((*world)->entities);
	free(*world);
	*world = NULL;
}
