#ifndef SCENE_H
#define SCENE_H

#include "light.h"
#include "ray.h"
#include "sphere.h"
#include "types.h"


#define MAX_SPHERES 32
#define MAX_LIGHTS 8

typedef struct {
  sphere spheres[MAX_SPHERES];
  int sphere_count;

  light lights[MAX_LIGHTS];
  int light_count;

  color3 background_top;
  color3 background_bottom;
  color3 ambient_light;
} scene;

void scene_init(scene *s);
int scene_add_sphere(scene *s, sphere sph);
int scene_add_light(scene *s, light l);
int scene_intersect(const scene *s, const ray *r, double *t,
                    sphere **hit_sphere);

#endif // SCENE_H