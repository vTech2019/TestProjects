#include "stdafx.h"

#include "TrueTypeGlyph.h"
#include "TrueTypeMath.h"
#include "TrueTypeTables.h"
#include "TrueTypeHead.h"
#include "TrueTypeLoca.h"

//static void* data[65536];

#define REPEAT_COPY2(array_0, i_0, f, array_1, i_1)			array_0[i_0 + 0] = f(array_1[i_1 + 0]); \
															array_0[i_0 + 1] = f(array_1[i_1 + 1]);
#define REPEAT_COPY4(array_0, i_0, f, array_1, i_1)			REPEAT_COPY2(array_0, i_0, f, array_1, i_1) \
															REPEAT_COPY2(array_0, i_0 + 2, f, array_1, i_1 + 2)
#define REPEAT_COPY8(array_0, i_0, f, array_1, i_1)			REPEAT_COPY4(array_0, i_0, f, array_1, i_1) \
															REPEAT_COPY4(array_0, i_0 + 4, f, array_1, i_1 + 4)
#define REPEAT_COPY16(array_0, i_0, f, array_1, i_1)		REPEAT_COPY8(array_0, i_0, f, array_1, i_1) \
															REPEAT_COPY8(array_0, i_0 + 8, f, array_1, i_1 + 8)

#define COPY1_SWITCH(array_0, i_0, f, array_1, i_1, id)		case (id + 1): array_0[i_0 + id] = f(array_1[i_1 + id]);
#define COPY2_SWITCH(array_0, i_0, f, array_1, i_1, id)		COPY1_SWITCH(array_0, i_0, f, array_1, i_1, id + 1) \
															COPY1_SWITCH(array_0, i_0, f, array_1, i_1, id + 0)
#define COPY4_SWITCH(array_0, i_0, f, array_1, i_1, id)		COPY2_SWITCH(array_0, i_0, f, array_1, i_1, id + 2) \
															COPY2_SWITCH(array_0, i_0, f, array_1, i_1, id + 0)
#define COPY8_SWITCH(array_0, i_0, f, array_1, i_1, id)		COPY4_SWITCH(array_0, i_0, f, array_1, i_1, id + 4) \
															COPY4_SWITCH(array_0, i_0, f, array_1, i_1, id + 0)
#define COPY16_SWITCH(array_0,i_0, f, array_1, i_1, id)		COPY8_SWITCH(array_0, i_0, f, array_1, i_1, id + 8) \
															COPY8_SWITCH(array_0, i_0, f, array_1, i_1, id + 0)
#define COPY32_SWITCH(array_0,i_0, f, array_1, i_1, id)		COPY16_SWITCH(array_0, i_0, f, array_1, i_1, id + 16) \
															COPY16_SWITCH(array_0, i_0, f, array_1, i_1, id + 0)
#define COPY64_SWITCH(array_0,i_0, f, array_1, i_1, id)		COPY32_SWITCH(array_0, i_0, f, array_1, i_1, id + 32) \
															COPY32_SWITCH(array_0, i_0, f, array_1, i_1, id + 0)

#define COPY2_DATA_SWITCH(array_0, i_0, f, array_1, i_1, id)	switch(id){\
																	default:;\
																	COPY2_SWITCH(array_0, i_0, f, array_1, i_1, 0);\
																	case 0:;\
																}
#define COPY4_DATA_SWITCH(array_0, i_0, f, array_1, i_1, id)	switch(id){\
																	default:;\
																	COPY4_SWITCH(array_0, i_0, f, array_1, i_1, 0)\
																	case 0:;\
																}
#define COPY8_DATA_SWITCH(array_0, i_0, f, array_1, i_1, id)	switch(id){\
																	default:;\
																	COPY8_SWITCH(array_0, i_0, f, array_1, i_1, 0)\
																	case 0:;\
																}
#define COPY16_DATA_SWITCH(array_0, i_0, f, array_1, i_1, id)	switch(id){\
																	default:;\
																	COPY16_SWITCH(array_0, i_0, f, array_1, i_1, 0)\
																	case 0:;\
																}
#define COPY32_DATA_SWITCH(array_0, i_0, f, array_1, i_1, id)	switch(id){\
																	default:;\
																	COPY32_SWITCH(array_0, i_0, f, array_1, i_1, 0)\
																	case 0:;\
																}
#define COPY64_DATA_SWITCH(array_0, i_0, f, array_1, i_1, id)	switch(id){\
																	default:;\
																	COPY64_SWITCH(array_0, i_0, f, array_1, i_1, 0)\
																	case 0:;\
																}

#define REPEAT_COPY2_ARRAY(type_0, type_1, array_0, f, array_1, j, j_end, i)\
							{type_0* ptr_0 = array_0; const type_1* ptr_1 = array_1;\
							for (j  = 0; j + 1 < j_end; j += 2, ptr_0 += 2, ptr_1 += 2)\
								for (i = 0; i < 2; i++)\
									 ptr_0[i] = f(ptr_1[i]);\
							if (j < j_end) array_0[j] = f(array_1[j]);}

#define REPEAT_COPY4_ARRAY(type_0, type_1, array_0, f, array_1, j, j_end, i)\
							{type_0* ptr_0 = array_0; const type_1* ptr_1 = array_1;\
							for (j = 0; j + 3 < j_end; j += 4, ptr_0 += 4, ptr_1 += 4)\
								for (i = 0; i < 4; i++)\
									ptr_0[i] = f(ptr_1[i]);\
							COPY4_DATA_SWITCH(ptr_0, 0, f, ptr_1, 0, ((j_end) & 0x3));}

#define REPEAT_COPY8_ARRAY(type_0, type_1, array_0, f, array_1, j, j_end, i)\
							{type_0* ptr_0 = array_0; const type_1* ptr_1 = array_1;\
							for (j = 0; j + 7 < j_end; j += 8, ptr_0 += 8, ptr_1 += 8)\
								for (i = 0; i < 8; i++)\
									ptr_0[i] = f(ptr_1[i]);\
							COPY8_DATA_SWITCH(ptr_0, 0, f, ptr_1, 0, ((j_end) & 0x7));}

