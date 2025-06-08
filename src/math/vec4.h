#ifndef VECTOR4_H
#define VECTOR4_H

typedef struct 
{
    float x, y, z, w;
} Vec4_t;

Vec4_t vec4(float x, float y, float z, float w);

Vec4_t vec4_add(Vec4_t v1, Vec4_t v2);

Vec4_t vec4_sub(Vec4_t v1, Vec4_t v2);

Vec4_t vec4_scale(Vec4_t v, float scalar);

float vec4_dot(Vec4_t a, Vec4_t b);

float vec4_len(Vec4_t v);

Vec4_t vec4_norm(Vec4_t v);

Vec4_t vec4_lerp(Vec4_t a, Vec4_t b, float t);

float vec4_angle(Vec4_t a, Vec4_t b);

Vec4_t vec4_proj(Vec4_t a, Vec4_t b);

Vec4_t vec4_refl(Vec4_t v, Vec4_t normal);

float vec4_dist(Vec4_t a, Vec4_t b);

#endif // VECTOR4_H