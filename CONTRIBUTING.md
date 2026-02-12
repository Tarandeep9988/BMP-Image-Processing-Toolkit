# Contributing to BMP Image Processing Toolkit

Thank you for your interest in contributing! This document provides guidelines and instructions for contributing to the project.

## Getting Started

1. Clone the repository
2. Create a new branch for your feature: `git checkout -b feature/your-feature-name`
3. Make your changes and test thoroughly
4. Commit with clear, descriptive messages
5. Push to your branch and create a pull request

## Code Style Guidelines

- Follow C++17 standards
- Use meaningful variable and function names
- Add comments for complex algorithms
- Keep functions focused and modular
- Use const correctness
- Avoid global variables

## Testing Before Submission

```bash
make clean
make
./filter -g test_image.bmp output.bmp
```

Test with multiple image files to ensure robustness.

## Commit Message Format

- Use imperative mood ("Add feature" not "Added feature")
- First line should be descriptive (50 chars max)
- Add blank line, then detailed explanation if needed
- Reference issues when relevant

Example:
```
Implement edge detection with Sobel operator

- Apply horizontal and vertical gradients
- Calculate magnitude using Pythagorean theorem
- Handle boundary conditions properly
```

## Areas for Contribution

- [ ] Add support for additional image formats (PNG, JPEG)
- [ ] Implement additional filters (Gaussian blur, posterize, etc.)
- [ ] Add unit tests and test suite
- [ ] Performance optimizations
- [ ] Threading support for large images
- [ ] Comprehensive error handling
- [ ] Documentation improvements

## Reporting Issues

When reporting bugs, include:
- Clear description of the issue
- Steps to reproduce
- Expected vs actual behavior
- System information and compiler version
- BMP file details

## Questions?

Feel free to open an issue for discussions or questions about the project.

Thank you for contributing!
