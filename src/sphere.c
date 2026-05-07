#include "sphere.h"
#include "vector.h" // ADD THIS LINE
#include <math.h>


int sphere_intersect(const ray *ray, const sphere *sphere, double *t) {
  // Vector from ray origin to sphere center
  vec3 oc = vec3_sub(sphere->center, ray->origin);

  // (ray.direction · oc)
  double b = vec3_dot(ray->direction, oc);

  // (oc · oc) - radius^2
  double c = vec3_length_squared(oc) - sphere->radius * sphere->radius;

  // Discriminant: b² - c
  double discriminant = b * b - c;

  // No real roots → no intersection
  if (discriminant < 0) {
    return 0;
  }

  // Calculate the two possible solutions
  discriminant = sqrt(discriminant);
  double t0 = b - discriminant;
  double t1 = b + discriminant;

  // We want the closest positive intersection
  if (t0 > 0) {
    *t = t0;
    return 1;
  } else if (t1 > 0) {
    *t = t1;
    return 1;
  }

  // Both solutions are negative (behind the ray origin)
  return 0;
}

vec3 sphere_normal(const sphere *sphere, point3 point) {
  // Normal is vector from center to point, normalized
  vec3 normal = vec3_sub(point, sphere->center);
  return vec3_normalize(normal);
}