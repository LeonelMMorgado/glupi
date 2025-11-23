#include <stdint.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <texture.h>
#include <vmm/vec2.h>

Texture *texture_create_mem(uint8_t *data, uint32_t x, uint32_t y) {
    Texture *t = malloc(sizeof(Texture));

    t->x = x;
    t->y = y;

    glGenTextures(1, &t->handle);
    glBindTexture(GL_TEXTURE_2D, t->handle);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    return t;
}

void texture_bind(Texture *texture) {
    glBindTexture(GL_TEXTURE_2D, texture->handle);
}

void texture_destroy(Texture **texture) {
    if(!texture) return;
    if(!*texture) return;
    glDeleteTextures(1, &((*texture)->handle));
    free(*texture);
    *texture = 0;
}

Atlas *atlas_create_mem(uint8_t *data, uint32_t x, uint32_t y, uint16_t spr_width, uint16_t spr_height) {
    Atlas *a = atlas_create_tex(texture_create_mem(data, x, y), spr_width, spr_height);
    return a;
}

Atlas *atlas_create_tex(Texture *texture, uint16_t spr_width, uint16_t spr_height) {
    Atlas *a = malloc(sizeof(Atlas));
    a->texture = texture;
    a->spr_width = spr_width;
    a->spr_height = spr_height;
    return a;
}

void atlas_destroy(Atlas **atlas) {
    if(!atlas) return;
    if(!*atlas) return;
    if((*atlas)->texture) texture_destroy(&((*atlas)->texture));
    free(*atlas);
    *atlas = NULL;
}
