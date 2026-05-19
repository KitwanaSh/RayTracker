#include "ray.h"
#include "vector.h" // ADD THIS LINE

ray ray_create(point3 origin, point3 point_on_ray) {
  ray r;
  r.origin = origin;
  r.direction = vec3_sub(point_on_ray, origin);
  r.direction = vec3_normalize(r.direction);
  return r;
}

point3 ray_at(ray r, double t) {
  return vec3_add(r.origin, vec3_mul(r.direction, t));
}