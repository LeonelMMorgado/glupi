#include <vmm/ivec3.h>
#include <color.h>

typedef enum _vox_type {
    VOX_AIR,
    VOX_GRASS,
    VOX_DIRT,
    VOX_STONE,
    VOX_WATER,

    VOX_LAST,
} Voxel_Type;

typedef struct _voxel {
    Voxel_Type type;
    float hardness, opacity, refraction;
} Voxel;

//Voxel voxels[] = {}; Array com blocos possíveis

typedef struct _vox_obj {
    Voxel voxel;
    ColorRGBA color;
    IVector3 coord;
} Voxel_Object;
