
#ifndef GRAPHICSTEST_FLOAT3_H
#define GRAPHICSTEST_FLOAT3_H
#include <math.h>

#define st_check_vec3(actual, expected, epsilon) printf( "%s: got (%.2f %.2f %.2f), expected (%.2f %.2f %.2f)\n",                           \
	(fabs((actual).f0 - (expected).f0) < (epsilon) &&                                        \
	fabs((actual).f1 - (expected).f1) < (epsilon) &&                                        \
	fabs((actual).f2 - (expected).f2) < (epsilon)   ? "true" : "false") ,					\
	(actual).f0, (actual).f1, (actual).f2,                                                   \
	(expected).f0, (expected).f1, (expected).f2                                              \
)

typedef struct vec3_t {
    union {
        struct { float f0, f1, f2; };
        struct { unsigned u0, u1, u2; };
        float fdata[3];
    };
}vec3_t;
static inline vec3_t fvec3(float x, float y, float z) { return  (vec3_t) { x, y, z }; }
static inline float  fvec3_length(vec3_t v) { return sqrtf(v.f0 * v.f0 + v.f1 * v.f1 + v.f2 * v.f2); }
static inline float  fvec3_dot(vec3_t a, vec3_t b) { return a.f0 * b.f0 + a.f1 * b.f1 + a.f2 * b.f2; }
static inline vec3_t fvec3_add(vec3_t a, vec3_t b) { return fvec3(a.f0 + b.f0, a.f1 + b.f1, a.f2 + b.f2 ); }
static inline vec3_t fvec3_sub(vec3_t a, vec3_t b) { return fvec3(a.f0 - b.f0, a.f1 - b.f1, a.f2 - b.f2 ); }
static inline vec3_t fvec3_mul(vec3_t a, vec3_t b) { return fvec3(a.f0 * b.f0, a.f1 * b.f1, a.f2 * b.f2 ); }
static inline vec3_t fvec3_muls(vec3_t a, float s) { return fvec3(a.f0 * s, a.f1 * s, a.f2 * s ); }
static inline vec3_t fvec3_norm(vec3_t v) {
	float length = fvec3_length(v);
	if (length > 0)
		return  fvec3( v.f0 / length, v.f1 / length, v.f2 / length );
	else
		return  fvec3( 0, 0, 0 );
}

static inline vec3_t fvec3_proj(vec3_t v, vec3_t onto) {
	return fvec3_muls(onto, fvec3_dot(v, onto) / fvec3_dot(onto, onto));
}

static inline vec3_t fvec3_cross(vec3_t a, vec3_t b) {
	return fvec3(
		a.f1* b.f2 - a.f2 * b.f1,
		a.f2* b.f0 - a.f0 * b.f2,
		a.f0* b.f1 - a.f1 * b.f0
	);
}
#endif 