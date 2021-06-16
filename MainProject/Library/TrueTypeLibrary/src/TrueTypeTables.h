#ifndef __TRUETYPETABLES_H__
#define __TRUETYPETABLES_H__

#include <sal.h>
#include <stdint.h>

#include "TrueTypeError.h"
#include "TrueTypeMath.h"

typedef enum _e_TRUE_TYPE {
    TRUE_TYPE0 = 1953658213,
    TRUE_TYPE1 = 1953784678,
    HMTX = 1752003704,
    NAME = 1851878757,
    OS2 = 1869819698,
    POST = 1886352244,
    MAXP = 1835104368,
    LOCA = 1819239265,
    HHEA = 1751672161,
    HEAD = 1751474532,
    GLYF = 1735162214,
    CMAP = 1668112752,
} e_TRUE_TYPE;

struct TrueTypeOffset_t {
    uint32_t tag;
    uint32_t checksum;
    uint32_t offset;
    uint32_t length;
};
typedef struct _TrueTypeHeader_t {
    uint32_t sfntVersion;
    uint16_t numTables;
    uint16_t searchRange;
    uint16_t entrySelector;
    uint16_t rangeShift;
    struct TrueTypeOffset_t tables[1];
} TrueTypeHeader_t;

typedef struct _HEAD_table_t {
    uint32_t version;
    uint32_t font_revision;
    uint32_t checksum_adjustment;
    uint32_t magic_number;
    uint16_t flags;
    uint16_t units_per_em;
    int32_t created[2];
    int32_t modified[2];
    int16_t x_min;
    int16_t y_min;
    int16_t x_max;
    int16_t y_max;
    uint16_t mac_style;
    uint16_t lowest_rec_ppem;
    int16_t font_direction_hint;
    int16_t locFormat;
    int16_t glyph_data_format;
} HEAD_table_t;

typedef struct _HHEA_table_t {
    uint16_t majorVersion;
    uint16_t minorVersion;
    int16_t ascender;
    int16_t descender;
    int16_t lineGap;
    uint16_t advanceWidthMax;
    int16_t minLeftSideBearing;
    int16_t minRightSideBearing;
    int16_t xMaxExtent;
    int16_t caretSlopeRise;
    int16_t caretSlopeRun;
    int16_t caretOffset;
    int16_t reserved[4];
    int16_t metricDataFormat;
    uint16_t numOfLongHorMetrics;
} HHEA_table_t;

typedef struct _TrueTypeTables_t {
    struct _TrueTypeLoca_t* loca;
    struct _TrueTypeMaxp_t* maxp;
    struct _HHEA_table_t* hhea;
    struct _HEAD_table_t* head;
    struct _HMTX_table_t* hmtx;
    struct _CMAP_table_t* cmap;
    struct _GLYF_table_t* glyf;
    uint32_t head_length;
    uint32_t hhea_length;
    uint32_t loca_length;
    uint32_t maxp_length;
    uint32_t hmtx_length;
    uint32_t cmap_length;
    uint32_t glyf_length;
}TrueTypeTables_t;

TrueTypeError_t TrueTypeTables_SByte(_Out_ TrueTypeTables_t* dst,
    _In_ struct _TrueTypeHeader_t* header,
    _In_ const size_t file_size);

#endif
