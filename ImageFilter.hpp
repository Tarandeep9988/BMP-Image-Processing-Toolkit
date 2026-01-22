#ifndef IMAGE_FILTER_HPP
#define IMAGE_FILTER_HPP

#include "bmp.hpp"
#include <vector>
#include <memory>

class ImageFilter {
private:
    int imageHeight;
    int imageWidth;
    std::vector<std::vector<RGBPixel>> pixelData;
    
    // Helper method to clamp values
    BYTE clampValue(int value);
    
    // Helper method to get pixel safely (returns black if out of bounds)
    RGBPixel getPixelSafe(int row, int col);
    
public:
    ImageFilter(int height, int width);
    
    // Accessor methods
    int getHeight() const { return imageHeight; }
    int getWidth() const { return imageWidth; }
    RGBPixel getPixel(int row, int col) const;
    void setPixel(int row, int col, const RGBPixel& pixel);
    
    // Filter operations
    void applyGrayscale();
    void applySepiaFilter();
    void applyHorizontalReflection();
    void applyBoxBlur();
    void applySobelEdgeDetection();
};

#endif
