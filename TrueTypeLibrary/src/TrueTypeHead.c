#include <TrueTypeHead.h>
#include <TrueTypeMath.h>
#include <TrueTypeTables.h>


uint32_t TrueTypeHEAD_size(_Inout_ uint8_t* table, int8_t swap_byte) {
	HEAD_table_t* m_table = (HEAD_table_t*)table;
	if (swap_byte) {
		m_table->version = swap_byte_32(m_table->version);
		m_table->font_revision = swap_byte_32(m_table->font_revision);
		m_table->checksum_adjustment = swap_byte_32(m_table->checksum_adjustment);
		m_table->magic_number = swap_byte_32(m_table->magic_number);
		m_table->flags = swap_byte_16(m_table->flags);
		m_table->units_per_em = swap_byte_16(m_table->units_per_em);
		*((uint64_t*)m_table->created) = swap_byte_64(*(uint64_t*)m_table->created);
		*((uint64_t*)m_table->modified) = swap_byte_64(*(uint64_t*)m_table->modified);
		m_table->x_min = (int16_t) swap_byte_16((uint16_t) m_table->x_min);
		m_table->y_min = (int16_t) swap_byte_16((uint16_t) m_table->y_min);
		m_table->x_max = (int16_t) swap_byte_16((uint16_t) m_table->x_max);
		m_table->y_max = (int16_t) swap_byte_16((uint16_t) m_table->y_max);
		m_table->mac_style = swap_byte_16(m_table->mac_style);
		m_table->lowest_rec_ppem = swap_byte_16(m_table->lowest_rec_ppem);
		m_table->font_direction_hint = (int16_t) swap_byte_16((uint16_t) m_table->font_direction_hint);
		m_table->locFormat = (int16_t) swap_byte_16((uint16_t) m_table->locFormat);
		m_table->glyph_data_format = (int16_t) swap_byte_16((uint16_t) m_table->glyph_data_format);
	}
	return sizeof(TrueTypeHead_t);
}