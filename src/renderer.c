#include "renderer.h"
#include "lighting.h"
#include "sphere.h"
#include "vector.h"
#include <math.h>
#include <stdlib.h>


// Helper: get background color
static color3 get_background(const scene *world, const ray *r) {
  // Vertical gradient based on ray direction
  vec3 unit_direction = vec3_normalize(r->direction);
  double t = 0.5 * (unit_direction.y + 1.0);

  color3 color;
  color.x =
      (1.0 - t) * world->background_top.x + t * world->background_bottom.x;
  color.y =
      (1.0 - t) * world->background_top.y + t * world->background_bottom.y;
  color.z =
      (1.0 - t) * world->background_top.z + t * world->background_bottom.z;
  return color;
}

// Helper: clamp color
static color3 color_clamp(color3 c) {
  color3 result;
  result.x = (c.x < 0.0) ? 0.0 : (c.x > 1.0) ? 1.0 : c.x;
  result.y = (c.y < 0.0) ? 0.0 : (c.y > 1.0) ? 1.0 : c.y;
  result.z = (c.z < 0.0) ? 0.0 : (c.z > 1.0) ? 1.0 : c.z;
  return result;
}

// Helper: component-wise color multiply
static color3 color_multiply(color3 a, color3 b) {
  return vec3_create(a.x * b.x, a.y * b.y, a.z * b.z);
}

color3 trace_ray(const scene *world, const ray *r, int depth) {
  // Stop recursion if too deep
  if (depth >= MAX_RECURSION_DEPTH) {
    return vec3_create(0, 0, 0); // Black
  }

  // Find intersection
  double t;
  sphere *hit_sphere = NULL;

  if (scene_intersect(world, r, &t, &hit_sphere)) {
    // We hit something!
    point3 hit_point = ray_at(*r, t);
    vec3 normal = sphere_normal(hit_sphere, hit_point);
    vec3 view_dir = vec3_mul(r->direction, -1.0);

    // Calculate local lighting (Phong)
    color3 local_color = calculate_lighting(hit_point, normal, view_dir,
                                            &hit_sphere->mat, world);

    // If material is reflective, trace reflection ray
    if (hit_sphere->mat.reflectivity > 0.0) {
      // Calculate reflection direction: R = I - 2(I·N)N
      vec3 incident = r->direction;
      vec3 reflect_dir = vec3_sub(
          incident, vec3_mul(normal, 2.0 * vec3_dot(incident, normal)));
      reflect_dir = vec3_normalize(reflect_dir);

      // Create reflection ray (offset slightly to avoid self-intersection)
      point3 reflect_origin = vec3_add(hit_point, vec3_mul(normal, 0.001));
      ray reflect_ray =
          ray_create(reflect_origin, vec3_add(reflect_origin, reflect_dir));

      // Recursively trace reflection
      color3 reflect_color = trace_ray(world, &reflect_ray, depth + 1);

      // Mix local color and reflection based on reflectivity
      double reflectivity = hit_sphere->mat.reflectivity;
      color3 final_color;
      final_color.x =
          (1.0 - reflectivity) * local_color.x + reflectivity * reflect_color.x;
      final_color.y =
          (1.0 - reflectivity) * local_color.y + reflectivity * reflect_color.y;
      final_color.z =
          (1.0 - reflectivity) * local_color.z + reflectivity * reflect_color.z;

      return color_clamp(final_color);
    } else {
      // Not reflective, just return local lighting
      return local_color;
    }
  }

  // No hit - return background
  return get_background(world, r);
}