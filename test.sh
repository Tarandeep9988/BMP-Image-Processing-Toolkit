#!/bin/bash
# BMP Image Processing Toolkit - Test Script
# This script tests all available filters on sample images

set -e

if [ ! -f "./filter" ]; then
    echo "Error: 'filter' executable not found. Run 'make' first."
    exit 1
fi

if [ ! -d "images" ]; then
    echo "Error: 'images' directory not found."
    exit 1
fi

# Check for test images
TEST_IMAGES=(images/courtyard.bmp images/stadium.bmp images/tower.bmp images/yard.bmp)
FOUND_IMAGES=false

for img in "${TEST_IMAGES[@]}"; do
    if [ -f "$img" ]; then
        FOUND_IMAGES=true
        break
    fi
done

if [ "$FOUND_IMAGES" = false ]; then
    echo "Warning: No test images found in images/ directory"
    exit 0
fi

# Test each filter
TEST_IMAGE=${TEST_IMAGES[0]}
echo "Testing filters on: $TEST_IMAGE"

echo "[1/5] Testing Grayscale filter..."
./filter -g "$TEST_IMAGE" images/test_grayscale.bmp
echo "✓ Grayscale filter successful"

echo "[2/5] Testing Sepia filter..."
./filter -s "$TEST_IMAGE" images/test_sepia.bmp
echo "✓ Sepia filter successful"

echo "[3/5] Testing Reflection filter..."
./filter -r "$TEST_IMAGE" images/test_reflection.bmp
echo "✓ Reflection filter successful"

echo "[4/5] Testing Blur filter..."
./filter -b "$TEST_IMAGE" images/test_blur.bmp
echo "✓ Blur filter successful"

echo "[5/5] Testing Edge Detection filter..."
./filter -e "$TEST_IMAGE" images/test_edges.bmp
echo "✓ Edge detection filter successful"

echo ""
echo "All tests completed successfully!"
echo "Output files created in images/ directory"

# Cleanup - remove .gitignore'd files from listing
rm -f images/test_*.bmp 2>/dev/null || true
