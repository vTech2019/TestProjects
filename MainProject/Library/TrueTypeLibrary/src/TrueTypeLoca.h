#include <stdint.h>
#include <stdlib.h>

#ifndef __TRUETYPELOCA_H__
#define __TRUETYPELOCA_H__

#include "TrueTypeMath.h"
#include "TrueTypeHead.h"
#include "TrueTypeMaxp.h"

#define TrueTypeLocaFormat16 0
#define TrueTypeLocaFormat32 1

typedef struct _TrueTypeLoca_t {
    uint16_t glyph_offsets16[1];
} TrueTypeLoca_t;

static inline void TrueTypeLOCA(TrueTypeLoca_t* src, TrueTypeLoca_t* dst, int16_t index_to_loc_format, uint16_t numGlyphs, int8_t byte_swap) {
    size_t i = 0, j = 0;
    const size_t i_v_end = numGlyphs / 32;
    size_t i_end = numGlyphs % 32;
    if (index_to_loc_format == TrueTypeLocaFormat16) {
        if (byte_swap) {
            struct vector32u16 { uint16_t s[32]; } *ptr_v16 = src->glyph_offsets16;
            struct vector32u16* ptr_dst_v16 = dst->glyph_offsets16;
            for (; i < i_v_end; i++) {
	ptr_dst_v16[i] = ptr_v16[i];
	for (j = 0; j < 32; j++)
	    ptr_dst_v16[i].s[j] = swap_byte_32(ptr_dst_v16[i].s[j]);
            }
            for (j = 0; j < i_end; j++)
	ptr_dst_v16[i].s[j] = swap_byte_32(ptr_v16[i].s[j]);
        }
    }
    else if (index_to_loc_format == TrueTypeLocaFormat32) {
        if (byte_swap) {
            struct vector32u32 { uint32_t s[32]; } *ptr_v32 = (uint32_t*)src->glyph_offsets16;
            struct vector32u32* ptr_dst_v32 = (uint32_t*)dst->glyph_offsets16;

            for (; i < i_v_end; i++) {
	ptr_dst_v32[i] = ptr_v32[i];
	for (j = 0; j < 32; j++)
	    ptr_dst_v32[i].s[j] = swap_byte_32(ptr_dst_v32[i].s[j]);
            }
            for (j = 0; j < i_end; j++)
	ptr_dst_v32[i].s[j] = swap_byte_32(ptr_v32[i].s[j]);
        }
    }
}

#endif
