#include "mv4.h"

#ifdef SIMD_X86
    #include <xmmintrin.h>
#elif defined(SIMD_ARCH)
    #include <arm_neon.h>
#endif


Vec4f_t mat4f_mul_vec4f(const Mat4f_t mat, Vec4f_t v)
{
    Vec4f_t out;
#if defined (SIMD_X86)
    __m128 vec = _mm_load_ps(v.data);
    
    for (int i = 0; i < 4; i++) 
    {
        __m128 row = _mm_load_ps(&mat.m[4*i]);
        __m128 mul = _mm_mul_ps(row, vec);

        __m128 shuf = _mm_movehl_ps(mul, mul);
        __m128 sum = _mm_add_ps(mul, shuf);
        shuf = _mm_movehl_ps(shuf, sum);
        sum = _mm_add_ss(sum, shuf);

        out.data[i] = _mm_cvtss_f32(sum);
    }

#elif defined (SIMD_ARCH)
    float32x4_t vec = vld1q_f32(v.data);

    for (int i = 0; i < 4; i++)
    {
        float32x4_t row = vld1q_f32(&mat.m[i*4]);
        float32x4_t mul = vmulq_f32(row, vec);

        float32x2_t sum_low = vget_low_f32(mul);
        float32x2_t sum_high = vget_high_f32(mul);
        float32x2_t sum_pair = vpadd_f32(sum_low, sum_high);
        sum_pair = vpadd_f32(sum_pair, sum_pair);

        out.data[i] = vget_lane_f32(sum_pair, 0);
    }

#else
    for (int i = 0; i < 4; i++)
    {
        out.data[i] = 0.f;
        for (int j = 0; j < 4; j++)
            out.data[i] += mat.m[i*4 + j] * v.data[j];
    }
#endif
    return out;
}