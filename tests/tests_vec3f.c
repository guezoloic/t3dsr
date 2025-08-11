//
//  tests.c
//  tests
//
//  Created by Loïc GUEZO on 26/06/2025.
//

#include <assert.h>
#include <stdio.h>

#include "../src/math/vec3.h"
#include "../src/math/vec4.h"

#define EPSILON 1e-6f

void test_vec3f_creation() {
    Vec3f_t v = vec3f(1.f, 2.f, 3.f);
    assert(fabsf(v.x - 1.f) < EPSILON);
    assert(fabsf(v.y - 2.f) < EPSILON);
    assert(fabsf(v.z - 3.f) < EPSILON);
}

// a -> [1, 2, 3]
// b -> [5, 6, 7]
// r -> [6, 8, 10]
void test_vec3f_add() {
    Vec3f_t a = vec3f(1.f, 2.f, 3.f);
    Vec3f_t b = vec3f(5.f, 6.f, 7.f);
    Vec3f_t r = vec3f_add(a, b);
    assert(fabsf(r.x - 6.f) < EPSILON);
    assert(fabsf(r.y - 8.f) < EPSILON);
    assert(fabsf(r.z - 10.f) < EPSILON);
}

// a -> [5, 6, 7]
// b -> [1, 2, 3]
// r -> [4, 4, 4]
void test_vec3f_sub() {
    Vec3f_t a = vec3f(5.f, 6.f, 7.f);
    Vec3f_t b = vec3f(1.f, 2.f, 3.f);
    Vec3f_t r = vec3f_sub(a, b);
    
    assert(fabsf(r.x - 4.f) < EPSILON);
    assert(fabsf(r.y - 4.f) < EPSILON);
    assert(fabsf(r.z - 4.f) < EPSILON);
}
// a -> [1, 2, 3]
// r -> [2, 4, 6]
void test_vec3f_scale() {
    Vec3f_t a = vec3f(1.f, 2.f, 3.f);
    Vec3f_t r = vec3f_scale(a, 2.f);
    assert(fabsf(r.x - 2.f) < EPSILON);
    assert(fabsf(r.y - 4.f) < EPSILON);
    assert(fabsf(r.z - 6.f) < EPSILON);
}

// dot product:
//      + : same direction
//      0 : orthgonal
//      - : opposite direction
void test_vec3f_dot() {
    Vec3f_t a = vec3f(1.f, 2.f, 3.f);
    Vec3f_t b = vec3f(5.f, 6.f, 7.f);
    float d = vec3f_dot(a, b);
    assert(fabsf(d - (1*5 + 2*6 + 3*7)) < EPSILON);
}

// normalize:
//      [4, 0, 0] -> [1, 0, 0]
void test_vec3f_norm() {
    Vec3f_t v = vec3f(3.f, 0.f, 0.f);
    Vec3f_t n = vec3f_norm(v);
    assert(fabsf(n.x - 1.f) < EPSILON);
    assert(fabsf(n.y) < EPSILON);
    assert(fabsf(n.z) < EPSILON);
}

// lerp:
//      return vector between a and b
//      if t = 0.5
//         a = [0, 0, 0]
//         b = [3, 3, 3]
//         r = [1.5, 1.5, 1.5] (t = 0.5) is middle
void test_vec3f_lerp() {
    Vec3f_t a = vec3f(0.f, 0.f, 0.f);
    Vec3f_t b = vec3f(1.f, 1.f, 1.f);
    Vec3f_t r = vec3f_lerp(a, b, 0.5f);
    assert(fabsf(r.x - 0.5f) < EPSILON);
    assert(fabsf(r.y - 0.5f) < EPSILON);
    assert(fabsf(r.z - 0.5f) < EPSILON);
}

// angle:
//      return angle of two vectors
void test_vec3f_angle() {
    Vec3f_t a = vec3f(1.f, 0.f, 0.f);
    Vec3f_t b = vec3f(0.f, 1.f, 0.f);
    float angle = vec3f_angle(a, b);
    assert(fabsf(angle - (float)(M_PI / 2)) < EPSILON);
}

// proj:
//      return size of a on b 
void test_vec3f_proj() {
    Vec3f_t a = vec3f(2.f, 0.f, 0.f);
    Vec3f_t b = vec3f(1.f, 0.f, 0.f);
    Vec3f_t r = vec3f_proj(a, b);
    assert(fabsf(r.x - 2.f) < EPSILON);
    assert(fabsf(r.y) < EPSILON);
    assert(fabsf(r.z) < EPSILON);
}

// refl:
//      return a bounce vector
//      raytracing
void test_vec3f_refl() {
    Vec3f_t v = vec3f(1.f, -1.f, 0.f);
    Vec3f_t normal = vec3f(0.f, 1.f, 0.f);
    Vec3f_t r = vec3f_refl(v, normal);
    assert(fabsf(r.x - 1.f) < EPSILON);
    assert(fabsf(r.y - 1.f) < EPSILON);
    assert(fabsf(r.z) < EPSILON);
}

// dist:
//      return distance between two vectors
void test_vec3f_dist() {
    Vec3f_t a = vec3f(1.f, 0.f, 0.f);
    Vec3f_t b = vec3f(0.f, 0.f, 0.f);
    float d = vec3f_dist(a, b);
    assert(fabsf(d - 1.f) < EPSILON);
}

int main(void) {
    test_vec3f_creation();
    test_vec3f_add();
    test_vec3f_sub();
    test_vec3f_scale();
    test_vec3f_dot();
    test_vec3f_norm();
    test_vec3f_lerp();
    test_vec3f_angle();
    test_vec3f_proj();
    test_vec3f_refl();
    test_vec3f_dist();
    return 0; // success
}
