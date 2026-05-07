#ifndef RAY_H
#define RAY_H

#include "types.h"

// Create a ray from origin through a point
ray ray_create(point3 origin, point3 point_on_ray);

// Get a point along the ray at distance t
point3 ray_at(ray r, double t);

#endif // RAY_H