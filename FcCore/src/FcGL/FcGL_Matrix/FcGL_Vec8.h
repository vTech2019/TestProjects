

#ifndef __FCGL_VEC8_H__
#define __FCGL_VEC8_H__

#include <math.h>
#include <inttypes.h>

#include "FcGL_Vec4.h"
#include "FcGL_Vec2.h"

typedef union FcGL_Vec8_t {
    FcGL_Vec2_t vec2[4];
    FcGL_Vec4_t vec4[2];
    float fdata[8];
    int32_t idata[8];
    int16_t sdata[16];
    int8_t cdata[32];
} FcGL_Vec8_t;

static inline FcGL_Vec8_t FcGL_Vec8f(float s0, float s1, float s2, float s3, float s4, float s5, float s6, float s7) {
    return (FcGL_Vec8_t) {s0, s1, s2, s3, s4, s5, s6, s7};
}

static inline FcGL_Vec8_t FcGL_Vec8i_p00000000_init(int32_t value) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 7; i++)
        result.idata[i] = value;
    return result;
}

static inline FcGL_Vec8_t FcGL_Vec8f_p00000000_init(float value) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 7; i++)
        result.fdata[i] = value;
    return result;
}

static inline FcGL_Vec8_t FcGL_Vec8_int16ToUint8_saturate(FcGL_Vec8_t a, FcGL_Vec8_t b) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 15; i++)
        result.cdata[i] = a.sdata[i];
    for (i = 0; i <= 15; i++)
        result.cdata[16 + i] = b.sdata[i];
    return result;
}

static inline FcGL_Vec8_t FcGL_Vec8_int32ToInt16_saturate(FcGL_Vec8_t a, FcGL_Vec8_t b) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 7; i++)
        result.sdata[i] = a.idata[i];
    for (i = 0; i <= 7; i++)
        result.sdata[8 + i] = b.idata[i];
    return result;
}

static inline FcGL_Vec8_t FcGL_Vec8_floatToInt(FcGL_Vec8_t value) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 7; i++)
        result.idata[i] = (int32_t) value.fdata[i];
    return result;
}

static inline FcGL_Vec8_t FcGL_Vec8f_div(FcGL_Vec8_t nominator, FcGL_Vec8_t denominator) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 7; i++)
        result.fdata[i] = nominator.fdata[i] / denominator.fdata[i];
    return result;
}

static inline FcGL_Vec8_t FcGL_Vec8i_mul(FcGL_Vec8_t nominator, FcGL_Vec8_t denominator) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 7; i++)
        result.idata[i] = nominator.idata[i] * denominator.idata[i];
    return result;
}

static inline FcGL_Vec8_t FcGL_Vec8f_mul(FcGL_Vec8_t nominator, FcGL_Vec8_t denominator) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 7; i++)
        result.fdata[i] = nominator.fdata[i] * denominator.fdata[i];
    return result;
}

static inline FcGL_Vec8_t FcGL_Vec8f_mulc(FcGL_Vec8_t nominator, float denominator) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 7; i++)
        result.fdata[i] = nominator.fdata[i] * denominator;
    return result;
}

static inline FcGL_Vec8_t FcGL_Vec8i_mulc(FcGL_Vec8_t nominator, int32_t denominator) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 7; i++)
        result.idata[i] = nominator.idata[i] * denominator;
    return result;
}

static inline FcGL_Vec8_t FcGL_Vec8i_addc(FcGL_Vec8_t nominator, int32_t denominator) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 7; i++)
        result.idata[i] = nominator.idata[i] + denominator;
    return result;
}

static inline FcGL_Vec8_t FcGL_Vec8f_addc(FcGL_Vec8_t nominator, float denominator) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 7; i++)
        result.fdata[i] = nominator.fdata[i] + denominator;
    return result;
}

static inline FcGL_Vec8_t FcGL_Vec8f_add(FcGL_Vec8_t nominator, FcGL_Vec8_t denominator) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 7; i++)
        result.fdata[i] = nominator.fdata[i] + denominator.fdata[i];
    return result;
}

static inline FcGL_Vec8_t FcGL_Vec8i_sub(FcGL_Vec8_t nominator, FcGL_Vec8_t denominator) {
    FcGL_Vec8_t result;
    int32_t i;
    for (i = 0; i <= 7; i++)
        result.idata[i] = nominator.idata[i] - denominator.idata[i];
    return result;
}

#endif //GRAPHICSTEST_FLOAT8_H
