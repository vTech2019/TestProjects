#ifndef __FCGL_MATRIX4X4_H__
#define __FCGL_MATRIX4X4_H__
#define _USE_MATH_DEFINES

#include "FcGL_Vec4.h"
#include "FcGL_Vec3.h"
#include <math.h>
#include <stdio.h>

typedef union _FcGL_Matrix4x4_t {
    FcGL_Vec4_t v[4];
    float m[4][4];
} FcGL_Matrix4x4_t;

static inline FcGL_Matrix4x4_t FcGL_Matrix4x4f(
        float m00, float m10, float m20, float m30,
        float m01, float m11, float m21, float m31,
        float m02, float m12, float m22, float m32,
        float m03, float m13, float m23, float m33
) {
    return (FcGL_Matrix4x4_t) {
            FcGL_Vec4f(m00, m10, m20, m30),
            FcGL_Vec4f(m01, m11, m21, m31),
            FcGL_Vec4f(m02, m12, m22, m32),
            FcGL_Vec4f(m03, m13, m23, m33)
    };
}

static inline FcGL_Matrix4x4_t FcGL_Matrix4x4f_identity() {
    return FcGL_Matrix4x4f(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    );
}

static inline FcGL_Matrix4x4_t FcGL_Matrix4x4f_transpose(FcGL_Matrix4x4_t matrix) {
    return FcGL_Matrix4x4f(
            matrix.v[0].f0, matrix.v[1].f0, matrix.v[2].f0, matrix.v[3].f0,
            matrix.v[0].f1, matrix.v[1].f1, matrix.v[2].f1, matrix.v[3].f1,
            matrix.v[0].f2, matrix.v[1].f2, matrix.v[2].f2, matrix.v[3].f2,
            matrix.v[0].f3, matrix.v[1].f3, matrix.v[2].f3, matrix.v[3].f3
    );
}

static inline FcGL_Vec4_t FcGL_Matrix4x4f_multiply_mv(FcGL_Matrix4x4_t matrix_0, union FcGL_Vec4_t vector_0) {
    FcGL_Vec4_t result;
    int i;
    for (i = 0; i < 4; i++)
        result.fdata[i] = FcGL_Vec4f_sum(FcGL_Vec4f_mul(matrix_0.v[i], vector_0));
    return result;
}

static inline FcGL_Matrix4x4_t FcGL_Matrix4x4f_multiply_mm(FcGL_Matrix4x4_t matrix_0, FcGL_Matrix4x4_t matrix_1) {
    FcGL_Matrix4x4_t matrix_transpose = FcGL_Matrix4x4f_transpose(matrix_1);
    FcGL_Matrix4x4_t result;
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            result.v[i].fdata[j] = FcGL_Vec4f_sum(FcGL_Vec4f_mul(matrix_0.v[i], matrix_transpose.v[j]));
    return result;
}

static FcGL_Vec3_t FcGL_Matrix4x4f_multiply_position(FcGL_Matrix4x4_t matrix, FcGL_Vec3_t position) {
    FcGL_Vec3_t result = FcGL_Vec3f(
            matrix.m[0][0] * position.f0 + matrix.m[0][1] * position.f1 + matrix.m[0][2] * position.f2 + matrix.m[0][3],
            matrix.m[1][0] * position.f0 + matrix.m[1][1] * position.f1 + matrix.m[1][2] * position.f2 + matrix.m[1][3],
            matrix.m[2][0] * position.f0 + matrix.m[2][1] * position.f1 + matrix.m[2][2] * position.f2 + matrix.m[2][3]
    );

    float w =
            matrix.m[3][0] * position.f0 + matrix.m[3][1] * position.f1 + matrix.m[3][2] * position.f2 + matrix.m[3][3];
    if (w != 0 && w != 1)
        return FcGL_Vec3f(result.f0 / w, result.f1 / w, result.f2 / w);

    return result;
}

static inline FcGL_Matrix4x4_t
FcGL_Matrix4x4f_ortho(float left, float right, float bottom, float top, float near, float far) {
    float l = left, r = right, b = bottom, t = top, n = near, f = far;
    float tx = -(r + l) / (r - l);
    float ty = -(t + b) / (t - b);
    float tz = -(f + n) / (f - n);
    return FcGL_Matrix4x4f(
            2 / (r - l), 0, 0, tx,
            0, 2 / (t - b), 0, ty,
            0, 0, 2 / (f - n), tz,
            0, 0, 0, 1
    );
}

