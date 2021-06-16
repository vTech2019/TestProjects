#include <stdint.h>
#include <stdlib.h>
#ifndef __TRUETYPEHEAD_H__
#define __TRUETYPEHEAD_H__

typedef __declspec(align(64)) struct _TrueTypeHead_t {
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
} TrueTypeHead_t;
void TrueTypeHead(_In_ uint8_t* src, _Out_ TrueTypeHead_t* dst);
uint32_t TrueTypeHEAD_size(_Inout_ uint8_t* table, int8_t swap_byte);
#endif
