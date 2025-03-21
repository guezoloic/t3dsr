#include "math/vector.h"

Vec3 Vec4ToVec3(Vec4 v)
{
    return vec3(v.x, v.y, v.z);
}

Vec4 Vec3ToVec4(Vec3 v) 
{
    return vec4(v.x, v.y, v.z, 0);
}
