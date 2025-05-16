#include <math.h>
#include <stdlib.h>
#include <float.h>

#include "vec4.h"

inline Vec4 vec4(float x, float y, float z, float w) 
{
    return (Vec4) {x, y, z, w};
}

Vec4 vec4_add(Vec4 v1, Vec4 v2)
{
    return vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

Vec4 vec4_sub(Vec4 v1, Vec4 v2)
{
    return vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

Vec4 vec4_scale(Vec4 v, float scalar)
{
    return vec4(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
}

float vec4_dot(Vec4 a, Vec4 b) 
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float vec4_len(Vec4 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

Vec4 vec4_norm(Vec4 v)
{
    float length = vec4_len(v);
    if (length == 0.f) return vec4(0, 0, 0, 0);

    return vec4_scale(v, 1.f / length);
}

Vec4 vec4_lerp(Vec4 a, Vec4 b, float t)
{
    t = fmaxf(0.f, fminf(t, 1.f));

    return vec4(
        a.x + t * (b.x - a.x),
        a.y + t * (b.y - a.y),
        a.z + t * (b.z - a.z),
        a.w + t * (b.w - a.w)
    );
}

float vec4Angle(Vec4 a, Vec4 b)
{
    float lenA = vec4_len(a);    
    float lenB = vec4_len(b);

    if (isnan(lenA) || isnan(lenB) 
        || lenA < FLT_EPSILON
        || lenB < FLT_EPSILON) 
        return NAN;

    float dot = vec4_dot(a, b);
    float cosTheta = dot / (lenA * lenB);

    cosTheta = fmaxf(-1.f, fminf(cosTheta, 1.f));

    return acosf(cosTheta); 
}

Vec4 vec4_proj(Vec4 a, Vec4 b)
{
    float dotA = vec4_dot(a, b);
    float dotB = vec4_dot(b, b);

    float scale = dotA / dotB;
    return vec4_scale(b, scale);
}

Vec4 vec4_refl(Vec4 v, Vec4 normal)
{
    Vec4 proj = vec4_proj(v, normal);
    Vec4 scal = vec4_scale(proj, 2.f);
    Vec4 rlt = vec4_sub(v, scal);
    return rlt; 
}

float vec4_dist(Vec4 a, Vec4 b)
{
    Vec4 vsub = vec4_sub(a, b);
    float rlt = vec4_len(vsub);
    return rlt;
}