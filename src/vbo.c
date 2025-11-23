#include <vbo.h>

VBO vbo_create(GLint type, bool dynamic) {
    VBO vbo = {
        .type = type,
        .dynamic = dynamic
    };
    glGenBuffers(1, &vbo.handle);
    return vbo;
}

void vbo_bind(VBO vbo) {
    glBindBuffer(vbo.type, vbo.handle);
}

void vbo_buffer(VBO vbo, void *data, size_t offset, size_t count) {
    vbo_bind(vbo);
    glBufferData(vbo.type, count - offset, data, vbo.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void vbo_destroy(VBO vbo) {
    glDeleteBuffers(1, &vbo.handle);
}
