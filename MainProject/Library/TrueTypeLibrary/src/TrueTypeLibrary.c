// TrueTypeReader.cpp: определяет точку входа для приложения.
//
#include "TrueTypeLibrary.h"

#include "TrueTypeError.h"
#include "TrueTypeSize.h"
#include "TrueTypeTables.h"
#include "TrueTypeMalloc.h"

TrueTypeReader_t* TrueTypeReader_Init(_In_z_ const char* const font) {
    TrueTypeError_t m_error;
    TrueTypeSize_t m_size = { 0 };
    TrueTypeTables_t m_tables = { 0 };
    TrueTypeFile_t m_file = { 0 };
    TrueTypeReader_t* m_reader = NULL;

    if ((m_error = TrueTypeFile(&m_file, font)) != e_TrueTypeCodeError_success)
        goto goto_error;
    if ((m_error = TrueTypeTables_SByte(&m_tables, m_file.memory.header, m_file.size)) != e_TrueTypeCodeError_success)
        goto goto_error;
    if ((m_error = TrueTypeSize(&m_size, &m_tables, 1)) != e_TrueTypeCodeError_success)
        goto goto_error;
    if ((m_reader = TrueTypeMalloc(&m_size)) == NULL) {
        m_error = e_TrueTypeCodeError_MallocOutOfMemory;
        goto goto_error;
    }

    TrueTypeHead(m_tables.head, m_reader->head);
    TrueTypeHhea(m_tables.hhea, m_reader->hhea);
    TrueTypeMaxp(m_tables.maxp, m_reader->maxp);

    TrueTypeHmtx(&m_tables, m_reader->hmtx);
    TrueTypeCmap(m_tables.cmap, m_reader->cmap);
    TrueTypeGlyf(&m_tables, m_reader->glyf, &m_size.glyf);

    TrueTypeFile_Free(&m_file);
    return m_reader;
goto_error:
    TrueTypeFile_Free(&m_file);
    TrueTypeFree(m_reader);
    return m_reader;
}
void TrueTypeReader_Free(_Pre_maybenull_ _Post_invalid_  TrueTypeReader_t* reader) {
    TrueTypeFree(reader);
}