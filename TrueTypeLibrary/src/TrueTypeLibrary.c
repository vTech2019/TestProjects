#include "TrueTypeLibrary.h"
#include "TrueTypeTables.h"
#include "TrueTypeError.h"
#include "TrueTypeSize.h"
#include "TrueTypeAlgo.h"
#include "TrueTypeMalloc.h"
#include "TrueTypeHmtx.h"
#include "TrueTypeCmap.h"

#include "TrueTypeFile.h"
#include "TrueTypeFileRead.h"

TrueTypeReader_t* TrueTypeReader_init(_In_z_ const char* const font, _Pre_maybenull_ int32_t* error) {
	TrueTypeError_t m_error;
	TrueTypeSize_t m_size = { 0 };
	TrueTypeTables_t m_tables = { 0 };
	TrueTypeFileRead_t m_file = { 0 };
	TrueTypeReader_t* m_reader = NULL;

	if ((m_error = TrueTypeFileRead(&m_file, font)) != e_TrueTypeCodeError_success)
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

	TrueTypeCmap((uint8_t*)m_tables.cmap, m_reader->cmap, &m_reader->selectGlyph);
	TrueTypeGlyf((uint8_t*)&m_tables, m_reader->glyf, &m_size.glyf);

	//TrueTypeGlyf_print(m_reader->glyf, 0);
	TrueTypeFileRead_Free(&m_file);
	return m_reader;
goto_error:
	if (error) *error = m_error;
	TrueTypeFileRead_Free(&m_file);
	TrueTypeFree(m_reader);
	return m_reader;
}

void TrueTypeReader_free(_Pre_maybenull_ _Post_invalid_  TrueTypeReader_t* reader) {
	TrueTypeFree(reader);
}

size_t TrueTypeReader_bmpScanConverter(TrueTypeReader_t* reader, uint32_t startX, uint32_t startY, uint32_t pixels, uint32_t unicode, TrueTypeImage_t* image) {
	size_t id, width, height, widthFont, heightFont, widthBox, heightBox;
	ptrdiff_t px1, px2, py1, py2;
	ptrdiff_t x0, x1, y0, y1;
	ptrdiff_t a, d, lineGap, aw;
	ptrdiff_t lsb, rsb, unit;

	id = reader->selectGlyph(reader, unicode);
	id = unicode;

	a = reader->hhea->ascender;
	d = reader->hhea->descender;
	lineGap = reader->hhea->lineGap;

	float linespace = a - d + lineGap;

	//float upem = TrueTypeGlyf_unitToPixel(linespace, pixels, 96, reader->head->units_per_em);
	//float ppem = (float)linespace * 96 / 72;
	//float scalePixel =  (upem) / linespace;

	double scalePixel = (float)pixels / linespace;

	a *= scalePixel;
	d *= scalePixel;
	lineGap *= scalePixel;

	x0 = reader->glyf->ptr_glyph[id].simple.x_min * scalePixel;
	x1 = reader->glyf->ptr_glyph[id].simple.x_max * scalePixel;
	y0 = reader->glyf->ptr_glyph[id].simple.y_min * scalePixel;
	y1 = reader->glyf->ptr_glyph[id].simple.y_max * scalePixel;
	linespace *= scalePixel;
	width = abs(x1 - x0);
	height = abs(y1 - y0);

	if (id < reader->hhea->numOfLongHorMetrics) {
		aw = reader->hmtx->hMetrics[id].advanceWidth;
		lsb = reader->hmtx->hMetrics[id].leftSideBearing;
	}
	else {
		aw = reader->hmtx->hMetrics[reader->hhea->numOfLongHorMetrics - 1].advanceWidth;
		lsb = reader->hmtx->leftSideBearing[id - reader->hhea->numOfLongHorMetrics];
	}
	aw *= scalePixel;
	lsb *= scalePixel;

	//rsb = aw - (lsb + width);

	px1 = x0 - lsb;
	px2 = px1 + aw;
	py1 = lineGap;
	py2 = linespace;

	x0 = startX + abs(lsb);
	y0 = startY + lineGap + (a - y1);

	if (y0 >= image->height || x0 >= image->width) {
		height = 0;
		width = 0;
		aw = 0;
	}
	else {
		if (y0 + height >= image->height)
			height = -y0 + image->height;
		if (x0 + width >= image->width)
			width = -x0 + image->width;
		if (aw < width)
			aw = abs(width) + abs(lsb);
	}

	uint8_t* const m_image = image->memory + y0 * image->pitch + x0;

	TrueTypeGlyf_bmpScanConverter(reader->glyf->ptr_glyph, id, m_image, image->pitch, width, height, scalePixel);
	return aw;
}
//stbtt_GetFontVMetrics(&font, &ascent, 0, 0);
//stbtt_GetCodepointHMetrics(&font, text[ch], &advance, &lsb);
//stbtt_GetCodepointBitmapBoxSubpixel(&font, text[ch], scale, scale, x_shift, 0, &x0, &y0, &x1, &y1);
//stbtt_MakeCodepointBitmapSubpixel(&font, &temp_bitmap[baseline + y0][(int)xpos + x0], x1 - x0, y1 - y0, textureWidth, scale, scale, x_shift, 0, text[ch]);

