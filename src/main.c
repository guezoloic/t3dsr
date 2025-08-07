#include <stdio.h>
#include "math/mat4.h"

int main(void) 
{
    float arr[16] = {
        1, 2, 3, 4, 
        5, 6, 7, 8, 
        9, 10, 11, 12, 
        13, 14, 15, 16
    };

    Mat4f_t mat1 =  mat4f_from_array(arr);
    Mat4f_t* mat_tps = mat4f_tpo_r(&mat1);

    printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n", 
        mat1.m[0],
        mat1.m[1],
        mat1.m[2],
        mat1.m[3],
        mat1.m[4],
        mat1.m[5],
        mat1.m[6],
        mat1.m[7],
        mat1.m[8],
        mat1.m[9],
        mat1.m[10],
        mat1.m[11],
        mat1.m[12],
        mat1.m[13],
        mat1.m[14],
        mat1.m[15]
    
    );
    return 0;
}
