#include <TrueTypeHmtx.h>
#include <TrueTypeMath.h>
#include <TrueTypeTables.h>
#include <TrueTypeMaxp.h>

typedef struct _HMTX_table_t {
    struct hMetrics_t hMetrics[1];
    uint16_t leftSideBearing[1];
} HMTX_table_t;

void TrueTypeHmtx(uint8_t* src, TrueTypeHmtx_t* dst) {
    TrueTypeTables_t* m_src = src;
    TrueTypeHmtx_t m_ptr_hmtx_src = { m_src->hmtx->hMetrics, &m_src->hmtx->hMetrics[m_src->hhea->numOfLongHorMetrics].advanceWidth };
    TrueTypeHmtx_t m_ptr_hmtx_dst = { ((HMTX_table_t*)(dst + 1))->hMetrics, &(((HMTX_table_t*)(dst + 1))->hMetrics[m_src->hhea->numOfLongHorMetrics].advanceWidth) };
    size_t i, i_end = m_src->hhea->numOfLongHorMetrics;
    *dst = m_ptr_hmtx_dst;
    for (i = 0; i < i_end; i++)
        dst->hMetrics[i].advanceWidth = m_ptr_hmtx_src.hMetrics[i].advanceWidth,
        dst->hMetrics[i].leftSideBearing = m_ptr_hmtx_src.hMetrics[i].leftSideBearing;
    for (i = 0, i_end = m_src->maxp->numGlyphs - m_src->hhea->numOfLongHorMetrics; i < i_end; i++)
        dst->leftSideBearing[i] = m_ptr_hmtx_src.leftSideBearing[i];
}

uint32_t TrueTypeHMTX_size(uint8_t* table, int8_t byte_swap) {
    size_t i, i_end; 
    TrueTypeTables_t* m_table = table;
    TrueTypeHmtx_t m_hmtx = { m_table->hmtx->hMetrics, &m_table->hmtx->hMetrics[m_table->hhea->numOfLongHorMetrics].advanceWidth };
    if (byte_swap) {
        for (i = 0; i < m_table->hhea->numOfLongHorMetrics; i++)
            m_hmtx.hMetrics[i].advanceWidth = swap_byte_16(m_hmtx.hMetrics[i].advanceWidth),
            m_hmtx.hMetrics[i].leftSideBearing = swap_byte_16(m_hmtx.hMetrics[i].leftSideBearing);
        for (i = 0, i_end = m_table->maxp->numGlyphs - m_table->hhea->numOfLongHorMetrics; i < i_end; i++)
            m_hmtx.leftSideBearing[i] = swap_byte_16(m_hmtx.leftSideBearing[i]);
    }

    return ALIGN64(sizeof(TrueTypeHmtx_t) + m_table->hhea->numOfLongHorMetrics * sizeof(struct hMetrics_t) +
        (m_table->maxp->numGlyphs - m_table->hhea->numOfLongHorMetrics) * sizeof(int16_t));
}