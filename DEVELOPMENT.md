# BMP Image Processing Toolkit - Development Guide

## Building the Project

### Prerequisites
- GCC 7.0+ or Clang 5.0+
- GNU Make 4.0+
- C++17 support

### Quick Build
```bash
cd BMP-Image-Processing-Toolkit
make
```

### Build Output
The compilation produces an executable named `filter`.

## Code Architecture

### Main Components

#### bmp.hpp
Contains BMP format structures with packed attribute for binary compatibility:
- `BitmapFileHeader`: File-level metadata
- `BitmapInfoHeader`: Image format information  
- `RGBPixel`: Individual pixel representation

#### ImageFilter Class
Core image processing engine with methods:
- `applyGrayscale()`: Luminosity-based conversion
- `applySepiaFilter()`: Sepia tone transformation
- `applyHorizontalReflection()`: Pixel mirroring
- `applyBoxBlur()`: Neighborhood averaging blur
- `applySobelEdgeDetection()`: Edge detection via gradients

#### main.cpp
Command-line interface and file I/O:
- Argument parsing and validation
- BMP file reading with padding calculation
- Filter selection and processing
- Output file writing

## Filter Algorithms

### Grayscale
```
Gray = (R + G + B) / 3
```

### Sepia
```
R' = 0.393*R + 0.769*G + 0.189*B
G' = 0.349*R + 0.686*G + 0.168*B
B' = 0.272*R + 0.534*G + 0.131*B
```

### Box Blur
3x3 neighborhood averaging with proper boundary handling.

### Sobel Edge Detection
```
Gx = [-1 0 1; -2 0 2; -1 0 1]
Gy = [-1 -2 -1; 0 0 0; 1 2 1]
Edge = sqrt(Gx² + Gy²)
```

## Testing

Test images should be:
- 24-bit BMP format
- Uncompressed
- Valid BMP headers

Example test run:
```bash
./filter -g sample.bmp output.bmp
./filter -e sample.bmp edges.bmp
./filter -b sample.bmp blurred.bmp
```

## Performance Considerations

- **Memory**: Linear with image dimensions (3 bytes per pixel)
- **Time Complexity**: O(width × height) for all filters
- **Blur/Edge**: Adds 9x neighboring pixel sampling
- **Threading**: Single-threaded (opportunity for parallelization)

## Future Enhancements

1. Multi-threaded processing
2. SIMD optimization with SSE/AVX
3. Real-time preview mode
4. GPU acceleration with CUDA
5. More sophisticated blur algorithms (Gaussian, Bilateral)
6. Additional color spaces (HSV, LAB)

## Debugging Tips

Enable verbose output by modifying main.cpp logging.

Use `valgrind` for memory leak detection:
```bash
valgrind --leak-check=full ./filter -g test.bmp out.bmp
```

Profile with `gprof`:
```bash
g++ -pg ... && ./filter ... && gprof ./filter gmon.out
```

## Common Issues

### Invalid file format error
- Check that image is 24-bit uncompressed BMP
- Use `file` command to verify format

### Image corruption
- Verify input file is readable
- Check disk space for output
- Ensure proper file permissions

## Style Guidelines

- Use `CamelCase` for class/struct names
- Use `snake_case` for functions and variables
- Keep functions under 50 lines
- Comment complex algorithms
- Use const and references appropriately
