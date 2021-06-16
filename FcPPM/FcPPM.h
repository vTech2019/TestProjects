#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#ifdef _WIN32
#include <Windows.h>
#endif
#ifdef UNICODE
#define strlen wcslen
#define rename _wrename
#define fopen _wfopen
#define fopen_s _wfopen_s
#define tchar wchar_t
#ifndef TEXT
#define __T(x) L ## x
#define TEXT(x) __T(x)
#endif
#else
#define strlen strlen
#define rename rename
#define fopen fopen
#define fopen_s fopen_s
#define tchar char
#ifndef TEXT
#define TEXT(x) (x)
#endif
#endif
#ifdef __cplusplus
extern "C" {
#endif
	void convert_sRGB_to_RGB_255(unsigned char* image, size_t width, size_t height);
	unsigned char* convert_pgm_to_pbm(const unsigned char* image_pgm, const size_t size_data);
	unsigned char* convert_pgm_to_ppm(const unsigned char* image_pgm, const size_t size_data);

	int FcPBM_write(tchar* name_file, char* image, size_t width_bit, size_t height_bit);
	int FcPGM_write(tchar* name_file, char* image, size_t width, size_t height, size_t max_color_component_pixel);
	int FcPPM_write(tchar* name_file, char* image, size_t width, size_t height, size_t max_color_component_pixel);

	int FcPBM_read(tchar* name_file, void** image, void* (*memory_reallocator)(void** memory, size_t width, size_t height, size_t pixel_bit_size));
	int FcPGM_read(tchar* name_file, void** image, void* (*memory_reallocator)(void** memory, size_t width, size_t height, size_t pixel_bit_size));
	int FcPPM_read(tchar* name_file, void** image, void* (*memory_reallocator)(void** memory, size_t width, size_t height, size_t pixel_bit_size));

#ifdef __cplusplus
}
#endif
