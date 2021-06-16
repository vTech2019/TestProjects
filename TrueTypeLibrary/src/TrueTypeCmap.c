#include "TrueTypeCmap.h"
#include "TrueTypeMaxp.h"
#include <TrueTypeMath.h>
#include "TrueTypeTables.h"
#include <TrueTypeLibrary.h>

struct CMAP_subtable4_t {
	uint16_t segCountX2;
	uint16_t searchRange;
	uint16_t entrySelector;
	uint16_t rangeShift;
	uint16_t endCode[1];
};
struct CMAP_subtable_header_t {
	uint16_t format;
	uint16_t length;
	uint16_t language;
	union {
		struct TrueTypeCmap0_t _0;
		struct CMAP_subtable4_t _4;
	} table;
};
struct CMAP_subtable_info_t {
	uint16_t platform_ID;
	uint16_t platform_specification_ID;
	uint32_t offset;
};
typedef struct _CMAP_table_t {
	uint16_t version;
	uint16_t number_subtable;
	struct CMAP_subtable_info_t subtables[1];
} CMAP_table_t;

uint32_t TrueTypeCmap_notFound(const TrueTypeReader_t* table, uint32_t unicode) { (void)(table); (void)(unicode); return 0; }
uint32_t TrueTypeCmap0_findIndex(const TrueTypeReader_t* table, uint32_t unicode);
uint32_t TrueTypeCmap4_findIndex(const TrueTypeReader_t* table, uint32_t unicode);

uint32_t TrueTypeCMAP_size(_Inout_ void* tables, _In_ int8_t swap_byte) {
	TrueTypeTables_t* m_tables = (TrueTypeTables_t*)tables;
	CMAP_table_t* m_table = m_tables->cmap;
	uint8_t* m_ptrEndTable;
	uint16_t* m_16;
	uint16_t m_0, m_1, m_2;
	size_t m_i, i, j, i_end, j_end, m_size = offsetof(TrueTypeCmap_t, subtables);

	if (swap_byte) {
		m_table->number_subtable = swap_byte_16(m_table->number_subtable);
		m_table->version = swap_byte_16(m_table->version);
	}
	m_size += m_table->number_subtable * sizeof(TrueTypeCmapData_t);
	if (swap_byte)
		for (m_i = 0; m_i < m_table->number_subtable; m_i++) {
			m_table->subtables[m_i].platform_ID = swap_byte_16(m_table->subtables[m_i].platform_ID);
			m_table->subtables[m_i].platform_specification_ID = swap_byte_16(m_table->subtables[m_i].platform_specification_ID);
			m_table->subtables[m_i].offset = swap_byte_32(m_table->subtables[m_i].offset);
		}

	for (m_i = 0; m_i < m_table->number_subtable; m_i++) {
		for (i = 0; i < m_i; i++) {
			if (m_table->subtables[i].offset == m_table->subtables[m_i].offset)
				i = m_i;
		}
		if (i == m_i + 1)
			continue;
		m_16 = (uint16_t*)((uint8_t*)m_table + m_table->subtables[m_i].offset) + 3;
		if (swap_byte) {
			m_16[-3] = swap_byte_16(m_16[-3]);
			m_16[-2] = swap_byte_16(m_16[-2]);
			m_16[-1] = swap_byte_16(m_16[-1]);
		}
		m_ptrEndTable = ((uint8_t*)m_16) + m_16[-2] - 6;
		switch (m_16[-3]) {
		case 0:
			m_size = ALIGN16(m_size);
			m_size += sizeof(struct TrueTypeCmap0_t);
			break;
		case 4:
			i_end = (size_t)((intptr_t)m_ptrEndTable - (intptr_t)m_16) / 2;

			if (swap_byte) 
				for (i = 0; i < i_end; i++) 
					m_16[i] = swap_byte_16(m_16[i]);

			i_end = m_16[0] / 2;

			for (i = 0, j_end = i_end; i < i_end; i++) {
				m_1 = m_16[0 * i_end + i + 4];
				m_2 = m_16[1 * i_end + i + 5];
				m_0 = m_16[3 * i_end + i + 5];
				if (m_0 == 0)
					continue;
				j = i + m_0 / 2 + m_1 - m_2;
				if (j_end <= j)
					j_end = j + 1;
			}
			if ((intptr_t)(m_16 + 3 * i_end + j_end + 5) != (intptr_t)m_ptrEndTable)
				return 0;

			m_size = ALIGN16(m_size);
			m_size += offsetof(struct TrueTypeCmap4_t, code) + i_end * sizeof(struct TrueTypeCmap4_subheader_t) + (j_end - i_end) * sizeof(uint16_t);
			break;
		}
	}
	//printf("%zd ", m_size);
	return (uint32_t)ALIGN64(m_size);
}

