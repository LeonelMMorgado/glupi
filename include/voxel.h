#ifndef _VOXEL_H
#define _VOXEL_H
#include <vmm/ivec3.h>
#include <color.h>
#include <stdbool.h>

typedef struct _voxel {
    float refraction, illumination, k;
} Voxel;

typedef struct _vox_obj {
    Voxel voxel;
    ColorRGBA color;
    IVector3 coord;
} Voxel_Object;

bool voxel_compare(Voxel a, Voxel b);
bool voxel_obj_compare(Voxel_Object a, Voxel_Object b);

#endif
