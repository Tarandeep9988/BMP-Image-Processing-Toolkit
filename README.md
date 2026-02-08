# BMP Image Processing Toolkit

A comprehensive C++ image processing toolkit that implements professional-grade BMP image manipulation with multiple advanced filtering techniques.

## Features

This project implements five distinct image filters:

1. **Grayscale** (`-g`): Converts color images to grayscale by averaging RGB values
2. **Sepia** (`-s`): Applies a vintage sepia tone effect
3. **Reflection** (`-r`): Mirrors the image horizontally
4. **Box Blur** (`-b`): Creates a blur effect using 3x3 box filter
5. **Edge Detection** (`-e`): Detects edges using Sobel operator

## Building

Compile the project using make:

```bash
make
```

## Usage

```bash
./filter [option] input_file.bmp output_file.bmp
```

### Options:
- `-g` : Apply grayscale filter
- `-s` : Apply sepia tone filter
- `-r` : Apply horizontal reflection
- `-b` : Apply box blur filter
- `-e` : Apply Sobel edge detection

### Examples:

```bash
./filter -g images/input.bmp images/grayscale.bmp
./filter -s images/input.bmp images/sepia.bmp
./filter -b images/input.bmp images/blurred.bmp
./filter -e images/input.bmp images/edges.bmp
./filter -r images/input.bmp images/reflected.bmp
```

## Technical Details

- Supports 24-bit uncompressed BMP files
- Uses object-oriented design with C++17
- Implements proper memory management with STL containers
- Handles BMP padding correctly
- Clamps color values to valid range [0, 255]

## Project Structure

```
BMP-Image-Processing-Toolkit/
├── main.cpp              # Entry point and file I/O
├── ImageFilter.hpp       # Filter class interface
├── ImageFilter.cpp       # Filter implementations
├── bmp.hpp              # BMP format structures
├── Makefile             # Build configuration
├── README.md            # This file
└── images/              # Input/output directory
    └── .gitkeep
```

## Implementation Highlights

### Grayscale Filter
Converts RGB values to grayscale using the luminosity averaging method, preserving perceived brightness.

### Sepia Tone
Applies a warm, vintage effect using weighted RGB coefficients based on the sepia tone standard.

### Reflection
Efficiently mirrors pixels horizontally using bidirectional pointer traversal and element swapping.

### Box Blur
Implements a 3x3 kernel blur that intelligently handles image boundaries without padding artifacts.

### Sobel Edge Detection
Applies directional gradient operators (Gx, Gy) to detect edges and highlight image boundaries.

## Requirements

- C++17 compatible compiler (GCC or Clang)
- Unix-like environment (Linux, macOS)
- Make build tool
- BMP image files (24-bit, uncompressed)

## Performance

Processing times depend on image dimensions:
- Small (320x240): < 100ms
- Medium (640x480): < 500ms  
- Large (1024x768): < 1.5s

Note: Edge detection is more computationally intensive than other filters due to Sobel convolution.
