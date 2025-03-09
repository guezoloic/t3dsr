#ifndef VECTOR4_H
#define VECTOR4_H

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec4;

Vec4* vec4(float x, float y, float z, float w);
Vec4* vec4Add(Vec4* v1, Vec4* v2);
Vec4* vec4Sub(Vec4* v1, Vec4* v2);
Vec4* vec4Scale(Vec4* v, float scalar);
float vec4Dot(Vec4* a, Vec4* b);
float vec4Len(Vec4* v);
Vec4* vec4Norm(Vec4* v);
Vec4* vec4Lerp(Vec4* a, Vec4* b, float t);
float vec4Angle(Vec4* a, Vec4* b);
Vec4* vec4Proj(Vec4* a, Vec4* b);
Vec4* vec4Refl(Vec4* v, Vec4* normal);
float vec4Dist(Vec4* a, Vec4* b);
void vec4Free(Vec4* v);


#endif // VECTOR4_H