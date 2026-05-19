#include "light.h"

light light_create(point3 position, color3 color, double intensity) {
  light l;
  l.position = position;
  l.color = color;
  l.intensity = intensity;
  return l;
}