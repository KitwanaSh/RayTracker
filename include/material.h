#ifndef MATERIAL_H
#define MATERIAL_H

#include "types.h"

// Material properties
typedef struct {
  color3 diffuse;   // Base color
  color3 specular;  // Specular highlight color
  double shininess; // Specular exponent (higher = sharper highlight)
  double ambient;   // Ambient reflection coefficient
} material;

// Create a material
material material_create(color3 diffuse, color3 specular, double shininess,
                         double ambient);

// Preset materials
material material_matte(color3 color); // Matte/diffuse surface
material material_shiny(color3 color); // Shiny plastic-like surface
material material_metal(color3 color); // Metallic surface

#endif // MATERIAL_H