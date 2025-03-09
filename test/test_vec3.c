#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "math/vector3.h"
#include "test_vec3.h"

void printVector3(const Vec3* v) {
    if (!v) {
        printf("Vector is NULL\n");
        return;
    }
    printf("Vector: [%f, %f, %f]\n", v->x, v->y, v->z);
}

void addVector3_test() {
    printf("Test: Add Vector 3D\n");

    Vec3 a = {1.0f, 2.0f, 3.0f};
    Vec3 b = {4.0f, 5.0f, 6.0f};

    Vec3* result = vec3Add(&a, &b);
    printVector3(result);

    assert(result->x == 5.0f);
    assert(result->y == 7.0f);
    assert(result->z == 9.0f);

    vec3Free(result);
}

void subVector3_test() {
    printf("Test: Subtract Vector 3D\n");

    Vec3 a = {5.0f, 6.0f, 7.0f};
    Vec3 b = {1.0f, 2.0f, 3.0f};

    Vec3* result = vec3Sub(&a, &b);
    printVector3(result);

    assert(result->x == 4.0f);
    assert(result->y == 4.0f);
    assert(result->z == 4.0f);

    vec3Free(result);
}

void scaleVector3_test() {
    printf("Test: Scale Vector 3D\n");

    Vec3 a = {1.0f, 2.0f, 3.0f};
    float scalar = 2.0f;

    Vec3* result = vec3Scale(&a, scalar);
    printVector3(result);

    assert(result->x == 2.0f);
    assert(result->y == 4.0f);
    assert(result->z == 6.0f);

    vec3Free(result);
}

void dotVector3_test() {
    printf("Test: Dot Product Vector 3D\n");

    Vec3 a = {1.0f, 2.0f, 3.0f};
    Vec3 b = {4.0f, 5.0f, 6.0f};

    float result = vec3Dot(&a, &b);
    printf("Dot product: %f\n", result);

    assert(result == 32.0f);
}

void lenVector3_test() {
    printf("Test: Length of Vector 3D\n");

    Vec3 a = {1.0f, 2.0f, 2.0f};

    float result = vec3Len(&a);
    printf("Length: %f\n", result);

    assert(fabs(result - 3.0f) < 0.0001f);
}

void normVector3_test() {
    printf("Test: Normalize Vector 3D\n");

    Vec3 a = {3.0f, 4.0f, 0.0f};

    Vec3* result = vec3Norm(&a);
    printVector3(result);

    assert(fabs(result->x - 0.6f) < 0.0001f);
    assert(fabs(result->y - 0.8f) < 0.0001f);
    assert(fabs(result->z - 0.0f) < 0.0001f);

    vec3Free(result);
}

void distVector3_test() {
    printf("Test: Distance between Vector 3D\n");

    Vec3 a = {1.0f, 2.0f, 3.0f};
    Vec3 b = {4.0f, 5.0f, 6.0f};

    float result = vec3Dist(&a, &b);
    printf("Distance: %f\n", result);

    assert(fabs(result - 5.1962f) < 0.0001f);
}