#define REPEAT_COPY16_ARRAY(type_0, type_1, array_0, f, array_1, j, j_end, i)	\
							{type_0* ptr_0 = array_0; const type_1* ptr_1 = array_1;\
							for (j = 0; j + 15 < j_end; j += 16, ptr_0 += 16, ptr_1 += 16)\
								for (i = 0; i < 16; i++)\
									ptr_0[i] = f(ptr_1[i]);\
							COPY16_DATA_SWITCH(ptr_0, 0, f, ptr_1, 0, ((j_end) & 0xf));}

#define REPEAT_COPY32_ARRAY(type_0, type_1, array_0, f, array_1, j, j_end, i)	\
							{type_0* ptr_0 = array_0; type_1* ptr_1 = array_1;\
							for (j = 0; j + 31 < j_end; j += 32, ptr_0 += 32, ptr_1 += 32)\
								for (i = 0; i < 32; i++)\
									ptr_0[i] = f(ptr_1[i]);\
							COPY32_DATA_SWITCH(ptr_0, 0, f, ptr_1, 0, ((j_end) & 0x1f));}

#define REPEAT_COPY32_SWITCH(type_0, type_1, array_0, f, array_1, j, j_end, i)	\
							{type_0* ptr_0 = array_0; type_1* ptr_1 = array_1; i = (j_end) / 32; j = (j_end) & 0x1f;\
							do{	 \
								COPY32_DATA_SWITCH(ptr_0, 0, f, ptr_1, 0, max(i * 32, j));   \
								ptr_0 += 32; ptr_1 += 32;\
							}while(i--);}

#define REPEAT_COPY64_ARRAY(type_0, type_1, array_0, f, array_1, j, j_end, i)	\
							{type_0* ptr_0 = array_0; type_1* ptr_1 = array_1;\
							for (j = 0; j + 63 < j_end; j += 64, ptr_0 += 64, ptr_1 += 64)\
								for (i = 0; i < 64; i++)\
									ptr_0[i] = f(ptr_1[i]);\
							COPY64_DATA_SWITCH(ptr_0, 0, f, ptr_1, 0, ((j_end) & 0x1f));}

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

typedef union _GLYF_table_t {
	uint8_t	ptrArr8[1];
} GLYPH_table_t;

static inline uint16_t TrueTypeGlyf_simple_flags(const uint8_t* flag_ptr_start, uint16_t* const flag_end, uint16_t* const number_parameters, const uint16_t lastCountour) {
	uint16_t y_start = 0;
	uint16_t flag_start = 0;
	uint16_t m_local_end = lastCountour;
	uint16_t m_local_parameters = 0;
	while (flag_start < m_local_end) {
		uint8_t m_f = flag_ptr_start[flag_start];
		uint8_t m_r = flag_ptr_start[flag_start + 1];
		uint16_t m_x_offset = 2;

		if (m_f & GLYPH_FLAGS_X_SHORT_VECTOR)
			m_x_offset = 1;
		else if (m_f & GLYPH_FLAGS_X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR)
			m_x_offset = 0;
		if (m_f & GLYPH_FLAGS_REPEAT_FLAG) {
			m_local_end -= (uint16_t)m_r - 1;
			y_start += (uint16_t)m_x_offset * (m_r + 1);
			m_local_parameters += (uint16_t)m_r + 1;
			flag_start += 2;
		}
		else {
			y_start += m_x_offset;
			m_local_parameters++;
			flag_start++;
		}
	}
	*flag_end = m_local_end;
	if (number_parameters) *number_parameters = m_local_parameters;
	return y_start + m_local_end;
}

