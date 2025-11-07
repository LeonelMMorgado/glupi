#ifndef _MESH_H
#define _MESH_H

#include <stdlib.h>
#include <vmm/vec2.h>
#include <vmm/vec3.h>
#include <vmm/vec4.h>

typedef struct _vert {
    Vector3 vert_pos;
    Vector4 vert_color;
    Vector2 uv;
    Vector3 normal;
} Vertex;

typedef struct _mesh {
    Vertex *vertexes; size_t vert_size;
    Vector3 *indexes; size_t index_size;
} Mesh;

Mesh *alloc_mesh(size_t vert_size, size_t index_size);
Mesh *create_mesh(void);
void load_mesh_file(Mesh *mesh, const char *file);
void destroy_mesh(Mesh *mesh);

#endif

