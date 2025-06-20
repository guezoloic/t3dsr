// Common math library

#ifndef MATH_H
#define MATH_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

#if defined(__x86_64__) || defined(__i386__)
    #define SIMD_X86
    #include <xmmintrin.h>
#elif defined(__aarch64__) || defined(__arm64__)
    #define SIMD_ARCH
    #include <arm_neon.h>
#else
    #define SIMD_NONE
#endif

#endif // MATH_H
