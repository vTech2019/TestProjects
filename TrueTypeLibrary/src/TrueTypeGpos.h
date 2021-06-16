#ifndef __TRUETYPEGPOS_H__
#define __TRUETYPEGPOS_H__
#include "stdafx.h"
#include "TrueTypeError.h"

typedef ALIGNED64(struct, _TrueTypeGpos_t {
	uint16_t    majorVersion;
	uint16_t    minorVersion;
	uint16_t 	scriptListOffset;
	uint16_t 	featureListOffset;
	uint16_t 	lookupListOffset;
	uint16_t 	featureVariationsOffset[2];
} TrueTypeGpos_t);

typedef struct _TrueTypeGpos_singlePosFormat1 {
	uint16_t 	posFormat;
	uint16_t 	coverageOffset;
	uint16_t 	valueFormat;
	//union {
	//	uint16_t 	valueCount;
		//ValueRecord valueRecords;
	//};
	// ValueRecord valueRecords[];
}TrueTypeGpos_singlePosFormat1;

void TrueTypeGpos(_In_ uint8_t* src, _Out_ TrueTypeGpos_t* dst);

uint32_t TrueTypeGpos_size(_Inout_ uint8_t* table, int8_t swap_byte);

#endif