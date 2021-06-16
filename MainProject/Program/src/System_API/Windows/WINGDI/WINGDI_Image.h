#pragma once

#ifdef _WIN32
#include <Windows.h>

#ifdef __cplusplus
#include <gdiplus.h>
#include <Commdlg.h>
#pragma comment(lib, "gdiplus.lib")
#endif

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

enum FORMATS { BMP, JPG, GIF, TIF, PNG };


//void WINGDI_read_image(const WCHAR* name_file, void** image, void* (*memory_reallocator)(void** memory, size_t width, size_t height, size_t pixel_bit_size));
//void WINGDI_save_image(dataImage& image, const WCHAR* directory_name, const WCHAR* name, size_t format);
