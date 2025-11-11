#include <renderer.h>
#include <stdlib.h>

Renderer *renderer_init(Camera *camera, Shader *shader, Vector4 clear_color) {
    Renderer *r = malloc(sizeof(Renderer));
    r->camera = camera;
    r->shader = shader;
    r->clear_color = clear_color;
    return r;
}

void renderer_set_camera(Renderer *renderer, Camera *camera) {
    renderer->camera = camera;
}

void renderer_set_shader(Renderer *renderer, Shader *shader) {
    renderer->shader = shader;
}

void renderer_delete(Renderer *renderer) {
    camera_delete(renderer->camera);
    shader_delete(renderer->shader);
    free(renderer);
}
