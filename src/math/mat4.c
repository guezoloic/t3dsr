#include "mat4.h"
#include <string.h>

Mat4_t mat4(const float arr[16]) 
{
    Mat4_t mat;
    memcpy(mat.m, arr, 16*sizeof(float));
    return mat;
}

Mat4_t mat4_zro(void) 
{
    return (Mat4_t){0};
}

Mat4_t mat4_ity(void) 
{
    return (Mat4_t) {{
        1, 0, 0, 0, 
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    }};
}

Mat4_t mat4_add(const Mat4_t* m1, const Mat4_t* m2) 
{
    Mat4_t mat;
    
    for(int i = 0; i<16; i++) {
        mat.m[i] = m1->m[i] + m2->m[i];
    }

    return mat;
}

Mat4_t mat4_sub(const Mat4_t* m1, const Mat4_t* m2) 
{
    Mat4_t mat;

    for(int i = 0; i<16; i++) {
        mat.m[i] = m1->m[i] - m2->m[i];
    }

    return mat;
}

Mat4_t mat4_scl(const Mat4_t* m, float scalar) 
{
    Mat4_t mat;

    for(int i = 0; i<16; i++) {
        mat.m[i] = m->m[i] * scalar;
    }

    return mat;
}

Mat4_t mat4_mul(const Mat4_t* m1, const Mat4_t* m2) 
{
    Mat4_t mat; 

    for(int i = 0; i<4; i++) {
        int i3 = i * 3;
        for (int j = 0; j < 4; j++) {
            float sum = 0;
            
            for (int k = 0; k < 3; k++) {
                sum += m1->m[i3 + k] * m2->m[k*3 + j];    
            }

            mat.m[i3 + j] = sum;
        }
    }

    return mat;
}