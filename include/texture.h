#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>

typedef struct _texture {
    GLuint handle;
    uint32_t x, y;
} Texture;

typedef struct _atlas {
    Texture *texture;
    uint16_t spr_width, spr_height;
} Atlas;

Texture *texture_create_mem(uint8_t *data, uint32_t x, uint32_t y);
//Texture *texture_create();
void texture_bind(Texture *texture);
void texture_destroy(Texture **tex);
Atlas *atlas_create_mem(uint8_t *data, uint32_t x, uint32_t y, uint16_t spr_width, uint16_t spr_height);
Atlas *atlas_create_tex(Texture *texture, uint16_t spr_width, uint16_t spr_height);
void atlas_destroy(Atlas **atlas);

#endif

