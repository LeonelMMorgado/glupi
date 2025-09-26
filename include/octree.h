#include <voxel.h>
#include <vmm/vec3.h>

typedef struct _octree {
    Voxel *voxel;
    struct _octree *children;
    Vector3 top_left_front, bot_right_back;
} Octree;

Octree *octree_new(void);
Octree *octree_create(Vector3 top_left_front, Vector3 bot_right_back);
void octree_include(Octree *tree, Voxel_Object *voxel);
Voxel_Object *octree_find(Octree *tree, Vector3 coord);
void octree_delete(Octree *tree);
