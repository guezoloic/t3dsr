#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    float m[9];
} Mat3;

Mat3 mat3(float arr[9]);
Mat3 mat3Zro();
Mat3 mat3Ity();

Mat3 mat3Add(Mat3 m1, Mat3 m2);
Mat3 mat3Sub(Mat3 m1, Mat3 m2);
Mat3 mat3Scl(Mat3 m, float scalar);
Mat3 mat3Mul(Mat3 m1, Mat3 m2);
Mat3 mat3Tpo(Mat3 m);
float mat3Det(Mat3 m);

#endif // MATRIX_H