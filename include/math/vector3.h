#ifndef VEC3_H
#define VEC3_H

typedef struct {
    float x, y, z;
} Vec3;

Vec3* vec3(float x, float y, float z);

Vec3* vec3Add(Vec3* v1, Vec3* v2);
Vec3* vec3Sub(Vec3* v1, Vec3* v2);
Vec3* vec3Scale(Vec3* v, float scalar);

float vec3Dot(Vec3* a, Vec3* b);
float vec3Len(Vec3* v);

Vec3* vec3Norm(Vec3* v);
Vec3* vec3Lerp(Vec3* a, Vec3* b, float t);
Vec3* vec3Cross(Vec3* a, Vec3* b);
float vec3Angle(Vec3* a, Vec3* b);
Vec3* vec3Proj(Vec3* a, Vec3* b);
Vec3* vec3Refl(Vec3* v, Vec3* normal);
float vec3Dist(Vec3* a, Vec3* b);
Vec3* vec3Rotate(Vec3* v, Vec3* axis, float angle);

void vec3Free(Vec3* v);

#endif // VEC3_H