#ifndef __TRUETYPESIZE_H__
#define __TRUETYPESIZE_H__
#include <sal.h>
#include <stdint.h>

#include "TrueTypeError.h"
#include "TrueTypeFile.h"
#include "TrueTypeGlyph.h"
#include "TrueTypeLoca.h"
#include "TrueTypeTables.h"

typedef struct _TrueTypeSize_t {
    uint32_t size;
    TrueTypeGlyph_size_t glyf;
    uint32_t head;
    uint32_t hhea;
    uint32_t hmtx;
    uint32_t cmap;
    uint32_t maxp;
} TrueTypeSize_t;

TrueTypeError_t TrueTypeSize(_Out_ TrueTypeSize_t* dst,
    _In_ TrueTypeTables_t* tables,
    _In_ int8_t swap_byte);

#endif
