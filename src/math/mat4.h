#ifndef MATRIX4_H
#define MATRIX4_H

#include "mconfig.h"

#define MAT_SIZE 16

typedef struct 
{
    float m[MAT_SIZE];
} ALIGN16 Mat4f_t;

Mat4f_t mat4f_from_array(const float arr[16]);
Mat4f_t mat4f_scalar(float f);
Mat4f_t mat4f_zero(void);
Mat4f_t mat4f_identity(void);

// Mat4_t mat4_zro(void);

// Mat4_t mat4_ity(void);

// Mat4_t mat4_add(const Mat4_t* m1, const Mat4_t* m2);

// Mat4_t mat4_sub(const Mat4_t* m1, const Mat4_t* m2);

// Mat4_t mat4_scl(const Mat4_t* m, float scalar);

// // row * col
// Mat4_t mat4_mul(const Mat4_t* m1, const Mat4_t* m2);

// Mat4_t mat4_tpo(const Mat4_t* m);

// float mat4_det(const Mat4_t* m);

// Mat4_t mat4_inv(const Mat4_t* m);

#endif // MATRIX4_H
