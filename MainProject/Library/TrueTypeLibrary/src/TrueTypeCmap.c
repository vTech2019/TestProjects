#include "TrueTypeCmap.h"
#include <TrueTypeMath.h>

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
    }table;
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
}CMAP_table_t;

uint32_t TrueTypeCMAP_size(_Inout_ uint8_t* table, int8_t swap_byte) {
    
    CMAP_table_t* m_table = (CMAP_table_t*)table;
    struct CMAP_subtable_header_t* m_ptrSubheader_src;

    uint32_t m_i, i, j, i_end, j_end, m_size = sizeof(TrueTypeCmap_t);
    uint16_t* m_max_ptr = NULL;
    uint16_t* m_ptrGlyphIndex = NULL;

    uint8_t* m_ptrEndTable;

    if (swap_byte) {
        m_table->number_subtable = SWAP_BYTE_16(m_table->number_subtable);
        m_table->version = SWAP_BYTE_16(m_table->version);
    }
    for (m_i = 0; m_i < m_table->number_subtable; m_i++) {
        if (swap_byte) {
            m_table->subtables[m_i].platform_ID = SWAP_BYTE_16(m_table->subtables[m_i].platform_ID);
            m_table->subtables[m_i].platform_specification_ID = SWAP_BYTE_16(m_table->subtables[m_i].platform_specification_ID);
            m_table->subtables[m_i].offset = SWAP_BYTE_32(m_table->subtables[m_i].offset);
        }
        m_ptrSubheader_src = (struct CMAP_subtable_header_t*)((uint8_t*)m_table + m_table->subtables[m_i].offset);
        if (swap_byte) {
            m_ptrSubheader_src->format = SWAP_BYTE_16(m_ptrSubheader_src->format);
            m_ptrSubheader_src->language = SWAP_BYTE_16(m_ptrSubheader_src->language);
            m_ptrSubheader_src->length = SWAP_BYTE_16(m_ptrSubheader_src->length);
        }
        m_ptrEndTable = ((uint8_t*)m_ptrSubheader_src) + m_ptrSubheader_src->length;
        switch (m_ptrSubheader_src->format) {
        case 0:

            // map(charCode : number) {
            //	if (charCode >= 0 && charCode <= 255) {
            //		//this.log("charCode %s maps to %s", charCode,
            // this.array[charCode]); 		return this.array[charCode];
            //	}
            //	return 0;
            //}
            m_size += sizeof(TrueTypeCmapData);
            m_size += ALIGN(sizeof(struct TrueTypeCmap0_t));
            break;
        case 4:
            if (swap_byte) {
	m_ptrSubheader_src->table._4.searchRange = SWAP_BYTE_16(m_ptrSubheader_src->table._4.searchRange);
	m_ptrSubheader_src->table._4.rangeShift = SWAP_BYTE_16(m_ptrSubheader_src->table._4.rangeShift);
	m_ptrSubheader_src->table._4.entrySelector = SWAP_BYTE_16(m_ptrSubheader_src->table._4.entrySelector);
	m_ptrSubheader_src->table._4.segCountX2 = SWAP_BYTE_16(m_ptrSubheader_src->table._4.segCountX2);
            }

            i_end = m_ptrSubheader_src->table._4.segCountX2 / 2;

            uint16_t* m_endCode = m_ptrSubheader_src->table._4.endCode;
            uint16_t* m_startCode = m_ptrSubheader_src->table._4.endCode + i_end + 1;
            uint16_t* m_idDelta = m_ptrSubheader_src->table._4.endCode + (size_t)2 * i_end + 1;
            uint16_t* m_idRangeOffset = m_ptrSubheader_src->table._4.endCode + (size_t)3 * i_end + 1;
            if (swap_byte) {
	for (i = 0; i < i_end; i++)
	    m_endCode[i] = SWAP_BYTE_16(m_endCode[i]),
	    m_startCode[i] = SWAP_BYTE_16(m_startCode[i]),
	    m_idDelta[i] = SWAP_BYTE_16(m_idDelta[i]),
	    m_idRangeOffset[i] = SWAP_BYTE_16(m_idRangeOffset[i]);
            }
            for (i = 0; i < i_end; i++) {
	for (j = m_startCode[i], j_end = m_endCode[i]; j < j_end; j++) {
	    if (m_idRangeOffset[i]) {
	        m_ptrGlyphIndex = (&m_idRangeOffset[i] + m_idRangeOffset[i] / 2 + j - m_startCode[i]);
	        if ((intptr_t)m_ptrGlyphIndex > (intptr_t) m_ptrEndTable)
	            return 0;
	        if (m_max_ptr < m_ptrGlyphIndex)
	            m_max_ptr = m_ptrGlyphIndex;
	        if (swap_byte)
	            *m_ptrGlyphIndex = SWAP_BYTE_16(*m_ptrGlyphIndex);
	    }

	    // else {
	    // index = (m_ptrIdDelta[i] + j) & 0xffff;
	    //}
	}
            }
            size_t m_length_glyph = m_max_ptr - (m_idRangeOffset + i_end);
            m_size += sizeof(TrueTypeCmapData);
            m_size += sizeof(struct TrueTypeCmap4_t);
            m_size += ALIGN(i_end * sizeof(uint16_t)) * 4;
            m_size += (uint32_t)ALIGN(m_length_glyph);
            break;
        }
    }
    return ALIGN64(m_size);
}

