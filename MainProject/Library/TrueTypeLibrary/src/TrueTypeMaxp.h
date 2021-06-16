#include <stdint.h>

#ifndef __TRUETYPEMAXP_H__
#define __TRUETYPEMAXP_H__

typedef struct _TrueTypeMaxp_t {
    uint32_t version;
    uint16_t numGlyphs;
    uint16_t maxPoints;
    uint16_t maxContours;
    uint16_t maxCompositePoints;
    uint16_t maxCompositeContours;
    uint16_t maxZones;
    uint16_t maxTwilightPoints;
    uint16_t maxStorage;
    uint16_t maxFunctionDefs;
    uint16_t maxInstructionDefs;
    uint16_t maxStackElements;
    uint16_t maxSizeOfInstructions;
    uint16_t maxComponentElements;
    uint16_t maxComponentDepth;
} TrueTypeMaxp_t;

void TrueTypeMaxp(_In_ const TrueTypeMaxp_t* table_src, _Out_ TrueTypeMaxp_t* table_dst);
uint32_t TrueTypeMAXP_size(_Inout_ TrueTypeMaxp_t* table, int8_t swap_byte);

#endif