static inline uint32_t TrueTypeGlyf_simpleUnpack(
	TrueTypeGlyf_simple_parameters* points,
	uint8_t* m_flags,
	uint16_t* m_c,
	const uint8_t* m_f,
	const uint8_t* m_x,
	const uint8_t* m_y,
	const uint16_t m_number_f,
	const uint16_t m_number_c
) {
	uint32_t m_points = 0;
	uint16_t prevCurve, j;
	uint16_t m_unpackCurvePoint = 0;
	int16_t m_local_sum_x, m_local_sum_y;
	int16_t nextCurveX, nextCurveY;
	uint8_t m_prevFlag = GLYPH_FLAGS_ON_CURVE_POINT;
	uint8_t m_currFlag;
	uint8_t m_startCurveFlag = 1;
	prevCurve = m_local_sum_x = m_local_sum_y = 0;
	if (m_number_f) {
		m_startCurveFlag = *m_f;
	}
	for (uint16_t i = 0; i < m_number_f; i++) {
		m_currFlag = m_f[i];
		uint8_t m_x_offset_0 = ((m_currFlag & (2 | 16)) == 0) + ((m_currFlag & (2 | 16)) != 16);
		uint8_t m_y_offset_0 = ((m_currFlag & (4 | 32)) == 0) + ((m_currFlag & (4 | 32)) != 32);
		int16_t m_pos_x_0 = 1 - 2 * ((m_currFlag & (2 | 16)) == 2);
		int16_t m_pos_y_0 = 1 - 2 * ((m_currFlag & (4 | 32)) == 4);
		int16_t mask_x_0 = (m_x_offset_0 == 1) * 0xff | (m_x_offset_0 == 2) * 0xffff;
		int16_t mask_y_0 = (m_y_offset_0 == 1) * 0xff | (m_y_offset_0 == 2) * 0xffff;
		uint16_t m_repeat = 0;
		if (m_currFlag & GLYPH_FLAGS_REPEAT_FLAG) {
			m_repeat = m_f[++i];
		}
		do {
			int16_t x = m_pos_x_0 * ((*(int16_t*)m_x) & mask_x_0);
			int16_t y = m_pos_y_0 * ((*(int16_t*)m_y) & mask_y_0);
			nextCurveX = m_local_sum_x + x;
			nextCurveY = m_local_sum_y + y;
			if (m_points > m_c[m_unpackCurvePoint])
				m_prevFlag = m_startCurveFlag,
				m_startCurveFlag = m_currFlag;

			uint16_t midPoint = (((m_prevFlag & GLYPH_FLAGS_ON_CURVE_POINT) == 0) & ((m_currFlag & GLYPH_FLAGS_ON_CURVE_POINT) == 0));
			if (m_points > m_c[m_unpackCurvePoint]) {
				nextCurveX = points[prevCurve].x;
				nextCurveY = points[prevCurve].y;
				prevCurve = m_points + midPoint;
				m_c[m_unpackCurvePoint] += midPoint;
				m_unpackCurvePoint++;
			}
			if (midPoint) {
				m_flags[m_points] = GLYPH_FLAGS_ON_CURVE_POINT;
				points[m_points].x = (m_local_sum_x + nextCurveX) / 2;
				points[m_points].y = (m_local_sum_y + nextCurveY) / 2;
				//points[m_points].x = (m_local_sum_x) ;
				//points[m_points].y = (m_local_sum_y) ;
				for (j = m_unpackCurvePoint; j < m_number_c; j++)
					m_c[j]++;
			}

			m_points += midPoint;
			m_local_sum_x += x;
			m_local_sum_y += y;
			m_flags[m_points] = m_currFlag & GLYPH_FLAGS_ON_CURVE_POINT;
			points[m_points].x = m_local_sum_x;
			points[m_points].y = m_local_sum_y;
			m_points++;
			m_x += m_x_offset_0;
			m_y += m_y_offset_0;
			m_prevFlag = m_currFlag;
		} while (m_repeat--);
	}
	if ((m_startCurveFlag & GLYPH_FLAGS_ON_CURVE_POINT) == 0 && (m_currFlag & GLYPH_FLAGS_ON_CURVE_POINT) == 0) {
		nextCurveX = points[prevCurve].x;
		nextCurveY = points[prevCurve].y;
		m_flags[m_points] = GLYPH_FLAGS_ON_CURVE_POINT;
		points[m_points].x = (m_local_sum_x + nextCurveX) / 2;
		points[m_points].y = (m_local_sum_y + nextCurveY) / 2;
		m_c[m_unpackCurvePoint]++;
		m_points++;
	}
	//printf("\n");
	return m_points;
}
struct _TrueTypeGlyf_size_t TrueTypeGLYF_size(uint8_t* tables) {
	struct _TrueTypeGlyf_size_t m_size = { 0 };
	TrueTypeTables_t* m_tables = (TrueTypeTables_t*)tables;
	const uint16_t* m_ptr16 = NULL;
	const uint16_t* m_ptrNext = NULL;
	const uint8_t* m_ptrGlyph = m_tables->glyf->ptrArr8;
	const int16_t m_locFormat = m_tables->head->locFormat;
	const uint16_t m_numberGlyph = m_tables->maxp->numGlyphs;
	uint32_t i, j, id, i_end, j_end;