//void stbtt_GetGlyphBitmapBoxSubpixel(const TrueTypeReader_t* reader, int glyph, float scale_x, float scale_y, float shift_x, float shift_y, int* ix0, int* iy0, int* ix1, int* iy1)
//{
	//int x0 = 0, y0 = 0, x1, y1; // =0 suppresses compiler warning
	//if (!stbtt_GetGlyphBox(font, glyph, &x0, &y0, &x1, &y1)) {
	//	// e.g. space character
	//	if (ix0) *ix0 = 0;
	//	if (iy0) *iy0 = 0;
	//	if (ix1) *ix1 = 0;
	//	if (iy1) *iy1 = 0;
	//}
	//else {
	//	// move to integral bboxes (treating pixels as little squares, what pixels get touched)?
	//	if (ix0) *ix0 = STBTT_ifloor(x0 * scale_x + shift_x);
	//	if (iy0) *iy0 = STBTT_ifloor(-y1 * scale_y + shift_y);
	//	if (ix1) *ix1 = STBTT_iceil(x1 * scale_x + shift_x);
	//	if (iy1) *iy1 = STBTT_iceil(-y0 * scale_y + shift_y);
	//}
//}

#ifdef WIN32
LPCTSTR fontRegistryPath = TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts");

LSTATUS GetSystemFonts_malloc(TrueType_systemFonts_t** resultFontFiles) {
	TCHAR winDir[MAX_PATH];
	HKEY hKey;
	LSTATUS result;
	DWORD i, j, c, dirLength;
	DWORD maxValueNameSize, maxValueDataSize;
	DWORD valueNameSize, valueDataSize, valueType, nameSize, dataSize, ptrSize;
	DWORD lpcCount;
	LPTSTR valueName;
	LPBYTE valueData;
	TrueType_systemFonts_t* arrayFonts;
	nameSize = dataSize = ptrSize = 0;
	valueData = NULL;
	valueName = NULL;

	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, fontRegistryPath, 0, KEY_READ, &hKey);
	if (result != ERROR_SUCCESS)
		goto error;
	result = RegQueryInfoKey(hKey, 0, 0, 0, 0, 0, 0, &lpcCount, &maxValueNameSize, &maxValueDataSize, 0, 0);
	if (result != ERROR_SUCCESS)
		goto error;
	dirLength = GetWindowsDirectory(winDir, MAX_PATH);
	if (dirLength == 0)
		goto error;

	valueName = (LPTSTR)malloc(maxValueNameSize * sizeof(TCHAR));
	valueData = (LPBYTE)malloc(maxValueDataSize * sizeof(BYTE));

	if (valueName == NULL)
		goto error;
	if (valueData == NULL)
		goto error;

	for (i = 0, j = 0; i < lpcCount; i++) {
		valueDataSize = maxValueDataSize;
		valueNameSize = maxValueNameSize;
		result = RegEnumValue(hKey, i, valueName, &valueNameSize, 0, &valueType, valueData, &valueDataSize);
		if (result != ERROR_SUCCESS || valueType != REG_SZ)
			continue;
		nameSize += valueNameSize + sizeof(TCHAR);
		dataSize += valueDataSize + 1;
		j++;
	}
	ptrSize = j * (sizeof(TCHAR*) + sizeof(BYTE*));
	arrayFonts = (TrueType_systemFonts_t*)malloc(nameSize + dataSize + ptrSize + sizeof(TCHAR*) + sizeof(size_t));
	uint8_t* end_ptr = (uint8_t*)arrayFonts + nameSize + dataSize + ptrSize + sizeof(TCHAR*) + sizeof(size_t);
	if (j == 0 || !arrayFonts) {
		free(arrayFonts);
		*resultFontFiles = NULL;
		goto error;;
	}

	*resultFontFiles = arrayFonts;
	arrayFonts->m_numberFonts = j;

	if (arrayFonts)
		arrayFonts->font[0].name = ((uint8_t*)arrayFonts) + ptrSize + sizeof(size_t);
	for (i = 0, j = 0; i < lpcCount; i++) {
		valueDataSize = maxValueDataSize;
		valueNameSize = maxValueNameSize;
		result = RegEnumValue(hKey, i, valueName, &valueNameSize, 0, &valueType, valueData, &valueDataSize);
		if (result != ERROR_SUCCESS || valueType != REG_SZ)
			continue;
		for (c = 0; c < valueNameSize; c++)
			arrayFonts->font[j].name[c] = valueName[c];
		arrayFonts->font[j].name[c] = 0;
		arrayFonts->font[j].data = arrayFonts->font[j].name + c + 1;
		for (c = 0; c < valueDataSize; c++)
			arrayFonts->font[j].data[c] = valueData[c];
		//arrayFonts[j].font->data[c] = 0;
		if (i < lpcCount - 1)
			arrayFonts->font[j + 1].name = arrayFonts->font[j].data + c;
		j++;
	}

