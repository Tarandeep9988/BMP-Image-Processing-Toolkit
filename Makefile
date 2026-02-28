CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = filter
SOURCES = main.cpp ImageFilter.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean help

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "✓ Build successful! Run with: ./filter [option] input.bmp output.bmp"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Clean complete"

help:
	@echo "BMP Image Processing Toolkit - Build Targets"
	@echo "  make         - Build the project"
	@echo "  make clean   - Remove build artifacts"
	@echo "  make help    - Display this help message"

# Dependencies
main.o: main.cpp ImageFilter.hpp bmp.hpp
ImageFilter.o: ImageFilter.cpp ImageFilter.hpp bmp.hpp