	j = id = i_end = j_end = 0;
	for (id = 0; id < m_numberGlyph; id++) {
		if (m_ptrNext != m_ptr16) {
			for (j = 0; m_ptr16 + j < m_ptrNext; j++)
				if (m_ptr16[j] != 0)
					printf("ERROR GLYPH id = %u: %p != %p\n", id - 1, m_ptrNext, m_ptr16);
		}
		//i = m_ptrGlyphOffset16[(id << m_locFormat) + 0];
		//j = m_ptrGlyphOffset16[(id << m_locFormat) + 1 + m_locFormat];
		//i |= 0xffffffff * m_locFormat & ((uint32_t)m_ptrGlyphOffset16[(id << m_locFormat) + 1] << 16);
		//j |= 0xffffffff * m_locFormat & ((uint32_t)m_ptrGlyphOffset16[(id << m_locFormat) + 3] << 16);
		if (m_locFormat)
			i = m_tables->loca->glyphOffsets32[id],
			j = m_tables->loca->glyphOffsets32[id + 1];
		else
			i = 2 * m_tables->loca->glyphOffsets16[id],
			j = 2 * m_tables->loca->glyphOffsets16[id + 1];

		m_ptr16 = m_ptrGlyph + i;
		m_ptrNext = m_ptrGlyph + j;

		if (i >= m_tables->glyf_length)
			continue;
		if (i == j)
			continue;

		int16_t numberCounters = (int16_t)swap_byte_16(*m_ptr16);
		if (numberCounters < 0) {
			uint16_t m_flag;
			i = i_end = j = 0;
			j_end = 5;
			do {
				m_flag = m_ptr16[j_end];
				m_flag = swap_byte_16(m_flag);
				j_end += 3 + (m_flag & GLYPH_COMPOSITE_ARG_1_AND_2_ARE_WORDS) +
					(((m_flag & GLYPH_COMPOSITE_WE_HAVE_A_SCALE) >> 3) |
						((m_flag & GLYPH_COMPOSITE_WE_HAVE_AN_X_AND_Y_SCALE) >> 5) |
						((m_flag & GLYPH_COMPOSITE_WE_HAVE_A_TWO_BY_TWO) >> 5));
				j++;
			} while (m_flag & GLYPH_COMPOSITE_MORE_COMPONENTS);
			j_end += m_flag & GLYPH_COMPOSITE_WE_HAVE_INSTRUCTIONS ? 1 : 0;

			m_size.parameters = (uint32_t)ALIGN16(m_size.parameters) + j * sizeof(TrueTypeGlyph_composite_parameters);
			m_size.glyphIndex += (uint32_t)j * sizeof(uint16_t);

			if (m_flag & GLYPH_COMPOSITE_WE_HAVE_INSTRUCTIONS) {
				i_end = swap_byte_16(m_ptr16[j_end - 1]);
				m_size.instructions += i_end;
			}
			REPEAT_COPY16_ARRAY(uint16_t, uint16_t, m_ptr16, swap_byte_16, m_ptr16, j, j_end, i);

			m_ptr16 = (uint16_t*)((((size_t)(m_ptr16 + j_end) + i_end) & ~(size_t)1) + 2 * (((size_t)(m_ptr16 + j_end) + i_end) & 1));
		}
		else {
			uint16_t m_number_c = (uint16_t)numberCounters;
			uint16_t m_number_i;
			uint16_t m_number_f;
			uint16_t m_number_x;
			uint16_t m_number_p;
			uint16_t m_repeat;

			const uint16_t* m_c = m_ptr16 + 5;
			const uint8_t* m_i;
			const uint8_t* m_f;
			uint8_t* m_x;
			uint8_t* m_y;

			REPEAT_COPY32_SWITCH(uint16_t, uint16_t, m_ptr16, swap_byte_16, m_ptr16, j, m_number_c + 6, i);

			m_number_i = m_c[m_number_c];
			m_i = (const uint8_t*)(m_c + m_number_c + 1);
			m_f = (const uint8_t*)(m_i + m_number_i);

			m_number_x = TrueTypeGlyf_simple_flags(m_f, &m_number_f, &m_number_p, m_c[m_number_c - 1] + 1);
			m_x = m_f + m_number_f;
			m_y = m_f + m_number_x;

			uint16_t m_unpackCurvePoint = 0;
			uint8_t m_startCurveFlag = 1;
			uint8_t m_prevFlag = 1;
			uint8_t m_currFlag = 0;
			uint8_t m_x_offset;
			uint8_t m_y_offset;
			uint32_t m_currentPointer = 0;
			if (1 <= m_number_f) {
				m_startCurveFlag = m_f[0];
				m_currFlag = m_f[0];
			}
			for (i = 0; i < m_number_f; i++) {
				m_repeat = 0;
				m_currFlag = m_f[i];
				m_x_offset = ((m_currFlag & (2u | 16u)) == 0u) + ((m_currFlag & (2u | 16u)) != 16u);
				m_y_offset = ((m_currFlag & (4u | 32u)) == 0u) + ((m_currFlag & (4u | 32u)) != 32u);
				if (m_currFlag & GLYPH_FLAGS_REPEAT_FLAG) {
					m_repeat = m_f[++i];
				}

				do {
					if (m_currentPointer > m_c[m_unpackCurvePoint])
						m_prevFlag = m_startCurveFlag,
						m_startCurveFlag = m_currFlag,
						m_unpackCurvePoint++;
					m_number_p += ((m_prevFlag & GLYPH_FLAGS_ON_CURVE_POINT) == 0) & ((m_currFlag & GLYPH_FLAGS_ON_CURVE_POINT) == 0);
					m_currentPointer++;
					//printf("%d", ((m_prevFlag & GLYPH_FLAGS_ON_CURVE_POINT) == 0) & ((m_currFlag & GLYPH_FLAGS_ON_CURVE_POINT) == 0));
					if (m_x_offset == 2) {
						m_x[0] ^= m_x[1];
						m_x[1] ^= m_x[0];
						m_x[0] ^= m_x[1];
						//*((uint16_t*)(m_x)) = swap_byte_16(*((uint16_t*)(m_x)));
					}
					if (m_y_offset == 2) {
						m_y[0] ^= m_y[1];
						m_y[1] ^= m_y[0];
						m_y[0] ^= m_y[1];
						//*((uint16_t*)(m_y)) = swap_byte_16(*((uint16_t*)(m_y)));
					}

					m_x += m_x_offset;
					m_y += m_y_offset;
					m_prevFlag = m_currFlag;
				} while (m_repeat--);
			}
			m_number_p += ((m_startCurveFlag & GLYPH_FLAGS_ON_CURVE_POINT) == 0) & ((m_currFlag & GLYPH_FLAGS_ON_CURVE_POINT) == 0);
			m_size.flags += m_number_p * sizeof(uint8_t);
			m_size.parameters = ALIGN16(m_size.parameters) + m_number_p * sizeof(TrueTypeGlyf_simple_parameters);
			m_size.endCounter += m_number_c * sizeof(uint16_t);
			m_size.instructions += m_number_i * sizeof(uint8_t);
			//data[id] = m_size.parameters;

			m_ptr16 = (uint16_t*)(((size_t)m_y & ~(size_t)1u) + 2 * ((size_t)m_y & 1u));
		}
		//printf("\n");
	}
	m_size.numberGlyph = m_numberGlyph;
	m_size.size = offsetof(TrueTypeGlyf_t, ptr_glyph);
	m_size.size += ALIGN16(m_numberGlyph * sizeof(union TrueTypeGlyfParameters));
	m_size.instructions = ALIGN16(m_size.instructions);
	m_size.endCounter = ALIGN16(m_size.endCounter);
	m_size.glyphIndex = ALIGN16(m_size.glyphIndex);
	m_size.flags = ALIGN16(m_size.flags);
	m_size.parameters = ALIGN16(m_size.parameters);

	m_size.size += m_size.instructions;
	m_size.size += m_size.endCounter;
	m_size.size += m_size.glyphIndex;
	m_size.size += m_size.flags;
	m_size.size += m_size.parameters;
	return m_size;
}