void TrueTypeCmap(_In_ uint8_t* src, _Out_ TrueTypeCmap_t* dst){
    CMAP_table_t* m_src = (CMAP_table_t*)src;
    uint8_t* m_ptr_dst_cmap = (uint8_t*)dst + sizeof(TrueTypeCmap_t) + (m_src->number_subtable - 1) * sizeof(TrueTypeCmapData);
    struct CMAP_subtable_header_t* m_Header_src;
    union { uint8_t* u8; uint16_t* u16; uint64_t* u64; } m_dst_8;
    union { uint8_t* u8; uint16_t* u16; uint64_t* u64; } m_src_8;
    uint16_t* m_ptrStartCode_src, * m_ptrIdDelta_src, * m_ptrIdRangeOffset_src;
    uint16_t* m_ptrGlyphId_src, * m_ptrGlyphId_dst;

    uint16_t m_i, i, j, i_end, j_end;

    dst->version = m_src->version;
    dst->number_subtable = m_src->number_subtable;
    dst->subtables[0] = (TrueTypeCmapData){ 0 };

    for (m_i = 0; m_i < m_src->number_subtable; m_i++) {
        m_Header_src = (struct CMAP_subtable_header_t*)(src + m_src->subtables[m_i].offset);

        dst->subtables[m_i].platform_ID = m_src->subtables[m_i].platform_ID;
        dst->subtables[m_i].platform_specification_ID = m_src->subtables[m_i].platform_specification_ID;
        dst->subtables[m_i].format = m_Header_src->format;
        dst->subtables[m_i].language = m_Header_src->language;
        dst->subtables[m_i].cmap._0 = (struct TrueTypeCmap0_t*)m_ptr_dst_cmap;

        switch (m_Header_src->format) {
        case 0:
            m_dst_8.u8 = dst->subtables[m_i].cmap._0->glyphIdArray;
            m_src_8.u8 = m_Header_src->table._0.glyphIdArray;
            for (i = 0; i < (256 / 8); ++i)
	m_dst_8.u64[i] = m_src_8.u64[i];
            m_ptr_dst_cmap = dst->subtables[m_i].cmap._0->glyphIdArray + i;
            break;
        case 4:
            i_end = m_Header_src->table._4.segCountX2 / 2;

            dst->subtables[m_i].cmap._4->segCountX2 = m_Header_src->table._4.segCountX2;
            dst->subtables[m_i].cmap._4->searchRange = m_Header_src->table._4.searchRange;
            dst->subtables[m_i].cmap._4->entrySelector = m_Header_src->table._4.entrySelector;
            dst->subtables[m_i].cmap._4->rangeShift = m_Header_src->table._4.rangeShift;

            m_dst_8.u16 = &dst->subtables[m_i].cmap._4->code->startCode;

            m_ptr_dst_cmap += sizeof(struct TrueTypeCmap4_t);

            m_ptrStartCode_src = m_Header_src->table._4.endCode + i_end + 1;
            m_ptrIdDelta_src = m_Header_src->table._4.endCode + (size_t)2 * i_end + 1;
            m_ptrIdRangeOffset_src = m_Header_src->table._4.endCode + (size_t)3 * i_end + 1;

            for (i = 0; i < i_end; ++i) {
	m_dst_8.u64[i] = m_ptrStartCode_src[i] |
	    (m_Header_src->table._4.endCode[i] << 16) | 
	    ((uint64_t)m_ptrIdDelta_src[i] << 32) | 
	    ((uint64_t)m_ptrIdRangeOffset_src[i] << 48);
	//dst->subtables[m_i].cmap._4->code[i].startCode = m_ptrStartCode_src[i];
	//dst->subtables[m_i].cmap._4->code[i].endCode = m_Header_src->table._4.endCode[i];
	//dst->subtables[m_i].cmap._4->code[i].idDelta = m_ptrIdDelta_src[i];
	//dst->subtables[m_i].cmap._4->code[i].idRangeOffset = m_ptrIdRangeOffset_src[i];
	if (m_ptrIdRangeOffset_src[i])
	    dst->subtables[m_i].cmap._4->code[i].idRangeOffset -= (uint16_t)2 * (i_end - i);
            }

            dst->subtables[m_i].cmap._4->glyphId = &dst->subtables[m_i].cmap._4->code[i].startCode;

            for (i = 0; i < i_end; i++) {
	for (j = m_ptrStartCode_src[i], j_end = m_Header_src->table._4.endCode[i]; j < j_end; j++) {
	    if (m_ptrIdRangeOffset_src[i]) {
	        m_ptrGlyphId_src = (&m_ptrIdRangeOffset_src[i] + m_ptrIdRangeOffset_src[i] / 2 + j - m_ptrStartCode_src[i]);
	        m_ptrGlyphId_dst = (dst->subtables[m_i].cmap._4->glyphId + m_ptrIdRangeOffset_src[i] / 2 + j - m_ptrStartCode_src[i]);

	        *m_ptrGlyphId_dst = *m_ptrGlyphId_src;
	    }
	}
            }
            break;
        }
    }
}

uint16_t TrueTypeCMAP_mapCode4(const TrueTypeCmap_t* cmap, uint16_t code) {
    //   size_t i;
    //   for (i = 0; i < cmap->subtables[cmap->select_table].cmap._4->segCountX2 / 2; i++)
    //   {
    //       if (cmap->subtables[cmap->select_table].cmap._4->code[i].endCode >= code)
    //       {
    //           if (cmap->subtables[cmap->select_table].cmap._4->code[i].startCode <= code)
    //           {
	   //if (cmap->subtables[cmap->select_table].cmap._4->code[i].idRangeOffset > 0)
	   //{
	   //    return (cmap->subtables[cmap->select_table].cmap._4->glyphId + cmap->subtables[cmap->select_table].cmap._4->code[i].idRangeOffset / 2 + code - cmap->subtables[cmap->select_table].cmap._4->code[i].startCode);
	   //}
	   //else
	   //{
	   //    return (cmap->subtables[cmap->select_table].cmap._4->code[i].idDelta + code) & 65536;
	   //}
    //           }
    //           else
    //           {
	   //break;
    //           }
    //       }
    //   }
    return 0;
}