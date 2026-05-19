#include "material.h"
#include "vector.h"

material material_create(color3 diffuse, color3 specular, double shininess,
                         double ambient) {
  material mat;
  mat.diffuse = diffuse;
  mat.specular = specular;
  mat.shininess = shininess;
  mat.ambient = ambient;
  return mat;
}

material material_matte(color3 color) {
  return material_create(color,                      // Diffuse color
                         vec3_create(0.1, 0.1, 0.1), // Low specular
                         10.0,                       // Low shininess
                         0.1                         // Low ambient
  );
}

material material_shiny(color3 color) {
  return material_create(color,                      // Diffuse color
                         vec3_create(1.0, 1.0, 1.0), // White specular
                         100.0,                      // High shininess
                         0.1                         // Low ambient
  );
}

material material_metal(color3 color) {
  return material_create(color, // Diffuse color
                         color, // Colored specular
                         200.0, // Very high shininess
                         0.05   // Very low ambient
  );
}