static inline const FcGL_Matrix4x4_t
FcGL_Matrix4x4f_orthot(float left, float right, float bottom, float top, float zNear, float zFar) {
    float sum_rl, sum_tb, sum_nf, inv_rl, inv_tb, inv_nf;
    sum_rl = (right + left);
    sum_tb = (top + bottom);
    sum_nf = (zNear + zFar);
    inv_rl = (1.0f / (right - left));
    inv_tb = (1.0f / (top - bottom));
    inv_nf = (1.0f / (zNear - zFar));
    return FcGL_Matrix4x4f((inv_rl + inv_rl), 0.0f, 0.0f, 0.0f,
                           0.0f, (inv_tb + inv_tb), 0.0f, 0.0f,
                           0.0f, 0.0f, (inv_nf + inv_nf), 0.0f,
                           (-sum_rl * inv_rl), (-sum_tb * inv_tb), (sum_nf * inv_nf), 1.0f);
}

static inline FcGL_Matrix4x4_t FcGL_Matrix4x4f_rotation(float angle_in_rad, FcGL_Vec3_t axis) {
    FcGL_Vec3_t normalized_axis = FcGL_Vec3f_norm(axis);
    float x = normalized_axis.f0,
            y = normalized_axis.f1,
            z = normalized_axis.f2;
    float c = cosf(angle_in_rad), s = sinf(angle_in_rad);

    return FcGL_Matrix4x4f(
            c + x * x * (1 - c), x * y * (1 - c) - z * s, x * z * (1 - c) + y * s, 0,
            y * x * (1 - c) + z * s, c + y * y * (1 - c), y * z * (1 - c) - x * s, 0,
            z * x * (1 - c) - y * s, z * y * (1 - c) + x * s, c + z * z * (1 - c), 0,
            0, 0, 0, 1
    );
}

static inline FcGL_Matrix4x4_t FcGL_Matrix4x4f_translate(FcGL_Vec3_t offset) {
    return FcGL_Matrix4x4f(
            1, 0, 0, offset.f0,
            0, 1, 0, offset.f1,
            0, 0, 1, offset.f2,
            0, 0, 0, 1
    );
}

static inline FcGL_Matrix4x4_t
FcGL_Matrix4x4f_gl_perspective(float vertical_field_of_view_in_deg, float aspect_ratio, float near_view_distance,
                               float far_view_distance) {
    float fovy_in_rad = vertical_field_of_view_in_deg / 180.0f * M_PI;
    float f = 1.0f / tanf(fovy_in_rad / 2.0f);
    float ar = aspect_ratio;
    float nd = near_view_distance, fd = far_view_distance;

    return FcGL_Matrix4x4f(
            f / ar, 0, 0, 0,
            0, f, 0, 0,
            0, 0, (fd + nd) / (nd - fd), (2 * fd * nd) / (nd - fd),
            0, 0, -1, 0
    );
}

static inline FcGL_Matrix4x4_t FcGL_Matrix4x4f_gl_look_at(FcGL_Vec3_t eay, FcGL_Vec3_t center, FcGL_Vec3_t up) {
    FcGL_Vec3_t z = FcGL_Vec3f_muls(FcGL_Vec3f_norm(FcGL_Vec3f_sub(center, eay)), -1);
    FcGL_Vec3_t x = FcGL_Vec3f_norm(FcGL_Vec3f_cross(up, z));
    FcGL_Vec3_t y = FcGL_Vec3f_cross(z, x);

    return FcGL_Matrix4x4f(
            x.f0, y.f0, z.f0, 0,
            x.f1, y.f1, z.f1, 0,
            x.f2, y.f2, z.f2, 0,
            -FcGL_Vec3f_dot(eay, x), -FcGL_Vec3f_dot(eay, y), -FcGL_Vec3f_dot(eay, z), 1
    );
}

static inline FcGL_Matrix4x4_t
FcGL_Matrix4x4f_gl_look_at_view_matrix(FcGL_Vec3_t eay, FcGL_Vec3_t center, FcGL_Vec3_t up) {
    FcGL_Vec3_t z = FcGL_Vec3f_muls(FcGL_Vec3f_norm(FcGL_Vec3f_sub(center, eay)), -1);
    FcGL_Vec3_t x = FcGL_Vec3f_norm(FcGL_Vec3f_cross(up, z));
    FcGL_Vec3_t y = FcGL_Vec3f_cross(z, x);

    return FcGL_Matrix4x4f(
            x.f0, y.f0, z.f0, 0,
            x.f1, y.f1, z.f1, 0,
            x.f2, y.f2, z.f2, 0,
            0, 0, 0, 1
    );
}

static void FcGL_Matrix4x4_fprintp(FcGL_Matrix4x4_t matrix, int width, int precision) {
    FcGL_Matrix4x4_t m = matrix;
    int w = width, p = precision, i;
    for (i = 0; i < 4; i++) {
        fprintf(stderr, "| %*.*f %*.*f %*.*f %*.*f |\n",
                w, p, m.m[0][i], w, p, m.m[1][i], w, p, m.m[2][i], w, p, m.m[3][i]
        );
    }
}

#endif //__FCGL_MATRIX4X4_H__
