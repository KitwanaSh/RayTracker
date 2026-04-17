#include "image.h"
#include <stdio.h>


// Clamp value between min and max
double clamp(double x, double min, double max) {
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}

// Convert color component (0.0-1.0) to RGB (0-255)
int color_to_rgb(double c) { return (int)(255.999 * clamp(c, 0.0, 1.0)); }

// Write PPM image file
int write_ppm(const char *filename, color3 *pixels, int width, int height) {
  FILE *file = fopen(filename, "w");
  if (!file) {
    fprintf(stderr, "Error: Could not open file '%s'\n", filename);
    return 0;
  }

  // PPM header
  fprintf(file, "P3\n");
  fprintf(file, "%d %d\n", width, height);
  fprintf(file, "255\n");

  // Write pixel data (top to bottom, left to right)
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      color3 pixel = pixels[j * width + i];

      int r = color_to_rgb(pixel.x);
      int g = color_to_rgb(pixel.y);
      int b = color_to_rgb(pixel.z);

      fprintf(file, "%d %d %d\n", r, g, b);
    }
  }

  fclose(file);
  printf("Image written to '%s'\n", filename);
  return 1;
}