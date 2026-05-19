#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#include "image.h"
#include "light.h"
#include "material.h"
#include "ray.h"
#include "renderer.h"
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

int main(void) {
  printf("SimpleRayTracer - Milestone 5: Reflections\n");
  printf("Rendering scene with mirror reflections...\n");

  int width = IMAGE_WIDTH;
  int height = IMAGE_HEIGHT;
  double aspect_ratio = (double)width / height;

  // Create scene
  scene world;
  scene_init(&world);

  // Add lights
  light main_light =
      light_create(vec3_create(-5, 5, -5), vec3_create(1.0, 1.0, 1.0), 1.0);
  scene_add_light(&world, main_light);

  light fill_light =
      light_create(vec3_create(5, 3, -3), vec3_create(0.8, 0.8, 1.0), 0.5);
  scene_add_light(&world, fill_light);

  // Add spheres with different materials

  // Center: Chrome/mirror sphere (highly reflective)
  sphere mirror_sphere = {
      .center = vec3_create(0, 0, 0),
      .radius = 1.0,
      .mat = material_mirror(vec3_create(0.95, 0.95, 1.0)) // Slightly blue tint
  };
  scene_add_sphere(&world, mirror_sphere);

  // Left: Matte green sphere (to be reflected)
  sphere left_sphere = {.center = vec3_create(-2.5, 0, -1),
                        .radius = 0.8,
                        .mat = material_matte(vec3_create(0.2, 1.0, 0.2))};
  scene_add_sphere(&world, left_sphere);

  // Right: Shiny blue sphere (partially reflective)
  sphere right_sphere = {.center = vec3_create(2.5, 0, 1),
                         .radius = 0.8,
                         .mat = material_shiny(vec3_create(0.2, 0.4, 1.0))};
  scene_add_sphere(&world, right_sphere);

  // Front: Small red metallic sphere
  sphere front_sphere = {.center = vec3_create(0, -1.3, -2),
                         .radius = 0.5,
                         .mat = material_metal(vec3_create(1.0, 0.2, 0.2))};
  scene_add_sphere(&world, front_sphere);

  // Back: Small yellow shiny sphere
  sphere back_sphere = {.center = vec3_create(1.5, 1.0, 2),
                        .radius = 0.6,
                        .mat = material_shiny(vec3_create(1.0, 1.0, 0.2))};
  scene_add_sphere(&world, back_sphere);

  // Ground
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

      // Trace ray with reflections
      color3 pixel_color = trace_ray(&world, &r, 0);
      pixels[j * width + i] = pixel_color;
    }

    // Progress indicator
    if (j % 50 == 0) {
      printf("Progress: %d%%\r", (int)(100.0 * j / height));
      fflush(stdout);
    }
  }
  printf("Progress: 100%%\n");

  // Write image
  write_ppm("output/reflections.ppm", pixels, width, height);

  free(pixels);
  printf("Done! Rendered %d spheres with reflections (depth=%d)\n",
         world.sphere_count, MAX_RECURSION_DEPTH);
  return 0;
}