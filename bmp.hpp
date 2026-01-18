#ifndef BMP_HPP
#define BMP_HPP

#include <cstdint>

// Type aliases for better readability
using BYTE = uint8_t;
using DWORD = uint32_t;
using LONG = int32_t;
using WORD = uint16_t;

// Structure to hold bitmap file header information
struct __attribute__((__packed__)) BitmapFileHeader {
    WORD fileType;
    DWORD fileSize;
    WORD reserved1;
    WORD reserved2;
    DWORD pixelDataOffset;
};

// Structure to hold bitmap information header
struct __attribute__((__packed__)) BitmapInfoHeader {
    DWORD headerSize;
    LONG imageWidth;
    LONG imageHeight;
    WORD colorPlanes;
    WORD bitsPerPixel;
    DWORD compressionType;
    DWORD imageSize;
    LONG horizontalResolution;
    LONG verticalResolution;
    DWORD colorsUsed;
    DWORD importantColors;
};

// Structure representing an RGB pixel
struct __attribute__((__packed__)) RGBPixel {
    BYTE blue;
    BYTE green;
    BYTE red;
};

#endif
