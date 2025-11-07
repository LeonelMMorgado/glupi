#ifndef _VAO_H
#define _VAO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vbo.h>

typedef struct _vao {
    GLuint handle;
} VAO;

VAO vao_create(void);
void vao_delete(VAO vao);
void vao_bind(VAO vao);
void vao_attr(VAO vao, VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

#endif

