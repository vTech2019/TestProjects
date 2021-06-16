#ifndef __TRUETYPECMAP_H__
#define __TRUETYPECMAP_H__

#include "stdafx.h"
#include "TrueTypeError.h"

enum TrueTypeCmap_platform {
	Unicode,
	Macintosh,
	Microsoft = 3
};
enum TrueTypeCmap_UnicodeEncodingPlatform {
	Unicode_1_0,
	Unicode_1_1,
	Unicode_ISO_IEC_10646,
	Unicode_2_0_BMP,
	Unicode_2_0_Full,
	Unicode_Variation_Sequences,
	Unicode_Full_Repertoire
};
enum TrueTypeCmap_MicrosoftEncodingPlatform {
	Microsoft_Symbol,
	Microsoft_Unicode_BMP,
	Microsoft_ShiftJIS,
	Microsoft_PRC,
	Microsoft_BigFive,
	Microsoft_Wansung,
	Microsoft_Johab,
	Microsoft_Unicode_full_repertoire = 10
};

struct TrueTypeCmap0_t {
	uint8_t glyphIdArray[256];
};
struct TrueTypeCmap4_subheader_t {
	uint16_t endCode, startCode, idRangeOffset;
	int16_t idDelta;
};
struct TrueTypeCmap4_t {
	uint16_t segCountX2;
	uint16_t searchRange;
	uint16_t entrySelector;
	uint16_t rangeShift;
	const uint16_t* glyphId;
	struct TrueTypeCmap4_subheader_t code[1];
};
union TrueTypeCmap_subtable_t {
	struct TrueTypeCmap0_t* _0;
	struct TrueTypeCmap4_t* _4;
};
typedef struct _TrueTypeCmapData_t {
	uint16_t platform_ID;
	uint16_t platform_specification_ID;
	uint16_t format;
	uint16_t language;
	union TrueTypeCmap_subtable_t cmap;
} TrueTypeCmapData_t;

typedef ALIGNED64(struct, _TrueTypeCmap_t {
    TrueTypeCmapData_t* subtable_data;

	uint16_t version;
	uint16_t numberSubtables;

	TrueTypeCmapData_t subtables[1];
} TrueTypeCmap_t);


uint32_t TrueTypeCMAP_size(_Inout_ void* tables, _In_ int8_t swap_byte);
void TrueTypeCmap(_In_ uint8_t* src, _Out_ TrueTypeCmap_t* dst, void** ptrSelectFunction);


#endif
