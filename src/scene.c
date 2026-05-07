#include "scene.h"
#include "vector.h" // ADD THIS LINE
#include <stdio.h>


void scene_init(scene *s) {
  s->sphere_count = 0;
  s->background_top = vec3_create(0.5, 0.7, 1.0);    // Light blue
  s->background_bottom = vec3_create(0.1, 0.1, 0.3); // Dark blue
}

int scene_add_sphere(scene *s, sphere sph) {
  if (s->sphere_count >= MAX_SPHERES) {
    fprintf(stderr, "Error: Maximum sphere count reached\n");
    return 0;
  }

  s->spheres[s->sphere_count] = sph;
  s->sphere_count++;
  return 1;
}

int scene_intersect(const scene *s, const ray *r, double *t,
                    sphere **hit_sphere) {
  double closest_t = 1e10; // Very large number
  int hit_anything = 0;

  // Check intersection with all spheres
  for (int i = 0; i < s->sphere_count; i++) {
    double temp_t;
    if (sphere_intersect(r, &s->spheres[i], &temp_t)) {
      // Only consider positive intersections closer than current closest
      if (temp_t > 0.001 && temp_t < closest_t) {
        closest_t = temp_t;
        *hit_sphere = &s->spheres[i];
        hit_anything = 1;
      }
    }
  }

  if (hit_anything) {
    *t = closest_t;
    return 1;
  }

  return 0;
}