#ifndef _FCMATH_H
#define _FCMATH_H

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>

#define FCMATHSTATIC
#define FCMATHFLOAT

#ifdef FCMATHFLOAT
#define FCTYPE float
#define tan tanf
#define cos cosf
#define sin sinf
#define sqrt sqrtf
#else
#define FCTYPE double
#endif

#ifdef FCMATHSTATIC
#define FCDEF static inline
#else
#define FCDEF extern inline
#endif

#define REVERSE_BIT_7BIT(x)    do { \
                                x = ((x & 0x44) >> 2) | ((x & 0x11) << 2) | (x & 0x2c);\
                                x = (x & 0x08) | ((x & 0x70) >> 4) | ((x & 0x07) << 4); } while(0)
#define REVERSE_BIT_8BIT(x)    do { \
                                x = (((x & 0xaa) >> 1) | ((x & 0x55) << 1));\
                                x = (((x & 0xcc) >> 2) | ((x & 0x33) << 2));\
                                x = x >> 4 | x << 4) while(0)
#define REVERSE_BIT_64BIT(x)    x = (((x & 0xaaaaaaaaaaaaaaaa) >> 1) | ((x & 0x5555555555555555) << 1));\
                                x = (((x & 0xcccccccccccccccc) >> 2) | ((x & 0x3333333333333333) << 2));\
                                x = (((x & 0xf0f0f0f0f0f0f0f0) >> 4) | ((x & 0x0f0f0f0f0f0f0f0f) << 4));\
                                x = (((x & 0xff00ff00ff00ff00) >> 8) | ((x & 0x00ff00ff00ff00ff) << 8));\
                                x = (((x & 0xffff0000ffff0000) >> 16) | ((x & 0x0000ffff0000ffff) << 16));\
                                x = x >> 32 | x << 32
#define SWAP_READ_32BIT(p) (((p)[0] << 24) | ((p)[1] << 16)| ((p)[2] << 8) | ((p)[3] << 0))
#define SWAP_READ_16BIT(p) (((p)[0] << 8) | ((p)[1] << 0))
#define SWAP_BYTE_16BIT(v)   ((((v) >> 8) & 0xff) | (((v) & 0xff) << 8))
#define SWAP_BYTE_32BIT(v) (((((v)&0xff000000) >> 24) | (((v)&0x00ff0000) >> 8) | ((v)&0x0000ff00) << 8) | (((v)&0x000000ff) << 24))
/*mat3 rotationMatrix(vec3 axis, float angle)
{
	axis = normalize(axis);
	float s = sin(angle);
	float c = cos(angle);
	float oc = 1.0 - c;

	return mat3(
		oc * axis.x * axis.x + c, oc * axis.x * axis.y - axis.z * s, oc * axis.z * axis.x + axis.y * s,
		oc * axis.x * axis.y + axis.z * s, oc * axis.y * axis.y + c, oc * axis.y * axis.z - axis.x * s,
		oc * axis.z * axis.x - axis.y * s, oc * axis.y * axis.z + axis.x * s, oc * axis.z * axis.z + c
	);
}*/

typedef union FcVec2_t {
    FCTYPE m[2];
} FcVec2_t;
typedef union FcVec3_t {
    FCTYPE m[3];
} FcVec3_t;
typedef union FcVec4_t {
    FcVec2_t v[2];
    FCTYPE m[4];
} FcVec4_t;
typedef union FcVec8_t {
    FcVec4_t v[2];
    FCTYPE m[8];
} FcVec8_t;

typedef union FcMatrix2x2_t {
    FcVec2_t v[2];
    FCTYPE m[2][2];
} FcMatrix2x2_t;
typedef union FcMatrix3x3_t {
    FcVec3_t v[3];
    FCTYPE m[3][3];
} FcMatrix3x3_t;
typedef union FcMatrix4x4_t {
    FcVec4_t v[4];
    FCTYPE m[4][4];
} FcMatrix4x4_t;

FCDEF uint16_t FcSwapbyte16(uint16_t a);

FCDEF uint32_t FcSwapbyte32(uint32_t a);

FCDEF uint64_t FcSwapbyte64(uint64_t a);

