#include "mat4.h"

#include <math.h>
#include <float.h>

#ifdef SIMD_X86
    #include <xmmintrin.h>
#elif defined(SIMD_ARCH)
    #include <arm_neon.h>
#endif

Mat4f_t* mat4f_from_array_r(Mat4f_t *__restrict m, const float arr[16])
{
    for(int i = 0; i<MAT_SIZE; i+=MAT_DIM) {
#if defined (SIMD_X86)
        __m128 line = _mm_load_ps(&arr[i]);
        _mm_store_ps(&m->m[i], line);
#elif defined (SIMD_ARCH)
        float32x4_t line = vld1q_f32(&arr[i]);
        vst1q_f32(&m->m[i], line);
#else
        for(int j = 0; j<MAT_DIM; j++) {
            m->m[i+j] = arr[i+j];
        }   
#endif
    }
    return m;
}

Mat4f_t* mat4f_scalar_r(Mat4f_t *__restrict m, float f)
{
    for(int i = 0; i<MAT_SIZE; i+=MAT_DIM) {
#if defined (SIMD_X86)
        __m128 line_scalar = _mm_set1_ps(f);
        _mm_store_ps(&m->m[i], line_scalar);

#elif defined (SIMD_ARCH)
        float32x4_t line_scalar = vdupq_n_f32(f);
        vst1q_f32(&m->m[i], line_scalar);

#else
        for(int j = 0; j<MAT_DIM; j++) {
            m->m[i+j] = f;
        }
        #endif
    }
    return m;
}


Mat4f_t* mat4f_zero_r(Mat4f_t *__restrict m)
{
#if defined (SIMD_X86)
    for(int i = 0; i<MAT_SIZE; i+=MAT_DIM) {
        __m128 line_zero = _mm_setzero_ps();
        _mm_store_ps(&m->m[i], line_zero);
    }

    return m;
#else
    return mat4f_scalar_r(m, 0.f);
#endif
}

Mat4f_t* mat4f_identity_r(Mat4f_t *__restrict m)
{
    mat4f_zero_r(m);
    m->m[0] = 1.f;
    m->m[5] = 1.f;
    m->m[10] = 1.f;
    m->m[15] = 1.f;
    return m;
}

Mat4f_t* mat4f_add_r(Mat4f_t *out, const Mat4f_t *m2)
{
    for(int i = 0; i<MAT_SIZE; i+=MAT_DIM) {
#if defined (SIMD_X86)
        __m128 ma = _mm_load_ps(&out->m[i]);
        __m128 mb = _mm_load_ps(&m2->m[i]);

        __m128 mres = _mm_add_ps(ma, mb);
        _mm_store_ps(&out->m[i], mres);

#elif defined (SIMD_ARCH)
        float32x4_t ma = vld1q_f32(&out->m[i]);
        float32x4_t mb = vld1q_f32(&m2->m[i]);
        
        float32x4_t mres = vaddq_f32(ma, mb);

        vst1q_f32(&out->m[i], mres);
        
#else
        for (int j = 0; j < 4; j++) {
            out->m[i + j] += m2->m[i + j];
        }
#endif
    }
    return out;
}

Mat4f_t* mat4f_sub_r(Mat4f_t *out, const Mat4f_t *m2)
{
    for(int i = 0; i<MAT_SIZE; i+=MAT_DIM) {
#if defined (SIMD_X86)
        __m128 ma = _mm_load_ps(&out->m[i]);
        __m128 mb = _mm_load_ps(&m2->m[i]);

        __m128 mres = _mm_sub_ps(ma, mb);
        _mm_store_ps(&out->m[i], mres);

#elif defined (SIMD_ARCH)
        float32x4_t ma = vld1q_f32(&out->m[i]);
        float32x4_t mb = vld1q_f32(&m2->m[i]);
        
        float32x4_t mres = vsubq_f32(ma, mb);

        vst1q_f32(&out->m[i], mres);
        
#else
        for (int j = 0; j < 4; j++) {
            out->m[i + j] -= m2->m[i + j];
        }
#endif
    }
    return out;
}

