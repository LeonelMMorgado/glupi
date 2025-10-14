#include <octree.h>
#include <vmm/ivec3.h>
#include <ray.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#ifndef MIN_HEIGHT
#define MIN_HEIGHT -256
#endif

enum pos_in_octree {
    LEFTBOTBACK,
    LEFTBOTFRONT,
    LEFTTOPBACK,
    LEFTTOPFRONT,
    RIGHTBOTBACK,
    RIGHTBOTFRONT,
    RIGHTTOPBACK,
    RIGHTTOPFRONT
};

int _get_pos_in_octree(IVector3 coord, IVector3 mid_points) {
    if (coord.x <= mid_points.x) {
        if (coord.y <= mid_points.y) {
            if (coord.z <= mid_points.z)
                return LEFTBOTBACK;
            else
                return LEFTBOTFRONT;
        }
        else {
            if (coord.z <= mid_points.z)
                return LEFTTOPBACK;
            else
                return LEFTTOPFRONT;
        }
    }
    else {
        if (coord.y <= mid_points.y) {
            if (coord.z <= mid_points.z)
                return RIGHTBOTBACK;
            else
                return RIGHTBOTFRONT;
        }
        else {
            if (coord.z <= mid_points.z)
                return RIGHTTOPBACK;
            else
                return RIGHTTOPFRONT;
        }
    }
}

bool _coord_in_space(IVector3 coord, IVector3 left_bot_back, IVector3 right_top_front) {
    return coord.x < left_bot_back.x
        || coord.x > right_top_front.x
        || coord.y < left_bot_back.y
        || coord.y > right_top_front.y
        || coord.z < left_bot_back.z
        || coord.z > right_top_front.z;
}

Octree *octree_new(void) {
    Octree *ot = malloc(sizeof(Octree));
    ot->voxel = NULL;
    ot->children = NULL;
    ot->left_bot_back = (IVector3){0, 0, 0};
    ot->right_top_front = (IVector3){0, 0, 0};
    return ot;
}

Octree *octree_create(IVector3 left_bot_back, IVector3 right_top_front) {
    Octree *ot = octree_new();
    ot->left_bot_back = left_bot_back;
    ot->right_top_front = right_top_front;
    return ot;
}

Voxel_Object *octree_find(Octree *tree, IVector3 coord) {
    if(!_coord_in_space(coord, tree->left_bot_back, tree->right_top_front)) return NULL;
    if(!tree->voxel) return NULL;
    if(ivec3_equal_vec(tree->voxel->coord, coord)) return tree->voxel;
    if(!tree->children) return NULL;
    IVector3 mid_points = ivec3_scalar_div(ivec3_add(tree->left_bot_back, tree->right_top_front), 2);
    int pos = _get_pos_in_octree(coord, mid_points);
    Octree *ref = tree->children[pos];
    while(true) {
        if(!_coord_in_space(coord, ref->left_bot_back, ref->right_top_front)) return NULL;
        if(!ref->voxel) return NULL;
        if(ivec3_equal_vec(tree->voxel->coord, coord)) return tree->voxel;
        if(!tree->children) return NULL;
        mid_points = ivec3_scalar_div(ivec3_add(ref->left_bot_back, ref->right_top_front), 2);
        pos = _get_pos_in_octree(coord, mid_points);
        ref = ref->children[pos];
    }
    return NULL;
}