FCDEF FcVec2_t FcVec2(FCTYPE s0, FCTYPE s1);

FCDEF FcVec2_t FcVec2_add(FcVec2_t a, FcVec2_t b);

FCDEF FcVec2_t FcVec2_sub(FcVec2_t a, FcVec2_t b);

FCDEF FcVec2_t FcVec2_mul(FcVec2_t a, FcVec2_t b);

FCDEF FcVec2_t FcVec2_muls(FcVec2_t a, FCTYPE s);

FCDEF FcVec2_t FcVec2_norm(FcVec2_t a);

FCDEF FCTYPE FcVec2_length(FcVec2_t a);

FCDEF FCTYPE FcVec2_dot(FcVec2_t a, FcVec2_t b);

FCDEF FCTYPE FcVec2_cross(FcVec2_t a, FcVec2_t b);

FCDEF FcVec3_t FcVec3(FCTYPE s0, FCTYPE s1, FCTYPE s2);

FCDEF FCTYPE FcVec3_length(FcVec3_t a);

FCDEF FCTYPE FcVec3_dot(FcVec3_t a, FcVec3_t b);

FCDEF FcVec3_t FcVec3_add(FcVec3_t a, FcVec3_t b);

FCDEF FcVec3_t FcVec3_sub(FcVec3_t a, FcVec3_t b);

FCDEF FcVec3_t FcVec3_mul(FcVec3_t a, FcVec3_t b);

FCDEF FcVec3_t FcVec3_muls(FcVec3_t a, FCTYPE s);

FCDEF FcVec3_t FcVec3_norm(FcVec3_t a);

FCDEF FcVec3_t FcVec3_proj(FcVec3_t a, FcVec3_t onto);

FCDEF FcVec3_t FcVec3_cross(FcVec3_t a, FcVec3_t b);

FCDEF FcVec4_t FcVec4(FCTYPE s0, FCTYPE s1, FCTYPE s2, FCTYPE s3);

FCDEF FcVec4_t FcVec4_p0000_init(FCTYPE value);

FCDEF FCTYPE FcVec4_length(FcVec4_t a);

FCDEF FCTYPE FcVec4_sum(FcVec4_t a);

FCDEF FcVec4_t FcVec4_div(FcVec4_t nominator, FcVec4_t denominator);

FCDEF FcVec4_t FcVec4_mul(FcVec4_t nominator, FcVec4_t denominator);

FCDEF FcVec4_t FcVec4_add(FcVec4_t nominator, FcVec4_t denominator);

FCDEF FcVec4_t FcVec4_sub(FcVec4_t nominator, FcVec4_t denominator);

FCDEF FcVec4_t FcVec4_normalize(FcVec4_t a);

FCDEF FcVec4_t FcVec4_cross3(FcVec4_t a, FcVec4_t b);

FCDEF FcVec8_t FcVec8(FCTYPE, FCTYPE, FCTYPE, FCTYPE, FCTYPE, FCTYPE, FCTYPE, FCTYPE);

FCDEF FcVec8_t FcVec8_p00000000_init(FCTYPE value);

FCDEF FcVec8_t FcVec8_div(FcVec8_t nominator, FcVec8_t denominator);

FCDEF FcVec8_t FcVec8_mul(FcVec8_t nominator, FcVec8_t denominator);

FCDEF FcVec8_t FcVec8_mulc(FcVec8_t nominator, FCTYPE denominator);

FCDEF FcVec8_t FcVec8_addc(FcVec8_t nominator, FCTYPE denominator);

FCDEF FcVec8_t FcVec8f_add(FcVec8_t nominator, FcVec8_t denominator);

FCDEF FcMatrix4x4_t FcMatrix4x4(FCTYPE, FCTYPE, FCTYPE, FCTYPE,
                                FCTYPE, FCTYPE, FCTYPE, FCTYPE,
                                FCTYPE, FCTYPE, FCTYPE, FCTYPE,
                                FCTYPE, FCTYPE, FCTYPE, FCTYPE);

FCDEF FcMatrix4x4_t FcMatrix4x4_identity();

FCDEF FcMatrix4x4_t FcMatrix4x4_transpose(FcMatrix4x4_t matrix);

