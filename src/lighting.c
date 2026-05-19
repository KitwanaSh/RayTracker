#include <math.h>
#include <stdlib.h> // ADD THIS for NULL

#include "lighting.h"
#include "ray.h" // ADD THIS to be safe
#include "vector.h"

// The rest of the file remains unchanged
static color3 color_clamp(color3 c) {
  color3 result;
  result.x = (c.x < 0.0) ? 0.0 : (c.x > 1.0) ? 1.0 : c.x;
  result.y = (c.y < 0.0) ? 0.0 : (c.y > 1.0) ? 1.0 : c.y;
  result.z = (c.z < 0.0) ? 0.0 : (c.z > 1.0) ? 1.0 : c.z;
  return result;
}

static color3 color_multiply(color3 a, color3 b) {
  return vec3_create(a.x * b.x, a.y * b.y, a.z * b.z);
}

color3 calculate_lighting(point3 hit_point, vec3 normal, vec3 view_dir,
                          const material *mat, const scene *world) {
  // Start with ambient
  color3 final_color = color_multiply(world->ambient_light, mat->diffuse);
  final_color = vec3_mul(final_color, mat->ambient);

  normal = vec3_normalize(normal);
  view_dir = vec3_normalize(view_dir);

  for (int i = 0; i < world->light_count; i++) {
    light *l =
        &world->lights[i]; // Warning about const discarded – fine for now

    vec3 light_dir = vec3_sub(l->position, hit_point);
    double light_distance = vec3_length(light_dir);
    light_dir = vec3_normalize(light_dir);

    // Shadow ray (full type now known)
    ray shadow_ray = ray_create(hit_point, vec3_add(hit_point, light_dir));
    double shadow_t;
    sphere *shadow_sphere = NULL;

    int in_shadow = 0;
    if (scene_intersect(world, &shadow_ray, &shadow_t, &shadow_sphere)) {
      if (shadow_t < light_distance) {
        in_shadow = 1;
      }
    }

    if (!in_shadow) {
      double diffuse_strength = vec3_dot(normal, light_dir);
      if (diffuse_strength > 0.0) {
        color3 diffuse = color_multiply(mat->diffuse, l->color);
        diffuse = vec3_mul(diffuse, diffuse_strength * l->intensity);
        final_color = vec3_add(final_color, diffuse);
      }

      vec3 reflect_dir = vec3_sub(
          vec3_mul(normal, 2.0 * vec3_dot(normal, light_dir)), light_dir);
      reflect_dir = vec3_normalize(reflect_dir);

      double specular_strength = vec3_dot(view_dir, reflect_dir);
      if (specular_strength > 0.0) {
        specular_strength = pow(specular_strength, mat->shininess);
        color3 specular = color_multiply(mat->specular, l->color);
        specular = vec3_mul(specular, specular_strength * l->intensity);
        final_color = vec3_add(final_color, specular);
      }
    }
  }

  return color_clamp(final_color);
}