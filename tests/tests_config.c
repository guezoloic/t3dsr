#include "../src/math/mconfig.h"
#include <stdio.h>

void config() {
    #if defined (SIMD_X86)
        printf("SIMD enabled: X86\n");
    #elif defined (SIMD_ARCH)
        printf("SIMD enabled: ARCH\n");
    #else
        printf("SIMD disabled\n");
    #endif
}

int main() {
    config();
}