error:
	RegCloseKey(hKey);
	free(valueName);
	free(valueData);
	return result;
}

LSTATUS GetSystemFontFile_malloc(const TCHAR* fontName, TCHAR** resultFontFile) {
	TCHAR winDir[MAX_PATH];
	TCHAR* ptrResultFontFile;
	HKEY hKey;
	LSTATUS result;
	DWORD valueIndex, i, i_end, dirLength;
	DWORD maxValueNameSize, maxValueDataSize;
	DWORD valueNameSize, valueDataSize, valueType;
	LPTSTR valueName;
	LPBYTE valueData;

	const size_t cSize = _tcsclen(fontName) + 1;

	valueData = NULL;
	valueName = NULL;

	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, fontRegistryPath, 0, KEY_READ, &hKey);
	if (result != ERROR_SUCCESS)
		goto error;
	result = RegQueryInfoKey(hKey, 0, 0, 0, 0, 0, 0, 0, &maxValueNameSize, &maxValueDataSize, 0, 0);
	if (result != ERROR_SUCCESS)
		goto error;
	dirLength = GetWindowsDirectory(winDir, MAX_PATH);
	if (dirLength == 0)
		goto error;

	valueIndex = 0;
	valueName = (LPTSTR)malloc(maxValueNameSize * sizeof(TCHAR));
	valueData = (LPBYTE)malloc(maxValueDataSize * sizeof(BYTE));

	if (valueName == NULL)
		goto error;
	if (valueData == NULL)
		goto error;
	do {
		valueDataSize = maxValueDataSize;
		valueNameSize = maxValueNameSize;
		result = RegEnumValue(hKey, valueIndex, valueName, &valueNameSize, 0, &valueType, valueData, &valueDataSize);
		valueIndex++;
		if (result != ERROR_SUCCESS || valueType != REG_SZ)
			continue;
		if (_tcsnicmp(fontName, valueName, cSize) == 0)
			break;
	} while (result != ERROR_NO_MORE_ITEMS);

	if (result == ERROR_NO_MORE_ITEMS)
		goto error;;

	ptrResultFontFile = (TCHAR*)calloc(1, (sizeof("\\Fonts\\") + dirLength + valueDataSize) * sizeof(TCHAR));
	*resultFontFile = ptrResultFontFile;
	if (ptrResultFontFile == NULL)
		goto error;
	for (i = 0, i_end = dirLength > MAX_PATH ? MAX_PATH : dirLength; i < i_end; i++)
		ptrResultFontFile[i] = winDir[i];
	ptrResultFontFile[i + 0] = (TCHAR)'\\';
	ptrResultFontFile[i + 1] = (TCHAR)'F';
	ptrResultFontFile[i + 2] = (TCHAR)'o';
	ptrResultFontFile[i + 3] = (TCHAR)'n';
	ptrResultFontFile[i + 4] = (TCHAR)'t';
	ptrResultFontFile[i + 5] = (TCHAR)'s';
	ptrResultFontFile[i + 6] = (TCHAR)'\\';
	for (i = 0, i_end = valueDataSize; i < i_end; i++)
		ptrResultFontFile[dirLength + (sizeof("\\Fonts\\") - 1) + i] = (TCHAR)valueData[i];
