#include <stdint.h>

#ifndef __TRUETYPECMAP_H__
#define __TRUETYPECMAP_H__

struct TrueTypeCmap0_t {
    uint8_t glyphIdArray[256];
};
struct TrueTypeCmap4_t {
    uint16_t segCountX2;
    uint16_t searchRange;
    uint16_t entrySelector;
    uint16_t rangeShift;
    uint16_t* glyphId;
    struct {
        uint16_t startCode, endCode, idDelta, idRangeOffset;
    } code[1];
};
typedef struct _TrueTypeCmapData {
    uint16_t platform_ID;
    uint16_t platform_specification_ID;
    uint16_t format;
    uint16_t language;
    union {
        struct TrueTypeCmap0_t* _0;
        struct TrueTypeCmap4_t* _4;
    } cmap;
} TrueTypeCmapData;

typedef struct _TrueTypeCmap_t {
    uint16_t version;
    uint16_t number_subtable;
    uint32_t select_table;
    TrueTypeCmapData subtables[1];
} TrueTypeCmap_t;

uint32_t TrueTypeCMAP_size(_Inout_ uint8_t* table, int8_t swap_byte);
void TrueTypeCmap(_In_ uint8_t* src, _Out_ TrueTypeCmap_t* dst);
uint16_t TrueTypeCMAP_mapCode4(const TrueTypeCmap_t* cmap, uint16_t code);
#endif
