#ifndef __TRUETYPEOFFSET_H__
#define __TRUETYPEOFFSET_H__
#include <stdint.h>
#include "TrueTypeMath.h"
#include "TrueTypeError.h"
#include "TrueTypeHeader.h"


struct TrueTypeHeader_t {
	uint32_t sfntVersion;
	uint16_t numTables;
	uint16_t searchRange;
	uint16_t entrySelector;
	uint16_t rangeShift;
	struct TrueTypeTables_t {
		uint32_t tag;
		uint32_t checksum;
		uint32_t offset;
		uint32_t length;
	} tables[];
};

struct TrueTypeTable_t{
	struct TrueTypeHeader_t* header;
	struct TrueTypeTables_t* head;
	struct TrueTypeTables_t* hhea;
	struct TrueTypeTables_t* hmtx;
	struct TrueTypeTables_t* cmap;
	struct TrueTypeTables_t* maxp;
	struct TrueTypeTables_t* loca;
	struct TrueTypeTables_t* glyf;
};

TrueTypeError_t TrueTypeTables(struct TrueTypeTable_t* offset, uint8_t* header, uint32_t file_size, int32_t swap_byte);

#endif