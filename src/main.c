#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#include "image.h"
#include "ray.h"
#include "sphere.h"
#include "types.h"
#include "vector.h"


// Define M_PI if not available
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Camera parameters
#define CAM_POS vec3_create(0, 0, -5) // Camera at z = -5
#define LOOK_AT vec3_create(0, 0, 0)  // Looking at origin
#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT 600
#define FOV 60.0 // Field of view in degrees

// Scene
#define SPHERE_CENTER vec3_create(0, 0, 0)
#define SPHERE_RADIUS 1.0
#define SPHERE_COLOR vec3_create(1.0, 0.2, 0.2) // Red sphere

int main(void) {
  printf("SimpleRayTracer - Milestone 2\n");
  printf("Rendering sphere...\n");

  int width = IMAGE_WIDTH;
  int height = IMAGE_HEIGHT;

  // Allocate pixel buffer
  color3 *pixels = (color3 *)malloc(width * height * sizeof(color3));
  if (!pixels) {
    fprintf(stderr, "Error: Could not allocate memory\n");
    return 1;
  }

  // Create camera ray for each pixel
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      // Normalize pixel coordinates to [-1, 1] range
      // Adjust for aspect ratio
      double aspect_ratio = (double)width / height;
      double x = (2.0 * (i + 0.5) / width - 1.0) * aspect_ratio *
                 tan(FOV * M_PI / 360.0);
      double y = (1.0 - 2.0 * (j + 0.5) / height) * tan(FOV * M_PI / 360.0);

      // Ray origin (camera position)
      point3 ray_origin = CAM_POS;

      // Ray direction (from camera through pixel)
      vec3 ray_dir = vec3_create(x, y, 1.0);
      ray_dir = vec3_normalize(ray_dir);

      ray r = ray_create(ray_origin, vec3_add(ray_origin, ray_dir));

      // Define the sphere
      sphere sph = {.center = SPHERE_CENTER,
                    .radius = SPHERE_RADIUS,
                    .color = SPHERE_COLOR};

      // Check intersection
      double t;
      if (sphere_intersect(&r, &sph, &t)) {
        // Intersection found - get the hit point
        point3 hit_point = ray_at(r, t);

        // Get normal at hit point
        vec3 normal = sphere_normal(&sph, hit_point);

        // Simple shading: color based on normal
        // Map normal from [-1,1] to [0,1] for color
        color3 color =
            vec3_create((normal.x + 1.0) * 0.5, (normal.y + 1.0) * 0.5,
                        (normal.z + 1.0) * 0.5);

        pixels[j * width + i] = color;
      } else {
        // No intersection - background gradient
        double t_bg = (double)j / (height - 1);
        color3 bg = vec3_create(0.5 * (1.0 - t_bg) + 0.1 * t_bg,
                                0.7 * (1.0 - t_bg) + 0.1 * t_bg,
                                1.0 * (1.0 - t_bg) + 0.3 * t_bg);
        pixels[j * width + i] = bg;
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
  write_ppm("output/sphere_normals.ppm", pixels, width, height);

  free(pixels);
  printf("Done!\n");
  return 0;
}