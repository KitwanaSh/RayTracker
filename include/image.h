#ifndef IMAGE_H
#define IMAGE_H

#include "types.h"

// Write a PPM image file
// pixels: array of colors (row by row, left to right)
// width, height: image dimensions
// filename: output file path
int write_ppm(const char *filename, color3 *pixels, int width, int height);

// Helper: clamp a value between min and max
double clamp(double x, double min, double max);

// Helper: convert color (0.0-1.0) to RGB (0-255)
int color_to_rgb(double c);

#endif // IMAGE_H