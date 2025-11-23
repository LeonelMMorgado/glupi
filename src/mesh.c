#include <mesh.h>
#include <stdlib.h>

Mesh *mesh_create(Vertex *vertexes, size_t vert_size, Vector3 *indexes, size_t index_size) {
    Mesh *m = malloc(sizeof(Mesh));

    m->vertexes = vertexes;
    m->vert_size = vert_size;
    m->indexes = indexes;
    m->index_size = index_size;

    m->vao = vao_create();
    m->vbo = vbo_create(GL_ARRAY_BUFFER, true);
    m->ibo = vbo_create(GL_ELEMENT_ARRAY_BUFFER, true);

    vao_bind(m->vao);
    vbo_buffer(m->vbo, m->vertexes, 0, m->vert_size * sizeof(Vertex));
    vbo_buffer(m->ibo, m->indexes, 0, m->index_size * sizeof(Vector3));

    vao_attr(m->vao, m->vbo, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, vert_pos));
    vao_attr(m->vao, m->vbo, 1, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, vert_color));
    vao_attr(m->vao, m->vbo, 2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, uv));
    vao_attr(m->vao, m->vbo, 3, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, normal));

    vao_bind((VAO){0});
    
    return m;
}

void mesh_destroy(Mesh **mesh) {
    if(!mesh) return;
    if(!*mesh) return;
    if((*mesh)->vertexes) free((*mesh)->vertexes);
    if((*mesh)->indexes) free((*mesh)->indexes);
    vao_destroy((*mesh)->vao);
    vbo_destroy((*mesh)->vbo);
    vbo_destroy((*mesh)->ibo);
    free(*mesh);
    *mesh = NULL;
}

