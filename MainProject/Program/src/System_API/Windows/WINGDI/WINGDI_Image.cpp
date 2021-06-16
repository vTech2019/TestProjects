
#ifdef _WIN32
#include "WINGDI_Image.h"
#define _BMP L"{557cf400-1a04-11d3-9a73-0000f81ef32e}"
#define _JPG L"{557cf401-1a04-11d3-9a73-0000f81ef32e}"
#define _GIF L"{557cf402-1a04-11d3-9a73-0000f81ef32e}"
#define _TIF L"{557cf405-1a04-11d3-9a73-0000f81ef32e}"
#define _PNG L"{557cf406-1a04-11d3-9a73-0000f81ef32e}"

void WINGDI_read_image(const WCHAR* name_file, void** image, void* (*memory_reallocator)(void** memory, size_t width, size_t height, size_t pixel_bit_size)) {
	ULONG_PTR token;
	size_t m_width, m_height, m_size;
	Gdiplus::Color color;
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartupOutput output;
	Gdiplus::GdiplusStartup(&token, &input, &output);
	Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(name_file);
	m_height = bitmap->GetHeight();
	m_width = bitmap->GetWidth();
	Gdiplus::BitmapData bitmapData = {};
	Gdiplus::Rect rect(0, 0, m_width, m_height);
	bitmap->LockBits(&rect, Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeWrite, PixelFormat32bppRGB, &bitmapData);
	unsigned char* pixels = (unsigned char*)bitmapData.Scan0;
	m_size = abs(bitmapData.Stride) * m_height;

	if (memory_reallocator) {
		void* data = memory_reallocator(image, m_width, m_height, 32);
		memcpy(data, pixels, m_size);
	}
	bitmap->UnlockBits(&bitmapData);
	delete bitmap;
	Gdiplus::GdiplusShutdown(token);


}
/*void WIN_save_image(dataImage& image, const WCHAR* directory_name, const WCHAR* name, size_t format) {


	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartupOutput output;
	ULONG_PTR token;
	Gdiplus::GdiplusStartup(&token, &input, &output);
	Gdiplus::Color color;
	Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(image.width, image.height, image.stride, image.pixelFormat, (BYTE*)image.data);
	size_t length_dir;
	size_t length_file_name;

	CLSID �lsid;
	const WCHAR* _name = name;
	for (length_dir = 0; directory_name[length_dir] != 0; length_dir++)
		length_dir++;
	for (length_file_name = 0; name[length_file_name] != 0; length_file_name++)
		length_file_name++;
	WCHAR* name_file = (WCHAR*)alloca((length_file_name + length_dir + 6) * sizeof(WCHAR));
	for (size_t i = 0; i < length_dir; i++)
		name_file[i] = directory_name[i];
	for (size_t i = length_dir; i < length_dir + length_file_name; i++)
		name_file[i] = name[i - length_dir];
	size_t length = length_dir + length_file_name;
	switch (format) {
	case BMP:
		name_file[length] = L'.';
		name_file[length + 1] = L'b';
		name_file[length + 2] = L'm';
		name_file[length + 3] = L'p';
		name_file[length + 4] = 0;
		CLSIDFromString(_BMP, &�lsid);
		bitmap->Save(name_file, &�lsid, NULL);
		break;
	case JPG:
		name_file[length] = L'.';
		name_file[length + 1] = L'j';
		name_file[length + 2] = L'p';
		name_file[length + 3] = L'g';
		name_file[length + 4] = 0;
		CLSIDFromString(_JPG, &�lsid);
		bitmap->Save(name_file, &�lsid, NULL);
		break;
	case PNG:
		name_file[length] = L'.';
		name_file[length + 1] = L'p';
		name_file[length + 2] = L'n';
		name_file[length + 3] = L'g';
		name_file[length + 4] = 0;
		CLSIDFromString(_PNG, &�lsid);
		bitmap->Save(name_file, &�lsid, NULL);
		break;
	case TIF:
		name_file[length] = L'.';
		name_file[length + 1] = L't';
		name_file[length + 2] = L'i';
		name_file[length + 3] = L'f';
		name_file[length + 4] = L'f';
		name_file[length + 5] = 0;
		CLSIDFromString(_TIF, &�lsid);
		bitmap->Save(name_file, &�lsid, NULL);
		break;
	case GIF:
		name_file[length] = L'.';
		name_file[length + 1] = L'g';
		name_file[length + 2] = L'i';
		name_file[length + 3] = L'f';
		name_file[length + 4] = 0;
		CLSIDFromString(_GIF, &�lsid);
		bitmap->Save(name_file, &�lsid, NULL);
		break;
	}
	delete bitmap;
	Gdiplus::GdiplusShutdown(token);
	_mm_free(image.data);
}*/

#endif