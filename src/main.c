#include <stdio.h>
#include "cam.h"
#include "math/vec4.h"

Vec4f_t mat4f_mul_vec4f(const Mat4f_t mat, Vec4f_t v)
{
    Vec4f_t out;
    for (int i = 0; i < 4; i++)
    {
        out.data[i] = 0.f;
        for (int j = 0; j < 4; j++)
            out.data[i] += mat.m[i*4 + j] * v.data[j];
    }
    return out;
}

int main(int argc, const char** argv)
{
    const float fov = 60;
    const float width = 1000, height = 800;
    const float near = 0.1, far = 1000;

    const float aspect = width / height;

    // xyz = [-1, 1]
    Vec4f_t vec = vec4f(0.f, 0.f, -1.f, 1.f);
    Mat4f_t proj = perspCam(fov, aspect, near, far);

    Vec4f_t v_clip = mat4f_mul_vec4f(proj, vec);

    normCoord_r(&v_clip);
    viewport_r(&v_clip, width, height);

    printf("Screen coordinates: x = %f, y = %f, z = %f\n",
        v_clip.x, v_clip.y, v_clip.z);

    return 0;
}