//
// Created by human on 29.02.2020.
//

#ifndef GRAPHICSTEST_FLOAT4_H
#define GRAPHICSTEST_FLOAT4_H
#include <math.h>
#include <immintrin.h>
typedef struct vec4_t {
    union {
        struct {float f0, f1, f2, f3;};
        struct {unsigned u0, u1, u2, u3;};
        float fdata[4];
    };
}vec4_t;

static inline struct vec4_t fvec4(float s0, float s1, float s2, float s3){
    return (vec4_t) { s0, s1, s2, s3 };
}
static inline struct vec4_t fvec4_p0000_init(float value){
    return (vec4_t){ value, value,value,value };
}

static inline float fvec4_length(struct vec4_t v){
    return sqrtf(v.f0 * v.f0 + v.f1 * v.f1 + v.f2 * v.f2 + v.f3 * v.f3);
}

static inline float fvec4_sum(struct vec4_t v){
    return v.f0 + v.f1 + v.f2 + v.f3;
}

static inline struct vec4_t fvec4_div(struct vec4_t nominator, struct vec4_t denominator){
    struct vec4_t result;
    result.f0 = nominator.f0 / denominator.f0;
    result.f1 = nominator.f1 / denominator.f1;
    result.f2 = nominator.f2 / denominator.f2;
    result.f3 = nominator.f3 / denominator.f3;
    return result;
}
static inline struct vec4_t fvec4_mul(struct vec4_t nominator, struct vec4_t denominator){
    struct vec4_t result;
    result.f0 = nominator.f0 * denominator.f0;
    result.f1 = nominator.f1 * denominator.f1;
    result.f2 = nominator.f2 * denominator.f2;
    result.f3 = nominator.f3 * denominator.f3;
    return result;
}
static inline struct vec4_t fvec4_add(struct vec4_t nominator, struct vec4_t denominator){
    struct vec4_t result;
    result.f0 = nominator.f0 + denominator.f0;
    result.f1 = nominator.f1 + denominator.f1;
    result.f2 = nominator.f2 + denominator.f2;
    result.f3 = nominator.f3 + denominator.f3;
    return result;
}
static inline struct vec4_t fvec4_sub(struct vec4_t nominator, struct vec4_t denominator){
    struct vec4_t result;
    result.f0 = nominator.f0 - denominator.f0;
    result.f1 = nominator.f1 - denominator.f1;
    result.f2 = nominator.f2 - denominator.f2;
    result.f3 = nominator.f3 - denominator.f3;
    return result;
}

static inline struct vec4_t fvec4_normalize(struct vec4_t v){
    return fvec4_div(v,fvec4_p0000_init(fvec4_length(v)));
}

static inline struct vec4_t fvec4_cross3(struct vec4_t v0, struct vec4_t v1) {
    struct vec4_t result = fvec4( v0.f1 * v1.f2 - v1.f1 * v0.f2, v0.f2 * v1.f0 - v0.f0 * v1.f2, v0.f0 * v1.f1 - v0.f1 * v1.f0, 0 );
    return result;
}

#endif //GRAPHICSTEST_FLOAT4_H
