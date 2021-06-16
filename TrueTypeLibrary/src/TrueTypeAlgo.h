#ifndef _TRUETYPEINTERFACE_H
#define _TRUETYPEINTERFACE_H

#include <stdint.h>
#include <float.h>
#include <TrueTypeMath.h>
#include "TrueTypeGlyph.h"

#ifndef max
#define max(x, y) ((x < y) ? y: x)
#endif
#ifndef min
#define min(x, y) ((x > y) ? y: x)
#endif
#define STACK_LENGTH(data) (sizeof(data)/sizeof(*data))

static inline float TrueTypeGlyf_unitToPixel(float unit, float points, float dpi, float unitPerElement) {
	return unit * points * dpi / (dpi * unitPerElement);
}

//static inline int glyph_bbox(const SFT* sft, unsigned long outline, int box[4])
//{
//	double xScale, yScale;
//
//	box[0] = geti16(sft->font, outline + 2);
//	box[1] = geti16(sft->font, outline + 4);
//	box[2] = geti16(sft->font, outline + 6);
//	box[3] = geti16(sft->font, outline + 8);
//	if (box[2] <= box[0] || box[3] <= box[1])
//		return -1;
//	xScale = sft->xScale / sft->font->unitsPerEm;
//	yScale = sft->yScale / sft->font->unitsPerEm;
//	box[0] = (int)floor(box[0] * xScale + sft->xOffset);
//	box[1] = (int)floor(box[1] * yScale + sft->yOffset);
//	box[2] = (int)ceil(box[2] * xScale + sft->xOffset);
//	box[3] = (int)ceil(box[3] * yScale + sft->yOffset);
//	return 0;
//}
static inline uint16_t TrueType_Line(float line_x, float x0, float x1, float line_y, float y0, float y1) {
	float m_min_y = min(y0, y1);
	float m_max_y = max(y0, y1);
	if (!(line_y >= m_min_y && line_y < m_max_y))
		return 0;
	float t = (line_y - y0) / (y1 - y0);
	if (t >= 0.0f && t < 1.0f)
		return (x0 + (x1 - x0) * t) < line_x;
	return 0;
}

