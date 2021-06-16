#ifndef __TRUETYPEGLYPH_H__
#define __TRUETYPEGLYPH_H__
#include <stdint.h>
#include "TrueTypeHhea.h"
#include "TrueTypeError.h"
typedef  ALIGNED(4, struct, _TrueTypeGlyf_simple_parameters {
	int16_t x;
    int16_t y;
}TrueTypeGlyf_simple_parameters);

typedef ALIGNED(32, struct, _TrueTypeGlyf_composite_parameters {
	float xscale;
	float scale01;
	float scale10;
	float yscale;
	float xtranslate;
	float ytranslate;
	float point1;
	float point2;
} TrueTypeGlyph_composite_parameters);

struct TrueTypeGlyf_simple_t {
	int16_t number_contours;
	int16_t x_min;
	int16_t y_min;
	int16_t x_max;
	int16_t y_max;
	uint16_t numberInstructions;
	uint16_t number_points;
	uint16_t* endCountours;
	uint8_t* instructions;
	uint8_t* m_flags;
	TrueTypeGlyf_simple_parameters* parameters;
};
struct TrueTypeGlyf_composite_t {
	int16_t number_contours;
	int16_t x_min;
	int16_t y_min;
	int16_t x_max;
	int16_t y_max;
	uint16_t numberInstructions;
	uint16_t composite_number;
	uint16_t* glyphIndex;
	uint8_t* instructions;
	TrueTypeGlyph_composite_parameters* parameters;
};
union TrueTypeGlyfParameters{
	struct TrueTypeGlyf_simple_t simple;
	struct TrueTypeGlyf_composite_t composite;
};
typedef ALIGNED64(struct, _TrueTypeGlyf_t {
	uint16_t number_glyph;
	union TrueTypeGlyfParameters ptr_glyph[1];
} TrueTypeGlyf_t);

typedef struct _TrueTypeGlyf_size_t {
	uint16_t numberGlyph;
	uint32_t flags;
	uint32_t size;
	uint32_t instructions;
	uint32_t endCounter;
	uint32_t parameters;
	uint32_t glyphIndex;
} TrueTypeGlyph_size_t;

struct _TrueTypeGlyf_size_t TrueTypeGLYF_size(uint8_t* tables);


void TrueTypeGlyf(uint8_t* tables, TrueTypeGlyf_t* dst, struct _TrueTypeGlyf_size_t* ptr_size);

void TrueTypeGlyf_print(TrueTypeGlyf_t* glyph, uint8_t showPoints);

#endif
