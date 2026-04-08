#include <mesh.h>
#include <stdlib.h>
#include <file_util.h>
#include <strcts.h>
#include <color.h>

Mesh *mesh_create(Vertex *vertexes, size_t size_vertexes, Vec3 *indexes, size_t size_indexes) {
    Mesh *m = malloc(sizeof(Mesh));

    m->vertexes = vertexes;
	m->size_vertexes = size_vertexes;
    m->indexes = indexes;
	m->size_indexes = size_indexes;

    m->vao = vao_create();
    m->vbo = vbo_create(GL_ARRAY_BUFFER, true);
    m->ibo = vbo_create(GL_ELEMENT_ARRAY_BUFFER, true);

    vao_bind(m->vao);
    vbo_buffer(m->vbo, m->vertexes, 0, array_size(m->vertexes) * sizeof(Vertex));
    vbo_buffer(m->ibo, m->indexes, 0, array_size(m->indexes) * sizeof(Vec3));

    vao_attr(m->vao, m->vbo, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, vert_pos));
    vao_attr(m->vao, m->vbo, 1, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, vert_color));
    vao_attr(m->vao, m->vbo, 2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, uv));
    vao_attr(m->vao, m->vbo, 3, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, normal));

    vao_bind((VAO){0});
    
    return m;
}

void _read_until_nl(char *file, size_t *pos_f) {
	if(!file) return;
	while(file[*pos_f] != '\n') {
		if(file[*pos_f] == '\0') break;
		(*pos_f)++;
	}
	(*pos_f)++;
}

void _read_loop(char *file, Vertex **vertexes, Vec3 **indexes) {
	size_t pos_f = 0;
	while(file[pos_f] != '\0') {
		if(file[pos_f] == 'v') {
			pos_f++;
			if(file[pos_f] == 't') ; //_read_until_nl(file); //building blocks for the future
			if(file[pos_f] == 'n') ; //_read_until_nl(file); //building blocks for the future
			if(file[pos_f] == 'p') ; //_read_until_nl(file); //building blocks for the future
			if(file[pos_f] == ' ') {
				pos_f++;
				float vert_x, vert_y, vert_z;
				sscanf(file, "%f %f %f", &vert_x, &vert_y, &vert_z);
				Vec3 vec_read = vec3_float(vert_x, vert_y, vert_z);
				Vertex vertex = {0};
				vertex.vert_pos = vec_read;
				vertex.vert_color = get_rgba_vec4(COLOR_WHITEA);
				array_push(*vertexes, vertex);
			}
		}
		else if(file[pos_f] == 'f') {
			if(*(file + 1) != ' ') { _read_until_nl(file, &pos_f); continue; }
			file++;
			file++;
			int v1, v2, v3;
			sscanf(file, "%d %d %d", &v1, &v2, &v3);
			//sscanf(file, "%d%*[^ ] %d%*[^ ] %d%*[^ ]", &v1, &v2, &v3);
			Vec3 index = vec3_ivec3(ivec3_int(v1 - 1, v2 - 1, v3 - 1));
			array_push(*indexes, index);
		}
		else if(file[pos_f] == '#') ;
		else ;
		_read_until_nl(file, &pos_f);
	}
}

Mesh *mesh_create_from_file(const char *file_path) {
	char *file_content = file_read(file_path);
	if(!file_content) return NULL;

	Vertex *vertexes = NULL;
	Vec3 *indexes = NULL;
	_read_loop(file_content, &vertexes, &indexes);

	free(file_content);

	array_fit(vertexes);
	array_fit(indexes);

	size_t vs = array_size(vertexes);
	size_t is = array_size(indexes);
	Mesh *m = mesh_create(vertexes, vs, indexes, is);

	return m;
}

void mesh_destroy(Mesh **mesh) {
    if(!mesh) return;
    if(!*mesh) return;
    if((*mesh)->vertexes) array_destroy((*mesh)->vertexes);
    if((*mesh)->indexes) array_destroy((*mesh)->indexes);
    vao_destroy((*mesh)->vao);
    vbo_destroy((*mesh)->vbo);
    vbo_destroy((*mesh)->ibo);
    free(*mesh);
    *mesh = NULL;
}

