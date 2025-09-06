# T3DSR
Lightweight terminal-based 3d renderer of geometric shapes using ASCII characters.

## Features
- ### 3D Math Optimized with SIMD
    - High-performance vector and matrix operations using SSE on x86_64 and NEON on ARM.
- ### Demo
    - A fully rotationg 3d cube rendered in ASCII.
    - Z-buffering implementation for depth.

## Usage

```bash
cmake -B build && \
make -C build && \
# run demo
./build/main
```

# Requirements 
- C compiler (GCC, Clang, etc...)
- make and cmake

# Roadmap

This project is intended to be very lightweight, it's mainly an experiment with 3d math and terminal graphics.

**Feel free to fork it and add some features.**