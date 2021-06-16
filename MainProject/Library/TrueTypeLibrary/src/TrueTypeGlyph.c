#include "TrueTypeGlyph.h"

#include "TrueTypeMath.h"
#include "TrueTypeTables.h"
#include "TrueTypeHead.h"
#include "TrueTypeLoca.h"

#define GLYPH_FLAGS_ON_CURVE_POINT 0x01u
#define GLYPH_FLAGS_X_SHORT_VECTOR 0x02u
#define GLYPH_FLAGS_Y_SHORT_VECTOR 0x04u
#define GLYPH_FLAGS_REPEAT_FLAG 0x08u
#define GLYPH_FLAGS_X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR 0x10u
#define GLYPH_FLAGS_Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR 0x20u
#define GLYPH_FLAGS_OVERLAP_SIMPLE 0x40u
#define GLYPH_FLAGS_RESERVED 0x80u

#define GLYPH_COMPOSITE_ARG_1_AND_2_ARE_WORDS 0x0001u
#define GLYPH_COMPOSITE_ARGS_ARE_XY_VALUES 0x0002u
#define GLYPH_COMPOSITE_ROUND_XY_TO_GRID 0x0004u
#define GLYPH_COMPOSITE_WE_HAVE_A_SCALE 0x0008u
#define GLYPH_COMPOSITE_MORE_COMPONENTS 0x0020u
#define GLYPH_COMPOSITE_WE_HAVE_AN_X_AND_Y_SCALE 0x0040u
#define GLYPH_COMPOSITE_WE_HAVE_A_TWO_BY_TWO 0x0080u
#define GLYPH_COMPOSITE_WE_HAVE_INSTRUCTIONS 0x0100u
#define GLYPH_COMPOSITE_USE_MY_METRICS 0x0200u
#define GLYPH_COMPOSITE_OVERLAP_COMPOUND 0x0400u
#define GLYPH_COMPOSITE_SCALED_COMPONENT_OFFSET 0x0800u
#define GLYPH_COMPOSITE_UNSCALED_COMPONENT_OFFSET 0x1000u
#define GLYPH_COMPOSITE_RESERVED 0xE010u

#define GLYPH_COMPOSITE_VEC3                                                   \
  (GLYPH_COMPOSITE_ARG_1_AND_2_ARE_WORDS | GLYPH_COMPOSITE_WE_HAVE_A_SCALE)
#define GLYPH_COMPOSITE_VEC4                                                   \
  (GLYPH_COMPOSITE_ARG_1_AND_2_ARE_WORDS |                                     \
   GLYPH_COMPOSITE_WE_HAVE_AN_X_AND_Y_SCALE)
#define GLYPH_COMPOSITE_VEC6                                                   \
  (GLYPH_COMPOSITE_ARG_1_AND_2_ARE_WORDS | GLYPH_COMPOSITE_WE_HAVE_A_TWO_BY_TWO)

#define GLYPH_COMPOSITE_TRANSLATE16_SCALE_A                                    \
  (GLYPH_COMPOSITE_ARGS_ARE_XY_VALUES | GLYPH_COMPOSITE_VEC3)
#define GLYPH_COMPOSITE_TRANSLATE16_SCALE_XY                                   \
  (GLYPH_COMPOSITE_ARGS_ARE_XY_VALUES | GLYPH_COMPOSITE_VEC4)
#define GLYPH_COMPOSITE_TRANSLATE16_SCALE_XY01                                 \
  (GLYPH_COMPOSITE_ARGS_ARE_XY_VALUES | GLYPH_COMPOSITE_VEC6)

typedef struct _GLYF_table_t {
    uint8_t ptr8[1];
}GLYPH_table_t;

