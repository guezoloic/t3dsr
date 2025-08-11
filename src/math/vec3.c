#include "vec3.h"

Vec3f_t vec3f(float x, float y, float z)
{
    Vec3f_t vec = {.x = x, .y = y, .z = z};
    vec.data[3] = 0.f;
    return vec;
}

Vec3f_t vec3f_from_array(const float *__restrict val)
{
    Vec3f_t vec;
#if defined (SIMD_X86)
    __m128 arr = _mm_load_ps(val);
    _mm_store_ps(vec.data, arr);
#elif defined (SIMD_ARCH)
    float32x4_t arr = vld1q_f32(val);
    vst1q_f32(vec.data, arr);
#else
    for(int i = 0; i<VEC_SIZE; i++) {
        vec.data[i] = val[i];
    }
#endif
    return vec;
}

Vec3f_t vec3f_scalar(float f)
{
    Vec3f_t vec3;

#if defined(SIMD_X86)
    __m128 scalar = _mm_set1_ps(f);
    _mm_store_ps(vec3.data, scalar);

#elif defined(SIMD_ARCH)
    float32x4_t scalar = vdupq_n_f32(f);
    vst1q_f32(vec3.data, scalar);

#else
    for (int i = 0; i < VEC_SIZE; i++) {
        vec3.data[i] = f;
    }
#endif
    return vec3;
}

Vec3f_t vec3f_zero(void)
{
    return vec3f_scalar(0.f);
}

Vec3f_t* vec3f_add_r(Vec3f_t *__restrict out, Vec3f_t a)
{
#if defined (SIMD_X86)
    __m128 va = _mm_load_ps(a.data);
    __m128 vb = _mm_load_ps(out->data);
    __m128 vres = _mm_add_ps(va, vb);
    _mm_store_ps(out->data, vres);

#elif defined (SIMD_ARCH)
    float32x4_t va = vld1q_f32(a.data);
    float32x4_t vb = vld1q_f32(out->data);
    float32x4_t vres = vaddq_f32(va, vb);
    vst1q_f32(out->data, vres);
#else
    for(int i = 0; i<VEC_SIZE; i++) {
        out->data[i] += a.data[i];
    }
#endif
    return out;
}

Vec3f_t vec3f_add(Vec3f_t a, Vec3f_t b)
{
    vec3f_add_r(&a, b);
    return a;
}

Vec3f_t* vec3f_sub_r(Vec3f_t *__restrict out, Vec3f_t a)
{
#if defined (SIMD_X86)
    __m128 va = _mm_load_ps(out->data);
    __m128 vb = _mm_load_ps(a.data);
    __m128 vres = _mm_sub_ps(va, vb);
    _mm_store_ps(out->data, vres);

#elif defined (SIMD_ARCH)
    float32x4_t va = vld1q_f32(out->data);
    float32x4_t vb = vld1q_f32(a.data);
    float32x4_t vres = vsubq_f32(va, vb);
    vst1q_f32(out->data, vres);

#else
    for(int i = 0; i<VEC_SIZE; i++) {
        out->data[i] -= a.data[i];
    }
#endif
    return out;
}

Vec3f_t vec3f_sub(Vec3f_t a, Vec3f_t b)
{
    vec3f_sub_r(&a, b);
    return a;
}

Vec3f_t* vec3f_scale_r(Vec3f_t *__restrict out, float scalar)
{
#if defined (SIMD_X86)
    __m128 va = _mm_load_ps(out->data);
    __m128 vb = _mm_set1_ps(scalar);
    __m128 vres = _mm_mul_ps(va, vb);
    _mm_store_ps(out->data, vres);

#elif defined (SIMD_ARCH)
    float32x4_t va = vld1q_f32(out->data);
    float32x4_t vb = vdupq_n_f32(scalar);
    float32x4_t vres = vmulq_f32(va, vb);
    vst1q_f32(out->data, vres);
#else
    for(int i = 0; i<4; i++) {
        out->data[i] *= scalar;
    }
#endif
    return out;
}