void TrueTypeGlyf(uint8_t* tables, TrueTypeGlyf_t* dst, struct _TrueTypeGlyf_size_t* size) {
	const TrueTypeTables_t* m_tables = (TrueTypeTables_t*)tables;

	struct TrueTypeGlyf_simple_t* m_simple;
	struct TrueTypeGlyf_composite_t* m_composite;

	uint8_t* m_dst_instructions = align16(dst->ptr_glyph + size->numberGlyph);
	uint8_t* m_dst_endCountours = m_dst_instructions + size->instructions;
	uint8_t* m_dst_glyphIndex = m_dst_endCountours + size->endCounter;
	uint8_t* m_dst_flags = m_dst_glyphIndex + size->glyphIndex;
	uint8_t* m_dst_parameters = m_dst_flags + size->flags;

	//const void* tmp = m_dst_flags + size->flags;

	const int16_t locFormat = m_tables->head->locFormat;
	const uint16_t* m_src16;
	uint16_t* m_dst16;
	uint8_t* m_dst8;
	uint_fast32_t i, j, i_end, j_end, id;
	i = j = i_end = j_end = id = 0;

	dst->number_glyph = size->numberGlyph;

	for (id = 0; id < m_tables->maxp->numGlyphs; id++) {
		if (locFormat)
			i = m_tables->loca->glyphOffsets32[id],
			j = m_tables->loca->glyphOffsets32[id + 1];
		else
			i = 2 * m_tables->loca->glyphOffsets16[id],
			j = 2 * m_tables->loca->glyphOffsets16[id + 1];

		(dst->ptr_glyph + id)->simple.number_contours = 0;
		m_simple = &(dst->ptr_glyph + id)->simple;
		m_composite = &(dst->ptr_glyph + id)->composite;
		m_src16 = (const uint16_t*)(m_tables->glyf->ptrArr8 + i);

		m_simple->number_contours = 0;
		m_simple->x_min = 0;
		m_simple->y_min = 0;
		m_simple->x_max = 0;
		m_simple->y_max = 0;
		m_simple->numberInstructions = 0;
		m_simple->number_points = 0;
		m_simple->endCountours = 0;
		m_simple->instructions = 0;
		m_simple->m_flags = 0;
		m_simple->parameters = 0;

		if (i >= m_tables->glyf_length)
			continue;
		if (i == j)
			continue;
		i = 0;
		j = 0;
		if (*m_src16 > INT16_MAX) {
			m_composite->number_contours = m_src16[i++];
			m_composite->x_min = m_src16[i++];
			m_composite->y_min = m_src16[i++];
			m_composite->x_max = m_src16[i++];
			m_composite->y_max = m_src16[i++];
			m_composite->numberInstructions = 0;
			m_composite->parameters = (TrueTypeGlyph_composite_parameters*)align16(m_dst_parameters);
			m_composite->glyphIndex = (uint16_t*)m_dst_glyphIndex;
			m_composite->instructions = (uint8_t*)m_dst_instructions;

			do {
				TrueTypeGlyph_composite_parameters m_param = { 1.0f, 0.0f, 0.0f, 1.0f, 0, 0, 0, 0 };
				i_end = m_src16[i + 0];
				m_composite->glyphIndex[j] = m_src16[i + 1];
				if (i_end & GLYPH_COMPOSITE_ARG_1_AND_2_ARE_WORDS) {
					if (i_end & GLYPH_COMPOSITE_ARGS_ARE_XY_VALUES) {
						m_param.xtranslate = ((int16_t*)m_src16)[i + 2];
						m_param.ytranslate = ((int16_t*)m_src16)[i + 3];
					}
					else {
						m_param.point1 = m_src16[i + 2];
						m_param.point2 = m_src16[i + 3];
					}
					if (i_end & GLYPH_COMPOSITE_WE_HAVE_A_SCALE) {
						m_param.xscale = m_src16[i + 4];
						m_param.yscale = m_src16[i + 4];
					}
					else if (i_end & GLYPH_COMPOSITE_WE_HAVE_AN_X_AND_Y_SCALE) {
						m_param.xscale = m_src16[i + 4];
						m_param.yscale = m_src16[i + 5];
					}
					else if (i_end & GLYPH_COMPOSITE_WE_HAVE_A_TWO_BY_TWO) {
						m_param.xscale = m_src16[i + 4];
						m_param.scale01 = m_src16[i + 5];
						m_param.scale10 = m_src16[i + 6];
						m_param.yscale = m_src16[i + 7];
					}
				}
				else {
					if (i_end & GLYPH_COMPOSITE_ARGS_ARE_XY_VALUES) {
						m_param.xtranslate = ((int8_t*)m_src16)[(i + 2) * 2 + 0];
						m_param.ytranslate = ((int8_t*)m_src16)[(i + 2) * 2 + 1];
					}
					else {
						m_param.point1 = ((uint8_t*)m_src16)[(i + 2) * 2 + 0];
						m_param.point2 = ((uint8_t*)m_src16)[(i + 2) * 2 + 1];
					}
					if (i_end & GLYPH_COMPOSITE_WE_HAVE_A_SCALE) {
						m_param.xscale = m_src16[i + 3];
						m_param.yscale = m_src16[i + 3];
					}
					else if (i_end & GLYPH_COMPOSITE_WE_HAVE_AN_X_AND_Y_SCALE) {
						m_param.xscale = m_src16[i + 3];
						m_param.yscale = m_src16[i + 4];
					}
					else if (i_end & GLYPH_COMPOSITE_WE_HAVE_A_TWO_BY_TWO) {
						m_param.xscale = m_src16[i + 3];
						m_param.scale01 = m_src16[i + 4];
						m_param.scale10 = m_src16[i + 5];
						m_param.yscale = m_src16[i + 6];
					}
				}
				m_composite->parameters[j] = m_param;
				i += (size_t)(i_end & GLYPH_COMPOSITE_ARG_1_AND_2_ARE_WORDS) + 3;
				i += (size_t)((i_end & GLYPH_COMPOSITE_WE_HAVE_A_SCALE) >> 3) |
					((i_end & GLYPH_COMPOSITE_WE_HAVE_AN_X_AND_Y_SCALE) >> 5) |
					((i_end & GLYPH_COMPOSITE_WE_HAVE_A_TWO_BY_TWO) >> 5);
				j++;
			} while (i_end & GLYPH_COMPOSITE_MORE_COMPONENTS);
			m_composite->composite_number = j;

			m_dst_parameters = (uint8_t*)(m_composite->parameters + j);
			m_dst_glyphIndex = (uint8_t*)(m_composite->glyphIndex + j);

			if (i_end & GLYPH_COMPOSITE_WE_HAVE_INSTRUCTIONS) {
				j_end = m_src16[i];
				m_composite->numberInstructions = j_end;
				REPEAT_COPY32_ARRAY(uint8_t, uint8_t, m_composite->instructions, , (uint8_t*)(m_src16 + i + 1), j, j_end, i);
				m_dst_instructions = (uint8_t*)(m_composite->instructions + j_end);
			}
		}
		else {
			uint16_t m_number_c = m_src16[0];
			uint16_t m_number_i = m_src16[5 + m_number_c];
			uint16_t m_number_f;
			uint16_t m_number_x;
			uint16_t m_number_p;

			const uint16_t* m_c = ((uint16_t*)(m_src16 + 5));
			const uint8_t* m_i = ((uint8_t*)(m_c + m_number_c + 1));
			const uint8_t* m_f = ((uint8_t*)(m_c + m_number_c + 1)) + m_number_i;
			const uint8_t* m_x;
			const uint8_t* m_y;

			m_simple->number_contours = (int16_t)m_number_c;
			m_simple->numberInstructions = m_number_i;
			m_simple->x_min = (int16_t)m_src16[1];
			m_simple->y_min = (int16_t)m_src16[2];
			m_simple->x_max = (int16_t)m_src16[3];
			m_simple->y_max = (int16_t)m_src16[4];
			m_simple->endCountours = (uint16_t*)m_dst_endCountours;
			m_simple->instructions = (uint8_t*)m_dst_instructions;
			m_simple->m_flags = (uint8_t*)m_dst_flags;
			m_simple->parameters = (TrueTypeGlyf_simple_parameters*)align16(m_dst_parameters);

			m_dst16 = m_simple->endCountours;
			m_dst8 = m_simple->instructions;

			REPEAT_COPY16_ARRAY(uint16_t, uint16_t, m_dst16, , m_c, j, m_number_c, i);
			REPEAT_COPY64_ARRAY(uint8_t, uint8_t, m_dst8, , m_i, j, m_number_i, i);

			m_number_x = TrueTypeGlyf_simple_flags(m_f, &m_number_f, &m_number_p, m_c[m_number_c - 1] + 1);
			m_x = m_f + m_number_f;
			m_y = m_f + m_number_x;

			uint32_t m_points = TrueTypeGlyf_simpleUnpack(m_simple->parameters, m_dst_flags, m_dst16, m_f, m_x, m_y, m_number_f, m_number_c);
			if (m_points > m_tables->maxp->maxPoints)
				m_tables->maxp->maxPoints = m_points;
			m_simple->number_points = m_points;
			m_dst_endCountours = (uint8_t*)(m_simple->endCountours + m_number_c);
			m_dst_instructions = (uint8_t*)(m_simple->instructions + m_number_i);
			m_dst_parameters = (uint8_t*)(m_simple->parameters + m_points);
			m_dst_flags = (uint8_t*)(m_simple->m_flags + m_points);
			//if (data[id] != m_dst_parameters - tmp)
			//	printf("Error! %zd\n", ((ptrdiff_t)m_dst_parameters) - ((ptrdiff_t)tmp) - ((ptrdiff_t)data[id]));
			//TrueTypeGlyf_print(dst);
		}
	}
	m_dst8 = align16(dst->ptr_glyph + (size_t)size->numberGlyph) + (size_t)size->instructions;
	if (align16(m_dst_instructions) != m_dst8)
		printf("Error instructions! %zd != %zd\n", (size_t)m_dst_instructions, (size_t)m_dst8);
	m_dst8 += size->endCounter;
	if (align16(m_dst_endCountours) != m_dst8)
		printf("Error end counters! %zd != %zd\n", (size_t)m_dst_endCountours, (size_t)m_dst8);
	m_dst8 += size->glyphIndex;
	if (align16(m_dst_glyphIndex) != m_dst8)
		printf("Error composite! %zd != %zd\n", (size_t)m_dst_glyphIndex, (size_t)m_dst8);
	m_dst8 += size->flags;
	if (align16(m_dst_flags) != m_dst8)
		printf("Error flags! %zd != %zd\n", (size_t)align16(m_dst_flags), (size_t)m_dst8);
	m_dst8 += size->parameters;
	if (align16(m_dst_parameters) != m_dst8)
		printf("Error parameters! %zd != %zd\n", (size_t)m_dst_parameters, (size_t)m_dst8);
}

