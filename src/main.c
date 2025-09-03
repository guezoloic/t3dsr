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

    // xyz = [-1; 1]
    Vec4f_t vec = vec4f(0.f, 0.f, -1.f, 1.f);
    Mat4f_t proj = perspCam(fov, aspect, near, far);

    Vec4f_t v_clip = mat4f_mul_vec4f(proj, vec);

    normCoord_r(&v_clip);
    viewport_r(&v_clip, width, height);
    
    initCanvas(width, height);
    drawCanvas(v_clip, width, height);
    renderCanvas(width, height);
    printf("%f", v_clip.z);
    return 0;
}