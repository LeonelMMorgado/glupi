#ifndef _VBO_H
#define _VBO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct _vbo {
    GLuint handle;
    GLint type;
    bool dynamic;
} VBO;

VBO vbo_create(GLint type, bool dynamic);
void vbo_bind(VBO vbo);
void vbo_buffer(VBO vbo, void *data, size_t offset, size_t count);
void vbo_destroy(VBO vbo);

#endif

