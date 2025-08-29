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

Shader *create_shader(char * vert_path, char * frag_path);
void use_shader(Shader *program);
void set_uniform_int(Shader *program, char * name, int value);
void get_uniform_int(Shader *program, char * name, int * param);
void set_uniform_uint(Shader *program, char * name, unsigned int value);
void get_uniform_uint(Shader *program, char * name, unsigned int * param);
void set_uniform_float(Shader *program, char * name, float value);
void get_uniform_float(Shader *program, char * name, float * param);
void set_uniform_vec2(Shader *program, char * name, Vector2 vec);
void set_uniform_vec3(Shader *program, char * name, Vector3 vec);
void set_uniform_vec4(Shader *program, char * name, Vector4 vec);
void set_uniform_mat3(Shader *program, char * name, Mat3 mat);
void set_uniform_mat4(Shader *program, char * name, Mat4 mat);
void set_uniform_view_proj(Shader *program, ViewProj view_proj);
void delete_shader(Shader *program);

#endif
