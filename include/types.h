#ifndef TYPES_H
#define TYPES_H

// 3D Vector structure (also used for points and colors)
typedef struct {
  double x;
  double y;
  double z;
} vec3;

// Type aliases for clarity
typedef vec3 point3;
typedef vec3 color3;

#endif // TYPES_H