#include <sal.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef __TRUETYPEREADER_H__
#define __TRUETYPEREADER_H__
#include "TrueTypeCmap.h"
#include "TrueTypeGlyph.h"
#include "TrueTypeHead.h"
#include "TrueTypeHhea.h"
#include "TrueTypeHmtx.h"
#include "TrueTypeMaxp.h"

typedef struct _TrueTypeReader_t {
    uint32_t dsigLength;
    uint32_t dsigOffset;

    __declspec(align(64)) struct _TrueTypeHead_t* head;
    __declspec(align(64)) struct _TrueTypeHhea_t* hhea;
    __declspec(align(64)) struct _TrueTypeMaxp_t* maxp;
    __declspec(align(64)) struct _TrueTypeHmtx_t* hmtx;
    __declspec(align(64)) struct _TrueTypeCmap_t* cmap;
    __declspec(align(64)) struct _TrueTypeGlyf_t* glyf;
} TrueTypeReader_t;

#ifdef __cplusplus
extern "C" TrueTypeReader_t * TrueTypeReader_Init(_In_z_ const char* font);
void TrueTypeReader_Free(_Pre_maybenull_ _Post_invalid_  TrueTypeReader_t* reader);
#else
TrueTypeReader_t* TrueTypeReader_Init(_In_z_ const char* font);
void TrueTypeReader_Free(_Pre_maybenull_ _Post_invalid_  TrueTypeReader_t* reader);
#endif

#endif
