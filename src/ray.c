#include <vmm/vec3.h>
#include <ray.h>
#include <stdbool.h>

bool ray_hits_box(Ray ray, Vector3 left_bot_back, Vector3 right_top_front, float *tmin, float *tmax) {
    Vector3 t1 = vec3_div(vec3_sub(left_bot_back, ray.origin), ray.direction);
    Vector3 t2 = vec3_div(vec3_sub(right_top_front, ray.origin), ray.direction);
}
