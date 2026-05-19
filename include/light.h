#ifndef LIGHT_H
#define LIGHT_H

#include "types.h"

// Point light source
typedef struct {
  point3 position;
  color3 color;
  double intensity;
} light;

// Create a light
light light_create(point3 position, color3 color, double intensity);

#endif // LIGHT_H