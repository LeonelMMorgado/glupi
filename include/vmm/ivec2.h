#ifndef _IVEC2_H
#define _IVEC2_H

#include <stdint.h>
#include <stdbool.h>

typedef union _ivec2 {
    struct {
        int32_t x;
        int32_t y;
    };
    struct {
        int32_t u;
        int32_t v;
    };
} IVec2;

#include "vec2.h"

IVec2 ivec2_int(int32_t x, int32_t y);
IVec2 ivec2_ivec2(IVec2 vec);
IVec2 ivec2_vec2(Vec2 vec);
IVec2 ivec2_zero(void);
IVec2 ivec2_one(void);
IVec2 ivec2_left(void);
IVec2 ivec2_right(void);
IVec2 ivec2_down(void);
IVec2 ivec2_up(void);

bool ivec2_equal_vec(IVec2 a, IVec2 b);
IVec2 ivec2_min(IVec2 a, IVec2 b);
IVec2 ivec2_max(IVec2 a, IVec2 b);
IVec2 ivec2_abs(IVec2 a);
IVec2 ivec2_sign(IVec2 a);

IVec2 ivec2_scalar_add(IVec2 in, int scalar);
IVec2 ivec2_scalar_sub(IVec2 in, int scalar);
IVec2 ivec2_scalar_mul(IVec2 in, int scalar);
IVec2 ivec2_scalar_div(IVec2 in, int scalar);

IVec2 ivec2_negate(IVec2 in);
IVec2 ivec2_add(IVec2 a, IVec2 b);
IVec2 ivec2_sub(IVec2 a, IVec2 b);
IVec2 ivec2_mul(IVec2 a, IVec2 b);
IVec2 ivec2_div(IVec2 a, IVec2 b);

float ivec2_dot(IVec2 a, IVec2 b);
float ivec2_angle(IVec2 a, IVec2 b);
IVec2 ivec2_cross(IVec2 a, IVec2 b);
float ivec2_len(IVec2 in);

IVec2 ivec2_normalize(IVec2 in);

#endif
