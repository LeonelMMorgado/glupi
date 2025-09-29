#include <octree.h>
#include <vmm/vec3.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef MIN_HEIGHT
#define MIN_HEIGHT 256.0f
#endif

#define TOPLEFTFRONT 0
#define TOPRIGHTFRONT 1
#define TOPLEFTBACK 2
#define TOPRIGHTBACK 3
#define BOTTOMRIGHTFRONT 4
#define BOTTOMLEFTFRONT 5
#define BOTTOMRIGHTBACK 6
#define BOTTOMLEFTBACK 7

int _get_pos_in_octree(Vector3 coord, Vector3 mid_points) {
    if (coord.x <= mid_points.x) {
        if (coord.y <= mid_points.y) {
            if (coord.z <= mid_points.z)
                return TOPLEFTFRONT;
            else
                return TOPLEFTBACK;
        }
        else {
            if (coord.z <= mid_points.z)
                return BOTTOMLEFTFRONT;
            else
                return BOTTOMLEFTBACK;
        }
    }
    else {
        if (coord.y <= mid_points.y) {
            if (coord.z <= mid_points.z)
                return TOPRIGHTFRONT;
            else
                return TOPRIGHTBACK;
        }
        else {
            if (coord.z <= mid_points.z)
                return BOTTOMRIGHTFRONT;
            else
                return BOTTOMRIGHTBACK;
        }
    }
}

bool _coord_in_space(Vector3 coord, Vector3 top_left_front, Vector3 bot_right_back) {
    return coord.x < top_left_front.x
        || coord.x > bot_right_back.x
        || coord.y < top_left_front.y
        || coord.y > bot_right_back.y
        || coord.z < top_left_front.z
        || coord.z > bot_right_back.z;
}

Octree *octree_new(void) {
    Octree *ot = malloc(sizeof(Octree));
    ot->voxel = NULL;
    ot->children = NULL;
    ot->top_left_front = (Vector3){0.0, 0.0, 0.0};
    ot->bot_right_back = (Vector3){0.0, 0.0, 0.0};
    return ot;
}

Octree *octree_create(Vector3 top_left_front, Vector3 bot_right_back) {
    Octree *ot = octree_new();
    ot->top_left_front = top_left_front;
    ot->bot_right_back = bot_right_back;
    return ot;
}

Voxel_Object *octree_find(Octree *tree, Vector3 coord) {
    if(!_coord_in_space(coord, tree->top_left_front, tree->bot_right_back)) return NULL;
    if(!tree->voxel) return NULL;
    if(tree->voxel->coord.x == coord.x && tree->voxel->coord.y == coord.y && tree->voxel->coord.z == coord.z) return tree->voxel;
    Vector3 mid_points = vec3_scalar_div(vec3_add(tree->top_left_front, tree->bot_right_back), 2);
    int pos = _get_pos_in_octree(coord, mid_points);
    //TODO: iterfind instead of recursive
}

void octree_insert(Octree *tree, Voxel_Object *voxel) {
    //if(octree_find(tree, voxel->coord)) return;
    if(_coord_in_space(voxel->coord, tree->top_left_front, tree->bot_right_back)) return;
    if(!tree->voxel) {
        tree->voxel = voxel;
        return;
    }
    Vector3 mid_points = vec3_scalar_div(vec3_add(tree->top_left_front, tree->bot_right_back), 2);
    if(tree->voxel->coord.y > MIN_HEIGHT && !tree->children) {
        tree->children = malloc(sizeof(Octree*) * 8);
        tree->children[0] = octree_create(tree->top_left_front, mid_points);                                       //top left front
        tree->children[1] = octree_create((Vector3){mid_points.x, tree->top_left_front.y, tree->top_left_front.z}, //top right front
                                          (Vector3){tree->bot_right_back.x, mid_points.y, mid_points.z});
        tree->children[2] = octree_create((Vector3){tree->top_left_front.x, tree->top_left_front.y, mid_points.z}, //top left back
                                          (Vector3){mid_points.x, mid_points.y, tree->bot_right_back.z});
        tree->children[3] = octree_create((Vector3){mid_points.x, tree->top_left_front.y, mid_points.z},           //top right back
                                          (Vector3){tree->bot_right_back.x, mid_points.y, tree->bot_right_back.z});
        tree->children[4] = octree_create((Vector3){tree->top_left_front.x, mid_points.y, tree->top_left_front.z}, //bot left front
                                          (Vector3){mid_points.x, tree->bot_right_back.y, tree->bot_right_back.z});
        tree->children[5] = octree_create((Vector3){mid_points.x, mid_points.y, tree->top_left_front.z),           //bot right front
                                          (Vector3){tree->bot_right_back.x, tree->bot_right_back.y, mid_points.z});
        tree->children[6] = octree_create((Vector3){tree->top_left_front.x, mid_points.y, mid_points.z},           //bot left back
                                          (Vector3){mid_points.x, tree->bot_right_back.y, tree->bot_right_back.z});
        tree->children[7] = octree_create(mid_points, tree->bot_right_back);                                       //bot right back
        tree->voxel->coord.y = MIN_HEIGHT;
    }
    int pos = _get_pos_in_octree(voxel->coord, mid_points);
    octree_insert(tree->children[pos], voxel);
}

void octree_delete(Octree *tree) {
    if(!tree) return;
    for(int i = 0; i < 8; i++) octree_delete(tree);
    free(tree->voxel);
    free(tree->children);
    free(tree);
}
