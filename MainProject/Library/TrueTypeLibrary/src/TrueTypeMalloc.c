#include "TrueTypeMalloc.h"

_Ret_maybenull_ TrueTypeReader_t* TrueTypeMalloc(_In_ TrueTypeSize_t* size) {
    TrueTypeReader_t* dst = malloc(size->size);
    if (!dst)
        return NULL;
    union {
        TrueTypeReader_t* reader;
        struct _TrueTypeHead_t* head;
        struct _TrueTypeHhea_t* hhea;
        struct _TrueTypeMaxp_t* maxp;
        struct _TrueTypeHmtx_t* hmtx;
        struct _TrueTypeCmap_t* cmap;
        struct _TrueTypeGlyf_t* glyf;
        uint8_t* ptr8;
    } m_ptr_table = { align64((uintptr_t)(dst + 1)) };

    dst->head = m_ptr_table.head;
    m_ptr_table.ptr8 += size->head;
    dst->hhea = m_ptr_table.hhea;
    m_ptr_table.ptr8 += size->hhea;
    dst->maxp = m_ptr_table.maxp;
    m_ptr_table.ptr8 += size->maxp;
    dst->hmtx = m_ptr_table.hmtx;
    m_ptr_table.ptr8 += size->hmtx;
    dst->cmap = m_ptr_table.cmap;
    m_ptr_table.ptr8 += size->cmap;
    dst->glyf = m_ptr_table.glyf;
    m_ptr_table.ptr8 += size->glyf.size;

    return dst;
}
void TrueTypeFree(_Pre_maybenull_ _Post_invalid_ TrueTypeReader_t* ptr) {
    free(ptr);
}