#include <stdint.h>
#ifndef TRUETYPEREADER_TRUETYPEHMTX_H
#define TRUETYPEREADER_TRUETYPEHMTX_H

struct hMetrics_t {
    uint16_t advanceWidth;
    int16_t leftSideBearing;
};
typedef struct _TrueTypeHmtx_t {
    struct hMetrics_t* hMetrics;
    uint16_t* leftSideBearing;
} TrueTypeHmtx_t;

void TrueTypeHmtx(uint8_t* src, TrueTypeHmtx_t* dst);
uint32_t TrueTypeHMTX_size(uint8_t* table, int8_t byte_swap);
#endif // TRUETYPEREADER_TRUETYPEHMTX_H