FCDEF FcMatrix4x4_t FcMatrix4x4_multiply_mm(FcMatrix4x4_t matrix_0, FcMatrix4x4_t matrix_1);

FCDEF FcVec4_t FcMatrix4x4_multiply_mv(FcMatrix4x4_t matrix_0, FcVec4_t vector_0);

FCDEF FcVec3_t FcMatrix4x4_multiply_position(FcMatrix4x4_t matrix, FcVec3_t position);

FCDEF FcMatrix4x4_t FcMatrix4x4_ortho(FCTYPE left, FCTYPE right, FCTYPE bottom, FCTYPE top, FCTYPE zNear, FCTYPE zFar);

FCDEF FcMatrix4x4_t FcMatrix4x4_rotation(FCTYPE angle_in_rad, FcVec3_t axis);

FCDEF FcMatrix4x4_t FcMatrix4x4_translate(FcVec3_t offset);

FCDEF FcMatrix4x4_t FcMatrix4x4_perspective(FCTYPE vertical_field_of_view_in_deg, FCTYPE aspect_ratio,
                                            FCTYPE near_view_distance, FCTYPE far_view_distance);

FCDEF FcMatrix4x4_t FcMatrix4x4_gl_look_at(FcVec3_t eay, FcVec3_t center, FcVec3_t up);

FCDEF FcMatrix4x4_t FcMatrix4x4_gl_look_at_view_matrix(FcVec3_t eay, FcVec3_t center, FcVec3_t up);

FCDEF void FcMatrix4x4f_fprintp(FcMatrix4x4_t matrix, int width, int precision);

FCDEF uint16_t FcSwapbyte16(uint16_t a) {
    return ((uint16_t) ((uint16_t) ((a >> 8u) & 0xffu) |
                        (((uint16_t) (a & 0xffu) << 8u))));
}

FCDEF uint32_t FcSwapbyte32(uint32_t a) {
    return ((
                    ((a & 0xff000000u) >> (uintptr_t) 24) |
                    ((a & 0x00ff0000u) >> (uintptr_t) 8) |
                    ((a & 0x0000ff00u) << (uintptr_t) 8)) |
            ((a & 0x000000ffu) << (uintptr_t) 24));
}

FCDEF uint64_t FcSwapbyte64(uint64_t a) {
    return (((a & 0x00000000000000ffull) << (uintptr_t) 56) |
            ((a & 0x000000000000ff00ull) << (uintptr_t) 40) |
            ((a & 0x0000000000ff0000ull) << (uintptr_t) 24) |
            ((a & 0x00000000ff000000ull) << (uintptr_t) 8) |
            ((a & 0x000000ff00000000ull) >> (uintptr_t) 8) |
            ((a & 0x0000ff0000000000ull) >> (uintptr_t) 24) |
            ((a & 0x00ff000000000000ull) >> (uintptr_t) 40) |
            ((a & 0xff00000000000000ull) >> (uintptr_t) 56));
}

FCDEF FcVec2_t FcVec2(FCTYPE s0, FCTYPE s1) { return (FcVec2_t) {s0, s1}; }

FCDEF FcVec2_t FcVec2_add(FcVec2_t a, FcVec2_t b) { return FcVec2(a.m[0] + b.m[0], a.m[1] + b.m[1]); }

FCDEF FcVec2_t FcVec2_sub(FcVec2_t a, FcVec2_t b) { return FcVec2(a.m[0] - b.m[0], a.m[1] - b.m[1]); }

FCDEF FcVec2_t FcVec2_mul(FcVec2_t a, FcVec2_t b) { return FcVec2(a.m[0] * b.m[0], a.m[1] * b.m[1]); }

FCDEF FcVec2_t FcVec2_muls(FcVec2_t a, FCTYPE s) { return FcVec2(a.m[0] * s, a.m[1] * s); }

FCDEF FcVec2_t FcVec2_norm(FcVec2_t a) {
    FCTYPE length = FcVec2_length(a);
    if (length > 0)
        return FcVec2(a.m[0] / length, a.m[1] / length);
    else
        return FcVec2(0, 0);
}

FCDEF FCTYPE FcVec2_length(FcVec2_t a) { return sqrt(a.m[0] * a.m[0] + a.m[1] * a.m[1]); }

