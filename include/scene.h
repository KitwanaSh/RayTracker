#ifndef SCENE_H
#define SCENE_H

#include "sphere.h"
#include "types.h"


#define MAX_SPHERES 32

// Scene structure containing all objects
typedef struct {
  sphere spheres[MAX_SPHERES];
  int sphere_count;
  color3 background_top;
  color3 background_bottom;
} scene;

// Initialize an empty scene
void scene_init(scene *s);

// Add a sphere to the scene
int scene_add_sphere(scene *s, sphere sph);

// Find closest intersection with any object in scene
// Returns 1 if hit, 0 if no hit
// Sets hit_sphere to the sphere that was hit
// Sets t to the distance to the hit
int scene_intersect(const scene *s, const ray *r, double *t,
                    sphere **hit_sphere);

#endif // SCENE_H