Mat4f_t* mat4f_scale_r(Mat4f_t *__restrict out, float scalar)
{
    for(int i = 0; i<MAT_SIZE; i+=MAT_DIM) {
#if defined (SIMD_X86)
        __m128 ma = _mm_load_ps(&out->m[i]);
        __m128 mb = _mm_set1_ps(scalar);
        __m128 mres = _mm_mul_ps(ma, mb);
        _mm_store_ps(&out->m[i], mres);

#elif defined (SIMD_ARCH)
        float32x4_t ma = vld1q_f32(&out->m[i]);
        float32x4_t mb = vdupq_n_f32(scalar);
        float32x4_t mres = vmulq_f32(ma, mb);
        vst1q_f32(&out->m[i], mres);
#else
        for(int j = 0; j<MAT_DIM; j++) {
            out->m[i+j] *= scalar;
        }
#endif
    }
    return out;
}

Mat4f_t* mat4f_mul_r(Mat4f_t* out, const Mat4f_t* m2)
{
    Mat4f_t clone = mat4f_clone(out);

    for (int row = 0; row<MAT_DIM; row++) {
#if defined (SIMD_X86)
        __m128 mrow = _mm_load_ps(&clone.m[row * MAT_DIM]);

        for (int col = 0; col<MAT_DIM; col++) {
            __m128 mcol = _mm_set_ps(
                m2->m[3 * MAT_DIM + col],
                m2->m[2 * MAT_DIM + col],
                m2->m[1 * MAT_DIM + col],
                m2->m[0 * MAT_DIM + col]
            );
            __m128 mmul = _mm_mul_ps(mrow, mcol);

            __m128 shuf = _mm_shuffle_ps(mmul, mmul, _MM_SHUFFLE(2, 3, 0, 1)); // [y, y, w, w]
            __m128 sum = _mm_add_ps(mmul, shuf); // [x+y, y+y, z+w, w+w]

            shuf = _mm_movehl_ps(shuf, sum); // [z+w, w+w, w, w]
            sum = _mm_add_ss(sum, shuf); // [x+y+z+w, y+y, z+w, w+w]
            float mres = _mm_cvtss_f32(sum);
            
            out->m[row * MAT_DIM + col] = mres;
        }
#elif defined (SIMD_ARCH)
        float32x4_t mrow = vld1q_f32(&clone.m[row*MAT_DIM]);

        for (int col = 0; col<MAT_DIM; col++) {
            float32x4_t mcol = {
                m2->m[0 * MAT_DIM + col],
                m2->m[1 * MAT_DIM + col],
                m2->m[2 * MAT_DIM + col],
                m2->m[3 * MAT_DIM + col]
            };

            float32x4_t mmul = vmulq_f32(mrow, mcol);
            float32x2_t sum_pair = vadd_f32(vget_low_f32(mmul), vget_high_f32(mmul));
            float32x2_t final_sum = vpadd_f32(sum_pair, sum_pair);

            float mres = vget_lane_f32(final_sum, 0);
            out->m[row * MAT_DIM + col] = mres;
        }
#else
        for (int col = 0; col < MAT_DIM; col++) {
            float sum = 0.0f;
            for (int k = 0; k < MAT_DIM; k++) {
                sum += clone.m[row * MAT_DIM + k] * m2->m[k * MAT_DIM + col];
            }
            out->m[row * MAT_DIM + col] = sum;
        }
#endif
    }
    return out;
}

