#include "test_vec.h"

#include <stdio.h>

int main() {

    // --- Vector3 ---
    
    void addVector3_test();
    void subVector3_test();
    void scaleVector3_test();
    void dotVector3_test();
    void lenVector3_test();
    void normVector3_test();
    void lerpVector3_test();
    void anglVector3_test();
    void projVector3_test();
    void reflVector3_test();
    void distVector3_test();
    printf("All Vector3 tests succeeded\n");

    // --- Vector4 ---
    
    void addVector4_test();
    void subVector4_test();
    void scaleVector4_test();
    void dotVector4_test();
    void lenVector4_test();
    void normVector4_test();
    void lerpVector4_test();
    void anglVector4_test();
    void projVector4_test();
    void reflVector4_test();
    void distVector4_test();
    printf("All Vector4 tests succeeded\n");

    printf("All tests succeeded\n");
    return 0;
}