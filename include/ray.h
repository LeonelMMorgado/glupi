#include <vmm/vec3.h>
#include <stdbool.h>

typedef struct _ray {
    Vector3 origin, direction;
} Ray;

Ray ray_create(Vector3 origin, Vector3 direction);
Ray ray_change_dir(Vector3 new_direction);
Ray ray_change_origin(Vector3 new_origin);
bool ray_hits_box(Ray ray, Vector3 left_bot_back, Vector3 right_top_front, float *tmin, float *tmax);
