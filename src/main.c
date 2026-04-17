#include "image.h"
#include "types.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>


int main(void) {
  // Image dimensions
  const int width = 800;
  const int height = 600;

  printf("SimpleRayTracer - Milestone 1\n");
  printf("Rendering %dx%d gradient image...\n", width, height);

  // Allocate pixel buffer
  color3 *pixels = (color3 *)malloc(width * height * sizeof(color3));
  if (!pixels) {
    fprintf(stderr, "Error: Could not allocate memory\n");
    return 1;
  }

  // Generate gradient image
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      // Normalize coordinates to 0.0-1.0
      double r = (double)i / (width - 1);
      double g = (double)j / (height - 1);
      double b = 0.25;

      // Store pixel color
      pixels[j * width + i] = vec3_create(r, g, b);
    }

    // Progress indicator
    if (j % 50 == 0) {
      printf("Progress: %d%%\r", (int)(100.0 * j / height));
      fflush(stdout);
    }
  }
  printf("Progress: 100%%\n");

  // Write image file
  write_ppm("output/gradient.ppm", pixels, width, height);

  // Clean up
  free(pixels);

  printf("Done!\n");
  return 0;
}