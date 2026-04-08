#ifndef _VEC3_h
#define _VEC3_h

#include <stdbool.h>

typedef union _vec3 {
    struct {
        float x;
        float y;
        float z;
    };
    struct {
        float r;
        float g;
        float b;
    };
} Vec3;

#include "vec4.h"
#include "ivec3.h"

Vec3 vec3_float(float x, float y, float z);
Vec3 vec3_vec3(Vec3 vec);
Vec3 vec3_vec4(Vec4 vec);
Vec3 vec3_ivec3(IVec3 vec);
Vec3 vec3_zero(void);
Vec3 vec3_one(void);
Vec3 vec3_left(void);
Vec3 vec3_right(void);
Vec3 vec3_back(void);
Vec3 vec3_forward(void);
Vec3 vec3_down(void);
Vec3 vec3_up(void);

bool vec3_equal_vec(Vec3 a, Vec3 b);
Vec3 vec3_min(Vec3 a, Vec3 b);
Vec3 vec3_max(Vec3 a, Vec3 b);
Vec3 vec3_abs(Vec3 a);
Vec3 vec3_sign(Vec3 a);

Vec3 vec3_scalar_add(Vec3 in, float scalar);
Vec3 vec3_scalar_sub(Vec3 in, float scalar);
Vec3 vec3_scalar_mul(Vec3 in, float scalar);
Vec3 vec3_scalar_div(Vec3 in, float scalar);

Vec3 vec3_negate(Vec3 in);
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_mul(Vec3 a, Vec3 b);
Vec3 vec3_div(Vec3 a, Vec3 b);

float vec3_dot(Vec3 a, Vec3 b);
float vec3_angle(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);
float vec3_len(Vec3 in);

Vec3 vec3_normalize(Vec3 in);

#endif
