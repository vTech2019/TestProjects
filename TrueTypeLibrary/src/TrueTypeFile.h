#ifndef __TRUETYPEFILE_H__
#define __TRUETYPEFILE_H__

#include "TrueTypeTables.h"
#include "TrueTypeHead.h"
#include <TrueTypeHhea.h>
#include <TrueTypeHmtx.h>
#include <TrueTypeMaxp.h>

static inline void TrueTypeHead(_In_ HEAD_table_t *src, _Out_ TrueTypeHead_t *dst) {
    dst->version = src->version;
    dst->font_revision = src->font_revision;
    dst->checksum_adjustment = src->checksum_adjustment;
    dst->magic_number = src->magic_number;
    dst->flags = src->flags;
    dst->units_per_em = src->units_per_em;
    dst->created = (((int64_t) src->created[1] << 32) | src->created[0]);
    dst->modified = (((int64_t) src->modified[1] << 32) | src->modified[0]);
    dst->x_min = src->x_min;
    dst->y_min = src->y_min;
    dst->x_max = src->x_max;
    dst->y_max = src->y_max;
    dst->mac_style = src->mac_style;
    dst->lowest_rec_ppem = src->lowest_rec_ppem;
    dst->font_direction_hint = src->font_direction_hint;
    dst->index_to_loc_format = src->locFormat;
    dst->glyph_data_format = src->glyph_data_format;
}

static inline void TrueTypeHhea(_In_ HHEA_table_t *src, _Out_ TrueTypeHhea_t *dst) {
    dst->majorVersion = src->majorVersion;
    dst->minorVersion = src->minorVersion;
    dst->ascender = src->ascender;
    dst->descender = src->descender;
    dst->lineGap = src->lineGap;
    dst->advanceWidthMax = src->advanceWidthMax;
    dst->minLeftSideBearing = src->minLeftSideBearing;
    dst->minRightSideBearing = src->minRightSideBearing;
    dst->xMaxExtent = src->xMaxExtent;
    dst->caretSlopeRise = src->caretSlopeRise;
    dst->caretSlopeRun = src->caretSlopeRun;
    dst->caretOffset = src->caretOffset;
    dst->metricDataFormat = src->metricDataFormat;
    dst->numOfLongHorMetrics = src->numOfLongHorMetrics;
}


static inline void TrueTypeMaxp(_In_ const TrueTypeMaxp_t *src, _Out_ TrueTypeMaxp_t *dst) {
    *dst = *src;
}

typedef struct _HMTX_table_t {
    struct hMetrics_t hMetrics[1];
    uint16_t leftSideBearing[1];
} HMTX_table_t;

static inline void TrueTypeHmtx(TrueTypeTables_t *src, TrueTypeHmtx_t *dst) {
    TrueTypeHmtx_t m_ptr_hmtx_src = {src->hmtx->hMetrics,
                                     &src->hmtx->hMetrics[src->hhea->numOfLongHorMetrics].advanceWidth};
    TrueTypeHmtx_t m_ptr_hmtx_dst = {((HMTX_table_t *) (dst + 1))->hMetrics,
                                     &(((HMTX_table_t *) (dst +
                                                          1))->hMetrics[src->hhea->numOfLongHorMetrics].advanceWidth)};
    size_t i, i_end = src->hhea->numOfLongHorMetrics;
    *dst = m_ptr_hmtx_dst;
    for (i = 0; i < i_end; i++)
        dst->hMetrics[i].advanceWidth = m_ptr_hmtx_src.hMetrics[i].advanceWidth,
                dst->hMetrics[i].leftSideBearing = m_ptr_hmtx_src.hMetrics[i].leftSideBearing;
    for (i = 0, i_end = src->maxp->numGlyphs - src->hhea->numOfLongHorMetrics; i < i_end; i++)
        dst->leftSideBearing[i] = m_ptr_hmtx_src.leftSideBearing[i];
}


static inline uint32_t TrueTypeMAXP_size(_Inout_ TrueTypeMaxp_t *table, int8_t swap_byte) {
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

#endif