FCDEF FCTYPE FcVec2_dot(FcVec2_t a, FcVec2_t b) { return a.m[0] * b.m[0] + a.m[1] * b.m[1]; }

FCDEF FCTYPE FcVec2_cross(FcVec2_t a, FcVec2_t b) { return a.m[0] * b.m[1] - a.m[1] * b.m[0]; }

FCDEF FcVec3_t FcVec3(FCTYPE s0, FCTYPE s1, FCTYPE s2) { return (FcVec3_t) {s0, s1, s2}; }

FCDEF FCTYPE FcVec3_length(FcVec3_t a) { return sqrt(a.m[0] * a.m[0] + a.m[1] * a.m[1] + a.m[2] * a.m[2]); }

FCDEF FCTYPE FcVec3_sum(FcVec3_t a) { return a.m[0] + a.m[1] + a.m[2]; }

FCDEF FCTYPE FcVec3_dot(FcVec3_t a, FcVec3_t b) { return a.m[0] * b.m[0] + a.m[1] * b.m[1] + a.m[2] * b.m[2]; }

FCDEF FcVec3_t FcVec3_add(FcVec3_t a, FcVec3_t b) { return FcVec3(a.m[0] + b.m[0], a.m[1] + b.m[1], a.m[2] + b.m[2]); }

FCDEF FcVec3_t FcVec3_sub(FcVec3_t a, FcVec3_t b) { return FcVec3(a.m[0] - b.m[0], a.m[1] - b.m[1], a.m[2] - b.m[2]); }

FCDEF FcVec3_t FcVec3_mul(FcVec3_t a, FcVec3_t b) { return FcVec3(a.m[0] * b.m[0], a.m[1] * b.m[1], a.m[2] * b.m[2]); }

FCDEF FcVec3_t FcVec3_muls(FcVec3_t a, FCTYPE s) { return FcVec3(a.m[0] * s, a.m[1] * s, a.m[2] * s); }

FCDEF FcVec3_t FcVec3_norm(FcVec3_t a) {
    FCTYPE length = FcVec3_length(a);
    if (length > 0)
        return FcVec3(a.m[0] / length, a.m[1] / length, a.m[2] / length);
    else
        return FcVec3(0, 0, 0);
}

FCDEF FcVec3_t FcVec3_proj(FcVec3_t a, FcVec3_t onto) {
    return FcVec3_muls(onto, FcVec3_dot(a, onto) / FcVec3_dot(onto, onto));
}

FCDEF FcVec3_t FcVec3_cross(FcVec3_t a, FcVec3_t b) {
    return FcVec3(
            a.m[1] * b.m[2] - a.m[2] * b.m[1],
            a.m[2] * b.m[0] - a.m[0] * b.m[2],
            a.m[0] * b.m[1] - a.m[1] * b.m[0]
    );
}

FCDEF FcVec4_t FcVec4(FCTYPE s0, FCTYPE s1, FCTYPE s2, FCTYPE s3) {
    return (FcVec4_t) {s0, s1, s2, s3};
}

FCDEF FcVec4_t FcVec4_p0000_init(FCTYPE value) {
    FcVec4_t result;
    int i;
    for (i = 0; i < 4; i++)
        result.m[i] = value;
    return result;
}

FCDEF FCTYPE FcVec4_length(FcVec4_t a) {
    return sqrt(a.m[0] * a.m[0] + a.m[1] * a.m[1] + a.m[2] * a.m[2] + a.m[3] * a.m[3]);
}

FCDEF FCTYPE FcVec4_sum(FcVec4_t a) {
    return a.m[0] + a.m[1] + a.m[2] + a.m[3];
}

FCDEF FcVec4_t FcVec4_div(FcVec4_t nominator, FcVec4_t denominator) {
    FcVec4_t result;
    int i;
    for (i = 0; i < 4; i++)
        result.m[i] = nominator.m[i] / denominator.m[i];
    return result;
}

FCDEF FcVec4_t FcVec4_mul(FcVec4_t nominator, FcVec4_t denominator) {
    FcVec4_t result;
    int i;
    for (i = 0; i < 4; i++)
        result.m[i] = nominator.m[i] * denominator.m[i];
    return result;
}

