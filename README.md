*This project has been created as part of the 42 curriculum by otlacerd, gustoliv.*

# cub3D

## Description
cub3D is a graphical project that recreates a simple 3D environment using ray-casting principles.  
The goal is to render a first-person view of a maze using the MiniLibX library, including textured walls, floor and ceiling colors, and basic player movement inside a map defined in a `.cub` file.

The player can move and rotate inside the maze while the program renders a 3D projection of the environment in real time.

## Features
- Ray-casting 3D rendering
- Wall textures depending on orientation (N/S/E/W)
- Configurable floor and ceiling colors
- First-person movement (W, A, S, D)
- Camera rotation (left/right arrows)
- Clean exit (ESC or window close button)
- `.cub` map file parsing with validation

## Instructions

### Requirements
- Linux or macOS environment
- MiniLibX library installed
- GCC compiler
- Make

### Compilation
```bash
make