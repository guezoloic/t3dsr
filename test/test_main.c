#include "test_vec3.h"

#include <stdio.h>

int main() {
    addVector3_test();
    subVector3_test();
    scaleVector3_test();
    dotVector3_test();
    lenVector3_test();
    normVector3_test();
    distVector3_test();
    printf("All Vector3 tests succeeded\n");
    return 0;
}