void TrueTypeGlyf_print(TrueTypeGlyf_t* glyph, uint8_t showPoints) {
	size_t  i, i_end, j, j_end, c, c_end, counter_noCurve, max_noCurve = 0;
	for (i = 0, i_end = glyph->number_glyph; i < i_end; i++) {
		if (glyph->ptr_glyph[i].composite.number_contours < 0) {
			printf("%zd %d %d \n",
				i,
				glyph->ptr_glyph[i].composite.composite_number,
				glyph->ptr_glyph[i].composite.numberInstructions
			);
			for (j = 0, j_end = glyph->ptr_glyph[i].composite.composite_number; j < j_end; j++) {
				printf("\t%hu %6f %6f %6.6f %6.6f %6.6f %6.6f %6f %6f\n",
					glyph->ptr_glyph[i].composite.glyphIndex[j],
					glyph->ptr_glyph[i].composite.parameters[j].point1,
					glyph->ptr_glyph[i].composite.parameters[j].point2,
					glyph->ptr_glyph[i].composite.parameters[j].scale01,
					glyph->ptr_glyph[i].composite.parameters[j].scale10,
					glyph->ptr_glyph[i].composite.parameters[j].xscale,
					glyph->ptr_glyph[i].composite.parameters[j].yscale,
					glyph->ptr_glyph[i].composite.parameters[j].xtranslate,
					glyph->ptr_glyph[i].composite.parameters[j].ytranslate
				);
			}
		}
		else {
			printf("%zd %d %d %d %d %d %d %d\n",
				i,
				glyph->ptr_glyph[i].simple.number_contours,
				glyph->ptr_glyph[i].simple.numberInstructions,
				glyph->ptr_glyph[i].simple.number_points,
				glyph->ptr_glyph[i].simple.x_min,
				glyph->ptr_glyph[i].simple.x_max,
				glyph->ptr_glyph[i].simple.y_min,
				glyph->ptr_glyph[i].simple.y_max
			);
			//for (counter_noCurve = 0, j = 0, c = 0, j_end = (size_t)glyph->ptr_glyph[i].simple.number_contours; j < j_end; j++) {
			//	for (c_end = glyph->ptr_glyph[i].simple.endCountours[j]; c <= c_end; c++) {
			//		printf("%d ",
			//			glyph->ptr_glyph[i].simple.m_flags[c]
			//		);
			//		if (glyph->ptr_glyph[i].simple.m_flags[c] == 0) {
			//			counter_noCurve++;
			//			if (counter_noCurve > max_noCurve)
			//				max_noCurve = counter_noCurve;
			//		}
			//		else
			//			counter_noCurve = 0;
			//	}
			//}
			//printf("\n ");
			//if (max_noCurve > 3)
			//	printf("ERROR CURVE!");
			for (j = 0, c = 0, j_end = (size_t)glyph->ptr_glyph[i].simple.number_contours; j < j_end; j++) {
				for (c_end = glyph->ptr_glyph[i].simple.endCountours[j]; c <= c_end; c++) {
					if (showPoints)
						if (glyph->ptr_glyph[i].simple.m_flags[c] & GLYPH_FLAGS_ON_CURVE_POINT)
							printf("\t%d %d %d\n",
								glyph->ptr_glyph[i].simple.m_flags[c],
								glyph->ptr_glyph[i].simple.parameters[c].x,
								glyph->ptr_glyph[i].simple.parameters[c].y
							);
					if (glyph->ptr_glyph[i].simple.m_flags[c] & GLYPH_FLAGS_ON_CURVE_POINT)
						if (glyph->ptr_glyph[i].simple.parameters[c].x < glyph->ptr_glyph[i].simple.x_min ||
							glyph->ptr_glyph[i].simple.parameters[c].x > glyph->ptr_glyph[i].simple.x_max ||
							glyph->ptr_glyph[i].simple.parameters[c].y < glyph->ptr_glyph[i].simple.y_min ||
							glyph->ptr_glyph[i].simple.parameters[c].y > glyph->ptr_glyph[i].simple.y_max)
							printf("ERROR");
				}
			}
		}
	}
}
//float4 QuadraticPS(float2 p : TEXCOORD0, float4 color : COLOR0) : COLOR{
// Gradients    float2 px = ddx(p);   float2 py = ddy(p);
// Chain rule    float fx = (2*p.x)*px.x - px.y;   float fy = (2*p.x)*py.x - py.y;
// Signed distance    float sd = (p.x*p.x - p.y)/sqrt(fx*fx + fy*fy);
// Linear alpha    float alpha = 0.5 - sd;   if (alpha > 1)
// Inside     color.a = 1;   else if (alpha < 0)
// Outside    clip(-1);   else
// Near boundary     color.a = alpha;   return color; }

