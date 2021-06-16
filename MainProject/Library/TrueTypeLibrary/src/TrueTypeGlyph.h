#include <stdint.h>
#include <stdlib.h>

#ifndef __TRUETYPEGLYPH_H__
#define __TRUETYPEGLYPH_H__


struct TrueTypeGlyf_simple_parameters {
    int16_t x, y;
};
typedef struct _TrueTypeGlyf_composite_parameters {
    float xscale;
    float scale01;
    float scale10;
    float yscale;
    int16_t xtranslate;
    int16_t ytranslate;
    uint16_t point1;
    uint16_t point2;
} TrueTypeGlyph_composite_parameters;

struct TrueTypeGlyf_simple_t {
    int16_t number_contours;
    int16_t x_min;
    int16_t y_min;
    int16_t x_max;
    int16_t y_max;
    uint16_t number_instructions;
    uint16_t number_points;
    uint16_t* end_countours;
    uint8_t* instructions;
    struct TrueTypeGlyf_simple_parameters* parameters;
};
struct TrueTypeGlyf_composite_t {
    int16_t number_contours;
    int16_t x_min;
    int16_t y_min;
    int16_t x_max;
    int16_t y_max;
    uint16_t number_instructions;
    uint16_t composite_number;
    uint16_t* glyph_index;
    uint8_t* instructions;
    TrueTypeGlyph_composite_parameters* parameters;
};
typedef struct _TrueTypeGlyf_t {
    uint16_t number_glyph;
    union {
        struct TrueTypeGlyf_simple_t simple;
        struct TrueTypeGlyf_composite_t composite;
    } ptr_glyph[1];
} TrueTypeGlyf_t;

typedef struct _TrueTypeGlyf_size_t {
    uint16_t numberGlyph;
    uint32_t size;
    uint32_t simple;
    uint32_t composite;
    uint32_t instructions;
    uint32_t endCounter;
    uint32_t parameters;
    uint32_t glyphIndex;
} TrueTypeGlyph_size_t;

void TrueTypeGLYF_size(uint8_t* tables, struct _TrueTypeGlyf_size_t* m_size, int8_t swap_byte);
void TrueTypeGlyf(uint8_t* src, TrueTypeGlyf_t* dst, struct _TrueTypeGlyf_size_t* ptr_size);
#endif
