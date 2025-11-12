#ifndef _SHADER_H
#define _SHADER_H
#include <stdbool.h>
#include <glad/glad.h>
#include <vmm/vec2.h>
#include <vmm/vec3.h>
#include <vmm/vec4.h>
#include <vmm/mat3.h>
#include <vmm/mat4.h>
#include <camera.h>

typedef struct _shader {
    GLuint program, fragment, vertex;
} Shader;

Shader *shader_create(char * vert_path, char * frag_path);
void shader_use(Shader *program);
void shader_set_uniform_int(Shader *program, char * name, int value);
void shader_get_uniform_int(Shader *program, char * name, int * param);
void shader_set_uniform_uint(Shader *program, char * name, unsigned int value);
void shader_get_uniform_uint(Shader *program, char * name, unsigned int * param);
void shader_set_uniform_float(Shader *program, char * name, float value);
void shader_get_uniform_float(Shader *program, char * name, float * param);
void shader_set_uniform_vec2(Shader *program, char * name, Vector2 vec);
void shader_set_uniform_vec3(Shader *program, char * name, Vector3 vec);
void shader_set_uniform_vec4(Shader *program, char * name, Vector4 vec);
void shader_set_uniform_mat3(Shader *program, char * name, Mat3 mat);
void shader_set_uniform_mat4(Shader *program, char * name, Mat4 mat);
void shader_set_uniform_view_proj(Shader *program, ViewProj view_proj);
void shader_delete(Shader **program);

#endif

