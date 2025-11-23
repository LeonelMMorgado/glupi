#include <renderer.h>
#include <stdbool.h>
#include <shader.h>
#include <camera.h>
#include <stdlib.h>
#include <stddef.h>
#include <vao.h>
#include <vbo.h>
#include <mesh.h>

#ifndef DEBUG_COLOR
#define DEBUG_COLOR COLOR_PURPLEA
#endif

Renderer *renderer_create(Camera *camera, Shader *shader, ColorRGBA clear_color) {
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
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderer_view_proj(Renderer *renderer) {
    shader_set_uniform_view_proj(renderer->shader, renderer->camera->view_proj);
}

void renderer_color(Renderer *renderer, Mesh *mesh, ColorRGBA color, Mat4 model) {
    //FIXME:
    //TODO:
    shader_set_uniform_mat4(renderer->shader, "model", model);
    vao_bind(mesh->vao);

    glDrawElements(GL_TRIANGLES, mesh->index_size, GL_UNSIGNED_INT, 0);
}

void renderer_texture(Renderer *renderer, Mesh *mesh, Texture *texture, ColorRGBA color, Mat4 model) {
    //FIXME: make function work
    //TODO: pass model to shader, pass right shader
    shader_set_uniform_mat4(renderer->shader, "model", model);
    vao_bind(mesh->vao);
    texture_bind(texture);

    glDrawElements(GL_TRIANGLES, mesh->index_size, GL_UNSIGNED_INT, 0);
}

void renderer_render_entity(Renderer *renderer, Entity *entity) {
    if(!entity || !renderer) return;
    if(!entity->mesh || !renderer->shader) return;
    //FIXME: change how colors are treated
    if(!entity->tex) {
      renderer_color(renderer, entity->mesh, DEBUG_COLOR, entity->model);
      return;
    }
    renderer_texture(renderer, entity->mesh, entity->tex, COLOR_WHITEA, entity->model);
}

void renderer_destroy(Renderer **renderer) {
    if(!renderer) return;
    if(!*renderer) return;
    if((*renderer)->shader) shader_destroy(&((*renderer)->shader));
    if((*renderer)->camera) camera_destroy(&((*renderer)->camera));
    free(*renderer);
    *renderer = NULL;
}
