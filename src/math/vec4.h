#ifndef VECTOR4_H
#define VECTOR4_H

#ifndef SIMD 
#if defined(__x86_64__) || defined(__amd64__) || defined(_M_X64) 
    #define SIMD_X86

#elif defined(__aarch64__) || defined(__arm64__) || defined(_M_ARM64)
    #define SIMD_ARCH

#else
#endif
#define SIMD
#endif


#ifndef ALIGN16_VEC
#ifdef _MSC_VER
    #define ALIGN16_VEC __declspec(align(16))
#else
    #define ALIGN16_VEC __attribute__((aligned(16)))
#endif
#endif

#define VEC_SIZE 4



// must be aligned by 16 Bytes (less instruction executed for SSE)
typedef union
{
    struct { float x, y, z, w; };
    float data[VEC_SIZE];
} ALIGN16_VEC Vec4f_t;

Vec4f_t vec4f_from_array(const float *__restrict val);
Vec4f_t vec4f(float x, float y, float z, float w);
// (f, f, f, f)
Vec4f_t vec4f_scalar(float f);
// (0, 0, 0, 0)
Vec4f_t vec4f_zero(void);

inline static Vec4f_t vec4f_clone(const Vec4f_t *__restrict v)
{
    return *v;
}

Vec4f_t* vec4f_add_r(Vec4f_t *__restrict out, Vec4f_t a);
Vec4f_t vec4f_add(Vec4f_t a, Vec4f_t b);

Vec4f_t* vec4f_sub_r(Vec4f_t *__restrict out, Vec4f_t a);
Vec4f_t vec4f_sub(Vec4f_t a, Vec4f_t b);

Vec4f_t* vec4f_scale_r(Vec4f_t *__restrict out, float scale);
Vec4f_t vec4f_scale(Vec4f_t a, float scale);

float vec4f_dot(Vec4f_t a, Vec4f_t b);

float vec4f_len(Vec4f_t v);

Vec4f_t* vec4f_norm_r(Vec4f_t *__restrict v);
Vec4f_t vec4f_norm(Vec4f_t v);

Vec4f_t* vec4f_lerp_r(Vec4f_t *__restrict a, Vec4f_t b, float t);
Vec4f_t vec4f_lerp(Vec4f_t a, Vec4f_t b, float t);

float vec4f_angle(Vec4f_t a, Vec4f_t b);

Vec4f_t vec4f_proj(Vec4f_t a, Vec4f_t b);

Vec4f_t vec4f_refl(Vec4f_t v, Vec4f_t normal);

float vec4f_dist(Vec4f_t a, Vec4f_t b);

Vec4f_t* vec4f_cross_r(Vec4f_t* __restrict out, Vec4f_t a, Vec4f_t b);

Vec4f_t vec4f_cross(Vec4f_t a, Vec4f_t b);

#undef VEC_SIZE

#endif // VECTOR4_H
