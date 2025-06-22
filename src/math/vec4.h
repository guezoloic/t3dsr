#ifndef VECTOR4_H
#define VECTOR4_H

#include "mconfig.h"

// must be aligned by 16 Bytes (less instruction executed for SSE)
typedef union
{
    struct { float x, y, z, w; };
    float data[4];
} ALIGN16 Vec4f_t;

Vec4f_t vec4f_from_array(const float *__restrict val);
Vec4f_t vec4f(float x, float y, float z, float w);
// (f, f, f, f)
Vec4f_t vec4f_scalar(float f);
// (0, 0, 0, 0)
Vec4f_t vec4f_zero(void);

inline static Vec4f_t vec4f_clone(const Vec4f_t *__restrict v)
{
    return *v;
}

Vec4f_t vec4f_add_r(Vec4f_t *__restrict out, Vec4f_t a);
Vec4f_t vec4f_add(Vec4f_t a, Vec4f_t b);

Vec4f_t vec4f_sub_r(Vec4f_t *__restrict out, Vec4f_t a);
Vec4f_t vec4f_sub(Vec4f_t a, Vec4f_t b);

Vec4f_t vec4f_scale_r(Vec4f_t *__restrict out, float scale);
Vec4f_t vec4f_scale(Vec4f_t a, float scale);

float vec4f_dot(Vec4f_t a, Vec4f_t b);

inline static float vec4f_len(Vec4f_t v)
{
    return sqrtf(vec4f_dot(v, v));
}

Vec4f_t vec4f_norm_r(Vec4f_t *__restrict v);
Vec4f_t vec4f_norm(Vec4f_t v);

Vec4f_t vec4f_lerp_r(Vec4f_t *__restrict a, Vec4f_t b, float t);
Vec4f_t vec4f_lerp(Vec4f_t a, Vec4f_t b, float t);

float vec4f_angle(Vec4f_t a, Vec4f_t b);

Vec4f_t vec4f_proj(Vec4f_t a, Vec4f_t b);

Vec4f_t vec4f_refl(Vec4f_t v, Vec4f_t normal);

float vec4f_dist(Vec4f_t a, Vec4f_t b);

#endif // VECTOR4_H
