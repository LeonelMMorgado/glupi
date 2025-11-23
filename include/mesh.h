#ifndef _MESH_H
#define _MESH_H

#include <stdlib.h>
#include <vmm/vec2.h>
#include <vmm/vec3.h>
#include <vmm/vec4.h>
#include <vbo.h>
#include <vao.h>

typedef struct _vert {
    Vector3 vert_pos;
    Vector4 vert_color;
    Vector2 uv;
    Vector3 normal;
} Vertex;

typedef struct _mesh {
    Vertex *vertexes; size_t vert_size;
    Vector3 *indexes; size_t index_size;

    VBO vbo, ibo;
    VAO vao;
} Mesh;

Mesh *mesh_create(Vertex *vertexes, size_t vert_size, Vector3 *indexes, size_t index_size);
void mesh_load_from_file(Mesh *mesh, const char *file);
void mesh_destroy(Mesh **mesh);

#endif

