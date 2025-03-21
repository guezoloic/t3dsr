#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "math/vector3.h"
#include "test_vec.h"

#include "unity/unity.h"

// --- Tests Vec3 ---
void addVector3_test() {
    Vec3 a = {1, 2, 3};
    Vec3 b = {4, 5, 6};
    Vec3 r = vec3Add(a, b);

    TEST_ASSERT_EQUAL_FLOAT(5, r.x);
    TEST_ASSERT_EQUAL_FLOAT(7, r.y);
    TEST_ASSERT_EQUAL_FLOAT(9, r.z);
}

void subVector3_test() {
    Vec3 a = {5, 6, 7};
    Vec3 b = {1, 2, 3};
    Vec3 r = vec3Sub(a, b);

    TEST_ASSERT_EQUAL_FLOAT(4, r.x);
    TEST_ASSERT_EQUAL_FLOAT(4, r.y);
    TEST_ASSERT_EQUAL_FLOAT(4, r.z);
}

void scalVector3_test() {
    Vec3 a = {1, 2, 3};
    Vec3 r = vec3Scale(a, 2);

    TEST_ASSERT_EQUAL_FLOAT(2, r.x);
    TEST_ASSERT_EQUAL_FLOAT(4, r.y);
    TEST_ASSERT_EQUAL_FLOAT(6, r.z);
}

void dotVector3_test() {
    Vec3 a = {1, 2, 3};
    Vec3 b = {4, 5, 6};
    float result = vec3Dot(a, b);
    
    TEST_ASSERT_EQUAL_FLOAT(32, result);
}

void lenVector3_test() {
    Vec3 a = {1, 2, 2};
    float result = vec3Len(a);

    TEST_ASSERT_LESS_THAN_FLOAT(0.0001f, fabs(result - 3));
}

void normVector3_test() {
    Vec3 a = {3, 4, 0};
    Vec3 r = vec3Norm(a);

    TEST_ASSERT_LESS_THAN_FLOAT(0.0001f, fabs(r.x - 0.6f));
    TEST_ASSERT_LESS_THAN_FLOAT(0.0001f, fabs(r.y - 0.8f));
}

void lerpVector3_test() {    
    Vec3 a = {0, 0, 0};
    Vec3 b = {10, 10, 10};
    Vec3 r = vec3Lerp(a, b, 0.5f);
    
    TEST_ASSERT_EQUAL_FLOAT(5, r.x);
    TEST_ASSERT_EQUAL_FLOAT(5, r.y);
    TEST_ASSERT_EQUAL_FLOAT(5, r.z);
}

void crosVector3_test() {    
    Vec3 a = {1, 0, 0};
    Vec3 b = {0, 1, 0};
    Vec3 r = vec3Cross(a, b);

    TEST_ASSERT_EQUAL_FLOAT(0, r.x);
    TEST_ASSERT_EQUAL_FLOAT(0, r.y);
    TEST_ASSERT_EQUAL_FLOAT(1, r.z);
    
}

void anglVector3_test() {    
    Vec3 a = {1, 0, 0};
    Vec3 b = {0, 1, 0};
    float result = vec3Angle(a, b);

    TEST_ASSERT_LESS_THAN_FLOAT(0.0001f, fabs(result - (M_PI / 2)));
}

void projVector3_test() {    
    Vec3 a = {3, 4, 0};
    Vec3 b = {1, 0, 0};
    Vec3 r = vec3Proj(a, b);

    TEST_ASSERT_EQUAL_FLOAT(3, r.x);
    TEST_ASSERT_EQUAL_FLOAT(0, r.y);
    TEST_ASSERT_EQUAL_FLOAT(0, r.z);
    
}

void reflVector3_test() {    
    Vec3 v = {1, -1, 0};
    Vec3 normal = {0, 1, 0};
    Vec3 r = vec3Refl(v, normal);

    TEST_ASSERT_EQUAL_FLOAT(1, r.x);
    TEST_ASSERT_EQUAL_FLOAT(1, r.y);
    TEST_ASSERT_EQUAL_FLOAT(0, r.z);
}

void distVector3_test() {    
    Vec3 a = {1, 2, 3};
    Vec3 b = {4, 5, 6};
    float result = vec3Dist(a, b);

    TEST_ASSERT_FLOAT_WITHIN(0.0002f, 5.196, result);
}

void rotaVector3_test() {
    Vec3 v = {1.0f, 0.0f, 0.0f};
    Vec3 axis = {0.0f, 0.0f, 1.0f};
    float angle = M_PI / 2.0f;  
    Vec3 result = vec3Rotate(v, axis, angle);

    TEST_ASSERT_LESS_THAN_FLOAT(0.0001f, fabs(result.x - 0.0f));
    TEST_ASSERT_LESS_THAN_FLOAT(0.0001f, fabs(result.y - 1.0f));
    TEST_ASSERT_LESS_THAN_FLOAT(0.0001f, fabs(result.z - 0.0f));
}

void runVector3_test() {
    RUN_TEST(addVector3_test);
    RUN_TEST(subVector3_test);
    RUN_TEST(scalVector3_test);
    RUN_TEST(dotVector3_test);
    RUN_TEST(lenVector3_test);
    RUN_TEST(normVector3_test);
    RUN_TEST(lerpVector3_test);
    RUN_TEST(crosVector3_test);
    RUN_TEST(anglVector3_test);
    RUN_TEST(projVector3_test);
    RUN_TEST(reflVector3_test);
    RUN_TEST(distVector3_test);
    RUN_TEST(rotaVector3_test);
}