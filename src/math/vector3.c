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