void _create_children(Octree *tree, IVector3 mid_points) {
    tree->children = malloc(sizeof(Octree*) * 8);
    IVector3 min = tree->left_bot_back;
    IVector3 max = tree->right_top_front;
    IVector3 mid = ivec3_scalar_div(ivec3_add(min, max), 2);
    tree->children[LEFTBOTBACK]   = octree_create(min, mid);
    tree->children[LEFTBOTFRONT]  = octree_create((IVector3){min.x, min.y, mid.z},
                                                  (IVector3){mid.x, mid.y, max.z});
    tree->children[LEFTTOPBACK]   = octree_create((IVector3){min.x, mid.y, min.z},
                                                  (IVector3){mid.x, max.y, mid.z});
    tree->children[LEFTTOPFRONT]  = octree_create((IVector3){min.x, mid.y, mid.z},
                                                  (IVector3){mid.x, max.y, max.z});
    tree->children[RIGHTBOTBACK]  = octree_create((IVector3){mid.x, min.y, min.z},
                                                  (IVector3){max.x, mid.y, mid.z});
    tree->children[RIGHTBOTFRONT] = octree_create((IVector3){mid.x, min.y, mid.z},
                                                  (IVector3){max.x, mid.y, max.z});
    tree->children[RIGHTTOPBACK]  = octree_create((IVector3){mid.x, mid.y, min.z},
                                                  (IVector3){max.x, max.y, mid.z});
    tree->children[RIGHTTOPFRONT] = octree_create(mid, max);
    for(int i = 0; i < 8; i++) tree->children[i]->voxel = NULL;
    int pos = _get_pos_in_octree(tree->voxel->coord, mid_points);
    tree->children[pos]->voxel = tree->voxel;
    tree->voxel = malloc(sizeof(Voxel_Object));
    tree->voxel->coord.y = MIN_HEIGHT;
}

void octree_insert(Octree *tree, Voxel_Object *voxel) {
    if(octree_find(tree, voxel->coord)) return;
    if(!tree) return;
    Octree *curr = tree;
    while(true) {
        if(!_coord_in_space(voxel->coord, curr->left_bot_back, curr->right_top_front)) return;
        if(!curr->voxel) {
            curr->voxel = voxel;
            return;
        }
        if(ivec3_equal_vec(curr->voxel->coord, voxel->coord)) return;
        IVector3 mid_points = ivec3_scalar_div(ivec3_add(curr->left_bot_back, curr->right_top_front), 2);
        int pos = _get_pos_in_octree(voxel->coord, mid_points);
        if(curr->voxel->coord.y > MIN_HEIGHT || !curr->children) {
            _create_children(curr, mid_points);
            curr->children[pos]->voxel = voxel;
            return;
        }
        curr = curr->children[pos];
    }
}

//TODO: void octree_remove(IVector3 coord);

void octree_delete(Octree *tree) {
    if(!tree) return;
    for(int i = 0; i < 8; i++) octree_delete(tree);
    free(tree->voxel);
    free(tree->children);
    free(tree);
}

