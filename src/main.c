#include <stdio.h>
#include "math/vec4.h"

int main(void) 
{   
    Vec4f_t vec = vec4(1.f, 2, 3, 4);
    float vec_array[4] = {1, 2, 3, 4};

    vec4f_add_r(&vec, vec4f_from_array(vec_array));
    printf("%f\n", vec.data[1]);
} 