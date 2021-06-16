#ifndef TRUETYPEREADER_TRUETYPEHMTX_H
#define TRUETYPEREADER_TRUETYPEHMTX_H
#include "stdafx.h"
#include "TrueTypeError.h"

struct hMetrics_t {
	uint16_t advanceWidth;
	int16_t leftSideBearing;
};
typedef ALIGNED64(struct, _TrueTypeHmtx_t {
	struct hMetrics_t* hMetrics;
	uint16_t* leftSideBearing;
} TrueTypeHmtx_t);

uint32_t TrueTypeHMTX_size(uint8_t* table, int8_t byte_swap);

#endif // TRUETYPEREADER_TRUETYPEHMTX_H
