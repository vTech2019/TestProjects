//#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
typedef ptrdiff_t bmpReaderInfo;
#ifdef UNICODE
#define tchar wchar_t
#else
#define tchar char
#endif


#ifdef _MSC_VER
#define aligned_alloc(align, size) _aligned_malloc(size, align)
#define aligned_free _aligned_free
#else
#define aligned_free free
#endif


enum FILE_INFO {
	BMPLIB_NO_ERROR,
	BMPLIB_STDIO_ERROR,
	BMPLIB_BMP_FILE = 0x4D42
};

#define CACHE_LINE  64

#ifndef ALIGNED
#ifdef __GNUC__
#define ALIGNED(value, str, x) str x __attribute__ ((aligned(value)))
#else
#define ALIGNED(value, str, x) str __declspec(align(value)) x
#endif
#endif

typedef ALIGNED(CACHE_LINE, struct, bmpImage_t{
	size_t width;
	size_t height;
	size_t pitch;
	size_t number_bit_pixel;
	uint8_t memory[1];
}bmpImage_t);


static inline bmpImage_t* bmpLibrary_create(size_t width, size_t height, size_t bitsPerPixelSize){
	size_t i;
	size_t m_pitch = ((width * bitsPerPixelSize + 31) / 32) * 4;
	size_t m_size = offsetof(bmpImage_t, memory) + height * m_pitch;
	
	bmpImage_t* image = (bmpImage_t*)aligned_alloc(CACHE_LINE, m_size);
	for (i = 0; i < m_size; i++)
		((uint8_t*)image)[i] = 0;
	if (image) {
		image->height = height;
		image->width = width;
		image->number_bit_pixel = bitsPerPixelSize;
		image->pitch = m_pitch;
	}
	return image;
}
static inline void bmpLibrary_free(bmpImage_t* image)
{
	aligned_free(image);
}
#ifdef __cplusplus
extern "C" {
#endif
bmpReaderInfo FcBMP_write_8(const tchar* name_file, bmpImage_t* image);
bmpReaderInfo FcBMP_write_Bin(const tchar* name_file, bmpImage_t* image);
bmpReaderInfo FcBMP_write_TrueColor24(const tchar* name_file, bmpImage_t* image);
bmpReaderInfo FcBMP_read(const tchar* name_file, bmpImage_t* image);
#ifdef __cplusplus
}
#endif
