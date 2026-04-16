#include <mesh.h>
#include <stdlib.h>
#include <file_util.h>
#include <strcts.h>
#include <color.h>
#include <inttypes.h>

Mesh *mesh_create(Vertex *vertexes, size_t size_vertexes, uint32_t *indexes, size_t size_indexes) {
    Mesh *m = malloc(sizeof(Mesh));

    m->vertexes = vertexes;
	m->size_vertexes = size_vertexes;
    m->indexes = indexes;
	m->size_indexes = size_indexes;

    m->vao = vao_create();
    m->vbo = vbo_create(GL_ARRAY_BUFFER, false);
    m->ibo = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    vao_bind(m->vao);
    vbo_buffer(m->vbo, &(m->vertexes[0]), 0, m->size_vertexes * sizeof(Vertex));
    vbo_buffer(m->ibo, &(m->indexes[0]), 0, m->size_indexes * sizeof(uint32_t));

    vao_attr(m->vao, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, vert_pos));
    vao_attr(m->vao, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, normal));
    vao_attr(m->vao, 2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, uv));

    vao_bind((VAO){0});
    
    return m;
}

Vertex vertex_create(Vec3 pos, Vec3 normal, Vec2 uv) {
	Vertex v = {0};
	v.vert_pos = pos;
	v.normal = normal;
	v.uv = uv;
	return v;
}

void _read_until_nl(char **file) {
	if(!file || !*file) return;
	while(**file != '\n') {
		if(**file == '\0') break;
		(*file)++;
	}
	if(**file != '\0') (*file)++;
}

void _read_whitespaces(char **file) {
	if(!file || !*file) return;
	while(**file == ' ' || **file == '\t') {
		(*file)++;
	}
}

void _read_idxs(char *vinfo, int32_t *v_idx, int32_t *t_idx, int32_t *n_idx) { //vertex info, vertice index, texture index and normal index
	*t_idx = INT32_MAX;
	*n_idx = INT32_MAX;
	char *s1 = strchr(vinfo, '/');
	if(!s1) {
		sscanf(vinfo, "%" SCNd32, v_idx);
		return;
	}
	s1++;
	char *s2 = strchr(s1, '/');
	if(!s2) {
		sscanf(vinfo, "%" SCNd32 "/%" SCNd32, v_idx, t_idx);
		return;
	}
	if(s2 == s1) {
		sscanf(vinfo, "%" SCNd32 "//%" SCNd32, v_idx, n_idx);
		return;
	}
	sscanf(vinfo, "%" SCNd32 "/%" SCNd32 "/%" SCNd32, v_idx, t_idx, n_idx);
}

void _process_face(char *vert, Vec3 *verts, Vec3 *normals, Vec2 *uvs, HashMap *vert_map, Vertex **vertexes, uint32_t **indexes) {
	int32_t v_idx = 0, n_idx = 0, t_idx = 0;
	_read_idxs(vert, &v_idx, &t_idx, &n_idx);

	//x_idx > 0 => 1..n indexed => transform to 0..n-1
	//x_idx < 0 => relative indexed => uses last added
	if(v_idx > 0) v_idx -= 1;
	else if(verts) v_idx = array_size(verts) + v_idx;
	if(t_idx != INT32_MAX) {
		if(t_idx > 0) t_idx -= 1;
		else if(uvs) t_idx = array_size(uvs) + t_idx;
	}
	if(n_idx != INT32_MAX) {
		if(n_idx > 0) n_idx -= 1;
		else if(normals) n_idx = array_size(normals) + n_idx;
	}
	Vec3 v_add = verts && v_idx >= 0 && v_idx < array_size(verts) ? verts[v_idx] : vec3_zero();
	Vec3 n_add = normals && n_idx < INT32_MAX && n_idx >= 0 && n_idx < array_size(normals) ? normals[n_idx] : vec3_zero();
	Vec2 t_add = uvs && t_idx < INT32_MAX && t_idx >= 0 && t_idx < array_size(uvs) ? uvs[t_idx] : vec2_zero();
	Vertex vrtx = vertex_create(v_add, n_add, t_add);
	uint32_t *idx = (uint32_t*)hm_get_value(vert_map, &vrtx);
	if(idx) {
		array_push(*indexes, *idx);
		return;
	}
	array_push(*vertexes, vrtx);
	uint32_t indx = array_size(*vertexes) - 1; //should just be idx but i guess i cant shadow it...
	hm_add(vert_map, &vrtx, &indx);
	array_push(*indexes, indx);

}

