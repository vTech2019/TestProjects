#include <TrueTypeHmtx.h>
#include <TrueTypeMath.h>
#include <TrueTypeTables.h>
#include <TrueTypeMaxp.h>

typedef struct _HMTX_table_t {
	struct hMetrics_t hMetrics[1];
	uint16_t leftSideBearing[1];
} HMTX_table_t;
//
//void TrueTypeHmtx(uint8_t* src, TrueTypeHmtx_t* dst) {
//	TrueTypeTables_t* m_src = (TrueTypeTables_t*)src;
//	TrueTypeHmtx_t m_ptr_hmtx_src = { m_src->hmtx->hMetrics,
//									 &m_src->hmtx->hMetrics[m_src->hhea->numOfLongHorMetrics].advanceWidth };
//	TrueTypeHmtx_t m_ptr_hmtx_dst = { ((HMTX_table_t*)(dst + 1))->hMetrics,
//									 &(((HMTX_table_t*)(dst + 1))->hMetrics[m_src->hhea->numOfLongHorMetrics].advanceWidth) };
//	size_t i, i_end = m_src->hhea->numOfLongHorMetrics;
//	*dst = m_ptr_hmtx_dst;
//	for (i = 0; i < i_end; i++)
//		dst->hMetrics[i].advanceWidth = m_ptr_hmtx_src.hMetrics[i].advanceWidth,
//		dst->hMetrics[i].leftSideBearing = m_ptr_hmtx_src.hMetrics[i].leftSideBearing;
//	for (i = 0, i_end = m_src->maxp->numGlyphs - m_src->hhea->numOfLongHorMetrics; i < i_end; i++)
//		dst->leftSideBearing[i] = m_ptr_hmtx_src.leftSideBearing[i];
//}

uint32_t TrueTypeHMTX_size(uint8_t* table, int8_t byte_swap) {
	size_t i, i_end;
	TrueTypeTables_t* m_table = (TrueTypeTables_t*)table;
	TrueTypeHmtx_t m_hmtx = { m_table->hmtx->hMetrics,
							 &m_table->hmtx->hMetrics[m_table->hhea->numOfLongHorMetrics].advanceWidth };
	if (byte_swap) {
		uint16_t* m_metrics = (uint16_t*)m_hmtx.hMetrics;
		for (i = 0, i_end = m_table->hhea->numOfLongHorMetrics * 2; i < i_end; i++)
			m_metrics[i] = swap_byte_16(m_metrics[i]);
		for (i = 0, i_end = m_table->maxp->numGlyphs - m_table->hhea->numOfLongHorMetrics; i < i_end; i++)
			m_hmtx.leftSideBearing[i] = swap_byte_16(m_hmtx.leftSideBearing[i]);
	}

	return (uint32_t)ALIGN64(sizeof(TrueTypeHmtx_t) + m_table->hhea->numOfLongHorMetrics * sizeof(struct hMetrics_t) +
		(m_table->maxp->numGlyphs - m_table->hhea->numOfLongHorMetrics) * sizeof(int16_t));
}