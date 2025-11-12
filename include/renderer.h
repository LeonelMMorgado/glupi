#ifndef _RENDERER_H
#define _RENDERER_H

#include <shader.h>
#include <camera.h>
#include <texture.h>
#include <vmm/vec4.h>
#include <vmm/mat4.h>
#include <color.h>
#include <vbo.h>
#include <vao.h>
#include <entity.h>

typedef struct _renderer {
    Shader *shader;
    Camera *camera;
    Vector4 clear_color;
} Renderer;

Renderer *renderer_create(Camera *camera, Shader *shader, Vector4 clear_color);
void renderer_set_camera(Renderer *renderer, Camera *camera);
void renderer_set_shader(Renderer *renderer, Shader *shader);
void renderer_delete(Renderer **renderer);

#endif

