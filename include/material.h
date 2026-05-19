#ifndef MATERIAL_H
#define MATERIAL_H

#include "types.h"

// Material properties
typedef struct {
  color3 diffuse;      // Base color
  color3 specular;     // Specular highlight color
  double shininess;    // Specular exponent
  double ambient;      // Ambient reflection coefficient
  double reflectivity; // Mirror reflection (0.0 = none, 1.0 = perfect mirror)
} material;

// Create a material
material material_create(color3 diffuse, color3 specular, double shininess,
                         double ambient, double reflectivity);

// Preset materials
material material_matte(color3 color);
material material_shiny(color3 color);
material material_metal(color3 color);
material material_mirror(color3 tint);  // NEW: Perfect mirror
material material_chrome(color3 color); // NEW: Chrome-like

#endif // MATERIAL_H