enum TrueTypeGLYPH_instructions {
	SVTCAY = 0x00,
	SVTCAX = 0x01,
	SPVTCAY = 0x02,
	SPVTCAX = 0x03,
	SFVTCAY = 0x04,
	SFVTCAX = 0x05,
	SPVTLP1P2_00 = 0x06,
	SPVTLP1P2_90 = 0x07,
	SFVTLP1P2_00 = 0x08,
	SFVTLP1P2_90 = 0x09,
	SFVTPV = 0x0E,
	SDPVTL_00 = 0x86,
	SDPVTL_90 = 0x87,
	SPVFS = 0x0A,
	SFVFS = 0x0B,
	GPV = 0x0C,
	GFV = 0x0D,
	SRP0 = 0x10,
	SRP1,
	SRP2,
	SZP0,
	SZP1,
	SZP2,
	SZPS,
	RTG = 0x18,
	RTHG = 0x19,
	RTDG = 0x3D,
	ROFF = 0x7A,
	RUTG = 0x7C,
	RDTG = 0x7D,
	SROUND = 0x76,
	S45ROUND = 0x77,
	SLOOP = 0x17,
	SMD = 0x1A,
	INSTCTRL = 0x8E,
	SCANCTRL = 0x85,
	SCANTYPE = 0x8D,
	SCVTCI = 0x1D,
	SSWCI = 0x1E,
	SSW = 0x1F,
	FLIPON = 0x4D,
	FLIPOFF = 0x4E,
	SANGW = 0x7E,
	SDB = 0x5E,
	SDS = 0x5F,

	NPUSHB = 0x40,
	NPUSHW = 0x41,
	WS = 0x42,
	RS = 0x43,
	WCVTP = 0x44,
	RCVT = 0x45,
	WCVTF = 0x70,
	PUSHB0 = 0xB0,
	PUSHB1 = 0xB1,
	PUSHB2 = 0xB2,
	PUSHB3 = 0xB3,
	PUSHB4 = 0xB4,
	PUSHB5 = 0xB5,
	PUSHB6 = 0xB6,
	PUSHB7 = 0xB7,
	PUSHW0 = 0xB8,
	PUSHW1 = 0xB9,
	PUSHW2 = 0xBA,
	PUSHW3 = 0xBB,
	PUSHW4 = 0xBC,
	PUSHW5 = 0xBD,
	PUSHW6 = 0xBE,
	PUSHW7 = 0xBF,

