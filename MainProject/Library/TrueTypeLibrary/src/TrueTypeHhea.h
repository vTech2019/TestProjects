#include <sal.h>
#include <stdint.h>
#ifndef __FREETYPEHHEA_T__
#define __FREETYPEHHEA_T__

typedef struct _TrueTypeHhea_t {
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
    int16_t reserved[2];
    int16_t metricDataFormat;
    uint16_t numOfLongHorMetrics;
} TrueTypeHhea_t;

void TrueTypeHhea(_In_ uint8_t* src, _Out_ TrueTypeHhea_t* dst);
uint32_t TrueTypeHHEA_size(_Inout_ uint8_t* table, int8_t swap_byte);
#endif
