#ifndef SPHERE_H
#define SPHERE_H

#include "material.h"
#include "ray.h" // Include full ray definition
#include "types.h"

// Sphere definition
typedef struct {
  point3 center;
  double radius;
  material mat;
} sphere;

// Check if ray intersects sphere
int sphere_intersect(const ray *ray, const sphere *sphere, double *t);

// Get normal at point on sphere
vec3 sphere_normal(const sphere *sphere, point3 point);

#endif // SPHERE_H