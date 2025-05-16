#include <math.h>
#include <stdlib.h>
#include <float.h>

#include "vector3.h"

inline Vec3 vec3(float x, float y, float z) 
{
    return (Vec3) {x, y, z};
}

Vec3 vec3_add(Vec3 v1, Vec3 v2)
{
    return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec3 vec3_sub(Vec3 v1, Vec3 v2)
{
    return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vec3 vec3_scale(Vec3 v, float scalar)
{
    return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

Vec3 vec3_mul(Vec3 v1, Vec3 v2)
{
    return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

float vec3_dot(Vec3 a, Vec3 b) 
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vec3_len(Vec3 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 vec3_norm(Vec3 v)
{

    float length = vec3_len(v);
    if (length == 0.f) return vec3(0, 0, 0);

    return vec3_scale(v, 1.f / length);
}

Vec3 vec3_lerp(Vec3 a, Vec3 b, float t)
{
    t = fmaxf(0.f, fminf(t, 1.f));
    return vec3(
        a.x + t * (b.x - a.x),
        a.y + t * (b.y - a.y),
        a.z + t * (b.z - a.z)
    );
}

Vec3 vec3_cross(Vec3 a, Vec3 b) 
{
    return vec3(
        a.y * b.z - a.z * b.y, 
        a.z * b.x - a.x * b.z, 
        a.x * b.y - a.y * b.x
    );
}

float vec3_angle(Vec3 a, Vec3 b)
{
    float lenA = vec3_len(a);    
    float lenB = vec3_len(b);

    if (lenA < FLT_EPSILON || lenB < FLT_EPSILON) 
        return NAN;

    return acosf(fmaxf(-1.f, 
        fminf(vec3_dot(a, b) / (lenA * lenB), 1.f))); 
}

Vec3 vec3_proj(Vec3 a, Vec3 b)
{
    return vec3_scale(b, 
        vec3_dot(a, b) / vec3_dot(b, b));
}

Vec3 vec3_refl(Vec3 v, Vec3 normal)
{
    return vec3_sub(v, vec3_scale(vec3_proj(v, normal), 2.f)); 
}

float vec3_dist(Vec3 a, Vec3 b)
{
    return vec3_len(vec3_sub(a, b));
}

Vec3 vec3_rotate(Vec3 v, Vec3 axis, float angle) 
{
    Vec3 normAxis = vec3_norm(axis);

    Vec3 rlt = vec3_add(
        vec3_add(
            vec3_scale(v, cosf(angle)), 
            vec3_scale(vec3_cross(normAxis, v), sinf(angle))
        ), 
        vec3_scale(normAxis, vec3_dot(normAxis, v) * (1 - cosf(angle)))
    );

    return rlt;
}   