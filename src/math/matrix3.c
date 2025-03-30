#include "math/matrix3.h"
#include <string.h>
#include <math.h>

Mat3 mat3(float arr[9]) {
    Mat3 mat;
    memcpy(mat.m, arr, 9*sizeof(float));
    return mat;
}

Mat3 mat3Zro() {
    return (Mat3){0};
}

Mat3 mat3Ity() {
    return (Mat3) {{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    }};
}

Mat3 mat3Add(Mat3 m1, Mat3 m2) {
    Mat3 mat;
    
    for(int i = 0; i<9; i++) {
        mat.m[i] = m1.m[i] + m2.m[i];
    }

    return mat;
}

Mat3 mat3Sub(Mat3 m1, Mat3 m2) {
    Mat3 mat;

    for(int i = 0; i<9; i++) {
        mat.m[i] = m1.m[i] - m2.m[i];
    }

    return mat;
}

Mat3 mat3Scl(Mat3 m, float scalar) {
    Mat3 mat;

    for(int i = 0; i<9; i++) {
        mat.m[i] = m.m[i] * scalar;
    }

    return mat;
}

Mat3 mat3Mul(Mat3 m1, Mat3 m2) {
    Mat3 mat; 

    for(int i = 0; i<3; i++) {
        int i3 = i * 3;
        for (int j = 0; j < 3; j++) {
            float sum = 0;
            
            for (int k = 0; k < 3; k++) {
                sum += m1.m[i3 + k] * m2.m[k*3 + j];    
            }

            mat.m[i3 + j] = sum;
        }
    }

    return mat;
}

Mat3 mat3Tpo(Mat3 m) {
    Mat3 mat;

    for(int i = 0; i<3; i++) {
        int i3 = i * 3;
        
        for (int j = 0; j < 3; j++) {
            mat.m[i3 + j] = m.m[j*3 + i];
        }
    }

    return mat;
}

float mat3Det(Mat3 m) {
    return m.m[0] * (m.m[4] * m.m[8] - m.m[5] * m.m[7]) -
           m.m[1] * (m.m[3] * m.m[8] - m.m[5] * m.m[6]) +
           m.m[2] * (m.m[3] * m.m[7] - m.m[4] * m.m[6]);
}