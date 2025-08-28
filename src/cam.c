#include "math/mat4.h"
#include "math/vec3.h"
#include "math/vec4.h"

#include <math.h>

Mat4f_t perspCam(float fov, float asp, float near, float far)
{
    const float t = 1 / tanf(fov/2);
    const float persp[16] = 
    {
        t/asp,  0.f, 0.f,                               0.f, 
        0.f,    t,   0.f,                               0.f,
        0.f,    0.f, (far + near) / (far - near),       -1.f,
        0.f,    0.f, (2.f * far * near) / (far - near), 0.f
    };

    return mat4f_from_array(persp);
}

Vec4f_t* normCoord_r(Vec4f_t* vec)
{
    float inv_w = 1.f / vec->w;
    vec->x *= inv_w;
    vec->y *= inv_w;
    vec->z *= inv_w;
    return vec;
}

// Vec3f_t 