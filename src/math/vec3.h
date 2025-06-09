#ifndef VEC3__H
#define VEC3__H

typedef struct 
{
    float x, y, z;
} Vec3_t;

Vec3_t vec3(float x, float y, float z);

Vec3_t vec3_add(Vec3_t v1, Vec3_t v2);

Vec3_t vec3_sub(Vec3_t v1, Vec3_t v2);

Vec3_t vec3_scale(Vec3_t v, float scalar);

float vec3_dot(Vec3_t a, Vec3_t b);

float vec3_len(Vec3_t v);

Vec3_t vec3_norm(Vec3_t v);

Vec3_t vec3_lerp(Vec3_t a, Vec3_t b, float t);

Vec3_t vec3_cross(Vec3_t a, Vec3_t b);

float vec3_angle(Vec3_t a, Vec3_t b);

Vec3_t vec3_proj(Vec3_t a, Vec3_t b);

Vec3_t vec3_refl(Vec3_t v, Vec3_t normal);

float vec3_rist(Vec3_t a, Vec3_t b);

Vec3_t vec3_rotate(Vec3_t v, Vec3_t axis, float angle);

#endif // VEC3__H
