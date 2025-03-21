#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "math/vector4.h"
#include "test_vec.h"

#include "unity/unity.h"

// --- Tests Vec4 ---

void addVector4_test() {
    Vec4 a = {1, 2, 3, 4};
    Vec4 b = {4, 5, 6, 7};
    Vec4 r = vec4Add(a, b);

    TEST_ASSERT_EQUAL_FLOAT(5, r.x);
    TEST_ASSERT_EQUAL_FLOAT(7, r.y);
    TEST_ASSERT_EQUAL_FLOAT(9, r.z);
    TEST_ASSERT_EQUAL_FLOAT(11, r.w);
}

void subVector4_test() {
    Vec4 a = {5, 6, 7, 8};
    Vec4 b = {1, 2, 3, 4};
    Vec4 r = vec4Sub(a, b);

    TEST_ASSERT_EQUAL_FLOAT(4, r.x);
    TEST_ASSERT_EQUAL_FLOAT(4, r.y);
    TEST_ASSERT_EQUAL_FLOAT(4, r.z);
    TEST_ASSERT_EQUAL_FLOAT(4, r.w);
}

void scaleVector4_test() {
    Vec4 a = {1, 2, 3, 4};
    Vec4 r = vec4Scale(a, 2);

    TEST_ASSERT_EQUAL_FLOAT(2, r.x);
    TEST_ASSERT_EQUAL_FLOAT(4, r.y);
    TEST_ASSERT_EQUAL_FLOAT(6, r.z);
    TEST_ASSERT_EQUAL_FLOAT(8, r.w);
}

void dotVector4_test() {
    Vec4 a = {1, 2, 3, 4};
    Vec4 b = {4, 5, 6, 7};
    float result = vec4Dot(a, b);

    TEST_ASSERT_EQUAL_FLOAT((1*4 + 2*5 + 3*6 + 4*7), result);
}

void lenVector4_test() {
    Vec4 a = {1, 2, 2, 1};
    float result = vec4Len(a);

    TEST_ASSERT_LESS_THAN_FLOAT(0.0001f, fabs(result - sqrtf(10)));
}

void normVector4_test() {
    Vec4 a = {3, 4, 0, 0};
    Vec4 r = vec4Norm(a);

    TEST_ASSERT_LESS_THAN_FLOAT(0.0001f, fabs(r.x - (3.0f / 5.0f)));
    TEST_ASSERT_LESS_THAN_FLOAT(0.0001f, fabs(r.y - (4.0f / 5.0f)));
}

void lerpVector4_test() {
    Vec4 a = {0, 0, 0, 0};
    Vec4 b = {10, 10, 10, 10};
    Vec4 r = vec4Lerp(a, b, 0.5f);

    TEST_ASSERT_EQUAL_FLOAT(5, r.x);
    TEST_ASSERT_EQUAL_FLOAT(5, r.y);
    TEST_ASSERT_EQUAL_FLOAT(5, r.z);
    TEST_ASSERT_EQUAL_FLOAT(5, r.w);
}

void distVector4_test() {
    Vec4 a = {1, 2, 3, 4};
    Vec4 b = {4, 5, 6, 7};
    float result = vec4Dist(a, b);

    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 6, result);
}

void anglVector4_test() {
    Vec4 a = {1, 0, 0, 0};
    Vec4 b = {0, 1, 0, 0};
    float result = vec4Angle(a, b);

    TEST_ASSERT_LESS_THAN_FLOAT(0.0001f, fabs(result - (M_PI / 2)));
}

void projVector4_test() {
    Vec4 a = {3, 4, 0, 0};
    Vec4 b = {1, 0, 0, 0};
    Vec4 r = vec4Proj(a, b);

    TEST_ASSERT_EQUAL_FLOAT(3, r.x);
    TEST_ASSERT_EQUAL_FLOAT(0, r.y);
    TEST_ASSERT_EQUAL_FLOAT(0, r.z);
    TEST_ASSERT_EQUAL_FLOAT(0, r.w);
}

void reflVector4_test() {
    Vec4 v = {1, -1, 0, 0};
    Vec4 normal = {0, 1, 0, 0};
    Vec4 r = vec4Refl(v, normal);

    TEST_ASSERT_EQUAL_FLOAT(1, r.x);
    TEST_ASSERT_EQUAL_FLOAT(1, r.y);
    TEST_ASSERT_EQUAL_FLOAT(0, r.z);
    TEST_ASSERT_EQUAL_FLOAT(0, r.w);
}

void runVector4_test() {
    RUN_TEST(addVector4_test);
    RUN_TEST(subVector4_test);
    RUN_TEST(scaleVector4_test);
    RUN_TEST(dotVector4_test);
    RUN_TEST(lenVector4_test);
    RUN_TEST(normVector4_test);
    RUN_TEST(lerpVector4_test);
    RUN_TEST(anglVector4_test);
    RUN_TEST(projVector4_test);
    RUN_TEST(reflVector4_test);
    RUN_TEST(distVector4_test);
}