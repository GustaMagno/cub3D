*This project has been created as part of the 42 curriculum by otlacerd, gustoliv.*

# cub3D 🎮

## Description
cub3D is a graphical 3D game engine project inspired by the world-famous 1992 classic *Wolfenstein 3D*. The goal of this project is to explore the concepts of Ray-casting to render a dynamic first-person perspective environment from a strictly 2D grid map array.

Developed in C, the engine utilizes the MiniLibX graphical library to open a window, manage pixel buffers, handle real-time keyboard inputs, and render textures with perspective correction based on the player's position and viewing angle.

## Features
- **Real-time Ray-casting Engine:** Employs the DDA (Digital Differential Analysis) algorithm for fast wall collision calculation.
- **Directional Wall Textures:** Dynamically applies distinct textures to walls depending on the compass direction they face (North, South, East, West).
- **Customizable Environment:** Parses floor and ceiling colors from RGB configuration values.
- **Smooth First-Person Controls:** Responsive player movement (W, A, S, D) and camera rotation (Left/Right arrow keys).
- **Strict Map Parsing:** Complete validation of `.cub` scene files, checking for valid borders, player spawn points, correct character types, and missing texture paths.
- **Memory Safety:** Full memory management ensuring no memory leaks occur upon a clean exit (via `ESC` key or window close button).

## Technical Choices
- **DDA Algorithm:** Instead of advancing rays pixel-by-pixel (which degrades performance and risks wall-clipping glitches), we implemented DDA. It calculates the exact distance to the next grid intersection (`delta_dist`), allowing the ray to "jump" safely and efficiently from grid line to grid line.
- **Perpendicular Distance Projection:** To eliminate the "fish-eye" lens distortion effect where walls warp at the edge of the screen, the engine computes the perpendicular distance from the player's camera plane to the wall instead of using the raw Euclidean distance.

## Instructions

### Requirements
- **OS:** Linux (Ubuntu/Debian recommended) or macOS
- **Compiler:** GCC or Clang

### Compilation & Execution
To compile the project, clear object files, or run the game, use the following terminal commands:

```bash
make mlx
```
```bash
make
```
```bash
./cub3D maps/valid_map.cub
```

## Resources

### Documentation & References
- **Lode's Raycasting Tutorial:** The foundational math guide used to understand vector-based raycasting, DDA loops, and vertical texture mapping slices.
- **Wolfenstein 3D Specs:** Historical references regarding early 90s grid constraints and column-by-column rendering logic.
- **MiniLibX Documentation:** 42-specific manual sheets for window initialization, image indexing, and hook loops.

### Use of AI
Artificial Intelligence (Large Language Models) was actively utilized as a collaborative peer-programming tool during this project's development. Here is how it was applied:
1. **Mathematical Simplification & Geometry:** AI helped reverse-engineer and break down the vector normalization behind `delta_dist_x = fabs(1.0 / rayDirX)` using similar triangle geometry theorems. It was also used to visually map how `delta_dist` works as a dynamic step scale for DDA.
2. **Algorithm Architecture:** Collaborated with AI to conceptually contrast native pixel-by-pixel ray increments versus DDA grid boundary jumps, validating the core rendering performance choices.
