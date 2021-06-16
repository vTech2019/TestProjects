#include <TrueTypeMath.h>
#include <TrueTypeHhea.h>
#include <TrueTypeTables.h>

void TrueTypeHhea(_In_ uint16_t* src, _Out_ TrueTypeHhea_t* dst) {
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
		m_src->ascender = (int16_t)swap_byte_16((uint16_t) m_src->ascender);
		m_src->descender = (int16_t)swap_byte_16((uint16_t) m_src->descender);
		m_src->lineGap = (int16_t)swap_byte_16((uint16_t) m_src->lineGap);
		m_src->advanceWidthMax = swap_byte_16(m_src->advanceWidthMax);
		m_src->minLeftSideBearing = (int16_t)swap_byte_16((uint16_t) m_src->minLeftSideBearing);
		m_src->minRightSideBearing = (int16_t)swap_byte_16((uint16_t) m_src->minRightSideBearing);
		m_src->xMaxExtent = (int16_t)swap_byte_16((uint16_t) m_src->xMaxExtent);
		m_src->caretSlopeRise = (int16_t)swap_byte_16((uint16_t) m_src->caretSlopeRise);
		m_src->caretSlopeRun = (int16_t)swap_byte_16((uint16_t) m_src->caretSlopeRun);
		m_src->caretOffset = (int16_t)swap_byte_16((uint16_t) m_src->caretOffset);
		m_src->metricDataFormat = (int16_t)swap_byte_16((uint16_t) m_src->metricDataFormat);
		m_src->numOfLongHorMetrics = swap_byte_16(m_src->numOfLongHorMetrics);
	}
	return sizeof(TrueTypeHhea_t);
}