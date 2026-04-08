#ifndef _VEC2_H
#define _VEC2_H

#include <stdbool.h>

typedef union _vec2 {
    struct {
        float x;
        float y;
    };
    struct {
        float u;
        float v;
    };
    struct {
        float a;
        float b;
    };
} Vec2;

#include "ivec2.h"

Vec2 vec2_float(float x, float y);
Vec2 vec2_vec2(Vec2 vec);
Vec2 vec2_ivec2(IVec2 vec);
Vec2 vec2_zero(void);
Vec2 vec2_one(void);
Vec2 vec2_left(void);
Vec2 vec2_right(void);
Vec2 vec2_down(void);
Vec2 vec2_up(void);

bool vec2_equal_vec(Vec2 a, Vec2 b);
Vec2 vec2_min(Vec2 a, Vec2 b);
Vec2 vec2_max(Vec2 a, Vec2 b);
Vec2 vec2_abs(Vec2 a);
Vec2 vec2_sign(Vec2 a);

Vec2 vec2_scalar_add(Vec2 in, float scalar);
Vec2 vec2_scalar_sub(Vec2 in, float scalar);
Vec2 vec2_scalar_mul(Vec2 in, float scalar);
Vec2 vec2_scalar_div(Vec2 in, float scalar);

Vec2 vec2_negate(Vec2 in);
Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_sub(Vec2 a, Vec2 b);
Vec2 vec2_mul(Vec2 a, Vec2 b);
Vec2 vec2_div(Vec2 a, Vec2 b);

float vec2_dot(Vec2 a, Vec2 b);
float vec2_angle(Vec2 a, Vec2 b);
float vec2_len(Vec2 in);

Vec2 vec2_normalize(Vec2 in);

#endif
