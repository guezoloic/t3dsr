//
//  vec3.h
//  main
//
//  Created by Loïc GUEZO on 21/06/2025.
//

#ifndef vec3_h
#define vec3_h

#include "mconfig.h"

typedef union
{
    struct {float x, y, z; };
    float data[4];
} ALIGN16 Vec3f_t;

Vec3f_t vec3f_from_array(const float *restrict val);
Vec3f_t vec3f(float x, float y, float z);
// (f, f, f)
Vec3f_t vec3f_scalar(float f);
// (0, 0, 0)
Vec3f_t vec3f_zero(void);

inline static Vec3f_t vec3f_clone(const Vec3f_t *restrict v)
{
    return *v;
}

Vec3f_t vec3f_add_r(Vec3f_t *restrict out, Vec3f_t a);
Vec3f_t vec3f_add(Vec3f_t a, Vec3f_t b);

Vec3f_t vec3f_sub_r(Vec3f_t *restrict out, Vec3f_t a);
Vec3f_t vec3f_sub(Vec3f_t a, Vec3f_t b);

Vec3f_t vec3f_scale_r(Vec3f_t *restrict out, float scale);
Vec3f_t vec3f_scale(Vec3f_t a, float scale);

#endif /* vec3_h */
