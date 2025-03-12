#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "math/vector.h"
#include "test_vec.h"

void printVector3(const Vec3* v) {
    printf("Vec3: [%f, %f, %f]\n", v->x, v->y, v->z);
}

void printVector4(const Vec4* v) {
    printf("Vec4: [%f, %f, %f, %f]\n", v->x, v->y, v->z, v->w);
}

// --- Tests Vec3 ---

void addVector3_test() {
    Vec3 a = {1, 2, 3};
    Vec3 b = {4, 5, 6};
    Vec3* r = vec3Add(&a, &b);
    printVector3(r);
    assert(r->x == 5 && r->y == 7 && r->z == 9);
    vec3Free(r);
}

void subVector3_test() {
    Vec3 a = {5, 6, 7};
    Vec3 b = {1, 2, 3};
    Vec3* r = vec3Sub(&a, &b);
    printVector3(r);
    assert(r->x == 4 && r->y == 4 && r->z == 4);
    vec3Free(r);
}

void scaleVector3_test() {
    Vec3 a = {1, 2, 3};
    Vec3* r = vec3Scale(&a, 2);
    printVector3(r);
    assert(r->x == 2 && r->y == 4 && r->z == 6);
    vec3Free(r);
}

void dotVector3_test() {
    Vec3 a = {1, 2, 3};
    Vec3 b = {4, 5, 6};
    float result = vec3Dot(&a, &b);
    printf("Dot product: %f\n", result);
    assert(result == 32);
}

void lenVector3_test() {
    Vec3 a = {1, 2, 2};
    float result = vec3Len(&a);
    printf("Length: %f\n", result);
    assert(fabs(result - 3) < 0.0001f);
}

void normVector3_test() {
    Vec3 a = {3, 4, 0};
    Vec3* r = vec3Norm(&a);
    printVector3(r);
    assert(fabs(r->x - 0.6f) < 0.0001f);
    assert(fabs(r->y - 0.8f) < 0.0001f);
    vec3Free(r);
}

void lerpVector3_test() {
    Vec3 a = {0, 0, 0};
    Vec3 b = {10, 10, 10};
    Vec3* r = vec3Lerp(&a, &b, 0.5f);
    printVector3(r);
    assert(r->x == 5 && r->y == 5 && r->z == 5);
    vec3Free(r);
}

void anglVector3_test() {
    Vec3 a = {1, 0, 0};
    Vec3 b = {0, 1, 0};
    float result = vec3Angle(&a, &b);
    printf("Angle: %f radians\n", result);
    assert(fabs(result - (M_PI / 2)) < 0.0001f);
}

void projVector3_test() {
    Vec3 a = {3, 4, 0};
    Vec3 b = {1, 0, 0};
    Vec3* r = vec3Proj(&a, &b);
    printVector3(r);
    assert(r->x == 3 && r->y == 0 && r->z == 0);
    vec3Free(r);
}

void reflVector3_test() {
    Vec3 v = {1, -1, 0};
    Vec3 normal = {0, 1, 0};
    Vec3* r = vec3Refl(&v, &normal);
    printVector3(r);
    assert(r->x == 1 && r->y == 1 && r->z == 0);
    vec3Free(r);
}

void distVector3_test() {
    Vec3 a = {1, 2, 3};
    Vec3 b = {4, 5, 6};
    float result = vec3Dist(&a, &b);
    printf("Distance: %f\n", result);
    assert(fabs(result - 5.1962f) < 0.0001f);
}

// --- Tests Vec4 ---

void addVector4_test() {
    Vec4 a = {1, 2, 3, 4};
    Vec4 b = {4, 5, 6, 7};
    Vec4* r = vec4Add(&a, &b);
    printVector4(r);
    assert(r->x == 5 && r->y == 7 && r->z == 9 && r->w == 11);
    vec4Free(r);
}

void subVector4_test() {
    Vec4 a = {5, 6, 7, 8};
    Vec4 b = {1, 2, 3, 4};
    Vec4* r = vec4Sub(&a, &b);
    printVector4(r);
    assert(r->x == 4 && r->y == 4 && r->z == 4 && r->w == 4);
    vec4Free(r);
}

void scaleVector4_test() {
    Vec4 a = {1, 2, 3, 4};
    Vec4* r = vec4Scale(&a, 2);
    printVector4(r);
    assert(r->x == 2 && r->y == 4 && r->z == 6 && r->w == 8);
    vec4Free(r);
}

void dotVector4_test() {
    Vec4 a = {1, 2, 3, 4};
    Vec4 b = {4, 5, 6, 7};
    float result = vec4Dot(&a, &b);
    printf("Dot product: %f\n", result);
    assert(result == (1 * 4 + 2 * 5 + 3 * 6 + 4 * 7));
}

void lenVector4_test() {
    Vec4 a = {1, 2, 2, 1};
    float result = vec4Len(&a);
    printf("Length: %f\n", result);
    assert(fabs(result - sqrtf(10)) < 0.0001f);
}

void normVector4_test() {
    Vec4 a = {3, 4, 0, 0};
    Vec4* r = vec4Norm(&a);
    printVector4(r);
    assert(fabs(r->x - (3.0f / 5.0f)) < 0.0001f);
    assert(fabs(r->y - (4.0f / 5.0f)) < 0.0001f);
    vec4Free(r);
}

void lerpVector4_test() {
    Vec4 a = {0, 0, 0, 0};
    Vec4 b = {10, 10, 10, 10};
    Vec4* r = vec4Lerp(&a, &b, 0.5f);
    printVector4(r);
    assert(r->x == 5 && r->y == 5 && r->z == 5 && r->w == 5);
    vec4Free(r);
}

void distVector4_test() {
    Vec4 a = {1, 2, 3, 4};
    Vec4 b = {4, 5, 6, 7};
    float result = vec4Dist(&a, &b);
    printf("Distance: %f\n", result);
    assert(fabs(result - sqrtf(12)) < 0.0001f);
}

void anglVector4_test() {
    Vec4 a = {1, 0, 0, 0};
    Vec4 b = {0, 1, 0, 0};
    float result = vec4Angle(&a, &b);
    printf("Angle: %f radians\n", result);
    assert(fabs(result - (M_PI / 2)) < 0.0001f);
}

void projVector4_test() {
    Vec4 a = {3, 4, 0, 0};
    Vec4 b = {1, 0, 0, 0};
    Vec4* r = vec4Proj(&a, &b);
    printVector4(r);
    assert(r->x == 3 && r->y == 0 && r->z == 0 && r->w == 0);
    vec4Free(r);
}

void reflVector4_test() {
    Vec4 v = {1, -1, 0, 0};
    Vec4 normal = {0, 1, 0, 0};
    Vec4* r = vec4Refl(&v, &normal);
    printVector4(r);
    assert(r->x == 1 && r->y == 1 && r->z == 0 && r->w == 0);
    vec4Free(r);
}