#include "mat4.h"

Mat4f_t mat4f_from_array(const float arr[16])
{
    Mat4f_t mat;
    for(int i = 0; i<MAT_SIZE; i+=MAT_DIM) {
#if defined (SIMD_X86)
        __m128 line = _mm_load_ps(&arr[i]);
        _mm_store_ps(&mat.m[i], line);
#elif defined (SIMD_ARCH)
        float32x4_t line = vld1q_f32(&arr[i]);
        vst1q_f32(&mat.m[i], line);
#else
        for(int j = 0; j<MAT_DIM; j++) {
            mat.m[i+j] = arr[i+j];
        }   
#endif
    }
    return mat;
}

Mat4f_t mat4f_scalar(float f)
{
    Mat4f_t mat;
    for(int i = 0; i<MAT_SIZE; i+=MAT_DIM) {
#if defined (SIMD_X86)
        __m128 line_scalar = _mm_set1_ps(f);
        _mm_store_ps(&mat.m[i], line_scalar);

#elif defined (SIMD_ARCH)
        float32x4_t line_scalar = vdupq_n_f32(f);
        vst1q_f32(&mat.m[i], line_scalar);

#else
        for(int j = 0; j<MAT_DIM; j++) {
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
    
    for(int i = 0; i<MAT_SIZE; i+=MAT_DIM) {
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

Mat4f_t mat4_add(const Mat4f_t* m1, const Mat4f_t* m2) 
{
    Mat4f_t mout = mat4f_clone(m1);
    mat4f_add_r(&mout, m2);
    return mout;
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

Mat4f_t mat4_sub(const Mat4f_t* m1, const Mat4f_t* m2) 
{
    Mat4f_t mout = mat4f_clone(m1);
    mat4f_sub_r(&mout, m2);
    return mout;
}

Mat4f_t* mat4f_scale_r(Mat4f_t *out, float scalar)
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

Mat4f_t mat4f_scale(const Mat4f_t *__restrict m, float scalar)
{
    Mat4f_t mout = mat4f_clone(m);
    mat4f_scale_r(&mout, scalar);
    return mout;
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
Mat4f_t mat4_mul(const Mat4f_t* m1, const Mat4f_t* m2)
{
    Mat4f_t mout = mat4f_clone(m1);
    mat4f_mul_r(&mout, m2);
    return mout;
}

Mat4f_t* mat4_tpo_r(Mat4f_t *__restrict m)
{
    return m;    
}