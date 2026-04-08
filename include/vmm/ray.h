#ifndef _RAY_H
#define _RAY_H
#include "vec3.h"
#include <stdbool.h>

typedef struct _ray {
    Vec3 origin, direction;
} Ray;

Ray ray_create(Vec3 origin, Vec3 direction);
Ray ray_change_origin(Ray ray, Vec3 new_origin);
Ray ray_change_dir(Ray ray, Vec3 new_direction);
bool ray_hits_box(Ray ray, Vec3 left_bot_back, Vec3 right_top_front, float *tmin, float *tmax);
#endif