error:
	RegCloseKey(hKey);
	free(valueName);
	free(valueData);
	return result;
}
#endif

#if defined(linux) || defined(__linux)
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>

const char* fontDirectory[] = { "/usr/share/fonts", "/usr/local/share/fonts", "~/.fonts" };
const char* fontConfigs[] = { "/etc/fonts/fonts.conf", "/etc/fonts/local.conf." };

char* GetSystemFonts_findfiles(size_t* numberFiles, size_t** namesOffsets) {
	size_t m_numberDirs = 1;
	size_t m_sizeNames = 256;
	size_t m_sizeDirNames = 256;
	size_t m_numberNames = 0;
	size_t m_numberPath = sizeof(fontDirectory) / sizeof(fontDirectory[0]);
	size_t i, j0, j1, j2, j3, j4, m_nextOffset = 0;
	DIR* m_dir;
	char* m_names = (char*)malloc(m_sizeNames * sizeof(char));
	size_t* m_namesOffsets = NULL;
	char* m_nameDirs = (char*)malloc(m_sizeDirNames);
	size_t* m_offsetDirs = (size_t*)malloc(m_numberDirs * sizeof(size_t));
	*numberFiles = 0;
	m_offsetDirs[0] = 0;
	for (j4 = 0; j4 < m_numberPath; j4++) {
        i = 0;
        m_numberDirs = 1;
		size_t m_length = strlen(fontDirectory[j4]);
		j3 = m_offsetDirs[i];
		j0 = m_offsetDirs[m_numberDirs - 1];
		do {
			if (j0 >= m_sizeDirNames) {
				m_sizeDirNames += m_length + 2;
				m_nameDirs = (char*)realloc(m_nameDirs, m_sizeDirNames);
			}
			for (j1 = 0; j0 < m_sizeDirNames && fontDirectory[j4][j1]; j1++, j0++)
				m_nameDirs[j0] = fontDirectory[j4][j1];
			if (j0 < m_sizeDirNames && fontDirectory[j4][j1] == 0)
				m_nameDirs[j0] = 0;
			m_offsetDirs[i] = j0 + 1;
		} while (j0 >= m_sizeDirNames);

		for (i = 0; i < m_numberDirs; i++) {
			if ((m_dir = opendir(m_nameDirs + j3)) != NULL) {
				struct dirent* entry;
				while ((entry = readdir(m_dir)) != NULL) {
					if (entry->d_name[0] == '.')
						continue;
					if (entry->d_name[0] == '.' && entry->d_name[1] == '.')
						continue;
					m_length = strlen(entry->d_name);

					if (entry->d_type == DT_DIR) {
						j0 = m_offsetDirs[m_numberDirs - 1];
						j2 = j3;
						j1 = 0;
						do {
							if (j0 >= m_sizeDirNames) {
								m_sizeDirNames += m_length + 1;
								m_nameDirs = (char*)realloc(m_nameDirs, m_sizeDirNames);
							}
							for (; j0 < m_sizeDirNames && m_nameDirs[j2]; j0++, j2++)
								m_nameDirs[j0] = m_nameDirs[j2];
							if (j0 < m_sizeDirNames && m_nameDirs[j2] == 0 && j1 == 0)
								m_nameDirs[j0++] = '/';
							for (; j0 < m_sizeDirNames && entry->d_name[j1]; j1++, j0++)
								m_nameDirs[j0] = entry->d_name[j1];
						} while (j0 >= m_sizeDirNames);
						m_nameDirs[j0] = 0;
						m_numberDirs++;
						m_offsetDirs = (size_t*)realloc(m_offsetDirs, m_numberDirs * sizeof(size_t));
						m_offsetDirs[m_numberDirs - 1] = j0 + 1;
					}
					else if (entry->d_type == DT_REG) {
						if (m_length < 3)
							continue;
						if (entry->d_name[m_length - 1] != 'f' ||
							entry->d_name[m_length - 2] != 't' ||
							entry->d_name[m_length - 3] != 't')
							continue;
						j0 = m_nextOffset;
						j2 = j3;
						j1 = 0;
						do {
							if (j0 >= m_sizeNames) {
								m_sizeNames += m_length + 1;
								m_names = (char*)realloc(m_names, m_sizeNames);
							}
							for (; j0 < m_sizeNames && m_nameDirs[j2]; j0++, j2++)
								m_names[j0] = m_nameDirs[j2];
							if (j0 < m_sizeNames && m_nameDirs[j2] == 0 && j1 == 0)
								m_names[j0++] = '/';
							for (; j0 < m_sizeNames && entry->d_name[j1]; j1++, j0++)
								m_names[j0] = entry->d_name[j1];
						} while (j0 >= m_sizeNames);
						m_names[j0] = 0;
						m_numberNames++;
						m_namesOffsets = (size_t*)realloc(m_namesOffsets, m_numberNames * sizeof(size_t));
						m_namesOffsets[m_numberNames - 1] = m_nextOffset;
						m_nextOffset = j0 + 1;
					}
				}
				closedir(m_dir);
			}
			j3 = m_offsetDirs[i];
		}
	}

	for (i = 0; i < m_numberNames; i++)
	    printf("%s\n", m_names + m_namesOffsets[i]);
	free(m_nameDirs);
	free(m_offsetDirs);
	*numberFiles = m_numberNames;
	*namesOffsets = m_namesOffsets;
	return m_names;
}

