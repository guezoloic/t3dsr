#ifndef MATRIX4_H
#define MATRIX4_H

#include "mconfig.h"

#define MAT_SIZE 16
#define MAT_DIM 4

typedef struct 
{
    float m[MAT_SIZE];
} ALIGN16 Mat4f_t;

Mat4f_t mat4f_from_array(const float arr[16]);
Mat4f_t mat4f_scalar(float f);
Mat4f_t mat4f_zero(void);
Mat4f_t mat4f_identity(void);

inline static Mat4f_t mat4f_clone(const Mat4f_t *__restrict out)
{
    return *out;
}

Mat4f_t mat4f_add(const Mat4f_t* m1, const Mat4f_t* m2);
Mat4f_t* mat4f_add_r(Mat4f_t* out, const Mat4f_t* m2);

Mat4f_t mat4f_sub(const Mat4f_t* m1, const Mat4f_t* m2);
Mat4f_t* mat4f_sub_r(Mat4f_t* out, const Mat4f_t* m2);

Mat4f_t mat4f_scale(const Mat4f_t *__restrict m, float scalar);
Mat4f_t* mat4f_scale_r(Mat4f_t *out, float scalar);

// row * col
Mat4f_t mat4f_mul(const Mat4f_t* m1, const Mat4f_t* m2);
Mat4f_t* mat4f_mul_r(Mat4f_t* out, const Mat4f_t* m2);

Mat4f_t mat4_tpo(const Mat4f_t *__restrict m);
Mat4f_t* mat4_tpo_r(Mat4f_t *__restrict m);

// float mat4_det(const Mat4_t* m);

// Mat4_t mat4_inv(const Mat4_t* m);

#endif // MATRIX4_H
