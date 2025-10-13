#include <vmm/vec3.h>
#include <ray.h>
#include <stdbool.h>

bool ray_hits_box(Ray ray, Vector3 left_bot_back, Vector3 right_top_front, float *tmin, float *tmax) {
    Vector3 inverse_direction = vec3_div((Vector3){1.0, 1.0, 1.0}, ray.direction);

    Vector3 t1 = vec3_mul(vec3_sub(left_bot_back, ray.origin), inverse_direction);
}
