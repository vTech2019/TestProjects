#include "TrueTypeSize.h"
#include "TrueTypeTables.h"
#include "TrueTypeLibrary.h"
#include "TrueTypeError.h"

#include "TrueTypeLoca.h"
#include "TrueTypeGlyph.h"
#include "TrueTypeCmap.h"
#include "TrueTypeHead.h"
#include "TrueTypeHhea.h"
#include "TrueTypeHmtx.h"
#include "TrueTypeMaxp.h"

TrueTypeError_t TrueTypeSize(_Out_ TrueTypeSize_t* dst,
    _In_ TrueTypeTables_t* tables,
    _In_ int8_t byte_swap) {
    dst->head = TrueTypeHEAD_size(tables->head, byte_swap);
    dst->hhea = TrueTypeHHEA_size(tables->hhea, byte_swap);
    dst->maxp = TrueTypeMAXP_size(tables->maxp, byte_swap);
    TrueTypeLOCA(tables->loca, tables->loca, tables->head->locFormat, tables->maxp->numGlyphs, byte_swap);
    dst->cmap = TrueTypeCMAP_size(tables->cmap, byte_swap);
    TrueTypeGLYF_size(tables, &dst->glyf, byte_swap);
    dst->hmtx = TrueTypeHMTX_size(tables, byte_swap);

    dst->size = ALIGN64(sizeof(TrueTypeReader_t)) + dst->hhea + dst->cmap +
        dst->glyf.composite + dst->glyf.simple + dst->head +
        dst->maxp + dst->hmtx;
    return e_TrueTypeCodeError_success;
}