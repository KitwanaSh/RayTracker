#ifndef VECTOR_H
#define VECTOR_H

#include "types.h"

// Vector creation
vec3 vec3_create(double x, double y, double z);

// Vector arithmetic
vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_mul(vec3 v, double t); // Scalar multiplication
vec3 vec3_div(vec3 v, double t); // Scalar division

// Vector operations
double vec3_dot(vec3 a, vec3 b);
vec3 vec3_cross(vec3 a, vec3 b);
double vec3_length(vec3 v);
double vec3_length_squared(vec3 v);
vec3 vec3_normalize(vec3 v);

// Utility
void vec3_print(vec3 v);

#endif // VECTOR_H