inline uint32_t TrueTypeGlyf_simple_flags(uint8_t* flag_ptr_start, uint32_t flag_start, uint32_t* flag_end) {
    uint32_t y_start = 0;
    while (flag_start < *flag_end) {
        uint8_t m_flag = flag_ptr_start[flag_start];
        uint8_t m_x_offset = 0;
        if (m_flag & GLYPH_FLAGS_X_SHORT_VECTOR)
            m_x_offset = 1;
        else if (!(m_flag & GLYPH_FLAGS_X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR))
            m_x_offset = 2;
        flag_start++;
        if (m_flag & GLYPH_FLAGS_REPEAT_FLAG) {

            m_x_offset += m_x_offset * flag_ptr_start[flag_start];
            *flag_end -= flag_ptr_start[flag_start] - 1;
            flag_start++;
        }
        y_start += m_x_offset;
    }
    return y_start + *flag_end;
}
void TrueTypeGLYF_size(uint8_t* tables, struct _TrueTypeGlyf_size_t* m_size, int8_t swap_byte) {
    uint32_t i, j, id, i_end, j_end;
    uint16_t* m_ptr16;
    uint8_t* m_ptr8;

    TrueTypeTables_t* m_tables = tables;

    m_size->numberGlyph = m_tables->maxp->numGlyphs;
    m_size->size = sizeof(TrueTypeGlyf_t);

    //if ((uint8_t*)tables->glyf + ((tables->head->locFormat) ? tables->loca.glyph_offsets32[tables->maxp->numGlyphs - 1] :
    //    tables->loca.glyph_offsets16[tables->maxp->numGlyphs - 1]) > (uint8_t*)tables->glyf + tables->glyf_length)
    //    return ;
    for (id = 0; id < m_size->numberGlyph; id++) {
        if (m_tables->head->locFormat == 0)
            i = m_tables->loca->glyph_offsets16[id],
            j = m_tables->loca->glyph_offsets16[id + 1];
        else
            i = ((uint32_t*)m_tables->loca->glyph_offsets16)[id],
            j = ((uint32_t*)m_tables->loca->glyph_offsets16)[id + 1];

        //uint8_t* ptr_end = tables->glyf->ptr8 + j;

        m_ptr8 = (m_tables->glyf->ptr8 + i);
        m_ptr16 = (uint16_t*)(m_tables->glyf->ptr8 + i);

        if (i == j)
            continue;

        const int16_t numberCounters = swap_byte ? swap_byte_16(*m_ptr16) : *m_ptr16;
        if (numberCounters < 0) {
            j = 0;
            i = 5;
            do {
	i_end = swap_byte_16(m_ptr16[i]);
	if (!swap_byte)
	    i_end = swap_byte_16((uint16_t)i_end);
	i += (i_end & GLYPH_COMPOSITE_ARG_1_AND_2_ARE_WORDS) + 3;
	i += ((i_end & GLYPH_COMPOSITE_WE_HAVE_A_SCALE) >> 3) |
	    ((i_end & GLYPH_COMPOSITE_WE_HAVE_AN_X_AND_Y_SCALE) >> 5) |
	    ((i_end & GLYPH_COMPOSITE_WE_HAVE_A_TWO_BY_TWO) >> 5);
	j++;
            } while (i_end & GLYPH_COMPOSITE_MORE_COMPONENTS);

            m_size->composite += sizeof(struct TrueTypeGlyf_composite_t);
            m_size->composite += j * sizeof(TrueTypeGlyph_composite_parameters);
            m_size->composite += j * sizeof(uint16_t);
            m_size->parameters += j * sizeof(TrueTypeGlyph_composite_parameters);
            m_size->glyphIndex += j * sizeof(uint16_t);

            i += i_end & GLYPH_COMPOSITE_WE_HAVE_INSTRUCTIONS ? 1 : 0;
            if (swap_byte) {
	for (j = 0; j < i; j++)
	    m_ptr16[j] = swap_byte_16(m_ptr16[j]);
            }
            if (i_end & GLYPH_COMPOSITE_WE_HAVE_INSTRUCTIONS) {
	m_size->composite += m_ptr16[i - 1];
	m_size->instructions += m_ptr16[i - 1];
            }
        }
        else {
            m_size->endCounter += numberCounters * sizeof(uint16_t);
            m_size->simple += numberCounters * sizeof(uint16_t);

            j_end = (size_t)numberCounters + 5;
            i = j_end;

            if (swap_byte) {
	for (j = 0; j <= j_end; j++) {
	    m_ptr16[j] = swap_byte_16(m_ptr16[j]);
	}
            }

            j_end = (size_t)m_ptr16[i - 1] + 1;

            m_size->simple += sizeof(struct TrueTypeGlyf_simple_t);
            m_size->parameters += ALIGN(j_end * sizeof(struct TrueTypeGlyf_simple_parameters));
            m_size->simple += ALIGN(j_end * sizeof(struct TrueTypeGlyf_simple_parameters));

            m_size->instructions += m_ptr16[i];
            m_size->simple += m_ptr16[i];

            i = 2 * i + m_ptr16[i] + sizeof(uint16_t);

            i_end = j_end + i;
            j_end = TrueTypeGlyf_simple_flags(m_ptr8, i, &i_end);
            uint8_t* m_x = m_ptr8 + i_end;
            uint8_t* m_y = m_ptr8 + j_end;


            if (!swap_byte)
	continue;

            for (; i < i_end; i++) {
	uint8_t m_flag = m_ptr8[i];
	uint8_t m_repeat = m_ptr8[i + 1];
	uint8_t m_x_offset = 0;
	uint8_t m_y_offset = 0;
	if (m_flag & GLYPH_FLAGS_X_SHORT_VECTOR)
	    m_x_offset = 1;
	else if ((m_flag & GLYPH_FLAGS_X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR) == 0)
	    m_x_offset = 2;
	if (m_flag & GLYPH_FLAGS_Y_SHORT_VECTOR)
	    m_y_offset = 1;
	else if ((m_flag & GLYPH_FLAGS_Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR) == 0)
	    m_y_offset = 2;
	if (m_flag & GLYPH_FLAGS_REPEAT_FLAG)
	    i++;
	else
	    m_repeat = 0;
	j = swap_byte_16(*(uint16_t*)m_x);
	j_end = swap_byte_16(*(uint16_t*)m_y);
	do {
	    if (m_x_offset & 2)
	        *(uint16_t*)m_x = j;
	    if (m_y_offset & 2)
	        *(uint16_t*)m_y = j_end;
	    m_x += m_x_offset;
	    m_y += m_y_offset;

	    j = swap_byte_16(*(uint16_t*)m_x);
	    j_end = swap_byte_16(*(uint16_t*)m_y);

	} while (m_repeat--);
            }

 //           if (m_y > ptr_end)
	//break;
        }
    }
    m_size->size += m_size->simple + m_size->composite;
    m_size->size = ALIGN64(m_size->size);
}

