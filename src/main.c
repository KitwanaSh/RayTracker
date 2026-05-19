#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#include "image.h"
#include "light.h"
#include "lighting.h"
#include "material.h"
#include "ray.h"
#include "scene.h"
#include "sphere.h"
#include "types.h"
#include "vector.h"


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT 600
#define FOV 60.0

color3 get_background_color(const scene *s, double t) {
  color3 color;
  color.x = (1.0 - t) * s->background_top.x + t * s->background_bottom.x;
  color.y = (1.0 - t) * s->background_top.y + t * s->background_bottom.y;
  color.z = (1.0 - t) * s->background_top.z + t * s->background_bottom.z;
  return color;
}

int main(void) {
  printf("SimpleRayTracer - Milestone 4: Phong Lighting\n");
  printf("Rendering scene with realistic lighting...\n");

  int width = IMAGE_WIDTH;
  int height = IMAGE_HEIGHT;
  double aspect_ratio = (double)width / height;

  // Create scene
  scene world;
  scene_init(&world);

  // Add lights to the scene
  light main_light =
      light_create(vec3_create(-5, 5, -5),     // Position (up and to the left)
                   vec3_create(1.0, 1.0, 1.0), // White light
                   1.0                         // Full intensity
      );
  scene_add_light(&world, main_light);

  // Optional: Add a second light for more interesting lighting
  light fill_light =
      light_create(vec3_create(5, 3, -3),      // Position (right side)
                   vec3_create(0.8, 0.8, 1.0), // Slightly blue tint
                   0.5                         // Half intensity
      );
  scene_add_light(&world, fill_light);

  // Add spheres with different materials
  // Large red shiny sphere in center
  sphere sph1 = {.center = vec3_create(0, 0, 0),
                 .radius = 1.0,
                 .mat = material_shiny(vec3_create(1.0, 0.2, 0.2))};
  scene_add_sphere(&world, sph1);

  // Green matte sphere on the left
  sphere sph2 = {.center = vec3_create(-2.5, 0, -1),
                 .radius = 0.8,
                 .mat = material_matte(vec3_create(0.2, 1.0, 0.2))};
  scene_add_sphere(&world, sph2);

  // Blue metallic sphere on the right
  sphere sph3 = {.center = vec3_create(2.5, 0, 1),
                 .radius = 0.8,
                 .mat = material_metal(vec3_create(0.2, 0.4, 1.0))};
  scene_add_sphere(&world, sph3);

  // Small yellow shiny sphere in front
  sphere sph4 = {.center = vec3_create(0, -1.5, -2),
                 .radius = 0.5,
                 .mat = material_shiny(vec3_create(1.0, 1.0, 0.2))};
  scene_add_sphere(&world, sph4);

  // Ground (large matte gray sphere)
  sphere ground = {.center = vec3_create(0, -101, 0),
                   .radius = 100,
                   .mat = material_matte(vec3_create(0.5, 0.5, 0.5))};
  scene_add_sphere(&world, ground);

  // Camera position
  point3 camera_pos = vec3_create(0, 0, -5);

  // Allocate pixel buffer
  color3 *pixels = (color3 *)malloc(width * height * sizeof(color3));
  if (!pixels) {
    fprintf(stderr, "Error: Could not allocate memory\n");
    return 1;
  }

  // Render each pixel
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      // Calculate ray direction
      double x = (2.0 * (i + 0.5) / width - 1.0) * aspect_ratio *
                 tan(FOV * M_PI / 360.0);
      double y = (1.0 - 2.0 * (j + 0.5) / height) * tan(FOV * M_PI / 360.0);

      vec3 ray_dir = vec3_create(x, y, 1.0);
      ray_dir = vec3_normalize(ray_dir);

      ray r = ray_create(camera_pos, vec3_add(camera_pos, ray_dir));

      // Check for intersections
      double t;
      sphere *hit_sphere = NULL;

      if (scene_intersect(&world, &r, &t, &hit_sphere)) {
        // Hit something! Calculate lighting
        point3 hit_point = ray_at(r, t);
        vec3 normal = sphere_normal(hit_sphere, hit_point);
        vec3 view_dir = vec3_mul(ray_dir, -1.0); // From hit point to camera

        // Calculate Phong lighting
        color3 pixel_color = calculate_lighting(hit_point, normal, view_dir,
                                                &hit_sphere->mat, &world);

        pixels[j * width + i] = pixel_color;
      } else {
        // No hit - background gradient
        double t_bg = (double)j / (height - 1);
        pixels[j * width + i] = get_background_color(&world, t_bg);
      }
    }

    // Progress indicator
    if (j % 50 == 0) {
      printf("Progress: %d%%\r", (int)(100.0 * j / height));
      fflush(stdout);
    }
  }
  printf("Progress: 100%%\n");

  // Write image
  write_ppm("output/lit_scene.ppm", pixels, width, height);

  free(pixels);
  printf("Done! Rendered %d spheres with %d lights\n", world.sphere_count,
         world.light_count);
  return 0;
}