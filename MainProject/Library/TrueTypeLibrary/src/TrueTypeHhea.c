#include <TrueTypeMath.h>
#include <TrueTypeHhea.h>
#include <TrueTypeTables.h>

void TrueTypeHhea(_In_ uint8_t* src, _Out_ TrueTypeHhea_t* dst) {
    const HHEA_table_t* m_src = (const HHEA_table_t*)src;
    dst->majorVersion = m_src->majorVersion;
    dst->minorVersion = m_src->minorVersion;
    dst->ascender = m_src->ascender;
    dst->descender = m_src->descender;
    dst->lineGap = m_src->lineGap;
    dst->advanceWidthMax = m_src->advanceWidthMax;
    dst->minLeftSideBearing = m_src->minLeftSideBearing;
    dst->minRightSideBearing = m_src->minRightSideBearing;
    dst->xMaxExtent = m_src->xMaxExtent;
    dst->caretSlopeRise = m_src->caretSlopeRise;
    dst->caretSlopeRun = m_src->caretSlopeRun;
    dst->caretOffset = m_src->caretOffset;
    dst->metricDataFormat = m_src->metricDataFormat;
    dst->numOfLongHorMetrics = m_src->numOfLongHorMetrics;
}
uint32_t TrueTypeHHEA_size(_Inout_ uint8_t* table, int8_t swap_byte) {
    HHEA_table_t* m_src = (HHEA_table_t*)table;
    if (swap_byte) {
        m_src->majorVersion = swap_byte_16(m_src->majorVersion);
        m_src->minorVersion = swap_byte_16(m_src->minorVersion);
        m_src->ascender = swap_byte_16(m_src->ascender);
        m_src->descender = swap_byte_16(m_src->descender);
        m_src->lineGap = swap_byte_16(m_src->lineGap);
        m_src->advanceWidthMax = swap_byte_16(m_src->advanceWidthMax);
        m_src->minLeftSideBearing = swap_byte_16(m_src->minLeftSideBearing);
        m_src->minRightSideBearing = swap_byte_16(m_src->minRightSideBearing);
        m_src->xMaxExtent = swap_byte_16(m_src->xMaxExtent);
        m_src->caretSlopeRise = swap_byte_16(m_src->caretSlopeRise);
        m_src->caretSlopeRun = swap_byte_16(m_src->caretSlopeRun);
        m_src->caretOffset = swap_byte_16(m_src->caretOffset);
        m_src->metricDataFormat = swap_byte_16(m_src->metricDataFormat);
        m_src->numOfLongHorMetrics = swap_byte_16(m_src->numOfLongHorMetrics);
    }
    return sizeof(TrueTypeHhea_t);
}