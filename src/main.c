#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "ray.h"
#include "scene.h"
#include "sphere.h"
#include "types.h"
#include "vector.h"

// Define M_PI if not available
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Image parameters
#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT 600

// Camera parameters
#define FOV 60.0

// Function to get background color (gradient)
color3 get_background_color(const scene *s, double t) {
  // Linear interpolation between top and bottom colors
  color3 color;
  color.x = (1.0 - t) * s->background_top.x + t * s->background_bottom.x;
  color.y = (1.0 - t) * s->background_top.y + t * s->background_bottom.y;
  color.z = (1.0 - t) * s->background_top.z + t * s->background_bottom.z;
  return color;
}

int main(void) {
  printf("SimpleRayTracer - Milestone 3\n");
  printf("Rendering scene with multiple spheres...\n");

  int width = IMAGE_WIDTH;
  int height = IMAGE_HEIGHT;
  double aspect_ratio = (double)width / height;

  // Create scene
  scene world;
  scene_init(&world);

  // Add spheres to the scene
  // Large sphere in center
  sphere sph1 = {
      .center = vec3_create(0, 0, 0),
      .radius = 1.0,
      .color = vec3_create(1.0, 0.3, 0.3) // Red
  };
  scene_add_sphere(&world, sph1);

  // Small sphere on the left
  sphere sph2 = {
      .center = vec3_create(-2.5, 0, -1),
      .radius = 0.8,
      .color = vec3_create(0.3, 1.0, 0.3) // Green
  };
  scene_add_sphere(&world, sph2);

  // Small sphere on the right
  sphere sph3 = {
      .center = vec3_create(2.5, 0, 1),
      .radius = 0.8,
      .color = vec3_create(0.3, 0.3, 1.0) // Blue
  };
  scene_add_sphere(&world, sph3);

  // Tiny sphere in front
  sphere sph4 = {
      .center = vec3_create(0, -1.5, -2),
      .radius = 0.5,
      .color = vec3_create(1.0, 1.0, 0.3) // Yellow
  };
  scene_add_sphere(&world, sph4);

  // Ground sphere (very large, positioned below)
  sphere ground = {
      .center = vec3_create(0, -101, 0),
      .radius = 100,
      .color = vec3_create(0.5, 0.5, 0.5) // Gray
  };
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
      // Calculate ray direction for this pixel
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
        // Hit something! Get the hit point and normal
        point3 hit_point = ray_at(r, t);
        vec3 normal = sphere_normal(hit_sphere, hit_point);

        // Color based on surface normal (makes it look 3D)
        // Map normal from [-1,1] to [0,1]
        color3 normal_color =
            vec3_create((normal.x + 1.0) * 0.5, (normal.y + 1.0) * 0.5,
                        (normal.z + 1.0) * 0.5);

        pixels[j * width + i] = normal_color;
      } else {
        // No hit - render background gradient
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
  write_ppm("output/multiple_spheres.ppm", pixels, width, height);

  free(pixels);
  printf("Done! Rendered %d spheres\n", world.sphere_count);
  return 0;
}