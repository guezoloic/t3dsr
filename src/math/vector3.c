#include <math.h>
#include <stdlib.h>
#include <float.h>

#include <math/vector3.h>

Vec3* vec3(float x, float y, float z) 
{
    Vec3* vec = (Vec3*)malloc(sizeof(Vec3));
    if (!vec) return NULL;

    vec->x = x;
    vec->y = y;
    vec->z = z;

    return vec;
}

Vec3* vec3Add(Vec3* v1, Vec3* v2)
{
    if (!v1 || !v2) return NULL;
    return vec3(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}

Vec3* vec3Sub(Vec3* v1, Vec3* v2)
{
    if (!v1 || !v2) return NULL;
    return vec3(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}

Vec3* vec3Scale(Vec3* v, float scalar)
{
    if (!v) return NULL;
    return vec3(v->x * scalar, v->y * scalar, v->z * scalar);
}

float vec3Dot(Vec3* a, Vec3* b) 
{
    if (!a || !b) return NAN;
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

float vec3Len(Vec3* v)
{
    if (!v) return NAN;
    return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}

Vec3* vec3Norm(Vec3* v)
{
    if (!v) return NULL;

    float length = vec3Len(v);
    if (length == 0.f) return NULL;

    return vec3Scale(v, 1.f / length);
}

Vec3* vec3Lerp(Vec3* a, Vec3* b, float t)
{
    if (!a || !b) return NULL;
    t = fmaxf(0.f, fminf(t, 1.f));
    return vec3(
        a->x + t * (b->x - a->x),
        a->y + t * (b->y - a->y),
        a->z + t * (b->z - a->z)
    );
}

Vec3* vec3Cross(Vec3* a, Vec3* b) 
{
    if (!a || !b) return NULL;
    return vec3(
        a->y * b->z - a->z * b->y, 
        a->z * b->x - a->x * b->z, 
        a->x * b->y - a->y * b->x
    );
}

float vec3Angle(Vec3* a, Vec3* b)
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

Vec3* vec3Proj(Vec3* a, Vec3* b)
{
    if (!a || !b) return NULL;
    float dotA = vec3Dot(a, b);
    float dotB = vec3Dot(b, b);

    if (dotB < FLT_EPSILON) return NULL;

    float scale = dotA / dotB;
    return vec3Scale(b, scale);
}

Vec3* vec3Refl(Vec3* v, Vec3* normal)
{
    if (!v || !normal) return NULL;

    Vec3* proj = vec3Proj(v, normal);
    Vec3* scal = vec3Scale(proj, 2.f);
    Vec3* rlt = vec3Sub(v, scal);

    vec3Free(proj);
    vec3Free(scal);
    return rlt; 
}

float vec3Dist(Vec3* a, Vec3* b)
{
    if (!a || !b) return NAN;
    Vec3* vsub = vec3Sub(a, b);

    float rlt = vec3Len(vsub);
    vec3Free(vsub);
    return rlt;
}

Vec3* vec3Rotate(Vec3* v, Vec3* axis, float angle) 
{
    if (!v || !axis) return NULL;
    Vec3* normAxis = vec3Norm(axis);

    float dot = vec3Dot(normAxis, v);
    Vec3* cross = vec3Cross(normAxis, v);
    
    Vec3* vscal = vec3Scale(v, cosf(angle));
    Vec3* cscal = vec3Scale(cross, sinf(angle));

    Vec3* add = vec3Add(vscal, cscal);

    vec3Free(cross);

    Vec3* dscal = vec3Scale(normAxis, dot * (1 - cosf(angle)));
    vec3Free(normAxis);
    vec3Free(vscal);
    vec3Free(cscal);

    Vec3* rlt = vec3Add(add, dscal);

    vec3Free(add);
    vec3Free(dscal);

    return rlt;
}   

void vec3Free(Vec3* v) 
{
    free(v);
}