Mat4f_t* mat4f_tpo_r(Mat4f_t *__restrict out)
{
    Mat4f_t clone = mat4f_clone(out);
    
    #if defined (SIMD_X86)
    __m128 row[4];
    for (int i=0; i<MAT_DIM; i++) {
        row[i] = _mm_load_ps(&clone.m[i * MAT_DIM]);
    }
    
    __m128 t0 = _mm_unpacklo_ps(row[0], row[1]);
    __m128 t1 = _mm_unpackhi_ps(row[0], row[1]);
    __m128 t2 = _mm_unpacklo_ps(row[2], row[3]);
    __m128 t3 = _mm_unpackhi_ps(row[2], row[3]);
    
    __m128 r0 = _mm_movelh_ps(t0, t2);
    __m128 r1 = _mm_movehl_ps(t2, t0);
    __m128 r2 = _mm_movelh_ps(t1, t3);
    __m128 r3 = _mm_movehl_ps(t3, t1);
    
    _mm_store_ps(&out->m[0 * MAT_DIM], r0);
    _mm_store_ps(&out->m[1 * MAT_DIM], r1);
    _mm_store_ps(&out->m[2 * MAT_DIM], r2);
    _mm_store_ps(&out->m[3 * MAT_DIM], r3);
    
    
    #elif defined (SIMD_ARCH)
    float32x4_t row[4];
    for (int i = 0; i < MAT_DIM; i++) {
        row[i] = vld1q_f32(&clone.m[i * MAT_DIM]);
    }

    float32x4x2_t t01 = vtrnq_f32(row[0], row[1]);
    float32x4x2_t t23 = vtrnq_f32(row[2], row[3]);

    float32x2_t r0_low = vget_low_f32(t01.val[0]);
    float32x2_t r0_high = vget_low_f32(t23.val[0]);
    float32x4_t r0 = vcombine_f32(r0_low, r0_high);

    float32x2_t r1_low = vget_low_f32(t01.val[1]);
    float32x2_t r1_high = vget_low_f32(t23.val[1]);
    float32x4_t r1 = vcombine_f32(r1_low, r1_high);

    float32x2_t r2_low = vget_high_f32(t01.val[0]);
    float32x2_t r2_high = vget_high_f32(t23.val[0]);
    float32x4_t r2 = vcombine_f32(r2_low, r2_high);

    float32x2_t r3_low = vget_high_f32(t01.val[1]);
    float32x2_t r3_high = vget_high_f32(t23.val[1]);
    float32x4_t r3 = vcombine_f32(r3_low, r3_high);

    vst1q_f32(&out->m[0 * MAT_DIM], r0);
    vst1q_f32(&out->m[1 * MAT_DIM], r1);
    vst1q_f32(&out->m[2 * MAT_DIM], r2);
    vst1q_f32(&out->m[3 * MAT_DIM], r3);
    #else
    
    for(int i = 0; i < MAT_DIM; i++) {
        int dim_i = i * MAT_DIM;
        
        for (int j = 0; j < MAT_DIM; j++) {
            out->m[dim_i + j] = clone.m[(j * MAT_DIM) + i];
        }
    }
    #endif
    return out;    
}

float mat4f_det(const Mat4f_t* m)
{
    const float* const a = m->m;

    float det;
    det =
    a[0] * (a[5]*(a[10]*a[15] - a[11]*a[14]) - a[9]*(a[6]*a[15] - a[7]*a[14]) + a[13]*(a[6]*a[11] - a[7]*a[10])) -
    a[4] * (a[1]*(a[10]*a[15] - a[11]*a[14]) - a[9]*(a[2]*a[15] - a[3]*a[14]) + a[13]*(a[2]*a[11] - a[3]*a[10])) +
    a[8] * (a[1]*(a[6]*a[15] - a[7]*a[14]) - a[5]*(a[2]*a[15] - a[3]*a[14]) + a[13]*(a[2]*a[7]  - a[3]*a[6])) -
    a[12]* (a[1]*(a[6]*a[11] - a[7]*a[10]) - a[5]*(a[2]*a[11] - a[3]*a[10]) + a[9] *(a[2]*a[7]  - a[3]*a[6]));

    return det;
}

