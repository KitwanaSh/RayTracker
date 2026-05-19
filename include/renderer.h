#ifndef RENDERER_H
#define RENDERER_H

#include "ray.h"
#include "scene.h"
#include "types.h"


#define MAX_RECURSION_DEPTH 5

// Trace a ray through the scene
// Returns the color seen along the ray
// depth: current recursion depth (starts at 0)
color3 trace_ray(const scene *world, const ray *r, int depth);

#endif // RENDERER_H