static inline uint16_t
TrueType_BezierCurve(float x0, float x1, float x2, float x3,
	float y0, float y1, float y2, float y3) {
	float ax = x3 - 2 * x2 + x1;
	float ay = y3 - 2 * y2 + y1;
	if (ax == 0 || ay == 0) {
		x2 = x3;
		y2 = y3;
	}
	ax = x3 - 2 * x2 + x1;
	ay = y3 - 2 * y2 + y1;
	float bx = 2 * (x2 - x1);
	float by = 2 * (y2 - y1);
	float dx = bx * bx - 4 * ax * (x1 - x0);
	float dy = by * by - 4 * ay * (y1 - y0);
	if (dy < 0)
		return 0;
	float dSqrt = sqrtf(dy);
	float ty0 = (-by + dSqrt) / (2 * ay);
	float ty1 = (-by - dSqrt) / (2 * ay);
	float line0 = ty0 >= 0.f && ty0 <= 1.f;
	float line1 = ty1 >= 0.f && ty1 <= 1.f;
	float p0 = x1 + ty0 * bx + ty0 * ty0 * ax;
	float p1 = x1 + ty1 * bx + ty1 * ty1 * ax;
	float dist0 = (x0 - p0) * line0;
	float dist1 = (x0 - p1) * line1;
	if (dist0 > 0 && dist1 > 0 && dist0 != dist1)
		return 0;
	if (dist0 > 0 || dist1 > 0)
		return 1;
	return 0;
}
/*static inline float TrueType_BezierCurve_test(
	float x0, float x1, float x2, float x3,
	float y0, float y1, float y2, float y3,
	float* p0, float* p1) {
	float ax = x3 - 2 * x2 + x1;
	float ay = y3 - 2 * y2 + y1;
	if (ax == 0 || ay == 0) {
		x2 = x3;
		y2 = y3;
	}
	ax = x3 - 2 * x2 + x1;
	ay = y3 - 2 * y2 + y1;
	float bx = 2 * (x2 - x1);
	float by = 2 * (y2 - y1);
	float dx = bx * bx - 4 * ax * (x1 - x0);
	float dy = by * by - 4 * ay * (y1 - y0);
	float dSqrt = sqrtf(dy);
	float ty0 = (-by + dSqrt) / (2 * ay);
	float ty1 = (-by - dSqrt) / (2 * ay);
	*p0 = x1 + ty0 * bx + ty0 * ty0 * ax;
	*p1 = x1 + ty1 * bx + ty1 * ty1 * ax;
	float line0 = ty0 >= 0.f && ty0 <= 1.f;
	float line1 = ty1 >= 0.f && ty1 <= 1.f;
	float dist0 = (x0 - p0) * line0;
	float dist1 = (x0 - p1) * line1;
	return { dist0, dist1 };
}*/
static inline int16_t
TrueType_BezierCurve_test(
	float x0, float x1, float x2, float x3,
	float y0, float y1, float y2, float y3)
{
	float ax = x1 - 2 * x2 + x3;
	float ay = y1 - 2 * y2 + y3;
	float bx = 2 * (x2 - x1);
	if (ay == 0.0f) {
		if (y1 != y2) {
			float ty0 = (y0 - y1) / (2 * (y2 - y1));
			float line0 = ty0 >= 0.0f && ty0 <= 1.0f;
			float p0 = x1 + ty0 * bx + ty0 * ty0 * ax;
			float dist = (x0 - p0) * line0;
			if (dist > 0)
				return 1;
			else
				return 0;
		}
		else if (y1 == y2 && y2 != y3) {
			float ty0 = sqrtf((y0 - y1) / (y3 - y2));
			float line0 = ty0 >= 0.0f && ty0 <= 1.0f;
			float p0 = x1 + ty0 * bx + ty0 * ty0 * ax;
			float dist = (x0 - p0) * line0;
			if (dist > 0)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else {
		float vSqrt = sqrtf(ay * y0 + y2 * y2 - y1 * y3);
		float ty0 = (y1 - y2 + vSqrt) / ay;
		float ty1 = (y1 - y2 - vSqrt) / ay;
		float line0 = ty0 >= 0.0f && ty0 <= 1.0f;
		float line1 = ty1 >= 0.0f && ty1 <= 1.0f;
		float p0 = x1 + ty0 * bx + ty0 * ty0 * ax;
		float p1 = x1 + ty1 * bx + ty1 * ty1 * ax;
		float dist0 = (x0 - p0) * line0;
		float dist1 = (x0 - p1) * line1;
		if (dist0 > 0 && dist1 > 0)
			return 0;
		if (dist0 > 0 || dist1 > 0)
			return 1;
		return 0;
	}
}

static inline float TrueType_LinePoint(float x0, float x1, float line_y, float y0, float y1) {
	float t = (line_y - y0) / (y1 - y0);
	if (line_y >= y0 && line_y <= y1 || line_y >= y1 && line_y <= y0)
		if (t >= 0.0f && t <= 1.0f)
			return (x0 + (x1 - x0) * t);

	return FLT_MAX;
}
static inline void
TrueType_BezierCurve_test2(
	float points[2], float x1, float x2, float x3,
	float y0, float y1, float y2, float y3)
{
	float ax = x1 - 2 * x2 + x3;
	float ay = y1 - 2 * y2 + y3;
	float bx = 2 * (x2 - x1);
	points[0] = -FLT_MAX;
	points[1] = -FLT_MAX;
	if (ay == 0.0f) {
		if (y1 != y2) {
			float ty0 = (y0 - y1) / (2 * (y2 - y1));
			uint16_t line0 = ty0 >= 0.0f && ty0 <= 1.0f;
			if (line0)
				points[0] = x1 + ty0 * bx + ty0 * ty0 * ax;
		}
		else if (y1 == y2 && y2 != y3) {
			float ty0 = sqrtf((y0 - y1) / (y3 - y2));
			uint16_t line0 = ty0 >= 0.0f && ty0 <= 1.0f;
			if (line0)
				points[0] = x1 + ty0 * bx + ty0 * ty0 * ax;
		}
	}
	else {
		float vSqrt = sqrtf(ay * y0 + y2 * y2 - y1 * y3);
		float ty0 = (y1 - y2 + vSqrt) / ay;
		float ty1 = (y1 - y2 - vSqrt) / ay;
		uint16_t line0 = ty0 >= 0.0f && ty0 <= 1.0f;
		uint16_t line1 = ty1 >= 0.0f && ty1 <= 1.0f;
		if (line0)
			points[0] = x1 + ty0 * bx + ty0 * ty0 * ax;
		if (line1 && vSqrt)
			points[1] = x1 + ty1 * bx + ty1 * ty1 * ax;
	}
}
static void TrueTypeGlyf_parameters(const struct TrueTypeGlyf_simple_t* simple, float cashe[8], int16_t y) {
	uint16_t tmp, i0, i1, i2, i3;
	int16_t mParameters[8][2];
	uint8_t mFlags[8];
	float mCashe[16];
	float x0, x1, x2, y0, y1, y2, f0, f1, t;
	for (i0 = 0, i1 = simple->endCountours[0], i2 = simple->endCountours[0]; i0 < simple->number_points; ) {
		tmp = 0;
		for (i3 = 0; i3 < 8; i3++) {
			mParameters[i3][0] = INT16_MAX;
			mParameters[i3][1] = INT16_MAX;
		}
		if (i2 == i1)
			i3 = 0;
		switch (i1) {
		default: tmp = 8;
		case 7: mParameters[7][0] = simple->parameters[i0 + 7].x; mParameters[7][1] = simple->parameters[i0 + 7].y; mFlags[i0 + 7] = simple->m_flags[i0 + 7];
		case 6: mParameters[6][0] = simple->parameters[i0 + 6].x; mParameters[6][1] = simple->parameters[i0 + 6].y; mFlags[i0 + 6] = simple->m_flags[i0 + 6];
		case 5: mParameters[5][0] = simple->parameters[i0 + 5].x; mParameters[5][1] = simple->parameters[i0 + 5].y; mFlags[i0 + 5] = simple->m_flags[i0 + 5];
		case 4: mParameters[4][0] = simple->parameters[i0 + 4].x; mParameters[4][1] = simple->parameters[i0 + 4].y; mFlags[i0 + 4] = simple->m_flags[i0 + 4];
		case 3: mParameters[3][0] = simple->parameters[i0 + 3].x; mParameters[3][1] = simple->parameters[i0 + 3].y; mFlags[i0 + 3] = simple->m_flags[i0 + 3];
		case 2: mParameters[2][0] = simple->parameters[i0 + 2].x; mParameters[2][1] = simple->parameters[i0 + 2].y; mFlags[i0 + 2] = simple->m_flags[i0 + 2];
		case 1: mParameters[1][0] = simple->parameters[i0 + 1].x; mParameters[1][1] = simple->parameters[i0 + 1].y; mFlags[i0 + 1] = simple->m_flags[i0 + 1];
		case 0: mParameters[0][0] = simple->parameters[i0 + 0].x; mParameters[0][1] = simple->parameters[i0 + 0].y; mFlags[i0 + 0] = simple->m_flags[i0 + 0];
		}

		x0 = mParameters[i2][0];
		x1 = mParameters[i3 + 0][0];
		x2 = mParameters[i3 + 1][0];
		y0 = mParameters[i2][1];
		y1 = mParameters[i3 + 0][1];
		y2 = mParameters[i3 + 1][1];
		f0 = mFlags[i2];
		f1 = mFlags[i3];
		for (i3 = 0; i3 < 8; i3++) {
			if (y <= y1 && y >= y0)
				if (f0 > 0 && f1 > 0) {
					t = (y - y0) / (y1 - y0);
					if (t >= 0.0f && t < 1.0f) {
						mCashe[i0] = x0 - (x1 - x0) * t;
						i0++;
					}
				}
			if (f1 < 1) {
				TrueType_BezierCurve_test2(mCashe + i0, x0, x1, x2, y, y0, y1, y2);
				i0 += 2;
			}
			x0 = x1;
			x1 = x2;
			y0 = y1;
			y1 = y2;
			f0 = f1;
			x2 = mParameters[i3 + 2][0];
			y2 = mParameters[i3 + 2][1];
			f1 = mFlags[i3 + 1];
		}
		i0 += tmp ? tmp : i1;
		i2 = i0 - 1;
		i3 = i0;
	}
}
static inline float TrueTypeGlyf_getMinLineDistance(float min, float y_0, const struct TrueTypeGlyf_simple_t* simple) {
	size_t i1, j1, j2, j3;
	float mMin = FLT_MAX;
	float mCurrMin = min;
	int16_t mSign = INT16_MAX;
	for (i1 = j2 = j3 = 0; i1 < simple->number_contours; i1++) {
		j1 = simple->endCountours[i1];
		int16_t x0 = simple->parameters[j1].x;
		int16_t y0 = simple->parameters[j1].y;
		int16_t x1 = simple->parameters[j2].x;
		int16_t y1 = simple->parameters[j2].y;
		uint16_t f0 = simple->m_flags[j1] & 1;
		for (; j2 <= simple->endCountours[i1]; j1 = j2, j2++) {
			if (j2 + 1 > simple->endCountours[i1])
				j3 = i1 == 0 ? 0 : simple->endCountours[i1 - 1] + 1;
			else
				j3 = j2 + 1;
			int16_t x2 = simple->parameters[j3].x;
			int16_t y2 = simple->parameters[j3].y;
			uint16_t f1 = simple->m_flags[j2] & 1;
			int16_t sign = 0;
			float data[2] = { -FLT_MAX, -FLT_MAX };
			if ((f0 == 1) & (f1 == 1)) {
				data[0] = TrueType_LinePoint(x0, x1, y_0, y0, y1);
				sign = y0 > y1 ? -1 : 1;
			}
			else if (f1 == 0) {
				TrueType_BezierCurve_test2(data, x0, x1, x2, y_0, y0, y1, y2);
				sign = y0 > y2 ? -1 : 1;
			}
			if (data[0] > mCurrMin) {
				if (data[0] == mMin)
					mSign += sign;
				if (data[0] < mMin) {
					mMin = data[0];
					mSign = sign;
				}
			}
			if (data[1] > mCurrMin) {
				if (data[1] == mMin)
					mSign += sign;
				if (data[1] < mMin) {
					mMin = data[1];
					mSign = sign;
				}
			}
			x0 = x1;
			y0 = y1;
			x1 = x2;
			y1 = y2;
			f0 = f1;
		}
	}
	if (mSign == 0 && mMin != FLT_MAX)
		mMin = TrueTypeGlyf_getMinLineDistance(mMin, y_0, simple);
	return mMin;
}
static inline void TrueTypeGlyf_getMinLineDistances(int8_t* line, uint32_t width, float scale, float xMin, float y_0, const struct TrueTypeGlyf_simple_t* simple) {
	size_t i1, j1, j2, j3;
	int16_t sign = 0;
	for (i1 = j2 = j3 = 0; i1 < simple->number_contours; i1++) {
		j1 = simple->endCountours[i1];
		int16_t x0 = simple->parameters[j1].x;
		int16_t y0 = simple->parameters[j1].y;
		int16_t x1 = simple->parameters[j2].x;
		int16_t y1 = simple->parameters[j2].y;
		uint16_t f0 = simple->m_flags[j1] & 1;
		for (; j2 <= simple->endCountours[i1]; j1 = j2, j2++) {
			if (j2 + 1 > simple->endCountours[i1])
				j3 = i1 == 0 ? 0 : simple->endCountours[i1 - 1] + 1;
			else
				j3 = j2 + 1;
			int16_t x2 = simple->parameters[j3].x;
			int16_t y2 = simple->parameters[j3].y;
			uint16_t f1 = simple->m_flags[j2] & 1;
			if ((f0 == 1) & (f1 == 1)) {
				int32_t value = TrueType_LinePoint(x0, x1, y_0, y0, y1);
				//if (y_0 == y0 && y0 == y1) {
				//	value = x1;
				//	sign = -1;
				//}
				sign = y0 < y1 ? 1 : -1;
				value -= xMin;
				value /= scale;
				uint32_t d0 = (uint32_t)value;
				if (d0 < width)
					line[d0] += sign;
			}
			else if (f1 == 0) {
				float dataf[2];
				TrueType_BezierCurve_test2(dataf, x0, x1, x2, y_0, y0, y1, y2);
				int8_t sign0 = y0 < y2 ? 1 : -1;
				int8_t sign1 = y0 < y2 ? 1 : -1;
				dataf[0] -= xMin;
				dataf[1] -= xMin;
				dataf[0] /= scale;
				dataf[1] /= scale;
				uint32_t d0 = (int32_t)dataf[0];
				uint32_t d1 = (int32_t)dataf[1];
				if (d0 < width)
					line[d0] += sign0;
				if (d1 < width)
					line[d1] += sign1;
			}
			x0 = x1;
			y0 = y1;
			x1 = x2;
			y1 = y2;
			f0 = f1;
		}
	}
}
static inline void TrueTypeGlyf_bmpScanConverter_simple(const struct TrueTypeGlyf_simple_t* simple,
	uint8_t* const image, size_t widthImage, size_t widthBox, size_t heightBox,
	float scale, float xMin, float yMin) {
	ptrdiff_t i0;

	const float rotateHeight = (heightBox - 1) * scale;
	//#pragma omp parallel for
	for (i0 = 0; i0 < heightBox; i0++) {
		size_t indexCashe = 8;
		float min;
		min = -FLT_MAX;
		size_t j0 = 0, i1;
		int16_t y_0 = rotateHeight - (scale * i0) + yMin;
		int16_t m_color = 0;
		min = TrueTypeGlyf_getMinLineDistance(min, y_0, simple);
		for (j0 = 0; j0 < widthBox; j0++) {
			int16_t x_0 = (scale * j0) + xMin;
			while (min < x_0) {
				m_color += ((x_0 - min) > 0);
				min = TrueTypeGlyf_getMinLineDistance(min, y_0, simple);
			}
			if (m_color != 0)
				image[i0 * widthImage + j0] = min(255, 255 * (m_color & 1));
		}
	}
}
static inline void TrueTypeGlyf_bmpScanConverter_test(const struct TrueTypeGlyf_simple_t* simple,
	uint8_t* const image, size_t widthImage, size_t widthBox, size_t heightBox,
	float scale, float xMin, float yMin) {
	ptrdiff_t i0;
	ptrdiff_t j0, j2;

	float x0, y0;
	const float rotateHeight = (heightBox - 1) * scale + yMin;

	for (j2 = 0; j2 < simple->number_points; j2++) {
		unsigned f0 = simple->m_flags[j2] & 1;
		x0 = simple->parameters[j2].x;
		y0 = simple->parameters[j2].y;
		i0 = (rotateHeight - y0) / scale;
		j0 = (x0 - xMin) / scale;
		if (f0 == 1) {
			image[i0 * widthImage + j0] = 255;
		}
		else
			image[i0 * widthImage + j0] = 127;
	}
}
static inline void TrueTypeGlyf_bmpScanConverter_simple3(const struct TrueTypeGlyf_simple_t* simple,
	uint8_t* const image, size_t widthImage, size_t widthBox, size_t heightBox,
	float scale, float xMin, float yMin) {
	ptrdiff_t i0;
	int8_t* line = (int8_t*)malloc(widthBox);
	if (!line) return;
	const float rotateHeight = (heightBox - 1) * scale;
	//#pragma omp parallel for
	for (i0 = 0; i0 < heightBox; i0++) {
		size_t j0 = 0;
		int32_t y_0 = rotateHeight - (scale * i0) + yMin;
		int16_t m_color = 0;
		for (j0 = 0; j0 < widthBox; j0++) line[j0] = 0;

		TrueTypeGlyf_getMinLineDistances(line, widthBox, scale, xMin, y_0, simple);

		for (j0 = 0; j0 < widthBox; j0++) {
			//int16_t x_0 = (scale * j0) + xMin;
			m_color += line[j0];

			if (m_color != 0)
				image[i0 * widthImage + j0] = min(255, 127 * (m_color));
		}
	}
	free(line);
	TrueTypeGlyf_bmpScanConverter_test(simple, image, widthImage, widthBox, heightBox, scale, xMin, yMin);
}
static inline void TrueTypeGlyf_bmpScanConverter_simple2(const struct TrueTypeGlyf_simple_t* simple,
	uint8_t* const image, size_t widthImage, size_t widthBox, size_t heightBox,
	float scale, float xMin, float yMin) {
	//TrueTypeGlyf_bmpScanConverter_test(simple, image, widthImage, widthBox, heightBox, scale, xMin, yMin);
	//return;

	ptrdiff_t i0;
	const float rotateHeight = (heightBox - 1) * scale;
#pragma omp parallel for
	for (i0 = 0; i0 < heightBox; i0++) {
		ptrdiff_t i2;
		ptrdiff_t j0, j1, j2, j3;
		float x0, x1, x2, y0, y1, y2;

		uint16_t m_color;
		float y_0 = rotateHeight - (scale * i0) + yMin;
		for (j0 = 0; j0 < widthBox; j0++) {
			m_color = 0;
			float x_0 = (scale * j0) + xMin;
			for (i2 = 0, j2 = 0; i2 < simple->number_contours; i2++) {
				j1 = simple->endCountours[i2];
				x0 = simple->parameters[j1].x;
				y0 = simple->parameters[j1].y;
				x1 = simple->parameters[j2].x;
				y1 = simple->parameters[j2].y;
				unsigned f0 = simple->m_flags[j1] & 1;
				unsigned f1 = simple->m_flags[j2] & 1;
				for (j3 = j2 + 1; j3 <= j1; j3++) {
					unsigned f2 = simple->m_flags[j3] & 1;
					x2 = simple->parameters[j3].x;
					y2 = simple->parameters[j3].y;
					if ((f0 == 1) && (f1 == 1)) {
						m_color ^= TrueType_Line(x_0, x0, x1, y_0, y0, y1);
					}
					else if (f1 == 0u) {
						m_color ^= TrueType_BezierCurve_test(x_0, x0, x1, x2, y_0, y0, y1, y2);
					}
					if (f1 == 1 && ((x1 - x_0) * (x1 - x_0) + (y_0 - y1) * (y_0 - y1)) < 2) {
						m_color = 2;
						goto goColor;
					}
					if (f1 == 0 && ((x1 - x_0) * (x1 - x_0) + (y_0 - y1) * (y_0 - y1)) < 1) {
						m_color = 2;
						goto goColor;
					}
					x0 = x1, x1 = x2;
					y0 = y1, y1 = y2;
					f0 = f1, f1 = f2;
				}
				x2 = simple->parameters[j2].x;
				y2 = simple->parameters[j2].y;
				if (f1 == 1 && ((x1 - x_0) * (x1 - x_0) + (y_0 - y1) * (y_0 - y1)) < 2) {
					m_color = 4;
					goto goColor;
				}
				if (f1 == 0 && ((x1 - x_0) * (x1 - x_0) + (y_0 - y1) * (y_0 - y1)) < 1) {
					m_color = 4;
					goto goColor;
				}
				if ((f0 == 1) && (f1 == 1)) {
					m_color ^= TrueType_Line(x_0, x0, x1, y_0, y0, y1);
				}
				else if (f1 == 0u) {
					m_color ^= TrueType_BezierCurve_test(x_0, x0, x1, x2, y_0, y0, y1, y2);
				}
				if (j2 >= j1) {
					j2 = j2;
				}
				j2 = j3;
			}
		goColor:
			image[i0 * widthImage + j0] = 63 * m_color;
		}
	}
}
static inline void TrueTypeGlyf_bmpScanConverter_composite(const union TrueTypeGlyfParameters* glyphs, size_t id,
	uint8_t* const image, size_t widthImage, size_t widthBox, size_t heightBox, float scale) {
	ptrdiff_t i0, i1, i2;
	ptrdiff_t j0, j1, j2;
	uint16_t m_color;

	struct TrueTypeGlyf_simple_t* m_simple;
	struct TrueTypeGlyf_composite_t* m_compos;
	TrueTypeGlyph_composite_parameters m_param;
	m_compos = &glyphs[id].composite;
	//if (id >= 677)
	//    id = id;
	for (i0 = 0; i0 < heightBox; i0++) {
		for (j0 = 0; j0 < widthBox; j0++) {
			m_color = 0;
			for (i1 = 0; i1 < m_compos->composite_number; i1++) {
				m_simple = &glyphs[m_compos->glyphIndex[i1]].simple;
				m_param.xscale = scale * m_compos->parameters[i1].xscale;
				m_param.scale01 = scale * m_compos->parameters[i1].scale01;
				m_param.yscale = scale * m_compos->parameters[i1].yscale;
				m_param.scale10 = scale * m_compos->parameters[i1].scale10;
				m_param.xtranslate = m_compos->x_min - (m_compos->parameters[i1].xtranslate);
				m_param.ytranslate = m_compos->y_min - (m_compos->parameters[i1].ytranslate);

				float x_0 = (j0 * m_param.xscale + ((float)heightBox - i0) * m_param.scale01 + m_param.xtranslate);
				float y_0 = (j0 * m_param.scale10 + ((float)heightBox - i0) * m_param.yscale + m_param.ytranslate);
				for (i2 = 0, j2 = 0; i2 < m_simple->number_contours; i2++) {
					j1 = m_simple->endCountours[i2];
					float x0 = m_simple->parameters[j1].x;
					float y0 = m_simple->parameters[j1].y;
					uint8_t f0 = m_simple->m_flags[j1] & 1;
					for (; j2 <= m_simple->endCountours[i2]; j1 = j2, j2++) {
						float x1 = m_simple->parameters[j2].x;
						float y1 = m_simple->parameters[j2].y;
						float x2 = m_simple->parameters[j2 + 1].x;
						float y2 = m_simple->parameters[j2 + 1].y;
						uint8_t f1 = m_simple->m_flags[j2] & 1;
						if ((f0 > 0) & (f1 > 0)) {
							m_color ^= TrueType_BezierCurve(x_0, x0, x1, x1, y_0, y0, y1, y1);
						}
						else if (f1 == 0) {
							m_color ^= TrueType_BezierCurve(x_0, x0, x1, x2, y_0, y0, y1, y2);
						}
						x0 = x1;
						y0 = y1;
						f0 = f1;
					}
				}
			}
			//if (m_color)
			image[i0 * widthImage + j0] = 64 * (m_color + 2);
		}
	}
}

#undef CASHE_LENGTH

static inline void
TrueTypeGlyf_bmpScanConverter(const union TrueTypeGlyfParameters* glyphs, size_t id, uint8_t* const memory, size_t pitch, size_t widthBox, size_t heightBox, float scaleFactor) {
	if (glyphs[id].simple.number_contours > 0) {
		TrueTypeGlyf_bmpScanConverter_simple3(&glyphs[id].simple, memory, pitch, widthBox, heightBox, 1.0f / scaleFactor, glyphs[id].simple.x_min, glyphs[id].simple.y_min);
	}
	else {
		TrueTypeGlyf_bmpScanConverter_composite(glyphs, id, memory, pitch, widthBox, heightBox, 1.0f / scaleFactor);
	}
}

#endif