FCDEF FcVec4_t FcVec4_add(FcVec4_t nominator, FcVec4_t denominator) {
    FcVec4_t result;
    int i;
    for (i = 0; i < 4; i++)
        result.m[i] = nominator.m[i] + denominator.m[i];
    return result;
}

FCDEF FcVec4_t FcVec4_sub(FcVec4_t nominator, FcVec4_t denominator) {
    FcVec4_t result;
    int i;
    for (i = 0; i < 4; i++)
        result.m[i] = nominator.m[i] - denominator.m[i];
    return result;
}

FCDEF FcVec4_t FcVec4_normalize(FcVec4_t a) {
    return FcVec4_div(a, FcVec4_p0000_init(FcVec4_length(a)));
}

FCDEF FcVec4_t FcVec4_cross3(FcVec4_t a, FcVec4_t b) {
    FcVec4_t result = FcVec4(a.m[1] * b.m[2] - b.m[1] * a.m[2], a.m[2] * b.m[0] - a.m[0] * b.m[2],
                             a.m[0] * b.m[1] - a.m[1] * b.m[0], 0);
    return result;
}

FCDEF FcVec8_t FcVec8(FCTYPE s0, FCTYPE s1, FCTYPE s2, FCTYPE s3, FCTYPE s4, FCTYPE s5, FCTYPE s6, FCTYPE s7) {
    return (FcVec8_t) {s0, s1, s2, s3, s4, s5, s6, s7};
}

FCDEF FcVec8_t FcVec8_p00000000_init(FCTYPE value) {
    FcVec8_t result;
    int i;
    for (i = 0; i < 8; i++)
        result.m[i] = value;
    return result;
}

FCDEF FcVec8_t FcVec8_div(FcVec8_t nominator, FcVec8_t denominator) {
    FcVec8_t result;
    int i;
    for (i = 0; i < 8; i++)
        result.m[i] = nominator.m[i] / denominator.m[i];
    return result;
}

FCDEF FcVec8_t FcVec8_mul(FcVec8_t nominator, FcVec8_t denominator) {
    FcVec8_t result;
    int i;
    for (i = 0; i < 8; i++)
        result.m[i] = nominator.m[i] * denominator.m[i];
    return result;
}

FCDEF FcVec8_t FcVec8_mulc(FcVec8_t nominator, FCTYPE denominator) {
    FcVec8_t result;
    int i;
    for (i = 0; i < 8; i++)
        result.m[i] = nominator.m[i] * denominator;
    return result;
}

FCDEF FcVec8_t FcVec8_addc(FcVec8_t nominator, FCTYPE denominator) {
    FcVec8_t result;
    int i;
    for (i = 0; i < 8; i++)
        result.m[i] = nominator.m[i] + denominator;
    return result;
}

FCDEF FcVec8_t FcVec8f_add(FcVec8_t nominator, FcVec8_t denominator) {
    FcVec8_t result;
    int i;
    for (i = 0; i < 8; i++)
        result.m[i] = nominator.m[i] + denominator.m[i];
    return result;
}

FCDEF FcMatrix4x4_t FcMatrix4x4(
        FCTYPE m00, FCTYPE m10, FCTYPE m20, FCTYPE m30,
        FCTYPE m01, FCTYPE m11, FCTYPE m21, FCTYPE m31,
        FCTYPE m02, FCTYPE m12, FCTYPE m22, FCTYPE m32,
        FCTYPE m03, FCTYPE m13, FCTYPE m23, FCTYPE m33
) {
    return (FcMatrix4x4_t) {
            FcVec4(m00, m10, m20, m30),
            FcVec4(m01, m11, m21, m31),
            FcVec4(m02, m12, m22, m32),
            FcVec4(m03, m13, m23, m33)
    };
}

FCDEF FcMatrix4x4_t FcMatrix4x4_identity() {
    return FcMatrix4x4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    );
}

