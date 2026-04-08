/*

for reference of usage, check the tests folder

In order to use this single file, use the definition for VMM_IMPLEMENTATION before including this header in *one* file:
#define VMM_IMPLEMENTATION
#include "vmm.h"

*/
#ifndef _VMM_H
#define _VMM_H

#include <stdint.h>
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

typedef struct {
    union {
        float mat[9];
        struct {
          float a, b, c,
                d, e, f,
                g, h, i;
        };
    };
} Mat3;

typedef struct {
    union {
        float mat[16];
        struct {
            float a, b, c, d,
                  e, f, g, h,
                  i, j, k, l,
                  m, n, o, p;
        };
    };
} Mat4;

typedef struct _ray {
    Vec3 origin, direction;
} Ray;

#ifdef __cplusplus
extern "C" {
#endif

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

Mat3 mat3(float val);

Mat3 mat3_scalar(Mat3 in, float scalar);

Mat3 mat3_add(Mat3 a, Mat3 b);
Mat3 mat3_sub(Mat3 a, Mat3 b);

Mat3 mat3_mul(Mat3 a, Mat3 b);
Vec3 mat3_vec3(Mat3 a, Vec3 b);

float mat3_det(Mat3 a);
Mat3 mat3_transp(Mat3 a);
Mat3 mat3_inverse(Mat3 in);

Mat3 mat3_scale(float s1, float s2);
Mat3 mat3_translation(float t1, float t2);
Mat3 mat3_rotation(float r1);

Mat4 mat4(float val);

Mat4 mat4_scalar(Mat4 in, float scalar);

Mat4 mat4_add(Mat4 a, Mat4 b);
Mat4 mat4_sub(Mat4 a, Mat4 b);

Mat4 mat4_mul(Mat4 a, Mat4 b);
Vec4 mat4_vec4(Mat4 a, Vec4 b);

float mat4_det(Mat4 in);
Mat4 mat4_transp(Mat4 in);
Mat4 mat4_inverse(Mat4 in);

Mat4 mat4_scale(float s1, float s2, float s3);
Mat4 mat4_translation(float t1, float t2, float t3);
Mat4 mat4_rotation(float r1, float r2, float r3);

Mat4 mat4_look_at(Vec3 eye, Vec3 center, Vec3 up);
Mat4 mat4_make_model(Vec3 position, Vec3 rotation, Vec3 scale);
Mat4 mat4_orthogonal(float left, float right, float bottom, float top, float zNear, float zFar);
Mat4 mat4_perspective(float fov, float aspect, float zNear, float zFar);
Mat4 mat4_orthogonal(float left, float right, float bottom, float top, float zNear, float zFar);
Mat4 mat4_perspective(float fov, float aspect, float zNear, float zFar);

Ray ray_create(Vec3 origin, Vec3 direction);
Ray ray_change_origin(Ray ray, Vec3 new_origin);
Ray ray_change_dir(Ray ray, Vec3 new_direction);
bool ray_hits_box(Ray ray, Vec3 left_bot_back, Vec3 right_top_front, float *tmin, float *tmax);

#ifdef __cplusplus
}
#endif

#endif //VMM_H

#ifdef VMM_IMPLEMENTATION

Vec2 vec2_float(float x, float y) {
    return (Vec2){.x = x, .y = y};
}

Vec2 vec2_vec2(Vec2 vec) {
    return vec;
}

Vec2 vec2_ivec2(IVec2 vec) {
    return (Vec2){.x = (float)vec.x, .y = (float)vec.y};
}

Vec2 vec2_zero(void) {
    return (Vec2){.x = 0, .y = 0};
}

Vec2 vec2_one(void) {
    return (Vec2){.x = 1.0, .y = 1.0};
}

Vec2 vec2_left(void) {
    return (Vec2){.x = -1.0, .y = 0.0};
}

Vec2 vec2_right(void) {
    return (Vec2){.x = 1.0, .y = 0.0};
}

Vec2 vec2_down(void) {
    return (Vec2){.x = 0.0, .y = -1.0};
}

Vec2 vec2_up(void) {
    return (Vec2){.x = 0.0, .y = 1.0};
}

bool vec2_equal_vec(Vec2 a, Vec2 b) {
    return a.x == b.x && a.y == b.y;
}

Vec2 vec2_min(Vec2 a, Vec2 b) {
    return (Vec2){.x = fminf(a.x, b.x), .y = fminf(a.y, b.y)};
}

Vec2 vec2_max(Vec2 a, Vec2 b) {
    return (Vec2){.x = fmaxf(a.x, b.x), .y = fmaxf(a.y, b.y)};
}

Vec2 vec2_abs(Vec2 a) {
    return (Vec2){.x = fabsf(a.x), .y = fabsf(a.y)};
}

Vec2 vec2_sign(Vec2 a) {
    return vec2_div(a, vec2_abs(a));
}

Vec2 vec2_scalar_add(Vec2 in, float scalar) {
    return (Vec2){.x = in.x + scalar, .y = in.y + scalar};
}

