#include <TrueTypeMath.h>
#include <TrueTypeMaxp.h>

void TrueTypeMaxp(_In_ const TrueTypeMaxp_t* table_src, _Out_ TrueTypeMaxp_t* table_dst) {
    *table_dst = *table_src;
}

uint32_t TrueTypeMAXP_size(_Inout_ TrueTypeMaxp_t* table, int8_t swap_byte) {
    if (!swap_byte) return sizeof(TrueTypeMaxp_t);

    table->version = swap_byte_32(table->version);
    table->numGlyphs = swap_byte_16(table->numGlyphs);
    if (table->version == 0x00010000) {
        table->maxPoints = swap_byte_16(table->maxPoints);
        table->maxContours = swap_byte_16(table->maxContours);
        table->maxCompositePoints = swap_byte_16(table->maxCompositePoints);
        table->maxCompositeContours = swap_byte_16(table->maxCompositeContours);
        table->maxZones = swap_byte_16(table->maxZones);
        table->maxTwilightPoints = swap_byte_16(table->maxTwilightPoints);
        table->maxStorage = swap_byte_16(table->maxStorage);
        table->maxFunctionDefs = swap_byte_16(table->maxFunctionDefs);
        table->maxInstructionDefs = swap_byte_16(table->maxInstructionDefs);
        table->maxStackElements = swap_byte_16(table->maxStackElements);
        table->maxSizeOfInstructions = swap_byte_16(table->maxSizeOfInstructions);
        table->maxComponentElements = swap_byte_16(table->maxComponentElements);
        table->maxComponentDepth = swap_byte_16(table->maxComponentDepth);
    }

    return sizeof(TrueTypeMaxp_t);
}