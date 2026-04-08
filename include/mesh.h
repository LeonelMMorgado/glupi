#ifndef _MESH_H
#define _MESH_H

#include <stdlib.h>
#include <vmm/vec2.h>
#include <vmm/vec3.h>
#include <vmm/vec4.h>
#include <vbo.h>
#include <vao.h>

typedef struct _vert {
    Vec3 vert_pos;
    Vec4 vert_color;
    Vec2 uv;
    Vec3 normal;
} Vertex;

typedef struct _mesh {
    Vertex *vertexes; size_t size_vertexes;
    Vec3 *indexes; size_t size_indexes;

    VBO vbo, ibo;
    VAO vao;
} Mesh;

Mesh *mesh_create(Vertex *vertexes, size_t size_vertexes, Vec3 *indexes, size_t size_indexes);
Mesh *mesh_create_from_file(const char *file_path);
void mesh_destroy(Mesh **mesh);

#endif

