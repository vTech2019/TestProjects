//
// Created by human on 29.02.2020.
//

#ifndef GRAPHICSTEST_MATRIX4X4_H
#define GRAPHICSTEST_MATRIX4X4_H
#define _USE_MATH_DEFINES
#include "vector4.h"
#include "vector3.h"
#include <math.h>
#include <stdio.h>
typedef struct  fMatrix4x4_t {
	union {
		float m[4][4];
		struct vec4_t v[4];
	};
}fMatrix4x4_t;

static inline fMatrix4x4_t fMatrix4x4(
	float m00, float m10, float m20, float m30,
	float m01, float m11, float m21, float m31,
	float m02, float m12, float m22, float m32,
	float m03, float m13, float m23, float m33
) {
	return (fMatrix4x4_t) {
		.v[0] = fvec4(m00, m10, m20, m30),
			.v[1] = fvec4(m01, m11, m21, m31),
			.v[2] = fvec4(m02, m12, m22, m32),
			.v[3] = fvec4(m03, m13, m23, m33)
	};
}
static inline fMatrix4x4_t fMatrix4x4_identity() {
	return fMatrix4x4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

static inline fMatrix4x4_t fMatrix4x4_transpose(fMatrix4x4_t matrix) {
	return fMatrix4x4(
		matrix.v[0].f0, matrix.v[1].f0, matrix.v[2].f0, matrix.v[3].f0,
		matrix.v[0].f1, matrix.v[1].f1, matrix.v[2].f1, matrix.v[3].f1,
		matrix.v[0].f2, matrix.v[1].f2, matrix.v[2].f2, matrix.v[3].f2,
		matrix.v[0].f3, matrix.v[1].f3, matrix.v[2].f3, matrix.v[3].f3
	);
}

static inline fMatrix4x4_t fMatrix4x4_multiply(fMatrix4x4_t matrix_0, fMatrix4x4_t matrix_1) {
	fMatrix4x4_t matrix_transpose = fMatrix4x4_transpose(matrix_1);
	fMatrix4x4_t result;
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			result.v[i].fdata[j] = fvec4_length(fvec4_mul(matrix_0.v[i], matrix_transpose.v[j]));
	return result;
}

static vec3_t fMatrix4x4_multiply_position(fMatrix4x4_t matrix, vec3_t position) {
	vec3_t result = fvec3(
		matrix.m[0][0] * position.f0 + matrix.m[0][1] * position.f1 + matrix.m[0][2] * position.f2 + matrix.m[0][3],
		matrix.m[1][0] * position.f0 + matrix.m[1][1] * position.f1 + matrix.m[1][2] * position.f2 + matrix.m[1][3],
		matrix.m[2][0] * position.f0 + matrix.m[2][1] * position.f1 + matrix.m[2][2] * position.f2 + matrix.m[2][3]
	);

	float w = matrix.m[3][0] * position.f0 + matrix.m[3][1] * position.f1 + matrix.m[3][2] * position.f2 + matrix.m[3][3];
	if (w != 0 && w != 1)
		return fvec3(result.f0 / w, result.f1 / w, result.f2 / w);

	return result;
}

static inline fMatrix4x4_t fMatrix4x4_ortho(float left, float right, float bottom, float top, float back, float front) {
	float l = left, r = right, b = bottom, t = top, n = front, f = back;
	float tx = -(r + l) / (r - l);
	float ty = -(t + b) / (t - b);
	float tz = -(f + n) / (f - n);
	return fMatrix4x4(
		2 / (r - l), 0, 0, tx,
		0, 2 / (t - b), 0, ty,
		0, 0, 2 / (f - n), tz,
		0, 0, 0, 1
	);
}

static inline fMatrix4x4_t fMatrix4x4_rotation(float angle_in_rad, vec3_t axis) {
	vec3_t normalized_axis = fvec3_norm(axis);
	float x = normalized_axis.f0,
		y = normalized_axis.f1,
		z = normalized_axis.f2;
	float c = cosf(angle_in_rad), s = sinf(angle_in_rad);

	return fMatrix4x4(
		c + x * x * (1 - c), x * y * (1 - c) - z * s, x * z * (1 - c) + y * s, 0,
		y * x * (1 - c) + z * s, c + y * y * (1 - c), y * z * (1 - c) - x * s, 0,
		z * x * (1 - c) - y * s, z * y * (1 - c) + x * s, c + z * z * (1 - c), 0,
		0, 0, 0, 1
	);
}

static inline fMatrix4x4_t fMatrix4x4_translate(vec3_t offset) {
	return fMatrix4x4(
		1, 0, 0, offset.f0,
		0, 1, 0, offset.f1,
		0, 0, 1, offset.f2,
		0, 0, 0, 1
	);
}
static inline fMatrix4x4_t fMatrix4x4_gl_perspective(float vertical_field_of_view_in_deg, float aspect_ratio, float near_view_distance, float far_view_distance) {
	float fovy_in_rad = vertical_field_of_view_in_deg / 180 * M_PI;
	float f = 1.0f / tanf(fovy_in_rad / 2.0f);
	float ar = aspect_ratio;
	float nd = near_view_distance, fd = far_view_distance;

	return fMatrix4x4(
		f / ar, 0, 0, 0,
		0, f, 0, 0,
		0, 0, (fd + nd) / (nd - fd), (2 * fd * nd) / (nd - fd),
		0, 0, -1, 0
	);
}
static inline fMatrix4x4_t fMatrix4x4_gl_look_at(vec3_t eay, vec3_t center, vec3_t up) {
	vec3_t z = fvec3_muls(fvec3_norm(fvec3_sub(center, eay)), -1);
	vec3_t x = fvec3_norm(fvec3_cross(up, z));
	vec3_t y = fvec3_cross(z, x);

	return fMatrix4x4(
		x.f0, y.f0, z.f0, 0,
		x.f1, y.f1, z.f1, 0,
		x.f2, y.f2, z.f2, 0,
		-fvec3_dot(eay, x), -fvec3_dot(eay, y), -fvec3_dot(eay, z), 1
	);
}

static inline fMatrix4x4_t fMatrix4x4_gl_look_at_view_matrix(vec3_t eay, vec3_t center, vec3_t up) {
	vec3_t z = fvec3_muls(fvec3_norm(fvec3_sub(center, eay)), -1);
	vec3_t x = fvec3_norm(fvec3_cross(up, z));
	vec3_t y = fvec3_cross(z, x);

	return fMatrix4x4(
		x.f0, y.f0, z.f0, 0,
		x.f1, y.f1, z.f1, 0,
		x.f2, y.f2, z.f2, 0,
		0, 0, 0, 1
	);
}

static void fMatrix4x4_fprintp(fMatrix4x4_t matrix, int width, int precision) {
	fMatrix4x4_t m = matrix;
	int w = width, p = precision;
	for (int r = 0; r < 4; r++) {
		fprintf(stderr, "| %*.*f %*.*f %*.*f %*.*f |\n",
			w, p, m.m[0][r], w, p, m.m[1][r], w, p, m.m[2][r], w, p, m.m[3][r]
		);
	}
}

#endif //GRAPHICSTEST_MATRIX4X4_H
