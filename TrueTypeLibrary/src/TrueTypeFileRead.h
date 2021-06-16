#ifndef __TRUETYPEFILEREAD_H__
#define __TRUETYPEFILEREAD_H__
#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "TrueTypeError.h"
#include "TrueTypeTables.h"

typedef struct _TrueTypeFileRead_t {
	union {
		uint8_t* ptr8;
		struct _TrueTypeHeader_t* header;
	} memory;
	size_t size;
} TrueTypeFileRead_t;

static inline TrueTypeError_t TrueTypeFileRead(_Out_ TrueTypeFileRead_t* file,
	_In_z_  char const* const name) {
	_Out_ FILE* m_stream;
	long size_file;
	file->memory.ptr8 = NULL;
	file->size = 0;
#ifdef _MSC_VER
	if (fopen_s(&m_stream, name, "rb") != 0)
		return e_TrueTypeCodeError_fopen;
#else
	if ((m_stream = fopen(name, "rb")) == NULL)
		return e_TrueTypeCodeError_fopen;
#endif
	if (m_stream == NULL)
		return e_TrueTypeCodeError_fopen;

	if (fseek(m_stream, 0, SEEK_END) != 0)
		return e_TrueTypeCodeError_fseek;
	if ((size_file = ftell(m_stream)) == -1L)
		return e_TrueTypeCodeError_ftell;
	rewind(m_stream);
	if ((file->memory.ptr8 = (uint8_t*)malloc((size_t)size_file)) == NULL)
		return e_TrueTypeCodeError_malloc;
	file->size = (size_t)size_file;
	if (!fread(file->memory.ptr8, (size_t)size_file, 1, m_stream))
		return e_TrueTypeCodeError_read;
	if (fclose(m_stream) != 0)
		return e_TrueTypeCodeError_fclose;

	return e_TrueTypeCodeError_success;
}

static inline TrueTypeError_t
TrueTypeFileRead_Free(_Out_ TrueTypeFileRead_t* file) {
	free(file->memory.ptr8);
	file->memory.ptr8 = NULL;
	file->size = 0;
	return e_TrueTypeCodeError_success;
}

#endif
