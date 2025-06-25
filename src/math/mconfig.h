// Common math library

#ifndef MCONFIG_H
#define MCONFIG_H

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#if defined(__x86_64__) || defined(__amd64__) || defined(_M_X64) 
    #define SIMD_X86
    #define SIMD_ENABLE
    #include <xmmintrin.h>

#elif defined(__aarch64__) || defined(__arm64__) || defined(_M_ARM64)
    #define SIMD_ARCH
    #define SIMD_ENABLE
    #include <arm_neon.h>

#else
    #define SIMD_NONE
#endif


#ifdef _MSC_VER
    #define ALIGN16 __declspec(align(16))
#else
    #define ALIGN16 __attribute__((aligned(16)))
#endif

#endif // MCONFIG_H
