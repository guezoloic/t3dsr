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

// a -> [1, 2, 3, 4]
// b -> [5, 6, 7, 8]
// r -> [6, 8, 10, 12]
void test_vec4f_add() {
    Vec4f_t a = vec4f(1.f, 2.f, 3.f, 4.f);
    Vec4f_t b = vec4f(5.f, 6.f, 7.f, 8.f);
    Vec4f_t r = vec4f_add(a, b);
    assert(fabsf(r.x - 6.f) < EPSILON);
    assert(fabsf(r.y - 8.f) < EPSILON);
    assert(fabsf(r.z - 10.f) < EPSILON);
    assert(fabsf(r.w - 12.f) < EPSILON);
}

// a -> [5, 6, 7, 8]
// b -> [1, 2, 3, 4]
// r -> [4, 4, 4, 4]
void test_vec4f_sub() {
    Vec4f_t a = vec4f(5.f, 6.f, 7.f, 8.f);
    Vec4f_t b = vec4f(1.f, 2.f, 3.f, 4.f);
    Vec4f_t r = vec4f_sub(a, b);
    
    assert(fabsf(r.x - 4.f) < EPSILON);
    assert(fabsf(r.y - 4.f) < EPSILON);
    assert(fabsf(r.z - 4.f) < EPSILON);
    assert(fabsf(r.w - 4.f) < EPSILON);
}
// a -> [1, 2, 3, 4]
// r -> [2, 4, 6, 8]
void test_vec4f_scale() {
    Vec4f_t a = vec4f(1.f, 2.f, 3.f, 4.f);
    Vec4f_t r = vec4f_scale(a, 2.f);
    assert(fabsf(r.x - 2.f) < EPSILON);
    assert(fabsf(r.y - 4.f) < EPSILON);
    assert(fabsf(r.z - 6.f) < EPSILON);
    assert(fabsf(r.w - 8.f) < EPSILON);
}

// dot product:
//      + : same direction
//      0 : orthgonal
//      - : opposite direction
void test_vec4f_dot() {
    Vec4f_t a = vec4f(1.f, 2.f, 3.f, 4.f);
    Vec4f_t b = vec4f(5.f, 6.f, 7.f, 8.f);
    float d = vec4f_dot(a, b);
    assert(fabsf(d - (1*5 + 2*6 + 3*7 + 4*8)) < EPSILON);
}

// normalize:
//      [4, 0, 0, 0] -> [1, 0, 0, 0]
void test_vec4f_norm() {
    Vec4f_t v = vec4f(3.f, 0.f, 0.f, 0.f);
    Vec4f_t n = vec4f_norm(v);
    assert(fabsf(n.x - 1.f) < EPSILON);
    assert(fabsf(n.y) < EPSILON);
    assert(fabsf(n.z) < EPSILON);
    assert(fabsf(n.w) < EPSILON);
}

// lerp:
//      return vector between a and b
//      if t = 0.5
//         a = [0, 0, 0, 0]
//         b = [3, 3, 3, 3]
//         r = [1.5, 1.5, 1.5, 1.5] (t = 0.5) is middle
void test_vec4f_lerp() {
    Vec4f_t a = vec4f(0.f, 0.f, 0.f, 0.f);
    Vec4f_t b = vec4f(1.f, 1.f, 1.f, 1.f);
    Vec4f_t r = vec4f_lerp(a, b, 0.5f);
    assert(fabsf(r.x - 0.5f) < EPSILON);
    assert(fabsf(r.y - 0.5f) < EPSILON);
    assert(fabsf(r.z - 0.5f) < EPSILON);
    assert(fabsf(r.w - 0.5f) < EPSILON);
}

// angle:
//      return angle of two vectors
void test_vec4f_angle() {
    Vec4f_t a = vec4f(1.f, 0.f, 0.f, 0.f);
    Vec4f_t b = vec4f(0.f, 1.f, 0.f, 0.f);
    float angle = vec4f_angle(a, b);
    assert(fabsf(angle - (float)(M_PI / 2)) < EPSILON);
}

// proj:
//      return size of a on b 
void test_vec4f_proj() {
    Vec4f_t a = vec4f(2.f, 0.f, 0.f, 0.f);
    Vec4f_t b = vec4f(1.f, 0.f, 0.f, 0.f);
    Vec4f_t r = vec4f_proj(a, b);
    assert(fabsf(r.x - 2.f) < EPSILON);
    assert(fabsf(r.y) < EPSILON);
    assert(fabsf(r.z) < EPSILON);
    assert(fabsf(r.w) < EPSILON);
}

// refl:
//      return a bounce vector
//      raytracing
void test_vec4f_refl() {
    Vec4f_t v = vec4f(1.f, -1.f, 0.f, 0.f);
    Vec4f_t normal = vec4f(0.f, 1.f, 0.f, 0.f);
    Vec4f_t r = vec4f_refl(v, normal);
    assert(fabsf(r.x - 1.f) < EPSILON);
    assert(fabsf(r.y - 1.f) < EPSILON);
    assert(fabsf(r.z) < EPSILON);
    assert(fabsf(r.w) < EPSILON);
}

// dist:
//      return distance between two vectors
void test_vec4f_dist() {
    Vec4f_t a = vec4f(1.f, 0.f, 0.f, 0.f);
    Vec4f_t b = vec4f(0.f, 0.f, 0.f, 0.f);
    float d = vec4f_dist(a, b);
    assert(fabsf(d - 1.f) < EPSILON);
}

void run_all_tests() {
    test_vec4f_creation();
    test_vec4f_add();
    test_vec4f_sub();
    test_vec4f_scale();
    test_vec4f_dot();
    test_vec4f_norm();
    test_vec4f_lerp();
    test_vec4f_angle();
    test_vec4f_proj();
    test_vec4f_refl();
    test_vec4f_dist();
}

int main(void) {
    run_all_tests();
    return 0; // success
}