uint32_t GetSystemFonts_malloc(TrueType_systemFonts_t** resultFontFiles) {
	TrueType_systemFonts_t* m_font = NULL;
	uint32_t i, j, j_end;
	size_t* m_namesOffset;
	size_t m_numberFiles;
	char* m_names = GetSystemFonts_findfiles(&m_numberFiles, &m_namesOffset);
	if (m_names) {
		j_end = m_namesOffset[m_numberFiles - 1];
		m_font = malloc(offsetof(TrueType_systemFonts_t, font) + m_numberFiles * 2 * sizeof(char*) + j_end);
		m_font->m_numberFonts = m_numberFiles;
		for (i = 0; i < m_numberFiles; i++) {
			m_font->font[i].data = ((char*)(m_font->font + m_numberFiles)) + m_namesOffset[i];
		}
		for (j = 0; j < j_end; j++)
			((char*)(m_font->font + m_numberFiles))[j] = m_names[j];

		for (i = 1; i < m_numberFiles; i++) {
			for (j = m_namesOffset[i] - 1; j && ((char*)(m_font->font + m_numberFiles))[j] != '/'; j--);
			m_font->font[i - 1].name = ((char*)(m_font->font + m_numberFiles)) + j + 1;
		}
		if (j_end) {
			for (j = j_end - 1; j && ((char*)(m_font->font + m_numberFiles))[j] != '/'; j--);
			m_font->font[i - 1].name = ((char*)(m_font->font + m_numberFiles)) + j + 1;
		}
	}
	free(m_namesOffset);
	free(m_names);
	*resultFontFiles = m_font;
	return 0;
}
uint32_t GetSystemFontFile_malloc(const char* faceName, char** resultFontFile) {
	size_t i, j = 0, j_end;
	size_t* m_namesOffset;
	size_t m_numberFiles;
	char* m_names = GetSystemFonts_findfiles(&m_numberFiles, &m_namesOffset);
	if (m_names) {
		for (i = 0; i < m_numberFiles; i++) {
			if (strcmp(m_names + m_namesOffset[i], faceName) == 0) {
				j_end = strlen(m_names + m_namesOffset[i]);
				*resultFontFile = (char*)malloc(j_end + 1);
				for (j = 0; j < j_end; j++)
					(*resultFontFile)[j] = (m_names + m_namesOffset[i])[j];
				(*resultFontFile)[j] = 0;
				i = m_numberFiles;
			}
		}
	}
	free(m_namesOffset);
	free(m_names);
	return 0;
}

#endif