FCDEF FcMatrix4x4_t FcMatrix4x4_transpose(FcMatrix4x4_t matrix) {
    return FcMatrix4x4(
            matrix.v[0].m[0], matrix.v[1].m[0], matrix.v[2].m[0], matrix.v[3].m[0],
            matrix.v[0].m[1], matrix.v[1].m[1], matrix.v[2].m[1], matrix.v[3].m[1],
            matrix.v[0].m[2], matrix.v[1].m[2], matrix.v[2].m[2], matrix.v[3].m[2],
            matrix.v[0].m[3], matrix.v[1].m[3], matrix.v[2].m[3], matrix.v[3].m[3]
    );
}

FCDEF FcMatrix4x4_t FcMatrix4x4_multiply_mm(FcMatrix4x4_t matrix_0, FcMatrix4x4_t matrix_1) {
    FcMatrix4x4_t matrix_transpose = FcMatrix4x4_transpose(matrix_1);
    FcMatrix4x4_t result;
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            result.v[i].m[j] = FcVec4_sum(FcVec4_mul(matrix_0.v[i], matrix_transpose.v[j]));
    return result;
}

FCDEF FcVec4_t FcMatrix4x4_multiply_mv(FcMatrix4x4_t matrix_0, FcVec4_t vector_0) {
    FcVec4_t result;
    int i;
    for (i = 0; i < 4; i++)
        result.m[i] = FcVec4_sum(FcVec4_mul(matrix_0.v[i], vector_0));
    return result;
}

FCDEF FcVec3_t FcMatrix4x4_multiply_position(FcMatrix4x4_t matrix, FcVec3_t position) {
    FcVec3_t result = FcVec3(
            matrix.m[0][0] * position.m[0] + matrix.m[0][1] * position.m[1] + matrix.m[0][2] * position.m[2] +
            matrix.m[0][3],
            matrix.m[1][0] * position.m[0] + matrix.m[1][1] * position.m[1] + matrix.m[1][2] * position.m[2] +
            matrix.m[1][3],
            matrix.m[2][0] * position.m[0] + matrix.m[2][1] * position.m[1] + matrix.m[2][2] * position.m[2] +
            matrix.m[2][3]
    );

    FCTYPE w = matrix.m[3][0] * position.m[0] + matrix.m[3][1] * position.m[1] + matrix.m[3][2] * position.m[2] +
               matrix.m[3][3];
    if (w != 0 && w != 1)
        return FcVec3(result.m[0] / w, result.m[1] / w, result.m[2] / w);

    return result;
}

FCDEF FcMatrix4x4_t FcMatrix4x4_ortho(FCTYPE left, FCTYPE right, FCTYPE bottom, FCTYPE top, FCTYPE zNear, FCTYPE zFar) {
    FCTYPE l = left, r = right, b = bottom, t = top, n = zNear, f = zFar;
    FCTYPE tx = -(r + l) / (r - l);
    FCTYPE ty = -(t + b) / (t - b);
    FCTYPE tz = -(f + n) / (f - n);
    return FcMatrix4x4(
            2 / (r - l), 0, 0, tx,
            0, 2 / (t - b), 0, ty,
            0, 0, 2 / (f - n), tz,
            0, 0, 0, 1
    );
}

FCDEF FcMatrix4x4_t FcMatrix4x4_rotation(FCTYPE angle_in_rad, FcVec3_t axis) {
    FcVec3_t normalized_axis = FcVec3_norm(axis);
    FCTYPE s0 = normalized_axis.m[0],
            s1 = normalized_axis.m[1],
            s2 = normalized_axis.m[2],
            c = cos(angle_in_rad),
            s = sin(angle_in_rad);

    return FcMatrix4x4(
            c + s0 * s0 * (1 - c), s0 * s1 * (1 - c) - s2 * s, s0 * s2 * (1 - c) + s1 * s, 0,
            s1 * s0 * (1 - c) + s2 * s, c + s1 * s1 * (1 - c), s1 * s2 * (1 - c) - s0 * s, 0,
            s2 * s0 * (1 - c) - s1 * s, s2 * s1 * (1 - c) + s0 * s, c + s2 * s2 * (1 - c), 0,
            0, 0, 0, 1
    );
}

FCDEF FcMatrix4x4_t FcMatrix4x4_translate(FcVec3_t offset) {
    return FcMatrix4x4(
            1, 0, 0, offset.m[0],
            0, 1, 0, offset.m[1],
            0, 0, 1, offset.m[2],
            0, 0, 0, 1
    );
}

