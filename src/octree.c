#include <octree.h>

Octree *octree_create() {
    
}

Voxel *octree_find(Octree *tree, Vector3 coord) {
    if(coord.x < tree->top_left_front.x
        || coord.x > tree->bot_right_back.x
        || coord.y < tree->top_left_front.y
        || coord.y > tree->bot_right_back.y
        || coord.z < tree->top_left_front.z
        || coord.z > tree->bot_right_back.z
        )
        return NULL;
}

void octree_include(Octree *tree, Voxel *voxel, Vector3 coord) {

}

void octree_delete(Octree
