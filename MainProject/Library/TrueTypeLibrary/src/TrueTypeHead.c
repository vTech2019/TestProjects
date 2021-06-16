#include <TrueTypeHead.h>
#include <TrueTypeMath.h>
#include <TrueTypeTables.h>

void TrueTypeHead(_In_ uint8_t* src, _Out_ TrueTypeHead_t* dst) {
    const HEAD_table_t* m_src = (const HEAD_table_t*)src;
    dst->version = m_src->version;
    dst->font_revision = m_src->font_revision;
    dst->checksum_adjustment = m_src->checksum_adjustment;
    dst->magic_number = m_src->magic_number;
    dst->flags = m_src->flags;
    dst->units_per_em = m_src->units_per_em;
    dst->created = *(uint64_t*)m_src->created;
    dst->modified = *(uint64_t*)m_src->modified;
    dst->x_min = m_src->x_min;
    dst->y_min = m_src->y_min;
    dst->x_max = m_src->x_max;
    dst->y_max = m_src->y_max;
    dst->mac_style = m_src->mac_style;
    dst->lowest_rec_ppem = m_src->lowest_rec_ppem;
    dst->font_direction_hint = m_src->font_direction_hint;
    dst->index_to_loc_format = m_src->locFormat;
    dst->glyph_data_format = m_src->glyph_data_format;
}

uint32_t TrueTypeHEAD_size(_Inout_ uint8_t* table, int8_t swap_byte) {
    HEAD_table_t* m_table = (HEAD_table_t*)table;
    if (swap_byte) {
        m_table->version = swap_byte_32(m_table->version);
        m_table->font_revision = swap_byte_32(m_table->font_revision);
        m_table->checksum_adjustment = swap_byte_32(m_table->checksum_adjustment);
        m_table->magic_number = swap_byte_32(m_table->magic_number);
        m_table->flags = swap_byte_16(m_table->flags);
        m_table->units_per_em = swap_byte_16(m_table->units_per_em);
        *(uint64_t*)m_table->created = swap_byte_64(*(uint64_t*)m_table->created);
        *(uint64_t*)m_table->modified = swap_byte_64(*(uint64_t*)m_table->modified);
        m_table->x_min = swap_byte_16(m_table->x_min);
        m_table->y_min = swap_byte_16(m_table->y_min);
        m_table->x_max = swap_byte_16(m_table->x_max);
        m_table->y_max = swap_byte_16(m_table->y_max);
        m_table->mac_style = swap_byte_16(m_table->mac_style);
        m_table->lowest_rec_ppem = swap_byte_16(m_table->lowest_rec_ppem);
        m_table->font_direction_hint = swap_byte_16(m_table->font_direction_hint);
        m_table->locFormat = swap_byte_16(m_table->locFormat);
        m_table->glyph_data_format = swap_byte_16(m_table->glyph_data_format);
    }
    return sizeof(TrueTypeHead_t);
}