FCDEF FcMatrix4x4_t
FcMatrix4x4_perspective(FCTYPE vertical_field_of_view_in_deg, FCTYPE aspect_ratio, FCTYPE near_view_distance,
                        FCTYPE far_view_distance) {
    FCTYPE fovy_in_rad = (FCTYPE) vertical_field_of_view_in_deg / (FCTYPE) 180.0 * (FCTYPE) M_PI;
    FCTYPE f = (FCTYPE) 1.0 / tan(fovy_in_rad / (FCTYPE) 2.0);
    FCTYPE ar = aspect_ratio;
    FCTYPE nd = near_view_distance, fd = far_view_distance;

    return FcMatrix4x4(
            f / ar, 0, 0, 0,
            0, f, 0, 0,
            0, 0, (fd + nd) / (nd - fd), (2 * fd * nd) / (nd - fd),
            0, 0, -1, 0
    );
}

FCDEF FcMatrix4x4_t FcMatrix4x4_gl_look_at(FcVec3_t eay, FcVec3_t center, FcVec3_t up) {
    FcVec3_t s2 = FcVec3_muls(FcVec3_norm(FcVec3_sub(center, eay)), -1);
    FcVec3_t s0 = FcVec3_norm(FcVec3_cross(up, s2));
    FcVec3_t s1 = FcVec3_cross(s2, s0);

    return FcMatrix4x4(
            s0.m[0], s1.m[0], s2.m[0], -FcVec3_dot(eay, s0),
            s0.m[1], s1.m[1], s2.m[1], -FcVec3_dot(eay, s1),
            s0.m[2], s1.m[2], s2.m[2], -FcVec3_dot(eay, s2),
            0, 0, 0, 1
    );
}

FCDEF FcMatrix4x4_t
FcMatrix4x4_gl_look_at_view_matrix(FcVec3_t eay, FcVec3_t center, FcVec3_t up) {
    FcVec3_t s2 = FcVec3_muls(FcVec3_norm(FcVec3_sub(center, eay)), -1);
    FcVec3_t s0 = FcVec3_norm(FcVec3_cross(up, s2));
    FcVec3_t s1 = FcVec3_cross(s2, s0);

    return FcMatrix4x4(
            s0.m[0], s1.m[0], s2.m[0], 0,
            s0.m[1], s1.m[1], s2.m[1], 0,
            s0.m[2], s1.m[2], s2.m[2], 0,
            0, 0, 0, 1
    );
}

FCDEF void FcMatrix4x4f_fprintp(FcMatrix4x4_t matrix, int width, int precision) {
    FcMatrix4x4_t m = matrix;
    int w = width, p = precision, i;
    for (i = 0; i < 4; i++) {
        fprintf(stderr, "| %*.*f %*.*f %*.*f %*.*f |\n",
                w, p, m.m[0][i], w, p, m.m[1][i], w, p, m.m[2][i], w, p, m.m[3][i]
        );
    }
}

FCDEF FcMatrix3x3_t FcMatrix3x3(
        FCTYPE m00, FCTYPE m10, FCTYPE m20,
        FCTYPE m01, FCTYPE m11, FCTYPE m21,
        FCTYPE m02, FCTYPE m12, FCTYPE m22
) {
    return (FcMatrix3x3_t) {
            FcVec3(m00, m10, m20),
            FcVec3(m01, m11, m21),
            FcVec3(m02, m12, m22)
    };
}

FCDEF FcVec3_t FcMatrix3x3_multiply_mv(FcMatrix3x3_t matrix, FcVec3_t vec) {
    FcVec3_t result;
    int i;
    for (i = 0; i < 3; i++)
        result.m[i] = FcVec3_sum(FcVec3_mul(matrix.v[i], vec));
    return result;
}

FCDEF FcMatrix3x3_t FcMatrix3x3_rotation(FCTYPE angle_in_rad) {
    FCTYPE c = cos(angle_in_rad),
            s = sin(angle_in_rad);

    return FcMatrix3x3(c, -s, 0,
                       s, c, 0,
                       0, 0, 1
    );
}

#undef FCDEF

#endif _FCMATH_H
