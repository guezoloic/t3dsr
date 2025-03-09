#include <math/vector3.h>
#include <stdlib.h>

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
    if (!a || !b) return 0;
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

float vec3Len(Vec3* v)
{
    if (!v) return 0;
    return sqrtf(vec3Dot(v, v));
}

Vec3* vec3Norm(Vec3* v)
{
    if (!v) return NULL;

    float length = vec3Len(v);
    if (length == 0.f) return vec3(0, 0, 0);

    float invLength = 1.f / length;
    return vec3(v->x * invLength, v->y * invLength, v->z * invLength);
}

Vec3* vec3Lerp(Vec3* a, Vec3* b, float t)
{
    if (t < 0.f) t = 0.f;
    if (t > 1.f) t = 1.f;

    return vec3(
        a->x + t * (b->x - a->x),
        a->y + t * (b->y - a->y),
        a->z + t * (b->z - a->z)
    );
}

Vec3* vec3Cross(Vec3* a, Vec3* b) 
{
    return vec3(
        a->y * b->z - a->z * b->y, 
        a->z * b->x - a->x * b->z, 
        a->x * b->y - a->y * b->x
    );
}

float vec3Angle(Vec3* a, Vec3* b)
{
    float dot = vec3Dot(a, b);
    float lenA = vec3Len(a);    
    float lenB = vec3Len(b);
    return acosf(dot / (lenA * lenB)); 
}

Vec3* vec3Proj(Vec3* a, Vec3* b)
{
    float dotAB = vec3Dot(a, b);
    float lenB2 = vec3Dot(b, b);
    float scale = dotAB / lenB2;
    return vec3(b->x * scale, b->y * scale, b->z * scale);
}

Vec3* vec3Refl(Vec3* v, Vec3* normal)
{
    Vec3* proj = vec3Proj(v, normal);
    return vec3Sub(v, vec3Scale(proj, 2.f)); 
}

float vec3Dist(Vec3* a, Vec3* b)
{
    return vec3Len(vec3Sub(a, b));
}

Vec3* vec3Rotate(Vec3* v, Vec3* axis, float angle)
{
    axis = vec3Norm(axis);
    float dot = vec3Dot(axis, v);
    Vec3* cross = vec3Cross(axis, v);
    
    return vec3Add(
        vec3Add(
            vec3Scale(v, cosf(angle)), 
            vec3Scale(cross, sinf(angle))
        ),
        vec3Scale(axis, dot * (1 - cosf(angle)))
    );
}

void vec3Free(Vec3* v) 
{
    if (v) free(v);
}