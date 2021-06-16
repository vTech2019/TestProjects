//#include "App.h"
#include "TrueTypeLibrary.h"
#include "FcBMP.h"
#include "FcPPM.h"
#include "include/FcWindow.h"
#include "include/FcCore.h"
#include "include/FcPNG.h"
#include "FcTrueTypeGL.h"
#include "include/FcFilesystem.h"
#include "include/FcError.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

int test(char* fontDir, char* name) {
	/* load font file */
	long size;
	unsigned char* fontBuffer;

	FILE* fontFile;
	//fopen_s(&fontFile, fontDir, "rb");
	fontFile = fopen(fontDir, "rb");
	fseek(fontFile, 0, SEEK_END);
	size = ftell(fontFile); /* how long is the file ? */
	fseek(fontFile, 0, SEEK_SET); /* reset */

	fontBuffer = malloc(size);

	fread(fontBuffer, size, 1, fontFile);
	fclose(fontFile);
	int l_h = 2048; /* line height */

	stbtt_fontinfo font;
	if (!stbtt_InitFont(&font, fontBuffer, 0))
	{
		printf("failed\n");
	}

	int i, j, ascent, baseline;
	float scale, xpos = 2;

	scale = stbtt_ScaleForPixelHeight(&font, l_h);
	stbtt_GetFontVMetrics(&font, &ascent, 0, 0);
	baseline = (int)(ascent * scale);
	char text[64] = { "C:/test/" };
	size_t folderOffset = strlen(name);
	memcpy(text + strlen(text), name, folderOffset);
	text[strlen(text)] = '/';
	folderOffset = strlen(text);
	FcFilesystem_createFolder(text);
	for (i = 0; i < font.numGlyphs; ) {
		bmpImage_t* image = bmpLibrary_create(1024 * 24, 6144, 8);
		size_t startX = 0;
		xpos = 2;
		while (xpos + 2048 < image->width && i < font.numGlyphs) {
			int advance, lsb, x0, y0, x1, y1;
			float x_shift = xpos - (float)floor(xpos);
			stbtt_GetCodepointHMetrics(&font, i, &advance, &lsb);
			stbtt_GetCodepointBitmapBoxSubpixel(&font, i, scale, scale, x_shift, 0, &x0, &y0, &x1, &y1);
			stbtt_MakeCodepointBitmapSubpixel(&font, &image->memory[((baseline + y0) + 2048) * image->width + (int)xpos + x0], x1 - x0, y1 - y0, image->width, scale, scale, x_shift, 0, i);
			xpos += (max(abs(x1 - x0 + lsb), advance * scale));
			i++;
		}
		text[folderOffset + 0] = (i / 10000) % 10 + '0';
		text[folderOffset + 1] = (i / 1000) % 10 + '0';
		text[folderOffset + 2] = (i / 100) % 10 + '0';
		text[folderOffset + 3] = (i / 10) % 10 + '0';
		text[folderOffset + 4] = i % 10 + '0';
		text[folderOffset + 5] = '.';
		text[folderOffset + 6] = 'b';
		text[folderOffset + 7] = 'm';
		text[folderOffset + 8] = 'p';
		text[folderOffset + 9] = 0;
		FcBMP_write_8(text, image);
		bmpLibrary_free(image);
	}
	free(fontBuffer);
}
int test1(char* fontDir, char* name) {
	TrueTypeReader_t* m_font = TrueTypeReader_init(fontDir, NULL);
	if (m_font) {
		char text[64] = { "F:/testR/" };
		size_t folderOffset = strlen(name);
		memcpy(text + strlen(text), name, folderOffset);
		text[strlen(text)] = '/';
		folderOffset = strlen(text);
		FcFilesystem_createFolder(text);
		int id;
		//	TrueTypeGlyf_print(m_font->glyf);
		for (id = 0; id < m_font->glyf->number_glyph; ) {
			bmpImage_t* image = bmpLibrary_create(1024 * 24, m_font->head->units_per_em * 4, 8);
			size_t startX = 0;
			size_t startY = m_font->head->units_per_em;
			
			while (startY + m_font->head->units_per_em < image->height && id < m_font->glyf->number_glyph) {
				while (startX + m_font->head->units_per_em < image->width && id < m_font->glyf->number_glyph) {
					startX += TrueTypeReader_bmpScanConverter(m_font, startX, startY, m_font->head->units_per_em, id, (TrueTypeImage_t*)image);
					id++;
				}
				startY += m_font->head->units_per_em;
				startX = 0;
			}
			text[folderOffset + 0] = (id / 10000) % 10 + '0';
			text[folderOffset + 1] = (id / 1000) % 10 + '0';
			text[folderOffset + 2] = (id / 100) % 10 + '0';
			text[folderOffset + 3] = (id / 10) % 10 + '0';
			text[folderOffset + 4] = id % 10 + '0';
			text[folderOffset + 5] = '.';
			text[folderOffset + 6] = 'b';
			text[folderOffset + 7] = 'm';
			text[folderOffset + 8] = 'p';
			text[folderOffset + 9] = 0;
			FcBMP_write_8(text, image);
			bmpLibrary_free(image);
		}
	}
	TrueTypeReader_free(m_font);
}
int testgl(char* fontDir, char* name) {
	int error = 0;
    int e  =errno;
    FcError_t mError;
    printf("%d\n", e);
	TrueTypeReader_t* m_font = TrueTypeReader_init(fontDir, &error);

	if (m_font) {
		//char text[64] = { "F:/testR/" };
		//size_t folderOffset = strlen(name);
		//memcpy(text + strlen(text), name, folderOffset);
		//text[strlen(text)] = '/';
		//folderOffset = strlen(text);
		//FcFilesystem_createFolder(text);

		struct _FcTrueTypeGL_t m_glFont = { 0 };
		FcCore_t m_core = { 0 };
		FcGLWindow_t m_window = { 0 };
        FcError(FcCore_init(&m_core));
        FcError(FcGLWindow(&m_core, &m_window, 1280, 720));
		FcGLWindow_show(&m_window);
		FcTrueTypeGL_malloc(&m_core, &m_window, &m_glFont, fontDir);
		FcGLWindow_dispatch(&m_window);
		printf("disp end\n");
		FcTrueTypeGL_free(&m_glFont);
		printf("gl end\n");
		FcGLWindow_free(&m_core, &m_window);
		printf("win end\n");
		FcCore_free(&m_core);
		printf("core end\n");
		memset(&m_window, 0, sizeof(m_window));
	}
	TrueTypeReader_free(m_font);
}

int main() {

	TrueType_systemFonts_t* m_fonts;
	GetSystemFonts_malloc(&m_fonts);
    perror("");
	int32_t i;
	//#pragma omp parallel for
	for (i = 1; i < m_fonts->m_numberFonts; i++) {
		char* result = NULL;
		GetSystemFontFile_malloc(m_fonts->font[i].name, &result);
		printf("%s %s\n", m_fonts->font[i].name, m_fonts->font[i].data);
		testgl(m_fonts->font[i].data, m_fonts->font[i].name);
		//test(result, m_fonts->font[i].name);
		test1(result, m_fonts->font[i].name);

		GetSystemFontFile_free(result);
	}
	GetSystemFonts_free(m_fonts);
	return 0;

	//App_init(&app);
	//App_run(&app);
	//App_free(&app);
	return 0;
}