#include "math/mv4.h"
#include "draw.h"
#include "cam.h"
#include "sleepms.h"


Vec4f_t cubeVertices[8] = {
    { -1,-1,-1,1 }, { 1,-1,-1,1 },
    { 1, 1,-1,1 }, { -1, 1,-1,1 },
    { -1,-1, 1,1 }, { 1,-1, 1,1 },
    { 1, 1, 1,1 }, { -1, 1, 1,1 }
};

int cubeEdges[12][2] = {
    {0,1}, {1,2}, {2,3}, {3,0},
    {4,5}, {5,6}, {6,7}, {7,4},
    {0,4}, {1,5}, {2,6}, {3,7}
};

int main() 
{
    const float fov = 60.f;
    const int width = 120, height = 40;
    const float near = 0.1f, far = 1000.f;
    const float aspect = (float)width / (float)height;

    Vec4f_t eye = vec4f(0.f, 0.f, 15.f, 1.f);
    Vec4f_t center = vec4f(0.f, 0.f, 0.f, 1.f);
    Vec4f_t up = vec4f(0.f, 1.f, 0.f, 0.f);

    Mat4f_t view = lookAt(&eye, &center, &up);
    Mat4f_t proj = perspCam(fov, aspect, near, far);

    float angle = 0.f;

    initCanvas(width, height);
    
    while (1) {
        clearCanvas(width, height);

        Mat4f_t rx = rotateX(angle);
        Mat4f_t ry = rotateY(angle);
        Mat4f_t rz = rotateZ(angle);

        mat4f_mul_r(&ry, &rx);
        mat4f_mul_r(&rz, &ry);

        Mat4f_t model = rz;
        angle += 0.05f;

        Vec4f_t projected[8];
        for(int i=0;i<8;i++) {
            Vec4f_t v = mat4f_mul_vec4f(model, cubeVertices[i]); // rotation
            projected[i] = mat4f_mul_vec4f(proj, mat4f_mul_vec4f(view, v)); // model * view * proj
            
            normCoord_r(&projected[i]);
            float depth = (v.z + 1.f) * 0.5f; // zbuffer

            viewport_r(&projected[i], width, height);
            projected[i].z = depth;
        }
    
        for(int i=0;i<12;i++) {
            int a = cubeEdges[i][0];
            int b = cubeEdges[i][1];
            drawLine(projected[a], projected[b], width, height);
        }
        renderCanvas(width, height);
        sleep_ms(100);
    }

    freeCanvas();
    return 0;
}