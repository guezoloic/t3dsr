#include <math.h>
#include <stdlib.h>

#include "math/vector4.h"

Vec4* vec4(float x, float y, float z, float w) 
{
    Vec4* vec = (Vec4*)malloc(sizeof(Vec4));
    if (!vec) return NULL;

    vec->x = x;
    vec->y = y;
    vec->z = z;
    vec->w = w;

    return vec;
}

Vec4* vec4Add(Vec4* v1, Vec4* v2)
{
    if (!v1 || !v2) return NULL;
    return vec4(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z, v1->w + v2->w);
}

Vec4* vec4Sub(Vec4* v1, Vec4* v2)
{
    if (!v1 || !v2) return NULL;
    return vec4(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z, v1->w - v2->w);
}

Vec4* vec4Scale(Vec4* v, float scalar)
{
    if (!v) return NULL;
    return vec4(v->x * scalar, v->y * scalar, v->z * scalar, v->w * scalar);
}

float vec4Dot(Vec4* a, Vec4* b) 
{
    if (!a || !b) return 0;
    return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

float vec4Len(Vec4* v)
{
    if (!v) return 0;
    return sqrtf(vec4Dot(v, v));
}

Vec4* vec4Norm(Vec4* v)
{
    if (!v) return NULL;

    float length = vec4Len(v);
    if (length == 0.f) return vec4(0, 0, 0, 0);

    float invLength = 1.f / length;
    return vec4Scale(v, invLength);
}

Vec4* vec4Lerp(Vec4* a, Vec4* b, float t)
{
    if (!a || !b) return NULL;
    if (t < 0.f) t = 0.f;
    if (t > 1.f) t = 1.f;

    return vec4(
        a->x + t * (b->x - a->x),
        a->y + t * (b->y - a->y),
        a->z + t * (b->z - a->z),
        a->w + t * (b->w - a->w)
    );
}

float vec4Angle(Vec4* a, Vec4* b)
{
    float dot = vec4Dot(a, b);
    float lenA = vec4Len(a);    
    float lenB = vec4Len(b);
    return acosf(dot / (lenA * lenB)); 
}

Vec4* vec4Proj(Vec4* a, Vec4* b)
{
    if (!a || !b) return NULL;
    float dotAB = vec4Dot(a, b);
    float lenB2 = vec4Dot(b, b);
    float scale = dotAB / lenB2;
    return vec4Scale(b, scale); 
}

Vec4* vec4Refl(Vec4* v, Vec4* normal)
{
    if (!v || !normal) return NULL;
    Vec4* proj = vec4Proj(v, normal);
    Vec4* scal = vec4Scale(proj, 2.f);
    Vec4* rlt = vec4Sub(v, scal);
    vec4Free(proj);
    vec4Free(scal);
    return rlt; 
}

float vec4Dist(Vec4* a, Vec4* b)
{
    Vec4* vsub = vec4Sub(a, b);
    float rlt = vec4Len(vsub);
    vec4Free(vsub);
    return rlt;
}

void vec4Free(Vec4* v) 
{
    if (v) free(v);
}