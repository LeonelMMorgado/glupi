#include <stdlib.h>
#include <math.h>
#include <camera.h>
#include <vmm/projection.h>

Camera *camera_create(Window *win, CameraType type, Camera_Args args) {
    Camera *c = calloc(1, sizeof(Camera));
    c->type = type;
    c->position = (Vector3){0};
    if(type == ORTHOGRAPHIC_CAMERA) {
        c->camera_o.min = vec2_float(args.min_max.x, args.min_max.y);
        c->camera_o.max = vec2_float(args.min_max.z, args.min_max.w);
        c->view_proj.proj = mat4_orthogonal(c->camera_o.min.x, c->camera_o.max.x, c->camera_o.min.y, c->camera_o.max.y, -1, 1);

        Vector3 eye = vec3_forward();
        Vector3 center = vec3_zero();
        Vector3 up = vec3_up();
        c->view_proj.view = mat4_look_at(eye, center, up);
    }
    else if(type == PERSPECTIVE_CAMERA) {
        c->camera_p.fov = args.p_fov;
        c->camera_p.aspect = win->settings.size.x / win->settings.size.y;
        c->camera_p.zNear = 0.01f;
        c->camera_p.zFar = 1000.0f;
        c->camera_p.direction = vec3_back();
        c->camera_p.up = vec3_up();
        c->camera_p.world_up = c->camera_p.up;
        c->camera_p.right = vec3_cross(c->camera_p.direction, c->camera_p.up);
        c->view_proj.proj = mat4_perspective(c->camera_p.fov, c->camera_p.aspect, c->camera_p.zNear, c->camera_p.zFar);
        
        Vector3 eye = vec3_zero();
        Vector3 center = vec3_add(eye, c->camera_p.direction);
        Vector3 up = c->camera_p.up;
        c->view_proj.view = mat4_look_at(eye, center, up);
    }
    return c;
}

void camera_move(Camera *camera, Vector3 movement) {
    camera_update_pos(camera, vec3_add(camera->position, vec3_mul(camera->camera_p.direction, movement)));
}

void camera_update_pos(Camera *camera, Vector3 new_pos) {
    camera->position = new_pos;
    // camera_update_view(camera);
}

void camera_yaw_pitch(Camera *camera, Vector2 offset) {
    camera_update_yaw(camera, offset.x);
    camera_update_pitch(camera, offset.y);
}

void camera_update_yaw(Camera *camera, float xoffset) {
    camera->camera_p.yaw += (xoffset * camera->camera_p.sensitivity.x);
}

void camera_update_pitch(Camera *camera, float yoffset) {
    camera->camera_p.pitch += (yoffset * camera->camera_p.sensitivity.y);
    //TODO: add constraint
}

void camera_update_fov(Camera *camera, float new_fov) {
    camera->camera_p.fov = new_fov;
}

void camera_update_direction(Camera *camera) {
    float yaw_rad = camera->camera_p.yaw * M_PI / 180.0f;
    float pitch_rad = camera->camera_p.pitch * M_PI / 180.0f;

    camera->camera_p.direction.x = cosf(yaw_rad) * cosf(pitch_rad);
    camera->camera_p.direction.y = sinf(pitch_rad);
    camera->camera_p.direction.z = sinf(yaw_rad) * cosf(pitch_rad);
    camera->camera_p.direction = vec3_normalize(camera->camera_p.direction);
    camera->camera_p.right = vec3_normalize(vec3_cross(camera->camera_p.direction, camera->camera_p.world_up));
    camera->camera_p.up = vec3_normalize(vec3_cross(camera->camera_p.right, camera->camera_p.direction));
}

void camera_update_proj(Camera *camera) {
    if(camera->type == ORTHOGRAPHIC_CAMERA)
        ;
    if(camera->type == PERSPECTIVE_CAMERA)
        camera->view_proj.proj = mat4_perspective(camera->camera_p.fov, camera->camera_p.aspect, camera->camera_p.zNear, camera->camera_p.zFar);
}

void camera_update_view(Camera *camera) {
    if(camera->type == ORTHOGRAPHIC_CAMERA)
        ;
    if(camera->type == PERSPECTIVE_CAMERA) {
        Vector3 center = vec3_add(camera->position, camera->camera_p.direction);
        camera->view_proj.view = mat4_look_at(camera->position, center, camera->camera_p.up);
    }
}

void camera_update_view_proj(Camera *camera) {
    camera_update_view(camera);
    camera_update_proj(camera);
}

void camera_destroy(Camera **camera) {
    if(!camera) return;
    if(!*camera) return;
    free(*camera);
    *camera = NULL;
}
