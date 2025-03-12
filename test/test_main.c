#include "test_vec.h"

#include <stdio.h>

int main() {

    // --- Vector3 ---
    
    addVector3_test();
    subVector3_test();
    scaleVector3_test();
    dotVector3_test();
    lenVector3_test();
    normVector3_test();
    lerpVector3_test();
    anglVector3_test();
    projVector3_test();
    reflVector3_test();
    distVector3_test();
    printf("All Vector3 tests succeeded\n");

    // --- Vector4 ---
    
    addVector4_test();
    subVector4_test();
    scaleVector4_test();
    dotVector4_test();
    lenVector4_test();
    normVector4_test();
    lerpVector4_test();
    anglVector4_test();
    projVector4_test();
    reflVector4_test();
    distVector4_test();
    printf("All Vector4 tests succeeded\n");

    printf("All tests succeeded\n");
    return 0;
}