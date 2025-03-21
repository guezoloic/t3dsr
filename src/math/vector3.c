#include <math.h>
#include <stdlib.h>
#include <float.h>

#include "math/vector3.h"

Vec3 vec3(float x, float y, float z) 
{
    return (Vec3) {x, y, z};
}

Vec3 vec3Add(Vec3 v1, Vec3 v2)
{
    return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec3 vec3Sub(Vec3 v1, Vec3 v2)
{
    return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vec3 vec3Scale(Vec3 v, float scalar)
{
    return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

float vec3Dot(Vec3 a, Vec3 b) 
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vec3Len(Vec3 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 vec3Norm(Vec3 v)
{

    float length = vec3Len(v);
    if (length == 0.f) return vec3(0, 0, 0);

    return vec3Scale(v, 1.f / length);
}

Vec3 vec3Lerp(Vec3 a, Vec3 b, float t)
{
    t = fmaxf(0.f, fminf(t, 1.f));
    return vec3(
        a.x + t * (b.x - a.x),
        a.y + t * (b.y - a.y),
        a.z + t * (b.z - a.z)
    );
}

Vec3 vec3Cross(Vec3 a, Vec3 b) 
{
    return vec3(
        a.y * b.z - a.z * b.y, 
        a.z * b.x - a.x * b.z, 
        a.x * b.y - a.y * b.x
    );
}

float vec3Angle(Vec3 a, Vec3 b)
{
    float lenA = vec3Len(a);    
    float lenB = vec3Len(b);

    if (isnan(lenA) || isnan(lenB) 
        || lenA < FLT_EPSILON
        || lenB < FLT_EPSILON) 
        return NAN;

    float dot = vec3Dot(a, b);
    float cosTheta = dot / (lenA * lenB);

    cosTheta = fmaxf(-1.f, fminf(cosTheta, 1.f));

    return acosf(cosTheta); 
}

Vec3 vec3Proj(Vec3 a, Vec3 b)
{
    float dotA = vec3Dot(a, b);
    float dotB = vec3Dot(b, b);

    float scale = dotA / dotB;
    return vec3Scale(b, scale);
}

Vec3 vec3Refl(Vec3 v, Vec3 normal)
{
    Vec3 proj = vec3Proj(v, normal);
    Vec3 scal = vec3Scale(proj, 2.f);
    Vec3 rlt = vec3Sub(v, scal);
    return rlt; 
}

float vec3Dist(Vec3 a, Vec3 b)
{
    Vec3 vsub = vec3Sub(a, b);

    float rlt = vec3Len(vsub);
    return rlt;
}

Vec3 vec3Rotate(Vec3 v, Vec3 axis, float angle) 
{
    Vec3 normAxis = vec3Norm(axis);

    float dot = vec3Dot(normAxis, v);
    Vec3 cross = vec3Cross(normAxis, v);
    
    Vec3 vscal = vec3Scale(v, cosf(angle));
    Vec3 cscal = vec3Scale(cross, sinf(angle));

    Vec3 add = vec3Add(vscal, cscal);

    Vec3 dscal = vec3Scale(normAxis, dot * (1 - cosf(angle)));

    Vec3 rlt = vec3Add(add, dscal);

    return rlt;
}   