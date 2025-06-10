#ifndef VECTOR4_H
#define VECTOR4_H

#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

#if defined(__x86_64__) || defined(__i386__)
#define SIMD_X86
#include <xmmintrin.h>
#elif defined(__aarch64__) || defined(__arm64__)
#define SIMD_ARCH
#include <arm_neon.h>
#else
#endif

typedef union 
{
    struct { float x, y, z, w; };
    float data[4];
} Vec4f_t;  

static inline Vec4f_t vec4f_from_array(float *__restrict val)
{
    Vec4f_t vec4;
    memcpy(vec4.data, val, 4*sizeof(float));
    return vec4;
}

static inline Vec4f_t vec4(float x, float y, float z, float w) 
{
    return (Vec4f_t){x, y, z, w};
}

// (f, f, f, f)
static inline Vec4f_t vec4f_scalar(float f) {
    Vec4f_t vec4;

// store f x 4 in register
// add all register into data
#if defined(SIMD_X86)
    __m128 scalar = _mm_set1_ps(f);
    _mm_storeu_ps(vec4.data, scalar);

#elif defined(SIMD_ARCH)
    float32x4_t scalar = vdupq_n_f32(f);
    vst1q_f32(vec4.data, scalar);

// add one by one each value to their specific address
#else
    for (int i = 0; i < 4; i++) {
        vec4.data[i] = f;
    }
#endif
    return vec4;
}

// (0, 0, 0, 0)
static inline Vec4f_t Vec4f_zero(void)
{
    return vec4f_scalar(0.f);
}

Vec4f_t vec4f_add_r(Vec4f_t *__restrict out, Vec4f_t a);
Vec4f_t vec4f_add(Vec4f_t a, Vec4f_t b);


// Vec4_t vec4(float x, float y, float z, float w);

// Vec4_t vec4_add(Vec4_t v1, Vec4_t v2);

// Vec4_t vec4_sub(Vec4_t v1, Vec4_t v2);

// Vec4_t vec4_scale(Vec4_t v, float scalar);

// float vec4_dot(Vec4_t a, Vec4_t b);

// float vec4_len(Vec4_t v);

// Vec4_t vec4_norm(Vec4_t v);

// Vec4_t vec4_lerp(Vec4_t a, Vec4_t b, float t);

// float vec4_angle(Vec4_t a, Vec4_t b);

// Vec4_t vec4_proj(Vec4_t a, Vec4_t b);

// Vec4_t vec4_refl(Vec4_t v, Vec4_t normal);

// float vec4_dist(Vec4_t a, Vec4_t b);

#endif // VECTOR4_H
