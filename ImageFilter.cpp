#include "ImageFilter.hpp"
#include <cmath>
#include <algorithm>

ImageFilter::ImageFilter(int height, int width) 
    : imageHeight(height), imageWidth(width) {
    pixelData.resize(height, std::vector<RGBPixel>(width));
}

BYTE ImageFilter::clampValue(int value) {
    if (value > 255) return 255;
    if (value < 0) return 0;
    return static_cast<BYTE>(value);
}

RGBPixel ImageFilter::getPixelSafe(int row, int col) {
    if (row < 0 || row >= imageHeight || col < 0 || col >= imageWidth) {
        return {0, 0, 0};
    }
    return pixelData[row][col];
}

RGBPixel ImageFilter::getPixel(int row, int col) const {
    return pixelData[row][col];
}

void ImageFilter::setPixel(int row, int col, const RGBPixel& pixel) {
    pixelData[row][col] = pixel;
}

void ImageFilter::applyGrayscale() {
    for (int row = 0; row < imageHeight; row++) {
        for (int col = 0; col < imageWidth; col++) {
            RGBPixel& currentPixel = pixelData[row][col];
            
            // Calculate average of RGB values
            int average = std::round(
                (currentPixel.red + currentPixel.green + currentPixel.blue) / 3.0
            );
            
            // Set all channels to the same value
            currentPixel.red = clampValue(average);
            currentPixel.green = clampValue(average);
            currentPixel.blue = clampValue(average);
        }
    }
}

void ImageFilter::applySepiaFilter() {
    for (int row = 0; row < imageHeight; row++) {
        for (int col = 0; col < imageWidth; col++) {
            RGBPixel& currentPixel = pixelData[row][col];
            
            // Store original values
            int originalRed = currentPixel.red;
            int originalGreen = currentPixel.green;
            int originalBlue = currentPixel.blue;
            
            // Apply sepia tone formula
            int sepiaRed = std::round(
                0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue
            );
            int sepiaGreen = std::round(
                0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue
            );
            int sepiaBlue = std::round(
                0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue
            );
            
            currentPixel.red = clampValue(sepiaRed);
            currentPixel.green = clampValue(sepiaGreen);
            currentPixel.blue = clampValue(sepiaBlue);
        }
    }
}

void ImageFilter::applyHorizontalReflection() {
    for (int row = 0; row < imageHeight; row++) {
        int leftCol = 0;
        int rightCol = imageWidth - 1;
        
        // Swap pixels from left and right sides
        while (leftCol < rightCol) {
            std::swap(pixelData[row][leftCol], pixelData[row][rightCol]);
            leftCol++;
            rightCol--;
        }
    }
}

void ImageFilter::applyBoxBlur() {
    // Create a temporary copy to store blurred values
    std::vector<std::vector<RGBPixel>> blurredData(
        imageHeight, std::vector<RGBPixel>(imageWidth)
    );
    
    for (int row = 0; row < imageHeight; row++) {
        for (int col = 0; col < imageWidth; col++) {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int pixelCount = 0;
            
            // Check 3x3 neighborhood around current pixel
            for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
                for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
                    int neighborRow = row + deltaRow;
                    int neighborCol = col + deltaCol;
                    
                    // Check if neighbor is within bounds
                    if (neighborRow >= 0 && neighborRow < imageHeight &&
                        neighborCol >= 0 && neighborCol < imageWidth) {
                        
                        RGBPixel neighbor = pixelData[neighborRow][neighborCol];
                        totalRed += neighbor.red;
                        totalGreen += neighbor.green;
                        totalBlue += neighbor.blue;
                        pixelCount++;
                    }
                }
            }
            
            // Calculate average
            blurredData[row][col].red = clampValue(std::round(totalRed / static_cast<double>(pixelCount)));
            blurredData[row][col].green = clampValue(std::round(totalGreen / static_cast<double>(pixelCount)));
            blurredData[row][col].blue = clampValue(std::round(totalBlue / static_cast<double>(pixelCount)));
        }
    }
    
    // Copy blurred data back to original
    pixelData = blurredData;
}

void ImageFilter::applySobelEdgeDetection() {
    // Sobel kernels for edge detection
    int sobelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    
    int sobelY[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };
    
    // Create temporary storage for edge-detected image
    std::vector<std::vector<RGBPixel>> edgeData(
        imageHeight, std::vector<RGBPixel>(imageWidth)
    );
    
    for (int row = 0; row < imageHeight; row++) {
        for (int col = 0; col < imageWidth; col++) {
            int gxRed = 0, gyRed = 0;
            int gxGreen = 0, gyGreen = 0;
            int gxBlue = 0, gyBlue = 0;
            
            // Apply Sobel operator to 3x3 neighborhood
            for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
                for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
                    int neighborRow = row + deltaRow;
                    int neighborCol = col + deltaCol;
                    
                    RGBPixel neighbor = getPixelSafe(neighborRow, neighborCol);
                    
                    int kernelRow = deltaRow + 1;
                    int kernelCol = deltaCol + 1;
                    
                    // Calculate Gx (horizontal gradient)
                    gxRed += neighbor.red * sobelX[kernelRow][kernelCol];
                    gxGreen += neighbor.green * sobelX[kernelRow][kernelCol];
                    gxBlue += neighbor.blue * sobelX[kernelRow][kernelCol];
                    
                    // Calculate Gy (vertical gradient)
                    gyRed += neighbor.red * sobelY[kernelRow][kernelCol];
                    gyGreen += neighbor.green * sobelY[kernelRow][kernelCol];
                    gyBlue += neighbor.blue * sobelY[kernelRow][kernelCol];
                }
            }
            
            // Calculate magnitude using Pythagorean theorem
            int edgeRed = std::round(std::sqrt(gxRed * gxRed + gyRed * gyRed));
            int edgeGreen = std::round(std::sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int edgeBlue = std::round(std::sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            
            edgeData[row][col].red = clampValue(edgeRed);
            edgeData[row][col].green = clampValue(edgeGreen);
            edgeData[row][col].blue = clampValue(edgeBlue);
        }
    }
    
    // Copy edge-detected data back to original
    pixelData = edgeData;
}