void _read_face(char *file, Vec3 *verts, Vec3 *normals, Vec2 *uvs, HashMap *vert_map, Vertex **vertexes, uint32_t **indexes) {
	char *nnl = strchr(file, '\n');
	if(!nnl) nnl = strchr(file, '\0');
	char *cpy = strndup(file, nnl-file);
	char *sv_ptr = cpy;
	char *vert[32] = {0};
	int count = 0;
	vert[count++] = strtok_r(cpy, " \t", &sv_ptr);
	while((vert[count++] = strtok_r(NULL, " \t", &sv_ptr))) {
		if(vert[count-1][0] == ' ' || vert[count-1][0] == '\t')
			count--;
	}
	count--;
	for(int i = 1; i < count-1; i++) {
		_process_face(vert[0]  , verts, normals, uvs, vert_map, vertexes, indexes);
		_process_face(vert[i]  , verts, normals, uvs, vert_map, vertexes, indexes);
		_process_face(vert[i+1], verts, normals, uvs, vert_map, vertexes, indexes);
	}
	free(cpy);
}

void _obj_read_loop(char *file, Vertex **vertexes, uint32_t **indexes) {
	Vec3 *verts = NULL;
	Vec3 *normals = NULL;
	Vec2 *uvs = NULL;
	HashMap *vert_map = hm_create(sizeof(Vertex), sizeof(uint32_t));
	while(*file != '\0') {
		if(*file == 'v') {
			file++;
			if(*file == 'p')
				; //_read_until_nl(file);
			if(*file == 't') { //texture indexes
				file++;
				_read_whitespaces(&file);
				float uv_u, uv_v;
				sscanf(file, "%f %f", &uv_u, &uv_v);
				Vec2 uv_read = vec2_float(uv_u, uv_v);
				array_push(uvs, uv_read);
			}
			if(*file == 'n') { //normals indexes
				file++;
				_read_whitespaces(&file);
				float normal_x, normal_y, normal_z;
				sscanf(file, "%f %f %f", &normal_x, &normal_y, &normal_z);
				Vec3 normal_read = vec3_float(normal_x, normal_y, normal_z);
				array_push(normals, normal_read);
			}
			if(*file == ' ' || *file == '\t') { //vertices indexes
				_read_whitespaces(&file);
				float vert_x, vert_y, vert_z;
				sscanf(file, "%f %f %f", &vert_x, &vert_y, &vert_z);
				Vec3 vec_read = vec3_float(vert_x, vert_y, vert_z);
				array_push(verts, vec_read);
			}
		}
		else if(*file == 'f') {
			file++;
			if(*file != ' ' || *file == '\t') { _read_until_nl(&file); continue; }
			_read_whitespaces(&file);
			_read_face(file, verts, normals, uvs, vert_map, vertexes, indexes);
		}
		else if(*file == '#') ;
		else ;
		_read_until_nl(&file);
	}
	array_destroy(verts);
	array_destroy(uvs);
	array_destroy(normals);
	hm_destroy(&vert_map);
}

Mesh *mesh_create_from_file(const char *file_path) {
	char *file_content = file_read(file_path);
	if(!file_content) return NULL;

	Vertex *vertexes = NULL;
	uint32_t *indexes = NULL;
	_obj_read_loop(file_content, &vertexes, &indexes);

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

