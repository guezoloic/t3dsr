#ifndef MATRIX3_H
#define MATRIX3_H

typedef struct 
{
    float m[9];
} Mat3_t;

Mat3_t mat3(const float arr[9]);

Mat3_t mat3_zro(void);

Mat3_t mat3_ity(void);

Mat3_t mat3_add(const Mat3_t* m1, const Mat3_t* m2);

Mat3_t mat3_sub(const Mat3_t* m1, const Mat3_t* m2);

Mat3_t mat3_scl(const Mat3_t* m, float scalar);

Mat3_t mat3_mul(const Mat3_t* m1, const Mat3_t* m2);

Mat3_t mat3_tpo(const Mat3_t* m);

float mat3_det(const Mat3_t* m);

Mat3_t mat3_inv(const Mat3_t* m);

#endif // MATRIX3_H
