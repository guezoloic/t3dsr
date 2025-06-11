#include <stdio.h>
#include "math/vec4.h"

int main(void) 
{
    Vec4f_t vec = vec4(1.f, 2.f, 8.f, 4.f);
    printf("%f %f %f %f\n", vec.x, vec.y, vec.z, vec.w);
    
    Vec4f_t vec2 = vec4f_clone(&vec);
    printf("%f %f %f %f\n", vec2.x, vec2.y, vec2.z, vec2.w);
    
    Vec4f_t vec3 = vec4f_add(vec, vec2);
    printf("%f %f %f %f\n", vec3.x, vec3.y, vec3.z, vec3.w);
    
    Vec4f_t vec4 = vec4f_sub(vec, vec3);
    printf("%f %f %f %f\n", vec4.x, vec4.y, vec4.z, vec4.w);
    
    Vec4f_t vec5 = vec4f_scale(vec4, 5.f);
    printf("%f %f %f %f\n", vec5.x, vec5.y, vec5.z, vec5.w);
}
