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

// Ray structure
typedef struct {
    point3 origin;
    vec3 direction;
} ray;

#endif // TYPES_H