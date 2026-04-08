#ifndef _IVEC3_H
#define _IVEC3_H

#include <stdint.h>
#include <stdbool.h>

typedef union _ivec3 {
    struct {
        int32_t x;
        int32_t y;
        int32_t z;
    };
    struct {
        int32_t r;
        int32_t g;
        int32_t b;
    };
} IVec3;

#include "vec3.h"

IVec3 ivec3_int(int32_t x, int32_t y, int32_t z);
IVec3 ivec3_ivec3(IVec3 vec);
IVec3 ivec3_vec3(Vec3 vec);
IVec3 ivec3_zero(void);
IVec3 ivec3_one(void);
IVec3 ivec3_left(void);
IVec3 ivec3_right(void);
IVec3 ivec3_back(void);
IVec3 ivec3_forward(void);
IVec3 ivec3_down(void);
IVec3 ivec3_up(void);

bool ivec3_equal_vec(IVec3 a, IVec3 b);
IVec3 ivec3_min(IVec3 a, IVec3 b);
IVec3 ivec3_max(IVec3 a, IVec3 b);
IVec3 ivec3_abs(IVec3 a);
IVec3 ivec3_sign(IVec3 a);

IVec3 ivec3_scalar_add(IVec3 in, int scalar);
IVec3 ivec3_scalar_sub(IVec3 in, int scalar);
IVec3 ivec3_scalar_mul(IVec3 in, int scalar);
IVec3 ivec3_scalar_div(IVec3 in, int scalar);

IVec3 ivec3_negate(IVec3 in);
IVec3 ivec3_add(IVec3 a, IVec3 b);
IVec3 ivec3_sub(IVec3 a, IVec3 b);
IVec3 ivec3_mul(IVec3 a, IVec3 b);
IVec3 ivec3_div(IVec3 a, IVec3 b);

float ivec3_dot(IVec3 a, IVec3 b);
float ivec3_angle(IVec3 a, IVec3 b);
IVec3 ivec3_cross(IVec3 a, IVec3 b);
float ivec3_len(IVec3 in);

IVec3 ivec3_normalize(IVec3 in);

#endif
