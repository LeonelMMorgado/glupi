#include <voxel.h>
#include <vmm/vec3.h>

typedef struct _octree {
    Voxel_Object *voxel;
    struct _octree **children; //always either NULL or with 8 members
    Vector3 top_left_front, bot_right_back;
} Octree;

Octree *octree_new(void);
Octree *octree_create(Vector3 top_left_front, Vector3 bot_right_back);
void octree_insert(Octree *tree, Voxel_Object *voxel);
Voxel_Object *octree_find(Octree *tree, Vector3 coord);
void octree_delete(Octree *tree);