// Octree *octree_dda(Octree *tree, Ray ray) {
//     float tmin;
//     float tmax;
// 
// 
//     /// make sure the ray hits the bounding box of the root octree node
//     if (!ray_hits_box(ray, tree->left_bot_back, tree->right_top_front, &tmin, &tmax))
//         return NULL;
// 
// 
//     /// move the ray position to the point of intersection with the bounding volume.
//     ray.origin = vec3_scalar_mul(ray.direction, fmin(tmin, tmax));
// 
//     /// get integer cell coordinates for the given position
//     ///     leafSize is a Vector3 containing the dimensions of a leaf node in world-space coordinates
//     ///     cellCount is a Vector3 containng the number of cells in each direction, or the size of the tree root divided by leafSize.
//     Vector3 cell = Vector3.Min(((ray.origin - boundingBox.Min) / leafSize).Truncate(), cellCount - Vector3.One);
//     Vector3 cell = vec3_min( ivec3_truncate_vec3( vec3_div( vec3_sub(ray.origin, tree->left_bot_back), leafSize(:1))), vec3_sub(cell_count, vec3_one()));
//
// 
//     /// get the Vector3 where of the intersection point relative to the tree root.
//     Vector3 pos = vec3_sub(ray.origin, tree->left_bot_back);
// 
//     /// get the bounds of the starting cell - leaf size offset by "pos"
//     var cellBounds = GetCellBounds(cell);
// 
//     /// calculate initial t values for each axis based on the sign of the ray.
//     /// See any good 3D DDA tutorial for an explanation of t, but it basically tells us the 
//     /// distance we have to move from ray.origin along ray.direction to reach the next cell boundary
//     /// This calculates t values for both positive and negative ray directions.
//     Vector3 tMaxNeg = vec3_div(vec3_sub(cellBounds.Min, ray.origin), ray.direction);
//     Vector3 tMaxPos = vec3_div(vec3_sub(cellBounds.Max, ray.origin), ray.direction);
// 
//     /// calculate t values within the cell along the ray direction.
//     /// This may be buggy as it seems odd to mix and match ray directions
//     var tMax = new Vector3(
//         ray.direction.X < 0 ? tMaxNeg.X : tMaxPos.X
//         ,
//         ray.direction.Y < 0 ? tMaxNeg.Y : tMaxPos.Y
//         ,
//         ray.direction.Z < 0 ? tMaxNeg.Z : tMaxPos.Z
//         );
// 
//     /// get cell coordinate step directions
//     /// .Sign() is an extension method that returns a Vector3 with each component set to +/- 1
//     var step = ray.direction.Sign();
// 
//     /// calculate distance along the ray direction to move to advance from one cell boundary 
//     /// to the next on each axis. Assumes ray.direction is normalized.
//     /// Takes the absolute value of each ray component since this value is in units along the
//     /// ray direction, which makes sure the sign is correct.
//     var tDelta = (leafSize / ray.direction).Abs();
// 
//     /// neighbor node indices to use when exiting cells
//     /// Griddirection.East = Vector3.Right
//     /// Griddirection.West = Vector3.Left
//     /// Griddirection.North = Vector3.Forward
//     /// Griddirection.South = Vector4.Back
//     /// Griddirection.Up = Vector3.Up
//     /// Griddirection.Down = Vector3.Down
//     var neighbour_directions = new[] { 
//         (step.X < 0) ? Griddirection.West : GridDirection.East
//         ,
//         (step.Y < 0) ? Griddirection.Down : GridDirection.Up
//         ,
//         (step.Z < 0) ? Griddirection.North : GridDirection.South
//     };
// 
//     OctreeNode node=root;
// 
//     /// step across the bounding volume, generating a marker entity at each
//     /// cell that we touch. Extension methods GreaterThanOrEEqual and LessThan
//     /// ensure that we stay within the bounding volume.
//     while (node != NULL) {
//         /// if the current node isn't a leaf, find one.
//         /// this version exits when it encounters the first leaf.
//         if(!node.Leaf)
//             for(var i = 0; i < OctreeNode.ChildCount; i++) {
//                 var child = node.Children[i];
//                 if(child != null && child.Contains(cell)) {
//                     //SetNode(ref node, child, visitedNodes);
//                     node = child;
//                     i = -1;
// 
//                     if (node.Leaf)
//                         return node;
//                 }
//             }
// 
//         /// index into the node's Neighbor[] array to move
//         int dir = 0;
// 
//         /// This is off-the-shelf DDA.
//         if(tMax.X < tMax.Y) {
//             if(tMax.X < tMax.Z) {
//                 tMax.X += tDelta.X;
//                 cell.X += step.X;
//                 dir = 0;
//             }
//             else {
//                 tMax.Z += tDelta.Z;
//                 cell.Z += step.Z;
//                 dir = 2;
//             }
//         }
//         else {
//             if(tMax.Y < tMax.Z) {
//                 tMax.Y += tDelta.Y;
//                 cell.Y += step.Y;
//                 dir = 1;
//             }
//             else {
//                 tMax.Z += tDelta.Z;
//                 cell.Z += step.Z;
//                 dir = 2;
//             }
//         }
// 
//         /// see if the new cell coordinates fall within the current node.
//         /// this is important when moving from a leaf into empty space within 
//         /// the tree.
//         if(!node.Contains(cell)) {
//             /// if we stepped out of this node, grab the appropriate neighbor. 
//             var neighborDir = neighbour_directions[dir];
//             node = node.GetNeighbor(neighborDir);
//         }
//         else if (node.Leaf && stopAtFirstLeaf)
//             return node;
//     }
// 
//     return null;
// 
// }

