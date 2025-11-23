#ifndef _CAMERA_H
#define _CAMERA_H

#include <vmm/vec2.h>
#include <vmm/vec3.h>
#include <vmm/vec4.h>
#include <vmm/mat4.h>
#include <window.h>

typedef enum _cam_type {
    ORTHOGRAPHIC_CAMERA,
    PERSPECTIVE_CAMERA,
} CameraType;

typedef struct _view_proj {
    Mat4 view, proj;
} ViewProj;

typedef struct _p_cam {
    Vector3 direction, up, world_up, right, sensitivity;

    float pitch, yaw, fov, aspect, zNear, zFar;
} PerspectiveCamera;

typedef struct _o_cam {
    Vector2 min, max;
} OrthographicCamera;

typedef struct _camera {
    //TODO: add roll for camera_shake
    ViewProj view_proj;
    CameraType type;
    Vector3 position;
    union {
        PerspectiveCamera camera_p;
        OrthographicCamera camera_o;
    };
} Camera;

typedef union _camera_args {
    float p_fov;
    Vector4 min_max;
} Camera_Args;

Camera *camera_create(Window *win, CameraType type, Camera_Args args);
void camera_move(Camera *camera, Vector3 movement);
void camera_yaw_pitch(Camera *camera, Vector2 offset);
void camera_update_pos(Camera *camera, Vector3 new_pos);
void camera_update_yaw(Camera *camera, float xoffset);
void camera_update_pitch(Camera *camera, float yoffset);
void camera_update_fov(Camera *camera, float new_fov);
void camera_update_direction(Camera *camera);
void camera_update_proj(Camera *camera);
void camera_update_view(Camera *camera);
void camera_update_view_proj(Camera *camera);
void camera_destroy(Camera **camera);

#endif