void TrueTypeCmap(_In_ uint8_t* src, _Out_ TrueTypeCmap_t* dst, void** ptrSelectFunction) {
	uint16_t* m_src16, * m_dst16;
	struct TrueTypeCmap0_t* m_dst0;
	struct TrueTypeCmap4_t* m_dst4;
	size_t m_i, i, j, i_end, j_end;

	CMAP_table_t* m_src = (CMAP_table_t*)src;
	uint8_t* m_dst = (uint8_t *) (dst->subtables + m_src->number_subtable);

	dst->version = ((uint16_t*)src)[0];
	dst->numberSubtables = ((uint16_t*)src)[1];

	*ptrSelectFunction = TrueTypeCmap_notFound;
	dst->subtable_data = NULL;

	for (m_i = 0; m_i < dst->numberSubtables; m_i++) {
		m_dst = ALIGN16((size_t)m_dst);

		m_src16 = (uint16_t*)(src + ((uint32_t*)src)[m_i * 2 + 2]);
		dst->subtables[m_i].platform_ID = ((uint16_t*)src)[m_i * 4 + 2];
		dst->subtables[m_i].platform_specification_ID = ((uint16_t*)src)[m_i * 4 + 3];
		dst->subtables[m_i].format = m_src16[0];
		dst->subtables[m_i].language = m_src16[2];
		dst->subtables[m_i].cmap._0 = (struct TrueTypeCmap0_t*)m_dst;

		for (i = 0; i < m_i; i++)
			if (m_src->subtables[i].offset == m_src->subtables[m_i].offset)
				dst->subtables[m_i].cmap._0 = dst->subtables[i].cmap._0,
				i = m_i;
		if (i == m_i + 1)
			continue;

		i = 0;
		switch (m_src->subtables[m_i].platform_ID) {
		case Unicode:
			i = 1;
			switch (m_src->subtables[m_i].platform_specification_ID) {
			case Unicode_1_0: break;
			case Unicode_1_1: break;
			case Unicode_ISO_IEC_10646: break;
			case Unicode_2_0_BMP: break;
			case Unicode_2_0_Full: break;
			case Unicode_Variation_Sequences: break;
			case Unicode_Full_Repertoire: break;
			}
			break;
		case Macintosh:
			break;
		case Microsoft:
			switch (m_src->subtables[m_i].platform_specification_ID) {
			case Microsoft_Symbol: break;
			case Microsoft_ShiftJIS: break;
			case Microsoft_PRC: break;
			case Microsoft_BigFive: break;
			case Microsoft_Wansung: break;
			case Microsoft_Johab: break;
			case Microsoft_Unicode_BMP:
			case Microsoft_Unicode_full_repertoire:
				i = 1; break;
			}
			break;
		}
		switch (m_src16[0]) {
		case 0:
			if (i) {
				*ptrSelectFunction = TrueTypeCmap0_findIndex;
				dst->subtable_data = dst->subtables + m_i;
			}
			i = 0;
			m_src16 += 3;
			m_dst0 = dst->subtables[m_i].cmap._0;
			do {
				((uint64_t*)m_dst0->glyphIdArray)[i] = ((uint64_t*)m_src16)[i];
				i++;
			} while (i < 256 / sizeof(uint64_t));
			m_dst = m_dst0->glyphIdArray + sizeof(struct TrueTypeCmap0_t);
			break;
		case 4:
			if (i) {
				*ptrSelectFunction = TrueTypeCmap4_findIndex;
				dst->subtable_data = dst->subtables + m_i;
			}
			m_dst4 = dst->subtables[m_i].cmap._4;
			i_end = m_src16[3] / 2;

			m_dst4->segCountX2 = m_src16[3];
			m_dst4->searchRange = m_src16[4];
			m_dst4->entrySelector = m_src16[5];
			m_dst4->rangeShift = m_src16[6];

			m_dst4->glyphId = (const uint16_t*)(m_dst4->code + i_end);
			m_dst16 = m_dst4->glyphId;
			for (i = 0; i < i_end; i++) {
				m_dst4->code[i].endCode = m_src16[i + 7];
				m_dst4->code[i].startCode = m_src16[1 * i_end + i + 8];
				m_dst4->code[i].idDelta = m_src16[2 * i_end + i + 8];
				m_dst4->code[i].idRangeOffset = m_src16[3 * i_end + i + 8];
			}
			for (i = 0, j_end = 0; i < i_end; i++) {
				if (m_dst4->code[i].idRangeOffset == 0)
					continue;
				j = i + m_dst4->code[i].idRangeOffset / 2 + m_dst4->code[i].endCode - m_dst4->code[i].startCode;
				if (j_end <= j)
					j_end = j + 1;
			}
			for (i = 0, j = i_end; j < j_end; j++, i++)
				m_dst16[i] = m_src16[4 * i_end + i + 8];

			m_dst += offsetof(struct TrueTypeCmap4_t, code) + i_end * sizeof(struct TrueTypeCmap4_subheader_t) + (j_end - i_end) * sizeof(uint16_t);

			break;
		}
	}
	//printf("%zd", (ptrdiff_t)m_dst - (ptrdiff_t)dst);
}
uint32_t TrueTypeCmap0_findIndex(const TrueTypeReader_t* table, uint32_t unicode) {
	struct TrueTypeCmap0_t* m_table = table->cmap->subtable_data->cmap._0;
	if (unicode < 256)
		return m_table->glyphIdArray[unicode];
	else
		return 0;
}

