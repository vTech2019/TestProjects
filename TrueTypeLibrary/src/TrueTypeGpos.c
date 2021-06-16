#include "TrueTypeGpos.h"

#include "TrueTypeError.h"
#include "TrueTypeSize.h"
#include "TrueTypeTables.h"
#include "TrueTypeMalloc.h"

struct lookupListTable {
	uint16_t lookupCount;
	uint16_t lookupOffsets[1];
};
void TrueTypeGpos(uint8_t* src, TrueTypeGpos_t* dst)
{
    (void)(src);
    (void)(dst);
	/*
	uint16_t i;
	uint8_t* m_featureList;
	uint8_t* m_lookupList;
	struct lookupListTable* listTableOffset;
	TrueTypeGpos_t* m_gpos = (TrueTypeGpos_t*)src;
	listTableOffset = (struct lookupListTable*)(src + m_gpos->lookupListOffset);

	if (m_gpos->majorVersion != 1 && m_gpos->minorVersion != 0)
		return;

	for (i = 0; i < listTableOffset->lookupCount; i++) {
	}
	 */
}