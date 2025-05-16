#ifndef MATRIX3_H
#define MATRIX3_H

typedef struct 
{
    float m[9];
} Mat3;

Mat3 mat3(const float arr[9]);
Mat3 mat3_zro();
Mat3 mat3_ity();

Mat3 mat3_add(const Mat3* m1, const Mat3* m2);
Mat3 mat3_sub(const Mat3* m1, const Mat3* m2);
Mat3 mat3_scl(const Mat3* m, float scalar);
Mat3 mat3_mul(const Mat3* m1, const Mat3* m2);

Mat3 mat3_tpo(const Mat3* m);
float mat3_det(const Mat3* m);
Mat3 mat3_inv(const Mat3* m);

#endif // MATRIX3_H