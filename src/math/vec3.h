//
//  vec3.h
//  main
//
//  Created by Loïc GUEZO on 21/06/2025.
//

#ifndef vec3_h
#define vec3_h

#include "mconfig.h"

typedef union
{
    struct {float x, y, z; };
    float data[4];
} ALIGN16 Vec3f_t;

Vec3f_t vec3f_from_array(const float *__restrict val);
Vec3f_t vec3f(float x, float y, float z);
// (f, f, f)
Vec3f_t vec3f_scalar(float f);
// (0, 0, 0)
Vec3f_t vec3f_zero(void);

inline static Vec3f_t vec3f_clone(const Vec3f_t *__restrict v)
{
    return *v;
}

Vec3f_t* vec3f_add_r(Vec3f_t *__restrict out, Vec3f_t a);
Vec3f_t vec3f_add(Vec3f_t a, Vec3f_t b);

Vec3f_t* vec3f_sub_r(Vec3f_t *__restrict out, Vec3f_t a);
Vec3f_t vec3f_sub(Vec3f_t a, Vec3f_t b);

Vec3f_t* vec3f_scale_r(Vec3f_t *__restrict out, float scale);
Vec3f_t vec3f_scale(Vec3f_t a, float scale);

float vec3f_dot(Vec3f_t a, Vec3f_t b);

inline static float vec3f_len(Vec3f_t v)
{
    return sqrtf(vec3f_dot(v, v));
}

Vec3f_t* vec3f_norm_r(Vec3f_t *__restrict v);
Vec3f_t vec3f_norm(Vec3f_t v);

Vec3f_t* vec3f_lerp_r(Vec3f_t *__restrict a, Vec3f_t b, float t);
Vec3f_t vec3f_lerp(Vec3f_t a, Vec3f_t b, float t);

float vec3f_angle(Vec3f_t a, Vec3f_t b);

Vec3f_t vec3f_proj(Vec3f_t a, Vec3f_t b);

Vec3f_t vec3f_refl(Vec3f_t v, Vec3f_t normal);

float vec3f_dist(Vec3f_t a, Vec3f_t b);

#endif /* vec3_h */
