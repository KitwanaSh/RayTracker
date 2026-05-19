#include "material.h"
#include "vector.h"

material material_create(color3 diffuse, color3 specular, double shininess,
                         double ambient, double reflectivity) {
  material mat;
  mat.diffuse = diffuse;
  mat.specular = specular;
  mat.shininess = shininess;
  mat.ambient = ambient;
  mat.reflectivity = reflectivity;
  return mat;
}

material material_matte(color3 color) {
  return material_create(color, vec3_create(0.1, 0.1, 0.1), 10.0, 0.1,
                         0.0 // No reflectivity
  );
}

material material_shiny(color3 color) {
  return material_create(color, vec3_create(1.0, 1.0, 1.0), 100.0, 0.1,
                         0.3 // Some reflectivity
  );
}

material material_metal(color3 color) {
  return material_create(color, color, 200.0, 0.05,
                         0.6 // High reflectivity
  );
}

material material_mirror(color3 tint) {
  return material_create(vec3_create(0.1, 0.1, 0.1), // Almost no diffuse
                         tint, 1000.0, 0.0,
                         0.95 // Nearly perfect reflection
  );
}

material material_chrome(color3 color) {
  return material_create(vec3_mul(color, 0.3), // Reduced diffuse
                         vec3_create(1.0, 1.0, 1.0), 300.0, 0.05,
                         0.8 // Very high reflectivity
  );
}