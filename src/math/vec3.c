//
//  vec3.c
//  main
//
//  Created by Loïc GUEZO on 21/06/2025.
//

#include "vec3.h"
#include "common_math.h"

#define VEC_SIZE 3

Vec3f_t vec3f(float x, float y, float z)
{
    return (Vec3f_t){.x = x, .y = y, .z = z};
}

Vec3f_t vec3f_from_array(const float *__restrict val)
{
    Vec3f_t vec;
#if defined (SIMD_X86)
    __m128 arr = _mm_loadu_ps(val);
    _mm_store_ps(vec.data, arr);
#elif defined (SIMD_ARCH)
    float32x4_t arr = vld1q_f32(val);
    vst1q_f32(vec.data, arr);
#else
    for (int i = 0; i < VEC_SIZE; i++) {
        vec.data[i] = val[i];
    }
#endif
    return vec;
}

Vec3f_t vec3f_scalar(float f)
{
    Vec3f_t vec;
#if defined(SIMD_X86)
    __m128 scalar = _mm_set1_ps(f);
    _mm_store_ps(vec.data, scalar);
#elif defined(SIMD_ARCH)
    float32x4_t scalar = vdupq_n_f32(f);
    vst1q_f32(vec.data, scalar);
#else
    for (int i = 0; i < VEC_SIZE; i++) {
        vec.data[i] = f;
    }
#endif
    return vec;
}

Vec3f_t vec3f_zero(void)
{
    return vec3f_scalar(0.f);
}

Vec3f_t vec3f_add_r(Vec3f_t *__restrict out, Vec3f_t a)
{
#if defined (SIMD_X86)
    __m128 va = _mm_load_ps(a.data);
    __m128 vb = _mm_load_ps(out->data);
    __m128 vres = _mm_add_ps(va, vb);
    _mm_store_ps(out->data, vres);
#elif defined (SIMD_ARCH)
    float32x4_t va = vld1q_f32(a.data);
    float32x4_t vb = vld1q_f32(out->data);
    float32x4_t vres = vaddq_f32(va, vb);
    vst1q_f32(out->data, vres);
#else
    for (int i = 0; i < VEC_SIZE; i++) {
        out->data[i] += a.data[i];
    }
#endif
    return *out;
}

Vec3f_t vec3f_add(Vec3f_t a, Vec3f_t b)
{
    return vec3f_add_r(&a, b);
}

Vec3f_t vec3f_sub_r(Vec3f_t *__restrict out, Vec3f_t a)
{
#if defined (SIMD_X86)
    __m128 va = _mm_load_ps(out->data);
    __m128 vb = _mm_load_ps(a.data);
    __m128 vres = _mm_sub_ps(va, vb);
    _mm_store_ps(out->data, vres);
#elif defined (SIMD_ARCH)
    float32x4_t va = vld1q_f32(out->data);
    float32x4_t vb = vld1q_f32(a.data);
    float32x4_t vres = vsubq_f32(va, vb);
    vst1q_f32(out->data, vres);
#else
    for (int i = 0; i < VEC_SIZE; i++) {
        out->data[i] -= a.data[i];
    }
#endif
    return *out;
}

Vec3f_t vec3f_sub(Vec3f_t a, Vec3f_t b)
{
    return vec3f_sub_r(&a, b);
}

Vec3f_t vec3f_scale_r(Vec3f_t *__restrict out, float scalar)
{
#if defined (SIMD_X86)
    __m128 va = _mm_load_ps(out->data);
    __m128 vb = _mm_set1_ps(scalar);
    __m128 vres = _mm_mul_ps(va, vb);
    _mm_store_ps(out->data, vres);
#elif defined (SIMD_ARCH)
    float32x4_t va = vld1q_f32(out->data);
    float32x4_t vb = vdupq_n_f32(scalar);
    float32x4_t vres = vmulq_f32(va, vb);
    vst1q_f32(out->data, vres);
#else
    for (int i = 0; i < VEC_SIZE; i++) {
        out->data[i] *= scalar;
    }
#endif
    return *out;
}

Vec3f_t vec3f_scale(Vec3f_t a, float scalar)
{
    return vec3f_scale_r(&a, scalar);
}


//Vec3f_t vec3f_add_r(Vec3f_t *__restrict out, Vec3f_t a);
//Vec3f_t vec3f_add(Vec3f_t a, Vec3f_t b);
//
//Vec3f_t vec3f_sub_r(Vec3f_t *__restrict out, Vec3f_t a);
//Vec3f_t vec3f_sub(Vec3f_t a, Vec3f_t b);
//
//Vec3f_t vec3f_scale_r(Vec3f_t *__restrict out, float scale);
//Vec3f_t vec3f_scale(Vec3f_t a, float scale);
