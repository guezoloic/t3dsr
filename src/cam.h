#include "math/mat4.h"
#include "math/vec4.h"

Mat4f_t perspCam(float fov, float asp, float near, float far);
Vec4f_t* normCoord_r(Vec4f_t* vec);
Vec4f_t* viewport_r(Vec4f_t* vec, float width, float height);