Vec2 vec2_scalar_sub(Vec2 in, float scalar) {
    return (Vec2){.x = in.x - scalar, .y = in.y - scalar};
}

Vec2 vec2_scalar_mul(Vec2 in, float scalar) {
    return (Vec2){.x = in.x * scalar, .y = in.y * scalar};
}

Vec2 vec2_scalar_div(Vec2 in, float scalar) {
    if(scalar == 0) return (Vec2){.x = 0, .y = 0};
    return (Vec2){.x = in.x / scalar, .y = in.y / scalar};
}

Vec2 vec2_negate(Vec2 in) {
    return (Vec2){.x = -in.x, .y = -in.y};
}

Vec2 vec2_add(Vec2 a, Vec2 b) {
    return (Vec2){.x = a.x + b.x, .y = a.y + b.y};
}

Vec2 vec2_sub(Vec2 a, Vec2 b) {
    return (Vec2){.x = a.x - b.x, .y = a.y - b.y};
}

Vec2 vec2_mul(Vec2 a, Vec2 b) {
    return (Vec2){.x = a.x * b.x, .y = a.y * b.y};
}

Vec2 vec2_div(Vec2 a, Vec2 b) {
    if(b.x == 0.0) {
        a.x = 0.0;
        b.x = 1.0;
    }
    if(b.y == 0.0) {
        a.y = 0.0;
        b.y = 1.0;
    }
    return (Vec2){.x = a.x / b.x, .y = a.y / b.y};
}

float vec2_dot(Vec2 a, Vec2 b) {
    return (a.x * b.x) + (a.y * b.y);
}

float vec2_len(Vec2 in) {
    return sqrtf((in.x*in.x) + (in.y*in.y));
}

float vec2_angle(Vec2 a, Vec2 b) {
    float la = vec2_len(a);
    float lb = vec2_len(b);
    if(la == 0 || lb == 0) return 0;
    return acosf(vec2_dot(a, b)/(la*lb));
}

Vec2 vec2_normalize(Vec2 in) {
    float len = vec2_len(in);
    if(len == 0) return (Vec2){{0, 0}};
    return vec2_scalar_div(in, len);
}

Vec3 vec3_float(float x, float y, float z) {
    return (Vec3){.x = x, .y = y, .z = z};
}

Vec3 vec3_vec3(Vec3 vec) {
    return vec;
}

Vec3 vec3_vec4(Vec4 vec) {
    return (Vec3){.x = vec.x, .y = vec.y, .z = vec.z};
}

Vec3 vec3_ivec3(IVec3 vec) {
    return (Vec3){.x = (float)vec.x, .y = (float)vec.y, .z = (float)vec.z};
}

Vec3 vec3_zero(void) {
    return (Vec3){.x = 0, .y = 0, .z = 0};
}

Vec3 vec3_one(void) {
    return (Vec3){.x = 1.0, .y = 1.0, .z = 1.0};
}

Vec3 vec3_left(void) {
    return (Vec3){.x = -1.0, .y = 0.0, .z = 0.0};
}

Vec3 vec3_right(void) {
    return (Vec3){.x = 1.0, .y = 0.0, .z = 0.0};
}

Vec3 vec3_back(void) {
    return (Vec3){.x = 0.0, .y = 0.0, .z = -1.0};
}

Vec3 vec3_forward(void) {
    return (Vec3){.x = 0.0, .y = 0.0, .z = 1.0};
}

Vec3 vec3_down(void) {
    return (Vec3){.x = 0.0, .y = -1.0, .z = 0.0};
}

Vec3 vec3_up(void) {
    return (Vec3){.x = 0.0, .y = 1.0, .z = 0.0};
}


bool vec3_equal_vec(Vec3 a, Vec3 b) {
    return a.x == b.x && a.y && b.y && a.z == b.z;
}

Vec3 vec3_min(Vec3 a, Vec3 b) {
    return (Vec3){.x = fminf(a.x, b.x), .y = fminf(a.y, b.y), .z = fminf(a.z, b.z)};
}

Vec3 vec3_max(Vec3 a, Vec3 b) {
    return (Vec3){.x = fmaxf(a.x, b.x), .y = fmaxf(a.y, b.y), .z = fmaxf(a.z, b.z)};
}

Vec3 vec3_abs(Vec3 a) {
    return (Vec3){.x = fabsf(a.x), .y = fabsf(a.y), .z = fabsf(a.z)};
}

Vec3 vec3_sign(Vec3 a) {
    return vec3_div(a, vec3_abs(a));
}

Vec3 vec3_scalar_add(Vec3 in, float scalar) {
    return (Vec3){.x = in.x + scalar, .y = in.y + scalar, .z = in.z + scalar};
}

Vec3 vec3_scalar_sub(Vec3 in, float scalar) {
    return (Vec3){.x = in.x - scalar, .y = in.y - scalar, .z = in.z - scalar};
}

Vec3 vec3_scalar_mul(Vec3 in, float scalar) {
    return (Vec3){.x = in.x * scalar, .y = in.y * scalar, .z = in.z * scalar};
}

