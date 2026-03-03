# Performance Optimization Guide

## Profiling the Application

### Using gprof

1. Compile with profiling enabled:
```bash
g++ -std=c++17 -pg -o filter main.cpp ImageFilter.cpp
```

2. Run the program:
```bash
./filter -b large_image.bmp output.bmp
```

3. View profiling results:
```bash
gprof ./filter gmon.out | head -30
```

## Optimization Opportunities

### Current Performance Characteristics

- **Grayscale**: O(n) single pass - optimal
- **Sepia**: O(n) single pass - optimal  
- **Reflection**: O(n) with swap operations - optimal
- **Blur**: O(9n) with 3x3 kernel - room for optimization
- **Edge Detection**: O(9n) with Sobel operator - room for optimization

### SIMD Optimization

The blur and edge detection filters can benefit from SIMD:

```cpp
// Potential SSE optimization for 3x3 blur
#include <immintrin.h>

// Process 4 pixels at once with SSE2
__m128i neighbor_sum = _mm_setzero_si128();
```

### Memory Layout Optimization

Current layout uses `std::vector<std::vector<>>`:
- Pros: Flexible, safe, proper cleanup
- Cons: Cache misses due to non-contiguous memory

Optimization option:
```cpp
// Use single large buffer with manual indexing
std::vector<RGBPixel> pixelBuffer(height * width);
// Access: pixelBuffer[row * width + col]
```

### Parallelization with OpenMP

```cpp
#pragma omp parallel for collapse(2)
for (int row = 0; row < imageHeight; row++) {
    for (int col = 0; col < imageWidth; col++) {
        // Process pixel
    }
}
```

Expected speedup: 4-8x on quad-core systems.

### GPU Acceleration

For large images (4K and above), consider:
- CUDA for NVIDIA GPUs
- OpenCL for cross-platform GPU support
- HIP for AMD GPUs

Expected speedup: 10-50x depending on GPU.

## Benchmarking Results

Typical performance on modern CPU:
- 640x480 image processing: ~50-100ms per filter
- 1920x1080 image processing: ~300-600ms per filter
- Edge detection is ~2x slower than blur due to Sobel computation

## Memory Usage

- 640x480: ~900KB (3 bytes × 640 × 480)
- 1920x1080: ~6.2MB
- 4K (3840x2160): ~24.8MB

Temporary buffers during processing double the memory requirement.

## Recommendations

1. **For images < 2MP**: Current implementation is fine
2. **For images 2-12MP**: Consider SIMD optimization
3. **For images > 12MP**: Implement tiling or GPU acceleration
4. **For real-time processing**: Use OpenMP + SIMD

## Testing Performance

```bash
# Time a single filter operation
time ./filter -e large_image.bmp output.bmp
```

## Future Improvements

- [ ] Implement separated convolution for blur
- [ ] Add SIMD optimization pass
- [ ] OpenMP parallelization
- [ ] GPU compute shader implementation
- [ ] Streaming processing for memory-limited systems
