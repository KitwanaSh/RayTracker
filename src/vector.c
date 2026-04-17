#include "vector.h"
#include <math.h>
#include <stdio.h>


// Create a vector
vec3 vec3_create(double x, double y, double z) {
  vec3 v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

// Vector addition: a + b
vec3 vec3_add(vec3 a, vec3 b) {
  return vec3_create(a.x + b.x, a.y + b.y, a.z + b.z);
}

// Vector subtraction: a - b
vec3 vec3_sub(vec3 a, vec3 b) {
  return vec3_create(a.x - b.x, a.y - b.y, a.z - b.z);
}

// Scalar multiplication: v * t
vec3 vec3_mul(vec3 v, double t) {
  return vec3_create(v.x * t, v.y * t, v.z * t);
}

// Scalar division: v / t
vec3 vec3_div(vec3 v, double t) { return vec3_mul(v, 1.0 / t); }

// Dot product: a · b
double vec3_dot(vec3 a, vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

// Cross product: a × b
vec3 vec3_cross(vec3 a, vec3 b) {
  return vec3_create(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                     a.x * b.y - a.y * b.x);
}

// Vector length (magnitude)
double vec3_length(vec3 v) { return sqrt(vec3_length_squared(v)); }

// Vector length squared (faster, avoids sqrt)
double vec3_length_squared(vec3 v) { return v.x * v.x + v.y * v.y + v.z * v.z; }

// Normalize vector (make unit length)
vec3 vec3_normalize(vec3 v) {
  double len = vec3_length(v);
  if (len > 0.0) {
    return vec3_div(v, len);
  }
  return v;
}

// Print vector (for debugging)
void vec3_print(vec3 v) { printf("(%.3f, %.3f, %.3f)\n", v.x, v.y, v.z); }