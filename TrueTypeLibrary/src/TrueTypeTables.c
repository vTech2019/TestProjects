#include "TrueTypeTables.h"
#include <TrueTypeHhea.h>
#include <TrueTypeMaxp.h>
#include "TrueTypeError.h"

TrueTypeError_t TrueTypeTables_SByte(_Out_ TrueTypeTables_t* dst,
	_In_ struct _TrueTypeHeader_t* header,
	_In_ const size_t file_size) {
	uint32_t i;
	*dst = (TrueTypeTables_t){ 0 };
	header->sfntVersion = swap_byte_32(header->sfntVersion);
	header->numTables = swap_byte_16(header->numTables);
	header->searchRange = swap_byte_16(header->searchRange);
	header->entrySelector = swap_byte_16(header->entrySelector);
	header->rangeShift = swap_byte_16(header->rangeShift);

	if (header->sfntVersion != TRUE_TYPE_TRUE_WinAbobe && header->sfntVersion != TRUE_TYPE_TRUE_OSX)
		return e_TrueTypeCodeError_notTrueType;

	for (i = 0; i < header->numTables; i++) {
		header->tables[i].tag = swap_byte_32(header->tables[i].tag);
		header->tables[i].checksum = swap_byte_32(header->tables[i].checksum);
		header->tables[i].offset = swap_byte_32(header->tables[i].offset);
		header->tables[i].length = swap_byte_32(header->tables[i].length);

		if (file_size < (size_t)header->tables[i].offset + header->tables[i].length) {
			return e_TrueTypeCodeError_tableOutOfMemory;
		}
		uint32_t* m_table = (uint32_t*)((uint8_t*)header + header->tables[i].offset);
		switch (header->tables[i].tag) {
		case HMTX:
			if (check_checksum_swapByte(m_table, header->tables[i].length) != header->tables[i].checksum)
				return e_TrueTypeCodeError_tableChecksum;
			dst->hmtx = (struct _HMTX_table_t*)m_table;
			dst->hmtx_length = header->tables[i].length;
			break;
		case LOCA:
			if (check_checksum_swapByte(m_table, header->tables[i].length) != header->tables[i].checksum)
				return e_TrueTypeCodeError_tableChecksum;
			dst->loca = (union _TrueTypeLoca_t*)m_table;
			//dst->loca_length = header->tables[i].length;
			break;
		case HHEA:
			if (check_checksum_swapByte(m_table, sizeof(struct _HHEA_table_t)) != header->tables[i].checksum)
				return e_TrueTypeCodeError_tableChecksum;
			dst->hhea = (struct _HHEA_table_t*)m_table;
			dst->hhea_length = header->tables[i].length;
			break;
		case MAXP:
			if (check_checksum_swapByte(m_table, 16 * sizeof(uint16_t)) != header->tables[i].checksum)
				return e_TrueTypeCodeError_tableChecksum;
			dst->maxp = (struct _TrueTypeMaxp_t*)m_table;
			dst->maxp_length = header->tables[i].length;
			break;
		case HEAD:
			//CHECK_CHECKSUM_SWAPBYTE32(m_sum, m_ptr_table, j, sizeof(TrueTypeHead_t));
			//if (m_sum != header->tables[i].checksum) return e_TrueTypeCodeError_tableChecksum;
			dst->head = (struct _HEAD_table_t*)m_table;
			dst->head_length = header->tables[i].length;
			break;
		case CMAP:
			if (check_checksum_swapByte(m_table, header->tables[i].length) != header->tables[i].checksum)
				return e_TrueTypeCodeError_tableChecksum;
			dst->cmap = (struct _CMAP_table_t*)m_table;
			dst->cmap_length = header->tables[i].length;
			break;
		case GLYF:
			if (check_checksum_swapByte(m_table, header->tables[i].length) != header->tables[i].checksum)
				return e_TrueTypeCodeError_tableChecksum;
			dst->glyf = (union _GLYF_table_t*)m_table;
			dst->glyf_length = header->tables[i].length;
			break;
		}
	}
	return e_TrueTypeCodeError_success;
}