#include "math/vector3.h"
#include <stdio.h>

#define printVector3(v) { printf("(%f, %f, %f)", v.x, v.y, v.z); }

int main() 
{   
    Vec3 vec = vec3(1, 1, 1);
    Vec3 val = vec3_add(vec, vec3(1, 2, 3));
    printVector3(val);
    return 0;
}