void TrueTypeGlyf(uint8_t* src, TrueTypeGlyf_t* dst, struct _TrueTypeGlyf_size_t* ptr_size){
    TrueTypeTables_t* m_src = src;
    dst->number_glyph = ptr_size->numberGlyph;
    uint8_t* m_dst_instructions = (uint8_t*)dst->ptr_glyph + ptr_size->numberGlyph;
    uint8_t* m_dst_endCountours = m_dst_instructions + ptr_size->instructions;
    uint8_t* m_dst_glyphIndex = m_dst_endCountours + ptr_size->endCounter;
    uint8_t* m_dst_parameters = m_dst_glyphIndex + ptr_size->glyphIndex;

    uint16_t* m_src_ptr16;
    uint8_t* m_src_ptr8;


    uint32_t i, j, i_end, j_end, id, id_end;

    id_end = ((size_t)m_src->head->locFormat + 1) * m_src->maxp->numGlyphs;
    for (id = 0; id < m_src->maxp->numGlyphs; id++) {
        i = m_src->loca->glyph_offsets16[id];
        j = m_src->loca->glyph_offsets16[id + 1];
        if (m_src->head->locFormat)
            i = ((uint32_t*)m_src->loca->glyph_offsets16)[id];
        if (m_src->head->locFormat)
            j = ((uint32_t*)m_src->loca->glyph_offsets16)[id + 1];

        dst->ptr_glyph[id].simple.number_contours = 0;

        if (i == j)
            continue;
        m_src_ptr16 = (uint16_t*)(m_src->glyf->ptr8 + i);
        m_src_ptr8 = m_src->glyf->ptr8 + i;

        i = 0;
        j = 0;
        if (*m_src_ptr16 > INT16_MAX) {
            dst->ptr_glyph[id].composite.number_contours = m_src_ptr16[i++];
            dst->ptr_glyph[id].composite.x_min = m_src_ptr16[i++];
            dst->ptr_glyph[id].composite.y_min = m_src_ptr16[i++];
            dst->ptr_glyph[id].composite.x_max = m_src_ptr16[i++];
            dst->ptr_glyph[id].composite.y_max = m_src_ptr16[i++];
            dst->ptr_glyph[id].composite.number_instructions = 0;
            dst->ptr_glyph[id].composite.parameters = (TrueTypeGlyph_composite_parameters*)m_dst_parameters;
            dst->ptr_glyph[id].composite.glyph_index = (uint16_t*)m_dst_glyphIndex;
            dst->ptr_glyph[id].composite.instructions = m_dst_instructions;

            do {
	TrueTypeGlyph_composite_parameters m_param = { 1.0f, 0.0f, 0.0f, 1.0f, 0, 0, 0, 0 };
	i_end = m_src_ptr16[i + 0];
	dst->ptr_glyph[id].composite.glyph_index[j] = m_src_ptr16[i + 1];
	if (i_end & GLYPH_COMPOSITE_ARG_1_AND_2_ARE_WORDS) {
	    if (i_end & GLYPH_COMPOSITE_ARGS_ARE_XY_VALUES) {
	        m_param.xtranslate = m_src_ptr16[i + 2];
	        m_param.ytranslate = m_src_ptr16[i + 3];
	    }
	    else {
	        m_param.point1 = m_src_ptr16[i + 2];
	        m_param.point2 = m_src_ptr16[i + 3];
	    }
	    if (i_end & GLYPH_COMPOSITE_WE_HAVE_A_SCALE) {
	        m_param.xscale = m_src_ptr16[i + 4];
	        m_param.yscale = m_src_ptr16[i + 4];
	    }
	    else if (i_end & GLYPH_COMPOSITE_WE_HAVE_AN_X_AND_Y_SCALE) {
	        m_param.xscale = m_src_ptr16[i + 4];
	        m_param.yscale = m_src_ptr16[i + 5];
	    }
	    else if (i_end & GLYPH_COMPOSITE_WE_HAVE_A_TWO_BY_TWO) {
	        m_param.xscale = m_src_ptr16[i + 4];
	        m_param.scale01 = m_src_ptr16[i + 5];
	        m_param.scale10 = m_src_ptr16[i + 6];
	        m_param.yscale = m_src_ptr16[i + 7];
	    }
	}
	else {
	    if (i_end & GLYPH_COMPOSITE_ARGS_ARE_XY_VALUES) {
	        m_param.xtranslate = (m_src_ptr16[i + 2] & 0x00ff);
	        m_param.ytranslate = (m_src_ptr16[i + 2] & 0xff00) >> 8;
	    }
	    else {
	        m_param.point1 = (m_src_ptr16[i + 2] & 0x00ff);
	        m_param.point2 = (m_src_ptr16[i + 2] & 0xff00) >> 8;
	    }
	    if (i_end & GLYPH_COMPOSITE_WE_HAVE_A_SCALE) {
	        m_param.xscale = m_src_ptr16[i + 3];
	        m_param.yscale = m_src_ptr16[i + 3];
	    }
	    else if (i_end & GLYPH_COMPOSITE_WE_HAVE_AN_X_AND_Y_SCALE) {
	        m_param.xscale = m_src_ptr16[i + 3];
	        m_param.yscale = m_src_ptr16[i + 4];
	    }
	    else if (i_end & GLYPH_COMPOSITE_WE_HAVE_A_TWO_BY_TWO) {
	        m_param.xscale = m_src_ptr16[i + 3];
	        m_param.scale01 = m_src_ptr16[i + 4];
	        m_param.scale10 = m_src_ptr16[i + 5];
	        m_param.yscale = m_src_ptr16[i + 6];
	    }
	}
	dst->ptr_glyph[id].composite.parameters[j] = m_param;
	i += (size_t)(i_end & GLYPH_COMPOSITE_ARG_1_AND_2_ARE_WORDS) + 3;
	i += (size_t)((i_end & GLYPH_COMPOSITE_WE_HAVE_A_SCALE) >> 3) |
	    ((i_end & GLYPH_COMPOSITE_WE_HAVE_AN_X_AND_Y_SCALE) >> 5) |
	    ((i_end & GLYPH_COMPOSITE_WE_HAVE_A_TWO_BY_TWO) >> 5);
	j++;
            } while (i_end & GLYPH_COMPOSITE_MORE_COMPONENTS);

            m_dst_parameters = (uint8_t*)(dst->ptr_glyph[id].composite.parameters + j);
            m_dst_glyphIndex = (uint8_t*)(dst->ptr_glyph[id].composite.glyph_index + j);

            if (i_end & GLYPH_COMPOSITE_WE_HAVE_INSTRUCTIONS) {
	dst->ptr_glyph[id].composite.number_instructions = m_src_ptr16[i];
	m_src_ptr8 = (uint8_t*)(m_src_ptr16 + i + 1);
	for (j = 0; j < m_src_ptr16[i]; j++)
	    dst->ptr_glyph[id].composite.instructions[j] = m_src_ptr8[j];
	m_dst_instructions = (uint8_t*)(dst->ptr_glyph[id].composite.instructions + j);
            }
        }
        else {
            j_end = m_src_ptr16[i];

            dst->ptr_glyph[id].simple.end_countours = (uint16_t*)m_dst_endCountours;
            dst->ptr_glyph[id].simple.instructions = m_dst_instructions;
            dst->ptr_glyph[id].simple.parameters = (struct TrueTypeGlyf_simple_parameters*)m_dst_parameters;
            dst->ptr_glyph[id].simple.number_contours = m_src_ptr16[i++];
            dst->ptr_glyph[id].simple.x_min = m_src_ptr16[i++];
            dst->ptr_glyph[id].simple.y_min = m_src_ptr16[i++];
            dst->ptr_glyph[id].simple.x_max = m_src_ptr16[i++];
            dst->ptr_glyph[id].simple.y_max = m_src_ptr16[i++];

            for (j = 0; j < j_end;) {
	dst->ptr_glyph[id].simple.end_countours[j++] = m_src_ptr16[i++];
            }
            j_end = m_src_ptr16[i - 1] + 1;
            i_end = m_src_ptr16[i];
            dst->ptr_glyph[id].simple.number_instructions = m_src_ptr16[i++];

            i *= 2;

            for (j = 0; j < i_end; i++, j++) {
	dst->ptr_glyph[id].simple.instructions[j] = m_src_ptr8[i];
            }


            i_end = j_end + i;
            j_end = TrueTypeGlyf_simple_flags(m_src_ptr8, i, &i_end);
            uint8_t* m_x = m_src_ptr8 + i_end;
            uint8_t* m_y = m_src_ptr8 + j_end;

            int16_t m_local_sum_x = 0;
            int16_t m_local_sum_y = 0;
            struct TrueTypeGlyf_simple_parameters* m_parameters = dst->ptr_glyph[id].simple.parameters;

            for (; i < i_end; i++) {
	uint8_t m_flag = m_src_ptr8[i];
	uint8_t m_repeat = m_src_ptr8[i + 1];
	uint8_t m_x_offset = 0;
	uint8_t m_y_offset = 0;
	if (m_flag & GLYPH_FLAGS_X_SHORT_VECTOR)
	    m_x_offset = 1;
	else if ((m_flag & GLYPH_FLAGS_X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR) == 0)
	    m_x_offset = 2;
	if (m_flag & GLYPH_FLAGS_Y_SHORT_VECTOR)
	    m_y_offset = 1;
	else if ((m_flag & GLYPH_FLAGS_Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR) == 0)
	    m_y_offset = 2;
	if (m_flag & GLYPH_FLAGS_REPEAT_FLAG)
	    i++;
	else
	    m_repeat = 0;

	do {
	    int16_t m_tmp_x = *(int16_t*)m_x;
	    int16_t m_tmp_y = *(int16_t*)m_y;
	    if (m_flag & GLYPH_FLAGS_X_SHORT_VECTOR) {
	        m_tmp_x &= 0xff;
	        if (m_flag & GLYPH_FLAGS_X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR)
	            m_tmp_x = m_tmp_x;
	        else
	            m_tmp_x = -m_tmp_x;
	    }
	    else {
	        if (m_flag & GLYPH_FLAGS_X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR)
	            m_tmp_x = 0;
	    }
	    if (m_flag & GLYPH_FLAGS_Y_SHORT_VECTOR) {
	        m_tmp_y &= 0xff;
	        if (m_flag & GLYPH_FLAGS_Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR)
	            m_tmp_y = m_tmp_y;
	        else
	            m_tmp_y = -m_tmp_y;
	    }
	    else {
	        if (m_flag & GLYPH_FLAGS_Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR)
	            m_tmp_y = 0;
	    }

	    m_local_sum_x += m_tmp_x;
	    m_local_sum_y += m_tmp_y;
	    m_parameters->x = m_local_sum_x;
	    m_parameters->y = m_local_sum_y;
	    m_parameters++;
	    m_x += m_x_offset;
	    m_y += m_y_offset;
	} while (m_repeat--);
            }

            dst->ptr_glyph[id].simple.number_points = ((ptrdiff_t)m_parameters - (ptrdiff_t)dst->ptr_glyph[id].simple.parameters) / 4;
            m_parameters = align16((uint8_t*)m_parameters);
            m_dst_endCountours = (uint8_t*)(dst->ptr_glyph[id].simple.end_countours + dst->ptr_glyph[id].simple.number_contours);
            m_dst_instructions = dst->ptr_glyph[id].simple.instructions + dst->ptr_glyph[id].simple.number_instructions;
            m_dst_parameters = (uint8_t*)m_parameters;
        }
    }
}