#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "ImageFilter.hpp"

void displayUsage() {
    std::cout << "Usage: ./filter [option] input_file output_file\n";
    std::cout << "Options:\n";
    std::cout << "  -g    Apply grayscale filter\n";
    std::cout << "  -s    Apply sepia tone filter\n";
    std::cout << "  -r    Apply horizontal reflection\n";
    std::cout << "  -b    Apply box blur filter\n";
    std::cout << "  -e    Apply Sobel edge detection\n";
}

bool loadBitmapFile(const char* filename, BitmapFileHeader& fileHeader,
                    BitmapInfoHeader& infoHeader, ImageFilter& filter) {
    std::ifstream inputFile(filename, std::ios::binary);
    
    if (!inputFile) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }
    
    // Read file header
    inputFile.read(reinterpret_cast<char*>(&fileHeader), sizeof(BitmapFileHeader));
    
    // Read info header
    inputFile.read(reinterpret_cast<char*>(&infoHeader), sizeof(BitmapInfoHeader));
    
    // Validate BMP format
    if (fileHeader.fileType != 0x4d42 || fileHeader.pixelDataOffset != 54 ||
        infoHeader.headerSize != 40 || infoHeader.bitsPerPixel != 24 ||
        infoHeader.compressionType != 0) {
        std::cerr << "Error: Unsupported file format" << std::endl;
        return false;
    }
    
    int height = std::abs(infoHeader.imageHeight);
    int width = infoHeader.imageWidth;
    
    // Calculate row padding
    int paddingBytes = (4 - (width * sizeof(RGBPixel)) % 4) % 4;
    
    // Read pixel data
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            RGBPixel pixel;
            inputFile.read(reinterpret_cast<char*>(&pixel), sizeof(RGBPixel));
            filter.setPixel(row, col, pixel);
        }
        
        // Skip padding bytes at end of row
        inputFile.seekg(paddingBytes, std::ios::cur);
    }
    
    inputFile.close();
    return true;
}

bool saveBitmapFile(const char* filename, const BitmapFileHeader& fileHeader,
                    const BitmapInfoHeader& infoHeader, const ImageFilter& filter) {
    std::ofstream outputFile(filename, std::ios::binary);
    
    if (!outputFile) {
        std::cerr << "Error: Cannot create file " << filename << std::endl;
        return false;
    }
    
    // Write file header
    outputFile.write(reinterpret_cast<const char*>(&fileHeader), sizeof(BitmapFileHeader));
    
    // Write info header
    outputFile.write(reinterpret_cast<const char*>(&infoHeader), sizeof(BitmapInfoHeader));
    
    int height = filter.getHeight();
    int width = filter.getWidth();
    
    // Calculate row padding
    int paddingBytes = (4 - (width * sizeof(RGBPixel)) % 4) % 4;
    BYTE paddingData[3] = {0, 0, 0};
    
    // Write pixel data
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            RGBPixel pixel = filter.getPixel(row, col);
            outputFile.write(reinterpret_cast<const char*>(&pixel), sizeof(RGBPixel));
        }
        
        // Write padding bytes at end of row
        if (paddingBytes > 0) {
            outputFile.write(reinterpret_cast<const char*>(paddingData), paddingBytes);
        }
    }
    
    outputFile.close();
    return true;
}

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 4) {
        displayUsage();
        return 1;
    }
    
    // Parse filter option
    char* filterOption = argv[1];
    char* inputFilename = argv[2];
    char* outputFilename = argv[3];
    
    if (strlen(filterOption) != 2 || filterOption[0] != '-') {
        std::cerr << "Error: Invalid filter option\n";
        displayUsage();
        return 1;
    }
    
    char filterType = filterOption[1];
    
    // Validate filter type
    if (filterType != 'g' && filterType != 's' && filterType != 'r' &&
        filterType != 'b' && filterType != 'e') {
        std::cerr << "Error: Unknown filter option\n";
        displayUsage();
        return 1;
    }
    
    // Read bitmap headers first to get dimensions
    std::ifstream tempFile(inputFilename, std::ios::binary);
    if (!tempFile) {
        std::cerr << "Error: Cannot open file " << inputFilename << std::endl;
        return 1;
    }
    
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    
    tempFile.read(reinterpret_cast<char*>(&fileHeader), sizeof(BitmapFileHeader));
    tempFile.read(reinterpret_cast<char*>(&infoHeader), sizeof(BitmapInfoHeader));
    tempFile.close();
    
    int height = std::abs(infoHeader.imageHeight);
    int width = infoHeader.imageWidth;
    
    // Create image filter object
    ImageFilter imageFilter(height, width);
    
    // Load the bitmap file
    if (!loadBitmapFile(inputFilename, fileHeader, infoHeader, imageFilter)) {
        return 1;
    }
    
    // Apply the selected filter
    switch (filterType) {
        case 'g':
            std::cout << "Applying grayscale filter...\n";
            imageFilter.applyGrayscale();
            break;
        case 's':
            std::cout << "Applying sepia filter...\n";
            imageFilter.applySepiaFilter();
            break;
        case 'r':
            std::cout << "Applying reflection...\n";
            imageFilter.applyHorizontalReflection();
            break;
        case 'b':
            std::cout << "Applying blur filter...\n";
            imageFilter.applyBoxBlur();
            break;
        case 'e':
            std::cout << "Applying edge detection...\n";
            imageFilter.applySobelEdgeDetection();
            break;
    }
    
    // Save the modified image
    if (!saveBitmapFile(outputFilename, fileHeader, infoHeader, imageFilter)) {
        return 1;
    }
    
    std::cout << "Filter applied successfully! Output saved to " << outputFilename << std::endl;
    return 0;
}