	GC0 = 0x46,
	GC1 = 0x47,
	SCFS = 0x48,
	MD0 = 0x49,
	MD1 = 0x4A,
	MPPEM = 0x4B,
	MPS = 0x4C,
	FLIPPT = 0x80,
	FLIPRGON = 0x81,
	FLIPRGOFF = 0x82,
	SHP_RP2_ZP1 = 0x32,
	SHP_RP1_ZP0 = 0x33,
	SHC_RP2_ZP1 = 0x34,
	SHC_RP1_ZP0 = 0x35,
	SHZ_RP2_ZP1 = 0x36,
	SHZ_RP1_ZP0 = 0x37,
	SHPIX = 0x38,
	MSIRP_not_rp0_p = 0x3A,
	MSIRP_rp0_p = 0x3B,
	MDAP_not_round = 0x2E,
	MDAP_round = 0x2F,
	MIAP0 = 0x3E,
	MIAP1 = 0x3F,

	MDRP_00000 = 0xC0,
	MDRP_00001,
	MDRP_00010,
	MDRP_00011,
	MDRP_00100,
	MDRP_00101,
	MDRP_00110,
	MDRP_00111,
	MDRP_01000,
	MDRP_01001,
	MDRP_01010,
	MDRP_01011,
	MDRP_01100,
	MDRP_01101,
	MDRP_01110,
	MDRP_01111,
	MDRP_10000,

	MDRP_10001,
	MDRP_10010,
	MDRP_10011,
	MDRP_10100,
	MDRP_10101,
	MDRP_10110,
	MDRP_10111,
	MDRP_11000,
	MDRP_11001,
	MDRP_11010,
	MDRP_11011,
	MDRP_11100,
	MDRP_11101,
	MDRP_11110,
	MDRP_11111,

	MIRP_00000,
	MIRP_00001,
	MIRP_00010,
	MIRP_00011,
	MIRP_00100,
	MIRP_00101,
	MIRP_00110,
	MIRP_00111,
	MIRP_01000,
	MIRP_01001,
	MIRP_01010,
	MIRP_01011,
	MIRP_01100,
	MIRP_01101,
	MIRP_01110,
	MIRP_01111,
	MIRP_10000,
	MIRP_10001,
	MIRP_10010,
	MIRP_10011,
	MIRP_10100,
	MIRP_10101,
	MIRP_10110,
	MIRP_10111,
	MIRP_11000,
	MIRP_11001,
	MIRP_11010,
	MIRP_11011,
	MIRP_11100,
	MIRP_11101,
	MIRP_11110,
	MIRP_11111,

	ALIGNRP = 0x3C,
	ISECT = 0x0F,
	ALIGNPTS = 0x27,
	IP = 0x39,
	UTP = 0x29,
	IUP0 = 0x30,
	IUP1,

	DELTAP1 = 0x5D,
	DELTAP2 = 0x71,
	DELTAP3 = 0x72,
	DELTAC1,
	DELTAC2,
	DELTAC3,
	DUP = 0x20,
	POP,
	CLEAR,
	SWAP,
	DEPTH,
	CINDEX,
	MINDEX,
	ROLL = 0x8A,
	IF = 0x58,
	ELSE = 0x1B,
	EIF = 0x59,
	JROT = 0x78,
	JMPR = 0x1C,
	JROF = 0x79,
	LT = 0x50,
	LTEQ,
	GT,
	GTEQ,
	EQ,
	NEQ,
	ODD,
	EVEN,
	AND = 0x5A,
	OR,
	NOT,

	ADD = 0x60,
	SUB,
	DIV,
	MUL,
	ABS,
	NEG,
	FLOOR,
	CEILING,
	MAX = 0x8B,
	MIN,

	ROUND00 = 0x68,
	ROUND01,
	ROUND10,
	ROUND11,
	NROUND00,
	NROUND01,
	NROUND10,
	NROUND11,

	LOOPCALL = 0x2A,
	CALL = 0x2B,
	FDEF = 0x2C,
	ENDF,
	IDEF = 0x89,
	DEBUG = 0x4F,
	GETINFO = 0x88,
	GETVARIATION = 0x91,
};

void TrueTypeGlyf_bmp_test(TrueTypeGlyf_t* glyph, uint32_t id) {
	size_t i;
	uint32_t srp[3];
	uint8_t* m_instructions;
	union TrueTypeGlyfParameters* m_param;
	enum TrueTypeGLYPH_instructions m_instruction;
	if (id >= glyph->number_glyph)
		return;
	m_param = glyph->ptr_glyph + id;
	if (m_param->simple.number_contours < 0)
		return;
	m_instructions = m_param->simple.instructions;
	for (i = 0; i < m_param->simple.numberInstructions; i++) {
		m_instruction = m_instructions[i];
		switch (m_instruction) {
		case PUSHW7:
			m_instructions[i + 15];
			m_instructions[i + 14];
		case PUSHW6:
			m_instructions[i + 13];
			m_instructions[i + 12];
		case PUSHW5:
			m_instructions[i + 11];
			m_instructions[i + 10];
		case PUSHW4:
			m_instructions[i + 9];
			m_instructions[i + 8];
		case PUSHW3:
			m_instructions[i + 7];
			m_instructions[i + 6];
		case PUSHW2:
			m_instructions[i + 5];
			m_instructions[i + 4];
		case PUSHW1:
			m_instructions[i + 3];
			m_instructions[i + 2];
		case PUSHW0:
			m_instructions[i + 2];
			m_instructions[i + 1];

		case PUSHB7:
			m_instructions[++i];
		case PUSHB6:
			m_instructions[++i];
		case PUSHB5:
			m_instructions[++i];
		case PUSHB4:
			m_instructions[++i];
		case PUSHB3:
			m_instructions[++i];
		case PUSHB2:
			m_instructions[++i];
		case PUSHB1:
			m_instructions[++i];
		case PUSHB0:
			m_instructions[++i];
		case SVTCAY:
			break;
		case CALL:
			break;
		}
	}
}