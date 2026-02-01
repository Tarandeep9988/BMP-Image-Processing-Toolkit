CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = filter
SOURCES = main.cpp ImageFilter.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

# Dependencies
main.o: main.cpp ImageFilter.hpp bmp.hpp
ImageFilter.o: ImageFilter.cpp ImageFilter.hpp bmp.hpp
