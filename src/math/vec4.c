#include <float.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#if defined(__x86_64__) || defined(__i386__)
#define SIMD_X86
#include <xmmintrin.h>
#elif defined(__aarch64__) || defined(__arm64__)
#define SIMD_ARCH
#include <arm_neon.h>
#else
#endif

#include "vec4.h"

Vec4f_t vec4f_add_r(Vec4f_t *__restrict out, Vec4f_t a)
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
    for(int i = 0; i<4; i++) {
        out->data[i] += a.data[i];
    }
#endif
    return *out;
}

Vec4f_t vec4_add(Vec4f_t v1, Vec4f_t v2)
{
    return vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

// Vec4_t vec4_sub(Vec4_t v1, Vec4_t v2)
// {
//     return vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
// }

// Vec4_t vec4_scale(Vec4_t v, float scalar)
// {
//     return vec4(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
// }

// float vec4_dot(Vec4_t a, Vec4_t b)
// {
//     return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
// }

// float vec4_len(Vec4_t v)
// {
//     return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
// }

// Vec4_t vec4_norm(Vec4_t v)
// {
//     float length = vec4_len(v);
//     if (length == 0.f) return vec4(0, 0, 0, 0);

//     return vec4_scale(v, 1.f / length);
// }

// Vec4_t vec4_lerp(Vec4_t a, Vec4_t b, float t)
// {
//     t = fmaxf(0.f, fminf(t, 1.f));

//     return vec4(
//         a.x + t * (b.x - a.x),
//         a.y + t * (b.y - a.y),
//         a.z + t * (b.z - a.z),
//         a.w + t * (b.w - a.w)
//     );
// }

// float vec4Angle(Vec4_t a, Vec4_t b)
// {
//     float lenA = vec4_len(a);
//     float lenB = vec4_len(b);

//     if (isnan(lenA) || isnan(lenB)
//         || lenA < FLT_EPSILON
//         || lenB < FLT_EPSILON)
//         return NAN;

//     float dot = vec4_dot(a, b);
//     float cosTheta = dot / (lenA * lenB);

//     cosTheta = fmaxf(-1.f, fminf(cosTheta, 1.f));

//     return acosf(cosTheta);
// }

// Vec4_t vec4_proj(Vec4_t a, Vec4_t b)
// {
//     float dotA = vec4_dot(a, b);
//     float dotB = vec4_dot(b, b);

//     float scale = dotA / dotB;
//     return vec4_scale(b, scale);
// }

// Vec4_t vec4_refl(Vec4_t v, Vec4_t normal)
// {
//     Vec4_t proj = vec4_proj(v, normal);
//     Vec4_t scal = vec4_scale(proj, 2.f);
//     Vec4_t rlt = vec4_sub(v, scal);
//     return rlt;
// }

// float vec4_dist(Vec4_t a, Vec4_t b)
// {
//     Vec4_t vsub = vec4_sub(a, b);
//     float rlt = vec4_len(vsub);
//     return rlt;
// }
