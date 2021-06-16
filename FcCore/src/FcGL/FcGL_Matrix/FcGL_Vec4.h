//
// Created by human on 29.02.2020.
//

#ifndef __FCGL_VEC4_H__
#define __FCGL_VEC4_H__

#include <math.h>
#include <inttypes.h>

#include "FcGL_Vec2.h"

typedef union FcGL_Vec4_t {
    struct {
        float f0, f1, f2, f3;
    };
    struct {
        int32_t i0, i1, i2, i3;
    };
    struct {
        int16_t s0, s1, s2, s3, s4, s5, s6, s7;
    };
    struct {
        uint8_t uc0, uc1, uc2, uc3, uc4, uc5, uc6, uc7, uc8, uc9, uc10, uc11, uc12, uc13, uc14, uc15;
    };
    FcGL_Vec2_t vec2[2];
    float fdata[4];
    int32_t idata[4];
    int16_t sdata[8];
    int8_t cdata[16];
} FcGL_Vec4_t;

static inline FcGL_Vec4_t FcGL_Vec4f(float s0, float s1, float s2, float s3) {
    return (FcGL_Vec4_t) {s0, s1, s2, s3};
}

static inline FcGL_Vec4_t FcGL_Vec4i_p0000_init(int32_t value) {
    FcGL_Vec4_t result;
    int32_t i;
    for (i = 0; i <= 3; i++)
        result.idata[i] = value;
    return result;
}

static inline FcGL_Vec4_t FcGL_Vec4f_p0000_init(float value) {
    FcGL_Vec4_t result;
    int32_t i;
    for (i = 0; i <= 3; i++)
        result.fdata[i] = value;
    return result;
}

static inline float FcGL_Vec4f_length(FcGL_Vec4_t v) {
    return sqrtf(v.f0 * v.f0 + v.f1 * v.f1 + v.f2 * v.f2 + v.f3 * v.f3);
}

static inline float FcGL_Vec4f_sum(FcGL_Vec4_t v) {
    return v.f0 + v.f1 + v.f2 + v.f3;
}

//static inline FcGL_Vec4_t FcGL_Vec4_int16ToUint8_saturate(FcGL_Vec4_t a, FcGL_Vec4_t b) {
//	FcGL_Vec4_t result;
//	int32_t i;
//	for (i = 0; i <= 7; i++)
//		result.cdata[i] = a.sdata[i];
//	for (i = 0; i <= 7; i++)
//		result.cdata[8 + i] = b.sdata[i];
//	return result;
//}
//static inline FcGL_Vec4_t FcGL_Vec4_int32ToInt16_saturate(FcGL_Vec4_t a, FcGL_Vec4_t b) {
//	FcGL_Vec4_t result;
//	int32_t i;
//	for (i = 0; i <= 3; i++)
//		result.sdata[i] = a.idata[i];
//	for (i = 0; i <= 3; i++)
//		result.sdata[4 + i] = b.idata[i];
//	return result;
//}
static inline FcGL_Vec4_t FcGL_Vec4_floatToInt(FcGL_Vec4_t value) {
    FcGL_Vec4_t result;
    int32_t i;
    for (i = 0; i <= 3; i++)
        result.idata[i] = (int32_t) value.fdata[i];
    return result;
}

static inline FcGL_Vec4_t FcGL_Vec4f_div(FcGL_Vec4_t nominator, FcGL_Vec4_t denominator) {
    FcGL_Vec4_t result;
    int32_t i;
    for (i = 0; i <= 3; i++)
        result.fdata[i] = nominator.fdata[i] / denominator.fdata[i];
    return result;
}

static inline FcGL_Vec4_t FcGL_Vec4i_mul(FcGL_Vec4_t nominator, FcGL_Vec4_t denominator) {
    FcGL_Vec4_t result;
    int32_t i;
    for (i = 0; i <= 3; i++)
        result.idata[i] = nominator.idata[i] * denominator.idata[i];
    return result;
}

static inline FcGL_Vec4_t FcGL_Vec4f_mul(FcGL_Vec4_t nominator, FcGL_Vec4_t denominator) {
    FcGL_Vec4_t result;
    int32_t i;
    for (i = 0; i <= 3; i++)
        result.fdata[i] = nominator.fdata[i] * denominator.fdata[i];
    return result;
}

static inline FcGL_Vec4_t FcGL_Vec4f_add(FcGL_Vec4_t nominator, FcGL_Vec4_t denominator) {
    FcGL_Vec4_t result;
    int32_t i;
    for (i = 0; i < 4; i++)
        result.fdata[i] = nominator.fdata[i] + denominator.fdata[i];
    return result;
}

static inline FcGL_Vec4_t FcGL_Vec4i_sub(FcGL_Vec4_t nominator, FcGL_Vec4_t denominator) {
    FcGL_Vec4_t result;
    int32_t i;
    for (i = 0; i <= 3; i++)
        result.idata[i] = nominator.idata[i] - denominator.idata[i];
    return result;
}

static inline FcGL_Vec4_t FcGL_Vec4_normalize(FcGL_Vec4_t v) {
    return FcGL_Vec4f_div(v, FcGL_Vec4f_p0000_init(FcGL_Vec4f_length(v)));
}

static inline FcGL_Vec4_t FcGL_Vec4_cross3(FcGL_Vec4_t v0, FcGL_Vec4_t v1) {
    FcGL_Vec4_t result = FcGL_Vec4f(v0.f1 * v1.f2 - v1.f1 * v0.f2, v0.f2 * v1.f0 - v0.f0 * v1.f2,
                                    v0.f0 * v1.f1 - v0.f1 * v1.f0, 0);
    return result;
}

#endif //GRAPHICSTEST_FLOAT4_H
