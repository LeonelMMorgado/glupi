#include <renderer.h>
#include <stdbool.h>
#include <shader.h>
#include <camera.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <vao.h>
#include <vbo.h>
#include <mesh.h>
#include <strcts.h>
#include <gl_util.h>

#ifndef DEBUG_COLOR
#define DEBUG_COLOR COLOR_PURPLEA
#endif

Renderer *renderer_create(Camera *camera, Shader *shader, ColorRGBA clear_color) {
	printf("Creating Renderer\n");
    Renderer *r = calloc(1, sizeof(Renderer));
    r->camera = camera;
    r->shader = shader;
    r->clear_color = get_rgba_vec4(clear_color);
  
    return r;
}

void renderer_set_camera(Renderer *renderer, Camera *camera) {
    renderer->camera = camera;
}

void renderer_set_shader(Renderer *renderer, Shader *shader) {
    renderer->shader = shader;
}

void renderer_clear(Renderer *renderer) {
    glClearColor(renderer->clear_color.x, renderer->clear_color.y, renderer->clear_color.z, renderer->clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer_view_proj(Renderer *renderer) {
	shader_use(renderer->shader);
    shader_set_uniform_view_proj(renderer->shader, renderer->camera->view_proj);
}

void renderer_color(Renderer *renderer, Mesh *mesh, ColorRGBA color) {
	shader_set_uniform_vec4(renderer->shader, "uColor", get_rgba_vec4(color));

	glDrawElements(GL_TRIANGLES, (GLsizei)mesh->size_indexes, GL_UNSIGNED_INT, 0);
	glCheckError();
}

void renderer_texture(Renderer *renderer, Mesh *mesh, Texture *texture, ColorRGBA color) {
    texture_bind(texture);
	shader_set_uniform_vec4(renderer->shader, "uColor", get_rgba_vec4(color));

    glDrawElements(GL_TRIANGLES, (GLsizei)mesh->size_indexes, GL_UNSIGNED_INT, 0);
	glCheckError();
}

void renderer_entity(Renderer *renderer, Entity *entity) {
    if(!entity || !renderer) return;
    if(!entity->mesh || !renderer->shader) return;
    //FIXME: change how colors are treated
	shader_use(renderer->shader);
    shader_set_uniform_mat4(renderer->shader, "model", entity->model);
	glCheckError();
    vao_bind(entity->mesh->vao);

	if(entity->texture)
		renderer_texture(renderer, entity->mesh, entity->texture, COLOR_WHITEA);
	else
		renderer_color(renderer, entity->mesh, DEBUG_COLOR);
}

void renderer_destroy(Renderer **renderer) {
    if(!renderer) return;
    if(!*renderer) return;
    if((*renderer)->shader) shader_destroy(&((*renderer)->shader));
    if((*renderer)->camera) camera_destroy(&((*renderer)->camera));
    free(*renderer);
    *renderer = NULL;
}
