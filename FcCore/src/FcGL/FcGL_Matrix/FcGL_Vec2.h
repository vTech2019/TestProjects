#ifndef __FCGL_VEC2_H__
#define __FCGL_VEC2_H__

#include <math.h>
#include <inttypes.h>

typedef union _FcGL_Vec2_t {
    struct {
        float f0, f1;
    };
    struct {
        uint32_t ui0, ui1;
    };
    struct {
        uint16_t us0, us1, us2, us3;
    };
    struct {
        int16_t s0, s1, s2, s3;
    };
    struct {
        uint8_t uc0, uc1, uc2, uc3, uc4, uc5, uc6, uc7;
    };
    struct {
        int8_t c0, c1, c2, c3, c4, c5, c6, c7;
    };
    float fdata[2];
} FcGL_Vec2_t;

static inline FcGL_Vec2_t FcGL_Vec2uca(uint8_t uc[8]) {
    return (FcGL_Vec2_t) {
            .uc0 = uc[0], .uc1 = uc[1],
            .uc2 = uc[2], .uc3 = uc[3],
            .uc4 = uc[4], .uc5 = uc[5],
            .uc6 = uc[6], .uc7 = uc[7]
    };
}

static inline FcGL_Vec2_t FcGL_Vec2uc(uint8_t uc0, uint8_t uc1,
                                      uint8_t uc2, uint8_t uc3,
                                      uint8_t uc4, uint8_t uc5,
                                      uint8_t uc6, uint8_t uc7) {
    return (FcGL_Vec2_t) {
            .uc0 = uc0, .uc1 = uc1,
            .uc2 = uc2, .uc3 = uc3,
            .uc4 = uc4, .uc5 = uc5,
            .uc6 = uc6, .uc7 = uc7
    };
}

static inline FcGL_Vec2_t FcGL_Vec2f(float x, float y) { return (FcGL_Vec2_t) {x, y}; }

static inline float FcGL_Vec2f_length(FcGL_Vec2_t v) { return sqrtf(v.f0 * v.f0 + v.f1 * v.f1); }

static inline float FcGL_Vec2f_dot(FcGL_Vec2_t a, FcGL_Vec2_t b) { return a.f0 * b.f0 + a.f1 * b.f1; }

static inline FcGL_Vec2_t FcGL_Vec2f_add(FcGL_Vec2_t a, FcGL_Vec2_t b) {
    return FcGL_Vec2f(a.f0 + b.f0, a.f1 + b.f1);
}

static inline FcGL_Vec2_t FcGL_Vec2f_sub(FcGL_Vec2_t a, FcGL_Vec2_t b) {
    return FcGL_Vec2f(a.f0 - b.f0, a.f1 - b.f1);
}

static inline FcGL_Vec2_t FcGL_Vec2f_mul(FcGL_Vec2_t a, FcGL_Vec2_t b) {
    return FcGL_Vec2f(a.f0 * b.f0, a.f1 * b.f1);
}

static inline FcGL_Vec2_t FcGL_Vec2f_muls(FcGL_Vec2_t a, float s) { return FcGL_Vec2f(a.f0 * s, a.f1 * s); }

static inline FcGL_Vec2_t FcGL_Vec2f_norm(FcGL_Vec2_t v) {
    float length = FcGL_Vec2f_length(v);
    if (length > 0)
        return FcGL_Vec2f(v.f0 / length, v.f1 / length);
    else
        return FcGL_Vec2f(0, 0);
}

static inline float FcGL_Vec2f_cross(FcGL_Vec2_t a, FcGL_Vec2_t b) {
    return a.f0 * b.f1 - a.f1 * b.f0;
}

static inline uint32_t FcGL_Vec2ui_equal(FcGL_Vec2_t a, FcGL_Vec2_t b) { return a.ui0 == b.ui0 & a.ui1 == b.ui1; }
//static inline FcGL_Vec2_t FcGL_Vec2_int16ToInt8_saturate(FcGL_Vec2_t a, FcGL_Vec2_t b) {
//	FcGL_Vec2_t result;
//	result.c0 = a.s0;
//	result.c1 = a.s1;
//	result.c2 = a.s2;
//	result.c3 = a.s3;
//	result.c4 = b.s0;
//	result.c5 = b.s1;
//	result.c6 = b.s2;
//	result.c7 = b.s3;
//	return result;
//}
#endif