uint32_t TrueTypeCmap4_findIndex(const TrueTypeReader_t* table, uint32_t unicode)
{
	struct TrueTypeCmap4_t* m_table = table->cmap->subtable_data->cmap._4;
	uint32_t result = 0;
	uint16_t m_count = m_table->segCountX2 / 2;
	uint16_t m_search = m_table->searchRange / 2;
	uint16_t m_entry = m_table->entrySelector;
	uint16_t m_range = m_table->rangeShift / 2;
	size_t search = 0;
	if (unicode >= m_table->code[search + m_range].startCode)
		search += m_range;
	while (m_entry) {
		m_search /= 2;
		if (unicode > m_table->code[search + m_search].startCode)
			search += m_search;
		m_entry--;
	}
	if (unicode < m_table->code[search].startCode);
	else if (unicode > m_table->code[search].endCode);
	else if (m_table->code[search].idRangeOffset)
		result = m_table->glyphId[unicode + search + m_table->code[search].idRangeOffset / 2 - m_table->code[search].startCode - m_count];
	else
		result = (m_table->code[search].idDelta + unicode) % 0xffff;
	return result;
}

//STBTT_DEF int stbtt_FindGlyphIndex(const CMAP_table_t* tables, int unicode_codepoint)
//{
//    stbtt_uint8* data = info->data;
//    stbtt_uint32 index_map = info->index_map;
//
//    stbtt_uint16 format = ttUSHORT(data + index_map + 0);
//    if (format == 0) { // apple byte encoding
//        stbtt_int32 bytes = ttUSHORT(data + index_map + 2);
//        if (unicode_codepoint < bytes - 6)
//            return ttBYTE(data + index_map + 6 + unicode_codepoint);
//        return 0;
//    }
//    else if (format == 6) {
//        stbtt_uint32 first = ttUSHORT(data + index_map + 6);
//        stbtt_uint32 count = ttUSHORT(data + index_map + 8);
//        if ((stbtt_uint32)unicode_codepoint >= first && (stbtt_uint32)unicode_codepoint < first + count)
//            return ttUSHORT(data + index_map + 10 + (unicode_codepoint - first) * 2);
//        return 0;
//    }
//    else if (format == 2) {
//        STBTT_assert(0); // @TODO: high-byte mapping for japanese/chinese/korean
//        return 0;
//    }
//    else if (format == 4) { // standard mapping for windows fonts: binary search collection of ranges
//        stbtt_uint16 segcount = ttUSHORT(data + index_map + 6) >> 1;
//        stbtt_uint16 searchRange = ttUSHORT(data + index_map + 8) >> 1;
//        stbtt_uint16 entrySelector = ttUSHORT(data + index_map + 10);
//        stbtt_uint16 rangeShift = ttUSHORT(data + index_map + 12) >> 1;
//
//        // do a binary search of the segments
//        stbtt_uint32 endCount = index_map + 14;
//        stbtt_uint32 search = endCount;
//
//        if (unicode_codepoint > 0xffff)
//            return 0;
//
//        // they lie from endCount .. endCount + segCount
//        // but searchRange is the nearest power of two, so...
//        if (unicode_codepoint >= ttUSHORT(data + search + rangeShift * 2))
//            search += rangeShift * 2;
//
//        // now decrement to bias correctly to find smallest
//        search -= 2;
//        while (entrySelector) {
//            stbtt_uint16 end;
//            searchRange >>= 1;
//            end = ttUSHORT(data + search + searchRange * 2);
//            if (unicode_codepoint > end)
//                search += searchRange * 2;
//            --entrySelector;
//        }
//        search += 2;
//
//        {
//            stbtt_uint16 offset, start;
//            stbtt_uint16 item = (stbtt_uint16)((search - endCount) >> 1);
//
//            STBTT_assert(unicode_codepoint <= ttUSHORT(data + endCount + 2 * item));
//            start = ttUSHORT(data + index_map + 14 + segcount * 2 + 2 + 2 * item);
//            if (unicode_codepoint < start)
//                return 0;
//
//            offset = ttUSHORT(data + index_map + 14 + segcount * 6 + 2 + 2 * item);
//            if (offset == 0)
//                return (stbtt_uint16)(unicode_codepoint + ttSHORT(data + index_map + 14 + segcount * 4 + 2 + 2 * item));
//
//            return ttUSHORT(data + offset + (unicode_codepoint - start) * 2 + index_map + 14 + segcount * 6 + 2 + 2 * item);
//        }
//    }
//    else if (format == 12 || format == 13) {
//        stbtt_uint32 ngroups = ttULONG(data + index_map + 12);
//        stbtt_int32 low, high;
//        low = 0; high = (stbtt_int32)ngroups;
//        // Binary search the right group.
//        while (low < high) {
//            stbtt_int32 mid = low + ((high - low) >> 1); // rounds down, so low <= mid < high
//            stbtt_uint32 start_char = ttULONG(data + index_map + 16 + mid * 12);
//            stbtt_uint32 end_char = ttULONG(data + index_map + 16 + mid * 12 + 4);
//            if ((stbtt_uint32)unicode_codepoint < start_char)
//                high = mid;
//            else if ((stbtt_uint32)unicode_codepoint > end_char)
//                low = mid + 1;
//            else {
//                stbtt_uint32 start_glyph = ttULONG(data + index_map + 16 + mid * 12 + 8);
//                if (format == 12)
//                    return start_glyph + unicode_codepoint - start_char;
//                else // format == 13
//                    return start_glyph;
//            }
//        }
//        return 0; // not found
//    }
//    // @TODO
//    STBTT_assert(0);
//    return 0;
//}