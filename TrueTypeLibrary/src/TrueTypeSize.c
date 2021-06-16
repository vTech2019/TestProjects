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

#include "TrueTypeFile.h"

TrueTypeError_t TrueTypeSize(_Out_ TrueTypeSize_t* dst,
	_In_ TrueTypeTables_t* tables,
	_In_ int8_t byte_swap) {
	dst->head = TrueTypeHEAD_size((uint8_t*)tables->head, byte_swap);
	dst->hhea = TrueTypeHHEA_size((uint8_t*)tables->hhea, byte_swap);
	dst->maxp = TrueTypeMAXP_size(tables->maxp, byte_swap);
	dst->hmtx = TrueTypeHMTX_size((uint8_t*)tables, byte_swap);
	TrueTypeLOCA(tables->loca, tables->loca, tables->head->locFormat, tables->maxp->numGlyphs, byte_swap);
	dst->cmap = TrueTypeCMAP_size((uint8_t*)tables, byte_swap);
	dst->glyf = TrueTypeGLYF_size((uint8_t*)tables);


	dst->size = 2 * ALIGN64(sizeof(TrueTypeReader_t));
	dst->size += dst->head;
	dst->size += dst->hhea;
	dst->size += dst->maxp; 
	dst->size += dst->cmap;
	dst->size += dst->glyf.size;
	dst->size += dst->hmtx;
	return e_TrueTypeCodeError_success;
}
