#include <stdio.h>
#include "math/mat4.h"

int main(void) 
{
    float arr[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    Mat4f_t mat1 =  mat4f_from_array(arr);
    Mat4f_t mat2 =  mat4f_scalar(1);
    Mat4f_t mat3 =  mat4f_zero();
    Mat4f_t mat4 =  mat4f_identity();
    printf("%f", arr[1]);
    return 0;
}
