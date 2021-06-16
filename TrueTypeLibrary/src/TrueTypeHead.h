#ifndef __TRUETYPEHEAD_H__
#define __TRUETYPEHEAD_H__

#include "stdafx.h"
#include "TrueTypeError.h"

#define HEAD_BASELINE_Y 1
#define LEFT_SIDEBEARING_X 2
#define INSTRUCTIONS_POINT_SIZE 4
#define INTEGER_PPEM 8
#define INSTRUCTIONS_ADVANCE_WIDTH 16
#define TrueTypeLeftSidebearingX 2
#define TrueTypeLeftSidebearingX 2

// Bit 4 - instructions may alter advance width (the advance widths might not scale linearly);
// Bits 5-10 - defined by Apple;
// Bit 11 - font compressed with Agfa MicroType Compression.
// Note: All other bits must be zero.
typedef ALIGNED64(struct, _TrueTypeHead_t {
	uint32_t version;
	uint32_t font_revision;
	uint32_t checksum_adjustment;
	uint32_t magic_number;
	uint16_t flags;
	uint16_t units_per_em;
	int64_t created;
	int64_t modified;
	int16_t x_min;
	int16_t y_min;
	int16_t x_max;
	int16_t y_max;
	uint16_t mac_style;
	uint16_t lowest_rec_ppem;
	int16_t font_direction_hint;
	int16_t index_to_loc_format;
	int16_t glyph_data_format;
} TrueTypeHead_t);

uint32_t TrueTypeHEAD_size(_Inout_ uint8_t* table, int8_t swap_byte);

#endif
