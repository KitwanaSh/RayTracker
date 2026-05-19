# SimpleRayTracer

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![GCC](https://img.shields.io/badge/GCC-0078D4?style=for-the-badge)
![Make](https://img.shields.io/badge/Make-427819?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

A lightweight, CPU-based ray tracer written in C from scratch. This project implements core ray tracing algorithms including Phong lighting, shadows, and recursive reflections to render photorealistic 3D scenes.

## Features

- **Vector Mathematics Library** - Custom 3D vector operations
- **Ray-Sphere Intersection** - Analytical geometry calculations
- **Phong Lighting Model** - Ambient, diffuse, and specular components
- **Hard Shadows** - Shadow ray casting with occlusion testing
- **Recursive Reflections** - Mirror-like surfaces with depth-limited recursion
- **Material System** - Matte, shiny, metallic, chrome, and mirror materials
- **PPM Image Output** - Simple, portable image format
- **Scene Management** - Support for multiple objects and light sources

## Quick Start

### Prerequisites

- GCC compiler
- Make
- ImageMagick (optional, for PPM to PNG conversion)

### Build

```bash
make
```

### Run
```bash
make run
```
### Output
Rendered images are saved to the output/ directory in PPM format.

```bash
# Convert to PNG (requires ImageMagick)
convert output/reflections.ppm output/reflections.png
```

### Clean
```bash
make clean
```

## Project Structure

```
SimpleRayTracer/
├── src/
│   ├── main.c           # Main entry point and scene setup
│   ├── vector.c         # Vector mathematics operations
│   ├── sphere.c         # Sphere intersection tests
│   ├── lighting.c       # Phong lighting calculations
│   ├── shadow.c         # Shadow ray casting
│   ├── reflection.c     # Reflection calculations
│   └── material.c       # Material properties and operations
├── include/
│   ├── vector.h
│   ├── sphere.h
│   ├── lighting.h
│   ├── shadow.h
│   ├── reflection.h
│   └── material.h
├── output/
│   └── reflections.ppm  # Rendered images (generated)
├── makefile             # Build configuration
└── README.md
```

## Core Components
**Vector Math** (vector.c/h)
Implements 3D vector operations: addition, subtraction, dot product, cross product, normalization.

**Ray Tracing** (ray.c/h)
Defines ray structure and operations for casting rays through the scene.

**Geometry** (sphere.c/h)
Ray-sphere intersection testing using analytical methods.

**Materials** (material.c/h)
Physical surface properties: diffuse color, specular highlights, shininess, reflectivity.

**Lighting** (lighting.c/h)
Phong illumination model with support for multiple point light sources.

**Renderer** (renderer.c/h)
Recursive ray tracing engine with configurable maximum depth.

**Scene Management** (scene.c/h)
Container for objects, lights, and global scene parameters.

## Technical Details
### Ray-Sphere Intersection
Uses the geometric solution to the ray-sphere intersection equation:

```text
(P - C) · (P - C) = r²
```

Where P is a point on the ray, C is the sphere center, and r is the radius.

### Phong Lighting Model

```text
I = Ia*Ka + Id*Kd*(N·L) + Is*Ks*(R·V)^n
```

- **Ia** - Ambient light intensity
- **Id** - Diffuse light intensity
- **Is** - Specular light intensity
- **Ka**, **Kd**, **Ks** - Material coefficients
- **N** - Surface normal
- **L** - Light direction
- **R** - Reflection vector
- **V** - View direction
- **n** - Shininess exponent

### Recursive Reflections
Traces reflection rays up to a maximum depth (default: 5) to simulate mirror-like surfaces.

### Performance
- **Resolution**: 800x600 (configurable)
- **Render Time**: ~2-5 seconds for typical scenes (single-threaded)
- **Memory**: Minimal allocation (pixel buffer only)

## Extending the Project
### Adding New Geometry
- Create new geometry files (e.g., plane.c/h, triangle.c/h)
- Implement intersection function
- Update scene.c to support new object types

### Adding New Features
- Anti-aliasing (supersampling)
- Soft shadows (area lights)
- Refraction and transparency
- Texture mapping
- Procedural patterns
- Parallelization (OpenMP/pthreads)
- Bounding Volume Hierarchies (BVH) for performance
- Triangle mesh support
- OBJ file loading

## Sample Renders
### Milestone 2: First Sphere

- Single sphere with normal-based coloring

### Milestone 3: Multiple Spheres

- Scene with 5 spheres and depth ordering

### Milestone 4: Phong Lighting

- Realistic shading with specular highlights and shadows

### Milestone 5: Reflections

- Chrome sphere reflecting the entire scene

## Contributing
Contributions are welcome! Please follow these guidelines:

- Fork the repository
- Create a feature branch (git checkout -b feature/new-feature)
- Follow the existing code style
- Add comments for complex algorithms
- Test thoroughly
- Submit a pull request

### Code Style
- Use descriptive variable names
- Keep functions under 50 lines when possible
- Comment non-obvious algorithms
- Use consistent indentation (4 spaces)
- Separate concerns (one responsibility per function)

## Acknowledgments
Inspired by "Ray Tracing in One Weekend" by Peter Shirley and Scratchapixel tutorials.

## Author
Created as a side project to learn about ray tracing and computer graphics.