Vec3 vec3_scalar_div(Vec3 in, float scalar) {
    if(scalar == 0) return (Vec3){.x = 0, .y = 0, .z = 0};
    return (Vec3){.x = in.x / scalar, .y = in.y / scalar, .z = in.z / scalar};
}

Vec3 vec3_negate(Vec3 in) {
    return (Vec3){.x = -in.x, .y = -in.y, .z = -in.z};
}

Vec3 vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return (Vec3){.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
}

Vec3 vec3_mul(Vec3 a, Vec3 b) {
    return (Vec3){.x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z};
}

Vec3 vec3_div(Vec3 a, Vec3 b) {
    if(b.x == 0.0) {
        a.x = 0.0;
        b.x = 1.0;
    }
    if(b.y == 0.0) {
        a.y = 0.0;
        b.y = 1.0;
    }
    if(b.z == 0.0) {
        a.z = 0.0;
        b.z = 1.0;
    }
    return (Vec3){.x = a.x / b.x, .y = a.y / b.y, .z = a.z / b.z};
}

float vec3_dot(Vec3 a, Vec3 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec3 vec3_cross(Vec3 a, Vec3 b) {
    return (Vec3){.x = (a.y*b.z)-(a.z*b.y), .y = (a.z*b.x)-(a.x*b.z), .z = (a.x*b.y)-(a.y*b.x)};
}

float vec3_len(Vec3 in) {
    return sqrtf((in.x*in.x) + (in.y*in.y) + (in.z*in.z));
}

float vec3_angle(Vec3 a, Vec3 b) {
    float la = vec3_len(a);
    float lb = vec3_len(b);
    if(la == 0 || lb == 0) return 0;
    return acosf(vec3_dot(a, b)/(la*lb));
}

Vec3 vec3_normalize(Vec3 in) {
    float len = vec3_len(in);
    if(len == 0) return (Vec3){.x = 0, .y = 0, .z = 0};
    return vec3_scalar_div(in, len);
}

Vec4 vec4_float(float x, float y, float z, float w) {
    return (Vec4){.x = x, .y = y, .z = z, .w = w};
}

Vec4 vec4_vec4(Vec4 vec) {
    return vec;
}

Vec4 vec4_zero(void) {
    return (Vec4){.x = 0, .y = 0, .z = 0, .w = 0};
}

Vec4 vec4_one(void) {
    return (Vec4){.x = 1.0, .y = 1.0, .z = 1.0, .w = 1.0};
}

bool vec4_equal_vec(Vec4 a, Vec4 b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

Vec4 vec4_min(Vec4 a, Vec4 b) {
    return (Vec4){.x = fminf(a.x, b.x), .y = fminf(a.y, b.y), .z = fminf(a.z, b.z), .w = fminf(a.w, b.w)};
}

Vec4 vec4_max(Vec4 a, Vec4 b) {
    return (Vec4){.x = fmaxf(a.x, b.x), .y = fmaxf(a.y, b.y), .z = fmaxf(a.z, b.z), .w = fmaxf(a.w, b.w)};
}

Vec4 vec4_abs(Vec4 a) {
    return (Vec4){.x = fabsf(a.x), .y = fabsf(a.y), .z = fabsf(a.z), .w = fabsf(a.w)};
}

Vec4 vec4_sign(Vec4 a) {
    return vec4_div(a, vec4_abs(a));
}

Vec4 vec4_scalar_add(Vec4 in, float scalar) {
    return (Vec4){.x = in.x + scalar, .y = in.y + scalar, .z = in.z + scalar, .w = in.w + scalar};
}

Vec4 vec4_scalar_sub(Vec4 in, float scalar) {
    return (Vec4){.x = in.x - scalar, .y = in.y - scalar, .z = in.z - scalar, .w = in.w - scalar};
}

Vec4 vec4_scalar_mul(Vec4 in, float scalar) {
    return (Vec4){.x = in.x * scalar, .y = in.y * scalar, .z = in.z * scalar, .w = in.w * scalar};
}

Vec4 vec4_scalar_div(Vec4 in, float scalar) {
    if(scalar == 0) return (Vec4){.x = 0, .y = 0, .z = 0, .w = 0};
    return (Vec4){.x = in.x / scalar, .y = in.y / scalar, .z = in.z / scalar, .w = in.w / scalar};
}

Vec4 vec4_negate(Vec4 in) {
    return (Vec4){.x = -in.x, .y = -in.y, .z = -in.z, .w = -in.w};
}

Vec4 vec4_add(Vec4 a, Vec4 b) {
    return (Vec4){.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z, .w = a.w + b.w};
}

Vec4 vec4_sub(Vec4 a, Vec4 b) {
    return (Vec4){.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z, .w = a.w - b.w};
}

Vec4 vec4_mul(Vec4 a, Vec4 b) {
    return (Vec4){.x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z, .w = a.w * b.w};
}

Vec4 vec4_div(Vec4 a, Vec4 b) {
    if(b.x == 0.0) {
        a.x = 0.0;
        b.x = 1.0;
    }
    if(b.y == 0.0) {
        a.y = 0.0;
        b.y = 1.0;
    }
    if(b.z == 0.0) {
        a.z = 0.0;
        b.z = 1.0;
    }
    if(b.w == 0.0) {
        a.w = 0.0;
        b.w = 1.0;
    }
    return (Vec4){.x = a.x / b.x, .y = a.y / b.y, .z = a.z / b.z, .w = a.w / b.w};
}

float vec4_dot(Vec4 a, Vec4 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

float vec4_len(Vec4 in) {
    return sqrtf((in.x*in.x) + (in.y*in.y) + (in.z*in.z) + (in.w*in.w));
}

float vec4_angle(Vec4 a, Vec4 b) {
    float la = vec4_len(a);
    float lb = vec4_len(b);
    if(la == 0 || lb == 0) return 0;
    return acosf(vec4_dot(a, b)/(la*lb));
}

Vec4 vec4_normalize(Vec4 in) {
    float len = vec4_len(in);
    if(len == 0) return (Vec4){.x = 0, .y = 0, .z = 0, .w = 0};
    return vec4_scalar_div(in, len);
}

int32_t _ivec2_min(int32_t a, int32_t b) {
    return a < b ? a : b;
}

int32_t _ivec2_max(int32_t a, int32_t b) {
    return a > b ? a : b;
}

IVec2 ivec2_int(int32_t x, int32_t y) {
    return (IVec2){.x = x, .y = y};
}

IVec2 ivec2_ivec2(IVec2 vec) {
    return vec;
}

IVec2 ivec2_vec3(Vec2 vec) {
    return (IVec2){.x = (int32_t)vec.x, .y = (int32_t)vec.y};
}

IVec2 ivec2_zero(void) {
    return (IVec2){.x = 0, .y = 0};
}

IVec2 ivec2_one(void) {
    return (IVec2){.x = 1, .y = 1};
}

IVec2 ivec2_left(void) {
    return (IVec2){.x = -1, .y = 0};
}

IVec2 ivec2_right(void) {
    return (IVec2){.x = 1, .y = 0};
}

IVec2 ivec2_down(void) {
    return (IVec2){.x = 0, .y = -1};
}

IVec2 ivec2_up(void) {
    return (IVec2){.x = 0, .y = 1};
}


bool ivec2_equal_vec(IVec2 a, IVec2 b) {
    return a.x == b.x && a.y && b.y;
}

IVec2 ivec2_min(IVec2 a, IVec2 b) {
    return (IVec2){.x = _ivec2_min(a.x, b.x), .y = _ivec2_min(a.y, b.y)};
}

IVec2 ivec2_max(IVec2 a, IVec2 b) {
    return (IVec2){.x = _ivec2_max(a.x, b.x), .y = _ivec2_max(a.y, b.y)};
}

IVec2 ivec2_abs(IVec2 a) {
    return (IVec2){.x = abs(a.x), .y = abs(a.y)};
}

IVec2 ivec2_sign(IVec2 a) {
    return ivec2_div(a, ivec2_abs(a));
}

IVec2 ivec2_scalar_add(IVec2 in, int scalar) {
    return (IVec2){.x = in.x + scalar, .y = in.y + scalar};
}

IVec2 ivec2_scalar_sub(IVec2 in, int scalar) {
    return (IVec2){.x = in.x - scalar, .y = in.y - scalar};
}

IVec2 ivec2_scalar_mul(IVec2 in, int scalar) {
    return (IVec2){.x = in.x * scalar, .y = in.y * scalar};
}

IVec2 ivec2_scalar_div(IVec2 in, int scalar) {
    if(scalar == 0) return (IVec2){.x = 0, .y = 0};
    return (IVec2){.x = in.x / scalar, .y = in.y / scalar};
}

IVec2 ivec2_negate(IVec2 in) {
    return (IVec2){.x = -in.x, .y = -in.y};
}

IVec2 ivec2_add(IVec2 a, IVec2 b) {
    return (IVec2){.x = a.x + b.x, .y = a.y + b.y};
}

IVec2 ivec2_sub(IVec2 a, IVec2 b) {
    return (IVec2){.x = a.x - b.x, .y = a.y - b.y};
}

IVec2 ivec2_mul(IVec2 a, IVec2 b) {
    return (IVec2){.x = a.x * b.x, .y = a.y * b.y};
}

IVec2 ivec2_div(IVec2 a, IVec2 b) {
    return (IVec2){.x = a.x / b.x, .y = a.y / b.y};
}

float ivec2_dot(IVec2 a, IVec2 b) {
    return (a.x * b.x) + (a.y * b.y);
}

float ivec2_len(IVec2 in) {
    return sqrtf((in.x*in.x) + (in.y*in.y));
}

float ivec2_angle(IVec2 a, IVec2 b) {
    float la = ivec2_len(a);
    float lb = ivec2_len(b);
    if(la == 0 || lb == 0) return 0;
    return acosf(ivec2_dot(a, b)/(la*lb));
}

IVec2 ivec2_normalize(IVec2 in) {
    float len = ivec2_len(in);
    if(len == 0) return (IVec2){.x = 0, .y = 0};
    return ivec2_scalar_div(in, len);
}

IVec3 ivec3_int(int32_t x, int32_t y, int32_t z) {
    return (IVec3){.x = x, .y = y, .z = z};
}

IVec3 ivec3_ivec3(IVec3 vec) {
    return vec;
}

IVec3 ivec3_vec3(Vec3 vec) {
    return (IVec3){.x = (int32_t)vec.x, .y = (int32_t)vec.y, .z = (int32_t)vec.z};
}

IVec3 ivec3_zero(void) {
    return (IVec3){.x = 0, .y = 0, .z = 0};
}

IVec3 ivec3_one(void) {
    return (IVec3){.x = 1, .y = 1, .z = 1};
}

IVec3 ivec3_left(void) {
    return (IVec3){.x = -1, .y = 0, .z = 0};
}

IVec3 ivec3_right(void) {
    return (IVec3){.x = 1, .y = 0, .z = 0};
}

IVec3 ivec3_back(void) {
    return (IVec3){ .x = 0, .y = 0, .z = -1};
}

IVec3 ivec3_forward(void) {
    return (IVec3){.x = 0, .y = 0, .z = 1};
}

IVec3 ivec3_down(void) {
    return (IVec3){.x = 0, .y = -1, .z = 0};
}

IVec3 ivec3_up(void) {
    return (IVec3){.x = 0, .y = 1, .z = 0};
}


bool ivec3_equal_vec(IVec3 a, IVec3 b) {
    return a.x == b.x && a.y && b.y && a.z == b.z;
}

IVec3 ivec3_min(IVec3 a, IVec3 b) {
    return (IVec3){.x = _ivec3_min(a.x, b.x), .y = _ivec3_min(a.y, b.y), .z = _ivec3_min(a.z, b.z)};
}

IVec3 ivec3_max(IVec3 a, IVec3 b) {
    return (IVec3){.x = _ivec3_max(a.x, b.x), .y = _ivec3_max(a.y, b.y), .z = _ivec3_max(a.z, b.z)};
}

IVec3 ivec3_abs(IVec3 a) {
    return (IVec3){.x = abs(a.x), .y = abs(a.y), .z = abs(a.z)};
}

IVec3 ivec3_sign(IVec3 a) {
    return ivec3_div(a, ivec3_abs(a));
}

IVec3 ivec3_scalar_add(IVec3 in, int scalar) {
    return (IVec3){.x = in.x + scalar, .y = in.y + scalar, .z = in.z + scalar};
}

IVec3 ivec3_scalar_sub(IVec3 in, int scalar) {
    return (IVec3){.x = in.x - scalar, .y = in.y - scalar, .z = in.z - scalar};
}

IVec3 ivec3_scalar_mul(IVec3 in, int scalar) {
    return (IVec3){.x = in.x * scalar, .y = in.y * scalar, .z = in.z * scalar};
}

IVec3 ivec3_scalar_div(IVec3 in, int scalar) {
    if(scalar == 0) return (IVec3){.x = 0, .y = 0, .z = 0};
    return (IVec3){.x = in.x / scalar, .y = in.y / scalar, .z = in.z / scalar};
}

IVec3 ivec3_negate(IVec3 in) {
    return (IVec3){.x = -in.x, .y = -in.y, .z = -in.z};
}

IVec3 ivec3_add(IVec3 a, IVec3 b) {
    return (IVec3){.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
}

IVec3 ivec3_sub(IVec3 a, IVec3 b) {
    return (IVec3){.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
}

IVec3 ivec3_mul(IVec3 a, IVec3 b) {
    return (IVec3){.x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z};
}

IVec3 ivec3_div(IVec3 a, IVec3 b) {
    return (IVec3){.x = a.x / b.x, .y = a.y / b.y, .z = a.z / b.z};
}

float ivec3_dot(IVec3 a, IVec3 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

IVec3 ivec3_cross(IVec3 a, IVec3 b) {
    return (IVec3){.x = (a.y*b.z)-(a.z*b.y), .y = (a.z*b.x)-(a.x*b.z), .z = (a.x*b.y)-(a.y*b.x)};
}

float ivec3_len(IVec3 in) {
    return sqrtf((in.x*in.x) + (in.y*in.y) + (in.z*in.z));
}

float ivec3_angle(IVec3 a, IVec3 b) {
    float la = ivec3_len(a);
    float lb = ivec3_len(b);
    if(la == 0 || lb == 0) return 0;
    return acosf(ivec3_dot(a, b)/(la*lb));
}

IVec3 ivec3_normalize(IVec3 in) {
    float len = ivec3_len(in);
    if(len == 0) return (IVec3){.x = 0, .y = 0, .z = 0};
    return ivec3_scalar_div(in, len);
}

Mat3 mat3(float val) {
    Mat3 ret = {0};
    ret.a = val;
    ret.d = val;
    ret.g = val;
    return ret;
}

Mat3 mat3_scalar(Mat3 in, float scalar) {
    Mat3 ret = {0};
    for(int i = 0; i < 9; i++) {
        ret.mat[i] = in.mat[i] * scalar;
    }
    return ret;
}

Mat3 mat3_add(Mat3 a, Mat3 b) {
    //Using godbolt, the assembly of this sum and the sum using for is almost the same, but the for uses SIMD for performance so lets choose it
    Mat3 ret = {0};
    //ret.a = a.a + b.a;
    //ret.b = a.b + b.b;
    //ret.c = a.c + b.c;
    //ret.d = a.d + b.d;
    //ret.e = a.e + b.e;
    //ret.f = a.f + b.f;
    //ret.g = a.g + b.g;
    //ret.h = a.h + b.h;
    //ret.i = a.i + b.i;
    for(int i = 0; i < 9; i++) ret.mat[i] = a.mat[i] + b.mat[i];
    return ret;
}

Mat3 mat3_sub(Mat3 a, Mat3 b) {
    Mat3 ret = {0};
    for(int i = 0; i < 9; i++) {
        ret.mat[i] = a.mat[i] - b.mat[i];
    }
    return ret;
}

Mat3 mat3_mul(Mat3 a, Mat3 b) {
    Mat3 ret = {0};
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            ret.mat[i*3 + j] = (a.mat[i*3]*b.mat[j])+(a.mat[i*3 + 1]*b.mat[3 + j])+(a.mat[i*3 + 2]*b.mat[6 + j]);
    return ret;
}

Vec3 mat3_vec3(Mat3 a, Vec3 b) {
    Vec3 ret = {0};
    ret.x = (a.a*b.x) + (a.b*b.y) + (a.c*b.z);
    ret.y = (a.d*b.x) + (a.e*b.y) + (a.f*b.z);
    ret.z = (a.g*b.x) + (a.h*b.y) + (a.i*b.z);
    return ret;
}


float mat3_det(Mat3 a) {
    //a(ei-hf)-d(bi-ch)+g(bf-ce);
    return a.a * (a.e * a.i - a.h * a.f)
         - a.d * (a.b * a.i - a.c * a.h)
         + a.g * (a.b * a.f - a.c * a.e);
}

Mat3 mat3_transp(Mat3 a) {
    Mat3 ret = {0};
    ret.a = a.mat[0];
    ret.b = a.d;
    ret.c = a.g;
    ret.d = a.b;
    ret.e = a.mat[4];
    ret.f = a.h;
    ret.g = a.c;
    ret.h = a.f;
    ret.i = a.mat[8];
    return ret;
}

Mat3 mat3_inverse(Mat3 in) {
    float det;
    float a = in.a, b = in.b, c = in.c,
          d = in.d, e = in.e, f = in.f,
          g = in.g, h = in.h, i = in.i;

    Mat3 dest;
    dest.a =   e * i - f * h;
    dest.b = -(b * i - h * c);
    dest.c =   b * f - e * c;
    dest.d = -(d * i - g * f);
    dest.e =   a * i - c * g;
    dest.f = -(a * f - d * c);
    dest.g =   d * h - g * e;
    dest.h = -(a * h - g * b);
    dest.i =   a * e - b * d;

  det = 1.0f / (a * dest.a + b * dest.d + c * dest.g);
  return mat3_scalar(dest, det);
}

Mat3 mat3_scale(float s1, float s2) {
    Mat3 ret = {0};
    ret.a = s1;
    ret.e = s2;
    ret.i = 1;
    return ret;
}

Mat3 mat3_translation(float t1, float t2) {
    Mat3 ret = mat3(1);
    ret.c = t1;
    ret.f = t2;
    return ret;
}

Mat3 mat3_rotation(float r1) {
    float cx = cosf(r1);
    float sx = sinf(r1);
    Mat3 ret = mat3(1);
    ret.a = cx;
    ret.e = cx;
    ret.b = -sx;
    ret.d = sx;
    return ret;
}

Mat4 mat4(float val) {
    Mat4 ret = {0};
    ret.a = val;
    ret.f = val;
    ret.k = val;
    ret.p = val;
    return ret;
}

Mat4 mat4_scalar(Mat4 in, float scalar) {
    Mat4 ret = {0};
    for(int i = 0; i < 16; i++) {
        ret.mat[i] = in.mat[i] * scalar;
    }
    return ret;
}

Mat4 mat4_add(Mat4 a, Mat4 b) {
    Mat4 ret = {0};
    for(int i = 0; i < 16; i++) {
        ret.mat[i] = a.mat[i] + b.mat[i];
    }
    return ret;
}

Mat4 mat4_sub(Mat4 a, Mat4 b) {
    Mat4 ret = {0};
    for(int i = 0; i < 16; i++) {
        ret.mat[i] = a.mat[i] - b.mat[i];
    }
    return ret;
}

Mat4 mat4_mul(Mat4 a, Mat4 b) {
    Mat4 ret = {0};
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            ret.mat[i*4 + j] = (a.mat[i*4]*b.mat[j])+(a.mat[i*4 + 1]*b.mat[4 + j])+(a.mat[i*4 + 2]*b.mat[8 + j])+(a.mat[i*4 + 3]*b.mat[12+j]);
    return ret;
}

Vec4 mat4_vec4(Mat4 a, Vec4 b) {
    Vec4 ret = {0};
    ret.x = (a.a*b.x) + (a.b*b.y) + (a.c*b.z) + (a.d*b.w);
    ret.y = (a.e*b.x) + (a.f*b.y) + (a.g*b.z) + (a.h*b.w);
    ret.z = (a.i*b.x) + (a.j*b.y) + (a.k*b.z) + (a.l*b.w);
    ret.w = (a.m*b.x) + (a.n*b.y) + (a.o*b.z) + (a.p*b.w);
    return ret;
}


float mat4_det(Mat4 in) {
    float t[6];

    t[0] = in.k * in.p - in.o * in.l;
    t[1] = in.j * in.p - in.n * in.l;
    t[2] = in.j * in.o - in.n * in.k;
    t[3] = in.i * in.p - in.m * in.l;
    t[4] = in.i * in.o - in.m * in.k;
    t[5] = in.i * in.n - in.m * in.j;
  
    return in.a * (in.f * t[0] - in.g * t[1] + in.h * t[2])
         - in.b * (in.e * t[0] - in.g * t[3] + in.h * t[4])
         + in.c * (in.e * t[1] - in.f * t[3] + in.h * t[5])
         - in.d * (in.e * t[2] - in.f * t[4] + in.g * t[5]);
}

Mat4 mat4_transp(Mat4 in) {
    Mat4 ret = {0};

    ret.a = in.a;
    ret.b = in.e;
    ret.c = in.i;
    ret.d = in.m;
    ret.e = in.b;
    ret.f = in.f;
    ret.g = in.j;
    ret.h = in.n;
    ret.i = in.c;
    ret.j = in.g;
    ret.k = in.k;
    ret.l = in.o;
    ret.m = in.d;
    ret.n = in.h;
    ret.o = in.l;
    ret.p = in.p;

    return ret;
}

Mat4 mat4_inverse(Mat4 in) {
    float t[6];
    float det;

    Mat4 dest;
    
    t[0] = in.k * in.p - in.o * in.l; t[1] = in.j * in.p - in.n * in.l; t[2] = in.j * in.o - in.n * in.k;
    t[3] = in.i * in.p - in.m * in.l; t[4] = in.i * in.o - in.m * in.k; t[5] = in.i * in.n - in.m * in.j;
    
    dest.mat[0] =  in.f * t[0] - in.g * t[1] + in.h * t[2];
    dest.mat[4] =-(in.e * t[0] - in.g * t[3] + in.h * t[4]);
    dest.mat[8] =  in.e * t[1] - in.f * t[3] + in.h * t[5];
    dest.mat[12] =-(in.e * t[2] - in.f * t[4] + in.g * t[5]);
    
    dest.mat[1] =-(in.b * t[0] - in.c * t[1] + in.d * t[2]);
    dest.mat[5] =  in.a * t[0] - in.c * t[3] + in.d * t[4];
    dest.mat[9] =-(in.a * t[1] - in.b * t[3] + in.d * t[5]);
    dest.mat[13] =  in.a * t[2] - in.b * t[4] + in.c * t[5];
    
    t[0] = in.g * in.p - in.o * in.h; t[1] = in.f * in.p - in.n * in.h; t[2] = in.f * in.o - in.n * in.g;
    t[3] = in.e * in.p - in.m * in.h; t[4] = in.e * in.o - in.m * in.g; t[5] = in.e * in.n - in.m * in.f;
    
    dest.mat[2] =  in.b * t[0] - in.c * t[1] + in.d * t[2];
    dest.mat[6] =-(in.a * t[0] - in.c * t[3] + in.d * t[4]);
    dest.mat[10]=  in.a * t[1] - in.b * t[3] + in.d * t[5];
    dest.mat[14]=-(in.a * t[2] - in.b * t[4] + in.c * t[5]);
    
    t[0] = in.g * in.l - in.k * in.h; t[1] = in.f * in.l - in.j * in.h; t[2] = in.f * in.k - in.j * in.g;
    t[3] = in.e * in.l - in.i * in.h; t[4] = in.e * in.k - in.i * in.g; t[5] = in.e * in.j - in.i * in.f;
    
    dest.mat[3] =-(in.b * t[0] - in.c * t[1] + in.d * t[2]);
    dest.mat[7] =  in.a * t[0] - in.c * t[3] + in.d * t[4];
    dest.mat[11]=-(in.a * t[1] - in.b * t[3] + in.d * t[5]);
    dest.mat[15]=  in.a * t[2] - in.b * t[4] + in.c * t[5];
    
    det = 1.0f / (in.a * dest.mat[0] + in.b * dest.mat[4]
                + in.c * dest.mat[8] + in.d * dest.mat[12]);
    
    return mat4_scalar(dest, det);
}


Mat4 mat4_scale(float s1, float s2, float s3) {
    Mat4 ret = {0};
    ret.a = s1;
    ret.f = s2;
    ret.k = s3;
    ret.p = 1;
    return ret;
}

Mat4 mat4_translation(float t1, float t2, float t3) {
    Mat4 ret = mat4(1);
    ret.d = t1;
    ret.h = t2;
    ret.l = t3;
    return ret;
}

Mat4 mat4_rotation(float r1, float r2, float r3) {
    Mat4 ret = mat4(1);
    float cz = cosf(r3);
    float cy = cosf(r2);
    float cx = cosf(r1);
    float sz = sinf(r3);
    float sy = sinf(r2);
    float sx = sinf(r1);
    ret.a = cz * cy;
    ret.b = -(sz * cx) + (cz * sy * sx);
    ret.c = (sz * sx) + (cz * sy * cx);
    ret.e = sz * cy;
    ret.f = (cz * cx) + (sz * sy * sx);
    ret.g = -(cz * sx) + (sz * sy * cx);
    ret.i = -sy;
    ret.j = cy * sx;
    ret.k = cy * cx;
    return ret;
}

Mat4 mat4_look_at(Vec3 eye, Vec3 center, Vec3 up) {
    Mat4 ret = mat4(1);

    Vec3 forward = vec3_sub(center, eye);
    forward = vec3_normalize(forward);

    Vec3 right = vec3_cross(up, forward);
    right = vec3_normalize(right);

    Vec3 new_up = vec3_cross(forward, right);
    ret.a = right.x;
    ret.b = right.y;
    ret.c = right.z;
    ret.d = 0.0f;
    ret.e = new_up.x;
    ret.f = new_up.y;
    ret.g = new_up.z;
    ret.h = 0.0f;
    ret.i = -forward.x;
    ret.j = -forward.y;
    ret.k = -forward.z;
    ret.l = 0.0f;
    ret.m = -vec3_dot(right, eye);
    ret.n = -vec3_dot(new_up, eye);
    ret.o = vec3_dot(forward, eye);
    ret.p = 1.0f;

    return ret;
}

Mat4 mat4_make_model(Vec3 position, Vec3 rotation, Vec3 scale) {
    Mat4 trans = mat4_translation(position.x, position.y, position.z);
    Mat4 rotat = mat4_rotation(rotation.x, rotation.y, rotation.z);
    Mat4 mscal = mat4_scale(scale.x, scale.y, scale.z);
    Mat4 model = mat4_mul(mscal, rotat);
    Mat4 nmodl = mat4_mul(model, trans);
    return nmodl;
}

Mat4 mat4_orthogonal(float left, float right, float bottom, float top, float zNear, float zFar) {
    Mat4 ret = mat4(1);
    float width = right - left;
    float height = top - bottom;
    float zDist = zFar - zNear;
    if(width == 0 || height == 0 || zDist == 0) return mat4(0);
    ret.mat[0] = 2 / width;
    ret.mat[5] = 2 / height;
    ret.mat[10] = 1 / zDist;
    ret.mat[12] = (right + left) / width;
    ret.mat[13] = (top + bottom) / height;
    ret.mat[14] = zNear / zDist;
    return ret;
}

Mat4 mat4_perspective(float fovy, float aspect, float zNear, float zFar) {
    float tanHalfFovy = tanf(fovy / 2);
    Mat4 ret = mat4(0);
    if(aspect == 0 || tanHalfFovy == 0 || zFar == zNear) return mat4(0);
    ret.mat[0] = 1 / (aspect * tanHalfFovy);
    ret.mat[5] = 1 / tanHalfFovy;
    ret.mat[10] = zFar / (zNear - zFar);
    ret.mat[11] = -1;
    ret.mat[14] = -(zFar * zNear) / (zFar - zNear);
    return ret;
}

Ray ray_create(Vec3 origin, Vec3 direction) {
    return (Ray){.origin = origin, .direction = direction};
}

Ray ray_change_origin(Ray ray, Vec3 new_origin) {
    return (Ray){.origin = new_origin, .direction = ray.direction};
}

Ray ray_change_dir(Ray ray, Vec3 new_direction) {
    return (Ray){.origin = ray.origin, .direction = new_direction};
}

bool ray_hits_box(Ray ray, Vec3 left_bot_back, Vec3 right_top_front, float *tmin, float *tmax) {
    Vec3 t1 = vec3_div(vec3_sub(left_bot_back, ray.origin), ray.direction);
    Vec3 t2 = vec3_div(vec3_sub(right_top_front, ray.origin), ray.direction);

    Vec3 tmin3 = vec3_float(fminf(t1.x, t2.x), fminf(t1.y, t2.y), fminf(t1.z, t2.z));
    Vec3 tmax3 = vec3_float(fmaxf(t1.x, t2.x), fmaxf(t1.y, t2.y), fmaxf(t1.z, t2.z));

    float tmin_p = fmaxf(fmaxf(tmin3.x, tmin3.y), tmin3.z);
    float tmax_p = fminf(fminf(tmax3.x, tmax3.y), tmax3.z);

    if (tmax_p < 0.0f || tmin_p > tmax_p) return false;

    if (tmin) *tmin = tmin_p;
    if (tmax) *tmax = tmax_p;
    return true;
}

#endif //VMM_IMPLEMENTATION

