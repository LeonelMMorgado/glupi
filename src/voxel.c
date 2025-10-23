#include <voxel.h>
#include <vmm/ivec3.h>

bool voxel_compare(Voxel a, Voxel b) {
    if(a.refraction != b.refraction) return false;
    if(a.illumination != b.illumination) return false;
    return true;
}

bool voxel_obj_compare(Voxel_Object a, Voxel_Object b) {
    if(!ivec3_equal_vec(a.coord, b.coord)) return false;
    if(!voxel_compare(a.voxel, b.voxel)) return false;
    return true;
}

