#include <glad/glad.h>
#include <stdbool.h>
#include <stdlib.h>
#include <shader.h>
#include <file_util.h>

Shader *shader_create(char * vert_path, char * frag_path) {
    if(!vert_path || !frag_path) return 0; //TODO: add way for frag only rendering? 
    int success;
    char infoLog[512];

    Shader *ret = calloc(1, sizeof(Shader));
    if(!ret) return 0;

    //vertex shader creation
    ret->vertex = glCreateShader(GL_VERTEX_SHADER);
    const char * vert_txt = read_file(vert_path);
    if(!vert_txt) {
        free(ret);
        return 0;
    }
    glShaderSource(ret->vertex, 1, &vert_txt, NULL);
    glCompileShader(ret->vertex);
    glGetShaderiv(ret->vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(ret->vertex, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
        printf("%s\n", infoLog);
        free(ret);
        return NULL;
    }
    
    //fragment shader creation
    ret->fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char * frag_txt = read_file(frag_path);
    if(!frag_txt) return 0;
    glShaderSource(ret->fragment, 1, &frag_txt, NULL);
    glCompileShader(ret->fragment);
    glGetShaderiv(ret->fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(ret->fragment, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
        printf("%s\n", infoLog);
        free(ret);
        return NULL;
    }

    free((char*)frag_txt);
    free((char*)vert_txt);

    // link shaders
    ret->program = glCreateProgram();
    glAttachShader(ret->program, ret->vertex);
    glAttachShader(ret->program, ret->fragment);
    glLinkProgram(ret->program);
    // check for linking errors
    glGetProgramiv(ret->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ret->program, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
        printf("%s\n", infoLog);
        return 0;
    }
    // glDeleteShader(ret->vertex);
    // glDeleteShader(ret->fragment);
    // glDeleteShader(ret->compute);
    return ret;
}

void shader_use(Shader *program) {
    glUseProgram(program->program);
}

int _get_loc(Shader *program, char *name) {
    return glGetUniformLocation(program->program, name);
}

void shader_set_uniform_int(Shader *program, char * name, int value) {
    glUniform1i(_get_loc(program, name), value);
}

void shader_get_uniform_int(Shader *program, char * name, int * param) {
    glGetUniformiv(program->program, _get_loc(program, name), param);
}

void shader_set_uniform_uint(Shader *program, char * name, unsigned int value) {
    glUniform1ui(_get_loc(program, name), value);
}

void shader_get_uniform_uint(Shader *program, char * name, unsigned int * param) {
    glGetUniformuiv(program->program, _get_loc(program, name), param);
}

void shader_set_uniform_float(Shader *program, char * name, float value) {
    glUniform1f(_get_loc(program, name), value);
}

void shader_get_uniform_float(Shader *program, char * name, float * param) {
    glGetUniformfv(program->program, _get_loc(program, name), param);
}

void shader_set_uniform_vec2(Shader *program, char * name, Vector2 vec) {
    glUniform2f(_get_loc(program, name), vec.x, vec.y);
}

void shader_set_uniform_vec3(Shader *program, char * name, Vector3 vec) {
    glUniform3f(_get_loc(program, name), vec.x, vec.y, vec.z);
}

void shader_set_uniform_vec4(Shader *program, char * name, Vector4 vec) {
    glUniform4f(_get_loc(program, name), vec.x, vec.y, vec.z, vec.w);
}

void shader_set_uniform_mat3(Shader *program, char * name, Mat3 mat) {
    glUniformMatrix3fv(_get_loc(program, name), 1, GL_FALSE, mat.m);
}

void shader_set_uniform_mat4(Shader *program, char * name, Mat4 mat) {
    glUniformMatrix4fv(_get_loc(program, name), 1, GL_FALSE, mat.m);
}

void shader_set_uniform_view_proj(Shader *program, ViewProj view_proj) {
    shader_set_uniform_mat4(program, "view", view_proj.view);
    shader_set_uniform_mat4(program, "projection", view_proj.proj);
}

void shader_delete(Shader **program) {
    if(!*program) return;
    glDeleteShader((*program)->fragment);
    glDeleteShader((*program)->vertex);
    glDeleteProgram((*program)->program);
    free(*program);
    *program = NULL;
}
