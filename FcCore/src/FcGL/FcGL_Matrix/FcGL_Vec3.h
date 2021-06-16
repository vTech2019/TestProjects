
#ifndef __FCGL_VEC3_H__
#define __FCGL_VEC3_H__

#include <math.h>

#define st_check_vec3(actual, expected, epsilon) printf( "%s: got (%.2f %.2f %.2f), expected (%.2f %.2f %.2f)\n",                           \
    (fabs((actual).f0 - (expected).f0) < (epsilon) &&                                        \
    fabs((actual).f1 - (expected).f1) < (epsilon) &&                                        \
    fabs((actual).f2 - (expected).f2) < (epsilon)   ? "true" : "false") ,                    \
    (actual).f0, (actual).f1, (actual).f2,                                                   \
    (expected).f0, (expected).f1, (expected).f2                                              \
)

typedef union FcGL_Vec3_t {

    struct {
        float f0, f1, f2;
    };
    struct {
        unsigned u0, u1, u2;
    };
    float fdata[3];
} FcGL_Vec3_t;

static inline FcGL_Vec3_t FcGL_Vec3f(float x, float y, float z) { return (FcGL_Vec3_t) {x, y, z}; }

static inline float FcGL_Vec3f_length(FcGL_Vec3_t v) { return sqrtf(v.f0 * v.f0 + v.f1 * v.f1 + v.f2 * v.f2); }

static inline float FcGL_Vec3f_dot(FcGL_Vec3_t a, FcGL_Vec3_t b) { return a.f0 * b.f0 + a.f1 * b.f1 + a.f2 * b.f2; }

static inline FcGL_Vec3_t FcGL_Vec3f_add(FcGL_Vec3_t a, FcGL_Vec3_t b) {
    return FcGL_Vec3f(a.f0 + b.f0, a.f1 + b.f1, a.f2 + b.f2);
}

static inline FcGL_Vec3_t FcGL_Vec3f_sub(FcGL_Vec3_t a, FcGL_Vec3_t b) {
    return FcGL_Vec3f(a.f0 - b.f0, a.f1 - b.f1, a.f2 - b.f2);
}

static inline FcGL_Vec3_t FcGL_Vec3f_mul(FcGL_Vec3_t a, FcGL_Vec3_t b) {
    return FcGL_Vec3f(a.f0 * b.f0, a.f1 * b.f1, a.f2 * b.f2);
}

static inline FcGL_Vec3_t FcGL_Vec3f_muls(FcGL_Vec3_t a, float s) { return FcGL_Vec3f(a.f0 * s, a.f1 * s, a.f2 * s); }

static inline FcGL_Vec3_t FcGL_Vec3f_norm(FcGL_Vec3_t v) {
    float length = FcGL_Vec3f_length(v);
    if (length > 0)
        return FcGL_Vec3f(v.f0 / length, v.f1 / length, v.f2 / length);
    else
        return FcGL_Vec3f(0, 0, 0);
}

static inline FcGL_Vec3_t FcGL_Vec3f_proj(FcGL_Vec3_t v, FcGL_Vec3_t onto) {
    return FcGL_Vec3f_muls(onto, FcGL_Vec3f_dot(v, onto) / FcGL_Vec3f_dot(onto, onto));
}

static inline FcGL_Vec3_t FcGL_Vec3f_cross(FcGL_Vec3_t a, FcGL_Vec3_t b) {
    return FcGL_Vec3f(
            a.f1 * b.f2 - a.f2 * b.f1,
            a.f2 * b.f0 - a.f0 * b.f2,
            a.f0 * b.f1 - a.f1 * b.f0
    );
}

#endif