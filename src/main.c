#include <stdio.h>
#include "cam.h"
#include "draw.h"
#include "math/mv4.h"

int main(int argc, const char** argv)
{
    const float fov = 60;
    const float width = 80, height = 30;
    const float near = 0.1, far = 1000;

    const float aspect = width / height;
    
    Mat4f_t proj = perspCam(fov, aspect, near, far);

    // xyz = [-1; 1]
    Vec4f_t vec0 = vec4f(0.f, 0.f, -1.f, 1.f);
    Vec4f_t v_clip0 = mat4f_mul_vec4f(proj, vec0);
    normCoord_r(&v_clip0);
    viewport_r(&v_clip0, width, height);

    Vec4f_t vec1 = vec4f(0.f, 0.6f, -1.f, 1.f);
    Vec4f_t v_clip1 = mat4f_mul_vec4f(proj, vec1);
    normCoord_r(&v_clip1);
    viewport_r(&v_clip1, width, height);
    
    initCanvas(width, height);
    // drawCanvas(v_clip, width, height);
    drawLine(v_clip0, v_clip1, width, height);
    renderCanvas(width, height);

    freeCanvas();
    return 0;
}