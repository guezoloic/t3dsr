//
//  test_vec3f.c
//  tests
//
//  Created by Loïc GUEZO on 21/06/2025.
//

#include <assert.h>
#include <stdio.h>
#include "../src/math/vec4.h"

#define EPSILON 1e-6f

void test_vec4f_creation() {
    Vec4f_t v = vec4f(1.f, 2.f, 3.f, 4.f);
    assert(fabsf(v.x - 1.f) < EPSILON);
    assert(fabsf(v.y - 2.f) < EPSILON);
    assert(fabsf(v.z - 3.f) < EPSILON);
    assert(fabsf(v.w - 4.f) < EPSILON);
}

void test_vec4f_add() {
    Vec4f_t a = vec4f(1.f, 2.f, 3.f, 4.f);
    Vec4f_t b = vec4f(5.f, 6.f, 7.f, 8.f);
    Vec4f_t r = vec4f_add(a, b);
    assert(fabsf(r.x - 6.f) < EPSILON);
    assert(fabsf(r.y - 8.f) < EPSILON);
    assert(fabsf(r.z - 10.f) < EPSILON);
    assert(fabsf(r.w - 12.f) < EPSILON);
}

void test_vec4f_sub() {
    Vec4f_t a = vec4f(5.f, 6.f, 7.f, 8.f);
    Vec4f_t b = vec4f(1.f, 2.f, 3.f, 4.f);
    Vec4f_t r = vec4f_sub(a, b);
    
    assert(fabsf(r.x - 4.f) < EPSILON);
    assert(fabsf(r.y - 4.f) < EPSILON);
    assert(fabsf(r.z - 4.f) < EPSILON);
    assert(fabsf(r.w - 4.f) < EPSILON);
}

void test_vec4f_scale() {
    Vec4f_t a = vec4f(1.f, 2.f, 3.f, 4.f);
    Vec4f_t r = vec4f_scale(a, 2.f);
    assert(fabsf(r.x - 2.f) < EPSILON);
    assert(fabsf(r.y - 4.f) < EPSILON);
    assert(fabsf(r.z - 6.f) < EPSILON);
    assert(fabsf(r.w - 8.f) < EPSILON);
}

void run_all_tests() {
    test_vec4f_creation();
    test_vec4f_add();
    test_vec4f_sub();
    test_vec4f_scale();
}

int main(void) {
    run_all_tests();
    return 0; // success
}
