#include "mat4.h"
#include <string.h>
#include <stdio.h>


#if defined(__x86_64__) || defined(__i386__)
#include <xmmintrin.h>  // SSE
#elif defined(__aarch64__) || defined(__arm64__) || defined(__ARM_NEON)
#include <arm_neon.h>   // NEON
#else
#warning "SIMD intrinsics not enabled for this architecture"
#endif

Mat4_t mat4(const float arr[16]) 
{
    Mat4_t mat;
    memcpy(mat.m, arr, 16*sizeof(float));
    return mat;
}

Mat4_t mat4_zro(void) 
{
    return (Mat4_t){0};
}

Mat4_t mat4_ity(void) 
{
    return (Mat4_t) {{
        1, 0, 0, 0, 
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    }};
}

Mat4_t mat4_add(const Mat4_t* m1, const Mat4_t* m2) 
{
    Mat4_t mat;

#if defined(__x86_64__) || defined(__i386__)
    // SSE : addition 4 floats en parallèle
    for (int i = 0; i < 16; i += 4) {
        __m128 a = _mm_loadu_ps(&m1->m[i]);
        __m128 b = _mm_loadu_ps(&m2->m[i]);
        __m128 c = _mm_add_ps(a, b);
        _mm_storeu_ps(&mat.m[i], c);
    }
#elif defined(__aarch64__)
    printf("hello world");
    // NEON : addition 4 floats en parallèle
    for (int i = 0; i < 16; i += 4) {
        float32x4_t a = vld1q_f32(&m1->m[i]);
        float32x4_t b = vld1q_f32(&m2->m[i]);
        float32x4_t c = vaddq_f32(a, b);
        vst1q_f32(&mat.m[i], c);
    }
#else
    // Fallback classique
    for (int i = 0; i < 16; i++) {
        mat.m[i] = m1->m[i] + m2->m[i];
    }
#endif

    return mat;
}

Mat4_t mat4_sub(const Mat4_t* m1, const Mat4_t* m2) 
{
    Mat4_t mat;

    for(int i = 0; i<16; i++) {
        mat.m[i] = m1->m[i] - m2->m[i];
    }

    return mat;
}

Mat4_t mat4_scl(const Mat4_t* m, float scalar) 
{
    Mat4_t mat;

    for(int i = 0; i<16; i++) {
        mat.m[i] = m->m[i] * scalar;
    }

    return mat;
}

Mat4_t mat4_mul(const Mat4_t* m1, const Mat4_t* m2) 
{
    Mat4_t mat;
    
    for(int i = 0; i<4; i++) {
        int i3 = i * 3;
        for (int j = 0; j < 4; j++) {
            float sum = 0;
            
            for (int k = 0; k < 3; k++) {
                sum += m1->m[i3 + k] * m2->m[k*3 + j];
            }
            
            mat.m[i3 + j] = sum;
        }
    }
    
    return mat;
}
