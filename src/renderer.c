#include <renderer.h>
#include <stdlib.h>
#include <stddef.h>
#include <mesh.h>

#ifndef DEBUG_COLOR
#define DEBUG_COLOR COLOR_PURPLEA
#endif

Renderer *renderer_init(Camera *camera, Shader *shader, Vector4 clear_color) {
    Renderer *r = calloc(1, sizeof(Renderer));
    r->camera = camera;
    r->shader = shader;
    r->clear_color = clear_color;
  
    r->vao = vao_create();
    r->vbo = vbo_create(GL_ARRAY_BUFFER, true);
    r->ibo = vbo_create(GL_ELEMENT_ARRAY_BUFFER, true);
    return r;
}

void renderer_set_camera(Renderer *renderer, Camera *camera) {
    renderer->camera = camera;
}

void renderer_set_shader(Renderer *renderer, Shader *shader) {
    renderer->shader = shader;
}

void renderer_color(Renderer *renderer, Mesh *mesh, ColorRGBA color, Mat4 model) {
    //FIXME:
    //TODO:
}

void renderer_texture(Renderer *renderer, Mesh *mesh, Texture *texture, ColorRGBA color, Mat4 model) {
    //FIXME: make function function
    //TODO: pass color to shader, pass right shader
    glBindVertexArray(renderer->vao.handle);
  
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo.handle);
    glBufferData(GL_ARRAY_BUFFER, mesh->vert_size * sizeof(Vertex), mesh->vertexes, GL_STATIC_DRAW);
  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->ibo.handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->index_size * sizeof(size_t), mesh->indexes, GL_STATIC_DRAW);
  
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, vert_pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, vert_color));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(0);
  
    glBindTexture(GL_TEXTURE_2D, texture->handle);
}

void renderer_entity(Renderer *renderer, Entity *entity, Texture *texture) {
    if(!entity) return;
    if(!texture) {
      renderer_color(renderer, entity->mesh, DEBUG_COLOR, entity->model);
      return;
    }
    renderer_texture(renderer, entity->mesh, texture, COLOR_WHITEA, entity->model);
}

void renderer_destroy(Renderer *renderer) {
    // FIXME: user should call destroy on camera and shader?
    vao_delete(renderer->vao);
    vbo_delete(renderer->vbo);
    vbo_delete(renderer->ibo);
    free(renderer);
}
