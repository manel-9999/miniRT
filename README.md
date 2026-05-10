*This project has been created as part of the 42 curriculum by mcarvalh, edugonza.*

# miniRT — A Ray Tracer in C

## Description

miniRT is a ray tracer written in C as part of the 42 curriculum. The goal is to render 3D scenes defined in `.rt` text files by simulating the path of light rays from a virtual camera through each pixel of a screen and into the scene.

The renderer supports three geometric primitives (sphere, plane, cylinder), a physically-based lighting model (ambient, diffuse, and specular), hard shadows, multiple light sources, and an interactive camera that re-renders the scene in real time when moved with the keyboard.

The project is built entirely from scratch: no rendering library is used for math or geometry. Only [minilibx](https://github.com/42Paris/minilibx-linux) is used to open a window and write pixels to it.

---

## Features

- **Three geometric primitives**: sphere, plane, and cylinder (with caps)
- **Blinn-Phong lighting model**: ambient, diffuse, and specular components
- **Hard shadows**: shadow rays cast toward each light source, tested against all objects
- **Multiple light sources**: dynamic array, each contributing diffuse and specular light independently
- **Interactive camera**: real-time movement along X, Y, and Z axes, screen recalculated per frame
- **Robust scene parser**: validates all numeric types, colors, vectors (normalized), object counts, and formats
- **Custom C library** (`Libft_power`): includes `get_next_line`, `ft_printf`, and standard utilities — no external dependencies beyond X11

---

## Instructions

### Requirements

- Linux with X11 (`libx11-dev`, `libxext-dev`)
- GCC or Clang
- `make`

### Compilation

```bash
git clone <repo-url> miniRT
cd miniRT
make
```

This builds `Libft_power/libft.a`, `minilibx-linux/libmlx.a`, and the final `miniRT` executable.

```bash
make clean    # Remove object files
make fclean   # Remove all binaries (including .a files and miniRT)
make re       # Full rebuild
```

### Running

```bash
./miniRT path/to/scene.rt
```

The window opens at 920×920 pixels with a 900×900 rendered image centered inside.

### Controls

| Key | Action |
|-----|--------|
| `↑` | Move camera forward |
| `↓` | Move camera backward |
| `→` | Move camera right |
| `←` | Move camera left |
| `h` | Move camera up |
| `l` | Move camera down |
| `ESC` | Exit |

Camera movement is proportional (10% of the camera's current distance from the world origin). The scene re-renders immediately after each movement.

---

## Project Structure

```
miniRT/
├── main.c                      # Entry point and rendering loop
├── main.h                      # All data structures, defines, and prototypes
├── utils.c                     # Keyboard input and camera movement
├── Makefile
├── Initialization/             # Scene file parsing and validation
│   ├── parser.c
│   ├── parse_alc.c             # Ambient, camera, light parsing
│   ├── parse_objects.c         # Sphere, plane, cylinder parsing
│   ├── parse_utils.c           # RGB conversion, vector/point helpers
│   ├── parse_counters.c        # Array counting utilities
│   ├── data_checker.c          # int, float, color, point validation
│   ├── data_checker_vectors.c  # Normalized vector validation
│   └── initializers.c          # MLX init, file validation
├── Rays/                       # Ray generation and intersection math
│   ├── ray_math.c              # Sphere and plane intersection
│   ├── ray_math_cylinder.c     # Cylinder intersection and caps
│   └── apply_ray.c             # Per-pixel dispatcher and lighting call
├── Light/                      # Lighting and shadow logic
│   ├── lights.c                # Ambient + punctual light accumulation
│   ├── lights_utils.c          # Specular, half-vector, color unpack
│   └── shadows.c               # Shadow ray casting
├── Utils/                      # Linear algebra and memory
│   ├── linear_math.c           # Vector add, subtract, cross product
│   ├── linear_math_2.c         # Dot product, magnitude, normalize
│   ├── memory_handler.c        # Point and vector allocation
│   ├── free_memory.c           # Full scene cleanup
│   └── utils.c
├── Libft_power/                # Custom C standard library
│   ├── get_next_line/
│   ├── ft_printf/
│   └── [string, list, math, memory]
├── minilibx-linux/             # Graphics library (X11 wrapper)
└── tests/                      # Sample .rt scene files
    ├── 0_fail_maps/
    ├── 1_basic_tests/
    ├── 2_functionalities/
    └── 3_other_maps/
```

---