Vec3f_t vec3f_scale(Vec3f_t a, float scalar)
{
    vec3f_scale_r(&a, scalar);
    return a;
}

float vec3f_dot(Vec3f_t a, Vec3f_t b)
{
#if defined (SIMD_X86)
    __m128 va = _mm_load_ps(a.data);
    __m128 vb = _mm_load_ps(b.data);
    __m128 vmul = _mm_mul_ps(va, vb);

    __m128 shuf = _mm_shuffle_ps(vmul, vmul, _MM_SHUFFLE(2, 3, 0, 1)); // [y, y, w, w]
    __m128 sum = _mm_add_ps(vmul, shuf); // [x+y, y+y, z+w, w+w]

    shuf = _mm_movehl_ps(shuf, sum); // [z+w, w+w, w, w]
    sum = _mm_add_ss(sum, shuf); // [x+y+z+w, y+y, z+w, w+w]

    return _mm_cvtss_f32(sum);
    
#elif defined (SIMD_ARCH)
    float32x4_t va = vld1q_f32(a.data);
    float32x4_t vb = vld1q_f32(b.data);
    
    float32x4_t vmul = vmulq_f32(va, vb);
    float32x2_t sum_pair = vadd_f32(vget_low_f32(vmul), vget_high_f32(vmul));
    float32x2_t final_sum = vpadd_f32(sum_pair, sum_pair);
    
    return vget_lane_f32(final_sum, 0);
#else
    return a.x * b.x + a.y * b.y + a.z * b.z;
#endif
}

Vec3f_t* vec3f_norm_r(Vec3f_t *__restrict v)
{
    float length = vec3f_len(*v);
    if (length < FLT_EPSILON) *v = vec3f_zero();
    vec3f_scale_r(v, 1.f / length);
    return v;
}

Vec3f_t vec3f_norm(Vec3f_t v)
{
    vec3f_norm_r(&v);
    return v;
}

Vec3f_t* vec3f_lerp_r(Vec3f_t *__restrict a, Vec3f_t b, float t)
{
    t = fmaxf(0.f, fminf(t, 1.f));
    
    a->x += t * (b.x - a->x);
    a->y += t * (b.y - a->y);
    a->z += t * (b.z - a->z);
    
    return a;
}

Vec3f_t vec3f_lerp(Vec3f_t a, Vec3f_t b, float t)
{
    vec3f_lerp_r(&a, b, t);
    return a;
}

 float vec3f_angle(Vec3f_t a, Vec3f_t b)
 {
     float lenA = vec3f_len(a);
     float lenB = vec3f_len(b);

     if (isnan(lenA) || isnan(lenB)
         || lenA < FLT_EPSILON
         || lenB < FLT_EPSILON)
         return NAN;

     float dot = vec3f_dot(a, b);
     float cosTheta = dot / (lenA * lenB);

     cosTheta = fmaxf(-1.f, fminf(cosTheta, 1.f));

     return acosf(cosTheta);
 }


 Vec3f_t vec3f_proj(Vec3f_t a, Vec3f_t b)
 {
     float dotA = vec3f_dot(a, b);
     float dotB = vec3f_dot(b, b);

     float scale = dotA / dotB;
     return vec3f_scale(b, scale);
 }

 Vec3f_t vec3f_refl(Vec3f_t v, Vec3f_t normal)
 {
     Vec3f_t proj = vec3f_proj(v, normal);
     Vec3f_t scal = vec3f_scale(proj, 2.f);
     Vec3f_t rlt = vec3f_sub(v, scal);
     return rlt;
 }

 float vec3f_dist(Vec3f_t a, Vec3f_t b)
 {
     Vec3f_t vsub = vec3f_sub(a, b);
     float rlt = vec3f_len(vsub);
     return rlt;
 }
