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
    Vector3 direction, up, right;

    float pitch, yaw, fov, aspect, zNear, zFar;
} PerspectiveCamera;

typedef struct _o_cam {
    Vector2 min, max;
} OrthographicCamera;

typedef struct _camera {
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
void camera_delete(Camera *camera);

#endif
