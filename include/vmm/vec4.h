#ifndef _VEC4_H
#define _VEC4_H

#include <stdbool.h>

typedef union _vec4 {
    struct {
        float x;
        float y;
        float z;
        float w;
    };
    struct {
        float r;
        float g;
        float b;
        float a;
    };
} Vec4;

Vec4 vec4_float(float x, float y, float z, float w);
Vec4 vec4_vec4(Vec4 vec);
Vec4 vec4_zero(void);
Vec4 vec4_one(void);

bool vec4_equal_vec(Vec4 a, Vec4 b);
Vec4 vec4_max(Vec4 a, Vec4 b);
Vec4 vec4_abs(Vec4 a);
Vec4 vec4_sign(Vec4 a);

Vec4 vec4_scalar_add(Vec4 in, float scalar);
Vec4 vec4_scalar_sub(Vec4 in, float scalar);
Vec4 vec4_scalar_mul(Vec4 in, float scalar);
Vec4 vec4_scalar_div(Vec4 in, float scalar);

Vec4 vec4_negate(Vec4 in);
Vec4 vec4_add(Vec4 a, Vec4 b);
Vec4 vec4_sub(Vec4 a, Vec4 b);
Vec4 vec4_mul(Vec4 a, Vec4 b);
Vec4 vec4_div(Vec4 a, Vec4 b);

float vec4_dot(Vec4 a, Vec4 b);
float vec4_angle(Vec4 a, Vec4 b);
float vec4_len(Vec4 in);

Vec4 vec4_normalize(Vec4 in);

#endif
