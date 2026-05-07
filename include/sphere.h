#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "types.h"


// Sphere definition
typedef struct {
  point3 center;
  double radius;
  color3 color;
} sphere;

// Check if ray intersects sphere
// Returns true if intersected, false otherwise
// If intersected, sets t to the distance along ray to intersection point
int sphere_intersect(const ray *ray, const sphere *sphere, double *t);

// Get normal at point on sphere
vec3 sphere_normal(const sphere *sphere, point3 point);

#endif // SPHERE_H