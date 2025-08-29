#ifndef CAM_H
#define CAM_H

#include "math/mat4.h"
#include "math/vec4.h"

Mat4f_t perspCam(float fov, float asp, float near, float far);
Vec4f_t* normCoord_r(Vec4f_t* vec);
Vec4f_t* viewport_r(Vec4f_t* vec, float width, float height);

Mat4f_t lookAt(Vec4f_t* eye, Vec4f_t* center, Vec4f_t* up);

Mat4f_t rotateX(float angle);
Mat4f_t rotateY(float angle);
Mat4f_t rotateZ(float angle);

#endif