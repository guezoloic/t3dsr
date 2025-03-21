#include "test_vec.h"
#include "unity/unity.h"

#include <stdio.h>

void setUp() {}
void tearDown() {}

int main() {

    UNITY_BEGIN();

    runVector3_test();
    runVector4_test();

    UNITY_END();
    
    return 0;
}