#ifndef __TRUETYPEREADER_H__
#define __TRUETYPEREADER_H__
#include "stdafx.h"
//#include "TrueTypeCmap.h"
#include "TrueTypeGlyph.h"
#include "TrueTypeHead.h"
//#include "TrueTypeHhea.h"
//#include "TrueTypeHmtx.h"
#include "TrueTypeMaxp.h"
#include "TrueTypeError.h"

struct _TrueTypeHead_t;
struct _TrueTypeHhea_t;
struct _TrueTypeHmtx_t;
struct _TrueTypeCmap_t;
struct _TrueTypeGlyf_t;

typedef struct _TrueTypeImage_t {
	size_t width;
	size_t height;
	size_t pitch;
	size_t number_bit_pixel;
	uint8_t memory[1];
}TrueTypeImage_t;

typedef struct _TrueTypeReader_t {
	uint32_t(*selectGlyph)(const struct _TrueTypeReader_t*, uint32_t unicode);

	struct _TrueTypeHead_t* head;
	struct _TrueTypeHhea_t* hhea;
	struct _TrueTypeMaxp_t* maxp;
	struct _TrueTypeHmtx_t* hmtx;
	struct _TrueTypeCmap_t* cmap;
	struct _TrueTypeGlyf_t* glyf;
} TrueTypeReader_t;

#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
typedef struct _TrueType_systemFonts_t {
	size_t m_numberFonts;
	struct {
		TCHAR* name;
		BYTE* data;
	}font[1];
}TrueType_systemFonts_t;
LSTATUS GetSystemFonts_malloc(TrueType_systemFonts_t** resultFontFiles);
LSTATUS GetSystemFontFile_malloc(const TCHAR* faceName, TCHAR** resultFontFile);
static inline void GetSystemFontFile_free(TCHAR* resultFontFile) { free(resultFontFile); };
static inline void GetSystemFonts_free(TCHAR* resultFontsFile) { free(resultFontsFile); };
#elif defined(linux) || defined(__linux)
typedef struct _TrueType_systemFonts_t {
	size_t m_numberFonts;
	struct {
		char* name;
		char* data;
	}font[1];
}TrueType_systemFonts_t;

uint32_t GetSystemFonts_malloc(TrueType_systemFonts_t** resultFontFiles);
uint32_t GetSystemFontFile_malloc(const char* faceName, char** resultFontFile);
static inline void GetSystemFontFile_free(char* resultFontFile) { free(resultFontFile); }
static inline void GetSystemFonts_free(char* resultFontsFile) { free(resultFontsFile); }

#endif

static inline uint16_t TrueTypeReader_maxPoints(TrueTypeReader_t* reader) { return reader->maxp->maxPoints; }

float* TrueTypeReader_getPoints(TrueTypeReader_t* reader, uint16_t unicode);


#ifdef __cplusplus
extern "C" {
#endif
TrueTypeReader_t* TrueTypeReader_init(_In_z_ const char* font, _Pre_maybenull_ int32_t* error);
void TrueTypeReader_free(_Pre_maybenull_ _Post_invalid_  TrueTypeReader_t* reader);
size_t TrueTypeReader_bmpScanConverter(TrueTypeReader_t* reader, uint32_t startX, uint32_t startY, uint32_t pixels, uint32_t unicode, TrueTypeImage_t* image);


#ifdef __cplusplus
}
#endif

#endif
