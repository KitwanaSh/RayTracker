#ifndef LIGHTING_H
#define LIGHTING_H

#include "light.h"
#include "material.h"
#include "scene.h"
#include "types.h"

// Calculate Phong lighting at a point
// hit_point: point on surface
// normal: surface normal at hit point
// view_dir: direction from hit point to camera
// mat: material properties
// scene: the scene (for lights and shadow testing)
color3 calculate_lighting(point3 hit_point, vec3 normal, vec3 view_dir,
                          const material *mat, const scene *world);

#endif // LIGHTING_H