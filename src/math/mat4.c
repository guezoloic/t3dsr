#include "mat4.h"

Mat4f_t mat4f_from_array(const float arr[16])
{
    Mat4f_t mat;
    for(int i = 0; i<MAT_SIZE; i+=4) {
#if defined (SIMD_X86)
        __m128 line = _mm_load_ps(&arr[i]);
        _mm_store_ps(&mat.m[i], line);
#elif defined (SIMD_ARCH)
        float32x4_t line = vld1q_f32(&arr[i]);
        vst1q_f32(&mat.m[i], line);
#else
        for(int j = 0; j<4; j++) {
            mat.m[i+j] = arr[i+j];
        }
#endif
    }
    return mat;
}

Mat4f_t mat4f_scalar(float f)
{
    Mat4f_t mat;
    for(int i = 0; i<MAT_SIZE; i+=4) {
        #if defined (SIMD_X86)
        __m128 line_scalar = _mm_set1_ps(f);
        _mm_store_ps(&mat.m[i], line_scalar);
        #elif defined (SIMD_ARCH)
        float32x4_t line_scalar = vdupq_n_f32(f);
        vst1q_f32(&mat.m[i], line_scalar);
        #else
        for(int j = 0; j<4; j++) {
            mat.m[i+j] = f;
        }
        #endif
    }
    return mat;
}

Mat4f_t mat4f_zero()
{
#if defined (SIMD_X86)
    Mat4f_t mat;
    
    for(int i = 0; i<MAT_SIZE; i+=4) {
        __m128 line_zero = _mm_setzero_ps();
        _mm_store_ps(&mat.m[i], line_zero);
    }

    return mat;
#else
    return mat4f_scalar(0.f);
#endif
}

Mat4f_t mat4f_identity()
{
    Mat4f_t mat = mat4f_zero();
    mat.m[0] = 1.f;
    mat.m[5] = 1.f;
    mat.m[10] = 1.f;
    mat.m[15] = 1.f;
    return mat;
}


// Mat4_t mat4_add(const Mat4_t* m1, const Mat4_t* m2) 
// {
//     Mat4_t mat;

// #if defined(__x86_64__) || defined(__i386__)
    
//     for (int i = 0; i < 16; i += 4) {
//         __m128 a = _mm_loadu_ps(&m1->m[i]);
//         __m128 b = _mm_loadu_ps(&m2->m[i]);
//         __m128 c = _mm_add_ps(a, b);
//         _mm_storeu_ps(&mat.m[i], c);
//     }
// #elif defined(__aarch64__)
//     for (int i = 0; i < 16; i += 4) {
//         float32x4_t a = vld1q_f32(&m1->m[i]);
//         float32x4_t b = vld1q_f32(&m2->m[i]);
//         float32x4_t c = vaddq_f32(a, b);
//         vst1q_f32(&mat.m[i], c);
//     }
// #else
//     for (int i = 0; i < 16; i++) {
//         mat.m[i] = m1->m[i] + m2->m[i];
//     }
// #endif

//     return mat;
// }

// Mat4_t mat4_sub(const Mat4_t* m1, const Mat4_t* m2) 
// {
//     Mat4_t mat;

//     for(int i = 0; i<16; i++) {
//         mat.m[i] = m1->m[i] - m2->m[i];
//     }

//     return mat;
// }

// Mat4_t mat4_scl(const Mat4_t* m, float scalar) 
// {
//     Mat4_t mat;

//     for(int i = 0; i<16; i++) {
//         mat.m[i] = m->m[i] * scalar;
//     }

//     return mat;
// }

// Mat4_t mat4_mul(const Mat4_t* m1, const Mat4_t* m2) 
// {
//     Mat4_t mat;
    
//     for(int i = 0; i<4; i++) {
//         int i3 = i * 3;
//         for (int j = 0; j < 4; j++) {
//             float sum = 0;
            
//             for (int k = 0; k < 3; k++) {
//                 sum += m1->m[i3 + k] * m2->m[k*3 + j];
//             }
            
//             mat.m[i3 + j] = sum;
//         }
//     }
    
//     return mat;
// }
