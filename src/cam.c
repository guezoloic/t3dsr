#include "math/mat4.h"
#include "math/vec4.h"

#include <math.h>

Mat4f_t perspCam(float fov, float asp, float near, float far)
{
    const float t = 1.f / tanf(fov * 0.5f * (M_PI/180.f));
    const float fn = far - near;
    const float persp[16] = 
    {
        t/asp,  0.f, 0.f,                               0.f, 
        0.f,    t,   0.f,                               0.f,
        0.f,    0.f, -(far + near) / fn,                 -1.f,
        0.f,    0.f, -(2.f * far * near) / fn,           0.f
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

// first off, apply to your vec normCoord fn
Vec4f_t* viewport_r(Vec4f_t* vec, float width, float height)
{
    vec->x = (vec->x + 1.f) * 0.5f * width;
    vec->y = (1.f - vec->y) * 0.5f * height;
    return vec;
}

Mat4f_t lookAt(Vec4f_t* eye, Vec4f_t* center, Vec4f_t* up)
{
    Vec4f_t f = vec4f_sub(*center, *eye);
    f.data[3] = 0.f;
    f = vec4f_scale(f, 1.f / vec4f_len(f));

    Vec4f_t s = vec4f_cross(f, *up);
    s.data[3] = 0.f;
    s = vec4f_scale(s, 1.f / vec4f_len(s));

    Vec4f_t u = vec4f_cross(s, f);
    u.data[3] = 0.f;

    float m[16] = {
        s.x,  s.y,  s.z,  -vec4f_dot(s, *eye),
        u.x,  u.y,  u.z,  -vec4f_dot(u, *eye),
        -f.x, -f.y, -f.z, -vec4f_dot(f, *eye),
        0.f,   0.f,  0.f,                 1.f
    };

    return mat4f_from_array(m);
}

Mat4f_t rotateX(float angle)
{
    Mat4f_t r = mat4f_identity();
    float c = cosf(angle);
    float s = sinf(angle);

    r.m[5] = c;
    r.m[6] = -s;
    r.m[9] = s;
    r.m[10] = c;

    return r;
}

Mat4f_t rotateY(float angle)
{
    Mat4f_t r = mat4f_identity();
    float c = cosf(angle);
    float s = sinf(angle);

    r.m[0] = c;
    r.m[2] = s;
    r.m[8] = -s;
    r.m[10] = c;

    return r;
}

Mat4f_t rotateZ(float angle)
{
    Mat4f_t r = mat4f_identity();
    float c = cosf(angle);
    float s = sinf(angle);

    r.m[0] = c;
    r.m[1] = -s;
    r.m[4] = s;
    r.m[5] = c;

    return r;
}