Mat4f_t* mat4f_inv_r(Mat4f_t* __restrict m)
{
    const float det = mat4f_det(m);

    if (fabsf(det) < FLT_EPSILON)
    {
        mat4f_identity_r(m);
        return m;
    }

    const float invDet = 1.f / det;
    const Mat4f_t mclone = mat4f_clone(m);
    const float* const a = mclone.m;

    m->m[0] =  (a[5] * (a[10]*a[15] - a[11]*a[14]) - a[9] * (a[6]*a[15] - a[7]*a[14]) + a[13] * (a[6]*a[11] - a[7]*a[10])) * invDet;
    m->m[1] = -(a[1] * (a[10]*a[15] - a[11]*a[14]) - a[9] * (a[2]*a[15] - a[3]*a[14]) + a[13] * (a[2]*a[11] - a[3]*a[10])) * invDet;
    m->m[2] =  (a[1] * (a[6]*a[15] - a[7]*a[14]) - a[5] * (a[2]*a[15] - a[3]*a[14]) + a[13] * (a[2]*a[7] - a[3]*a[6])) * invDet;
    m->m[3] = -(a[1] * (a[6]*a[11] - a[7]*a[10]) - a[5] * (a[2]*a[11] - a[3]*a[10]) + a[9] * (a[2]*a[7] - a[3]*a[6])) * invDet;

    m->m[4] = -(a[4] * (a[10]*a[15] - a[11]*a[14]) - a[8] * (a[6]*a[15] - a[7]*a[14]) + a[12] * (a[6]*a[11] - a[7]*a[10])) * invDet;
    m->m[5] =  (a[0] * (a[10]*a[15] - a[11]*a[14]) - a[8] * (a[2]*a[15] - a[3]*a[14]) + a[12] * (a[2]*a[11] - a[3]*a[10])) * invDet;
    m->m[6] = -(a[0] * (a[6]*a[15] - a[7]*a[14]) - a[4] * (a[2]*a[15] - a[3]*a[14]) + a[12] * (a[2]*a[7] - a[3]*a[6])) * invDet;
    m->m[7] =  (a[0] * (a[6]*a[11] - a[7]*a[10]) - a[4] * (a[2]*a[11] - a[3]*a[10]) + a[8] * (a[2]*a[7] - a[3]*a[6])) * invDet;

    m->m[8] =  (a[4] * (a[9]*a[15] - a[11]*a[13]) - a[8] * (a[5]*a[15] - a[7]*a[13]) + a[12] * (a[5]*a[11] - a[7]*a[9])) * invDet;
    m->m[9] = -(a[0] * (a[9]*a[15] - a[11]*a[13]) - a[8] * (a[1]*a[15] - a[3]*a[13]) + a[12] * (a[1]*a[11] - a[3]*a[9])) * invDet;
    m->m[10] = (a[0] * (a[5]*a[15] - a[7]*a[13]) - a[4] * (a[1]*a[15] - a[3]*a[13]) + a[12] * (a[1]*a[7] - a[3]*a[5])) * invDet;
    m->m[11] = -(a[0] * (a[5]*a[11] - a[7]*a[9]) - a[4] * (a[1]*a[11] - a[3]*a[9]) + a[8] * (a[1]*a[7] - a[3]*a[5])) * invDet;

    m->m[12] = -(a[4] * (a[9]*a[14] - a[10]*a[13]) - a[8] * (a[5]*a[14] - a[6]*a[13]) + a[12] * (a[5]*a[10] - a[6]*a[9])) * invDet;
    m->m[13] = (a[0] * (a[9]*a[14] - a[10]*a[13]) - a[8] * (a[1]*a[14] - a[2]*a[13]) + a[12] * (a[1]*a[10] - a[2]*a[9])) * invDet;
    m->m[14] = -(a[0] * (a[5]*a[14] - a[6]*a[13]) - a[4] * (a[1]*a[14] - a[2]*a[13]) + a[12] * (a[1]*a[6] - a[2]*a[5])) * invDet;
    m->m[15] = (a[0] * (a[5]*a[10] - a[6]*a[9]) - a[4] * (a[1]*a[10] - a[2]*a[9]) + a[8] * (a[1]*a[6] - a[2]*a[5])) * invDet;

    return m;
}
