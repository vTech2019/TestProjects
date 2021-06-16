#include "FcBMP.h"
#define __STDC_WANT_LIB_EXT1__
#include <stdio.h>
#ifdef _MSC_VER
#define fwrite_unlocked _fwrite_nolock
#elif !defined(fwrite_unlocked)
#define fwrite_unlocked fwrite
#endif

#ifdef UNICODE
#define fopen _wfopen
#define fopen_s _wfopen_s
#define __T(x) L ## x
#define TEXT(x) __T(x)
#else
#define TEXT(x) (x)
#endif

struct uchar32 {
	uint8_t data[32];
};
struct uchar64 {
	uint8_t data[64];
};
ALIGNED(64, struct, uchar64_align {
	uint8_t data[64];
});
enum Profile {
	PROFILE_LINKED = 0x4C494E4B,
	PROFILE_EMBEDDED = 0x4D424544
};
enum Intent {
	LCS_GM_BUSINESS = 1,
	LCS_GM_GRAPHICS = 2,
	LCS_GM_IMAGES = 4,
	LCS_GM_ABS_COLORIMETRIC = 8
};
enum Bit_Count {
	Bin = 1,
	CGA = 2,
	EGA = 4,
	Bit8 = 8,
	HiColor = 16,
	TrueColor24 = 24,
	TrueColor32 = 32,
	DeepColor48 = 48,
	DeepColor64 = 64
};
enum Compression {
	BI_RGB = 0,
	BI_RLE8 = 1,
	BI_RLE4 = 2,
	BI_BITFIELDS = 3,
	BI_JPEG = 4,
	BI_PNG = 5,
	BI_ALPHABITFIELDS = 6
};
enum Table_Color {
	offset_BMPInfo_Core = 0x0C,
	offset_BMPInfo_V3_compression_not_three_or_six = 0x28,
	offset_BMPInfo_v3_compression_three = 0x34,
	offset_BMPInfo_V3_compression_six = 0x38,
	offset_BMPInfo_V4 = 0x6c,
	offset_BMPInfo_V5 = 0x7b
};
enum Color_Space {
	NO = 0,
	sRGB = 0x73524742,
	Win = 0x57696E20,
	Link = 0x4C494E4B,
	MBED = 0x4D424544
};
enum BMP_VERSION {
	BMP_CORE = 12,
	BMP_V3 = 40,
	BMP_V4 = 108,
	BMP_V5 = 124
};

#pragma pack(push)
#pragma pack(1)
struct BMP_Core_info {
	uint32_t size_struct;
    int16_t width;
    int16_t height;
    int16_t planes;
    int16_t number_bit_pixel;
};
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
struct BMP_v3v4v5_info {
	uint32_t size_struct;
    int32_t width;
    int32_t signWay_absoluteHeight;
    uint16_t planes;
    uint16_t number_bit_pixel;
    uint32_t compression;
    uint32_t size_pixel;
	int32_t number_pixels_x;
    int32_t number_pixels_y;
    uint32_t size_cell_in_color_table;
    uint32_t number_cells;
	//v4 bmp
    uint32_t red_mask;
    uint32_t green_mask;
    uint32_t blue_mask;
    uint32_t alpha_mask;
    uint32_t color_space_type;
    uint32_t red_x;
    uint32_t red_y;
    uint32_t red_z;
    uint32_t green_x;
    uint32_t green_y;
    uint32_t green_z;
    uint32_t blue_x;
    uint32_t blue_y;
    uint32_t blue_z;
    uint32_t gamma_red;
    uint32_t gamma_green;
    uint32_t gamma_blue;
	//v5 bmp
    uint32_t color_intent;
    uint32_t offset_BMPInfo_color_profile;
    uint32_t size_color_profile;
    uint32_t reserved_null;
};
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
struct BMP_header {
    uint16_t type_file;
	uint32_t size_file;
    uint16_t reserved_null_0;
    uint16_t reserved_null_1;
    uint32_t pixel_offset_header;
};
#pragma pack(pop)

static inline void read_bmp_reverse_line_no_compression(uint8_t* __restrict data0, uint8_t* __restrict  data1, size_t height, size_t pitch) {
	size_t j0, j1;
	uint8_t tmp8;
	const size_t padding = pitch % 4;
	const size_t scalar64 = pitch % 64;
	const size_t vector64 = pitch / 64;
	const size_t end_i = height / 2;
	for (size_t i = 0; i < end_i; i++) {
		j0 = (i * pitch);
		j1 = (height - 1 - i) * (pitch + padding);
		struct uchar64 tmp64_0;
		struct uchar64 tmp64_1;
		struct uchar64* m_vector_0 = (struct uchar64*)(data0 + j0);
		struct uchar64* m_vector_1 = (struct uchar64*)(data1 + j1);
		for (j0 = 0; j0 < vector64; j0++) {
			tmp64_0 = m_vector_0[j0]; 
			tmp64_1 = m_vector_1[j0];
			m_vector_0[j0] = tmp64_1;
			m_vector_1[j0] = tmp64_0;
		}
		uint8_t* m_scalar_0 = (uint8_t*)(m_vector_0 + j0);
        uint8_t* m_scalar_1 = (uint8_t*)(m_vector_1 + j0);
		for (j0 = 0; j0 < scalar64; j0++) {
			tmp8 = m_scalar_0[j0];
			m_scalar_0[j0] = m_scalar_1[j0];
			m_scalar_1[j0] = tmp8;
		}
	}
}
static inline void read_bmp_no_revers_line_no_compression(uint8_t* __restrict image, uint8_t* __restrict pixel_array, uint32_t height, uint32_t width, uint32_t pixel_size) {
	const uint32_t padding = width % 4;
	const uint32_t line = width * pixel_size;
	const uint32_t number_uint32 = line / 32;
	for (uint32_t i = height - 1; i != UINT32_MAX; i--) {
        uint32_t j = 0;
		struct uchar32* ptr_image_line = (struct uchar32* )(image + i * width);
		struct uchar32* ptr_array_line = (struct uchar32* )(pixel_array + i * (width + padding));
		for (; j < number_uint32; j++)
			ptr_image_line[j] = ptr_array_line[j];
        uint8_t* uchar_ptr_image_line = (uint8_t*)(ptr_image_line + j);
        uint8_t* uchar_ptr_array_line = (uint8_t*)(ptr_array_line + j);
		for (j *= 32; j < line; j++)
			uchar_ptr_image_line[j] = *(uchar_ptr_array_line++);
	}
}
int read_BMP(uint8_t* memory, bmpImage_t* image) {
	struct BMP_header* ptr_header = (struct BMP_header*)memory;
    struct BMP_Core_info* ptr_core;
    const struct BMP_v3v4v5_info* ptr_modern;
	if (ptr_header->type_file == BMPLIB_BMP_FILE &&
            ptr_header->reserved_null_0 == 0 &&
            ptr_header->reserved_null_1 == 0) {
		uint32_t file_size = ptr_header->size_file;
		uint8_t* ptr_pixel = memory + ptr_header->pixel_offset_header;
        ptr_core = (struct BMP_Core_info* )(memory + 0xE);
		if (ptr_core->size_struct == BMP_CORE) {
			image = bmpLibrary_create(abs(ptr_core->height), ptr_core->width, ptr_core->number_bit_pixel);
			read_bmp_no_revers_line_no_compression(image->memory, ptr_pixel, image->height, image->width, image->number_bit_pixel / 8);
			return 1;
		}
		else if (ptr_core->size_struct == BMP_V3) {
            ptr_modern = (const struct BMP_v3v4v5_info *) (memory + sizeof(struct BMP_header));
			image = bmpLibrary_create(abs(ptr_modern->signWay_absoluteHeight), ptr_modern->width, ptr_modern->number_bit_pixel);

			if (ptr_modern->signWay_absoluteHeight > 0)
				read_bmp_reverse_line_no_compression(image->memory, ptr_pixel, image->height, image->pitch);
			else
				read_bmp_no_revers_line_no_compression(image->memory, ptr_pixel, image->height, image->width, image->number_bit_pixel / 8);
			return 1;
		}
		else if (ptr_core->size_struct == BMP_V4) {
            ptr_modern = (const struct BMP_v3v4v5_info *) (memory + sizeof(struct BMP_header));
			image = bmpLibrary_create(abs(ptr_modern->signWay_absoluteHeight), ptr_modern->width, ptr_modern->number_bit_pixel);
			if (ptr_modern->signWay_absoluteHeight > 0)
				read_bmp_reverse_line_no_compression(image->memory, ptr_pixel, image->height, image->pitch);
			else
				read_bmp_no_revers_line_no_compression(image->memory, ptr_pixel, image->height, image->width, image->number_bit_pixel / 8);
			return 1;
		}
		else if (ptr_core->size_struct == BMP_V5) {
            ptr_modern = (const struct BMP_v3v4v5_info *) (memory + sizeof(struct BMP_header));
			image = bmpLibrary_create(abs(ptr_modern->signWay_absoluteHeight), ptr_modern->width, ptr_modern->number_bit_pixel);
			if (ptr_modern->signWay_absoluteHeight > 0)
				read_bmp_reverse_line_no_compression(image->memory, ptr_pixel, image->height, image->pitch);
			else
				read_bmp_no_revers_line_no_compression(image->memory, ptr_pixel, image->height, image->width, image->number_bit_pixel / 8);
			return 1;
		}
	}
	return 0;
}
int write_BMP_Core(FILE* ptr_file, bmpImage_t* image) {
	struct BMP_header header_bmp = {
		 .type_file = BMPLIB_BMP_FILE,
		 .size_file = sizeof(struct BMP_header) + sizeof(struct BMP_Core_info) + image->width * image->height * (image->number_bit_pixel / 8),
		 .reserved_null_0 = 0,
		 .reserved_null_1 = 0,
		 .pixel_offset_header = sizeof(struct BMP_header) + sizeof(struct BMP_Core_info)
	};
	struct BMP_Core_info core_info = {
		.size_struct = BMP_CORE,
		.width = image->width,
		.height = image->height,
		.planes = 1,
		.number_bit_pixel = image->number_bit_pixel
	};
	if (fwrite_unlocked(&header_bmp, sizeof(struct BMP_header), 1, ptr_file)) {
		if (fwrite_unlocked(&core_info, sizeof(struct BMP_Core_info), 1, ptr_file)) {
			if (fwrite_unlocked(image->memory, image->pitch * image->height, 1, ptr_file))
				return 1;
		}
	}
	return 0;
}

int write_BMP_Core_Bit1(FILE* ptr_file, bmpImage_t* image) {
    uint8_t color_table[6] = { 0,0,0, 255,255,255 };
	struct BMP_header header_bmp = {
		 .type_file = BMPLIB_BMP_FILE,
		 .size_file = sizeof(struct BMP_header) + sizeof(struct BMP_Core_info) + sizeof(color_table) + image->height + image->pitch,
		 .reserved_null_0 = 0,
		 .reserved_null_1 = 0,
		 .pixel_offset_header = sizeof(struct BMP_header) + sizeof(struct BMP_Core_info) + sizeof(color_table)
	};
	struct BMP_Core_info core_info = {
		.size_struct = BMP_CORE,
		.width = image->width,
		.height = image->height,
		.planes = 1,
		.number_bit_pixel = 1
	};
	if (fwrite_unlocked(&header_bmp, sizeof(struct BMP_header), 1, ptr_file)) {
		if (fwrite_unlocked(&core_info, sizeof(struct BMP_Core_info), 1, ptr_file)) {
			if (fwrite_unlocked(color_table, sizeof(color_table), 1, ptr_file))
				if (fwrite_unlocked(image->memory, image->pitch * image->height, 1, ptr_file))
					return 1;
		}
	}
	return 0;
}
int write_BMP_Core_Bit8(FILE* ptr_file, bmpImage_t* image) {
	uint8_t color_table[256 * 3];
	uint16_t i, result = 0;
	struct BMP_header header_bmp = {
		 .type_file = BMPLIB_BMP_FILE,
		 .size_file = sizeof(struct BMP_header) + sizeof(struct BMP_Core_info) + image->width * image->height * (image->number_bit_pixel / 8),
		 .reserved_null_0 = 0,
		 .reserved_null_1 = 0,
		 .pixel_offset_header = sizeof(struct BMP_header) + sizeof(struct BMP_Core_info) + sizeof(color_table)
	};
	struct BMP_Core_info core_info = {
		.size_struct = BMP_CORE,
		.width = image->width,
		.height = image->height,
		.planes = 1,
		.number_bit_pixel = image->number_bit_pixel
	};
	for (i = 0; i < 256; i++) {
		color_table[i * 3 + 0] = i;
		color_table[i * 3 + 1] = i;
		color_table[i * 3 + 2] = i;
	}
	//uint8_t* data = malloc(image->pitch * image->height);
	read_bmp_reverse_line_no_compression(image->memory, image->memory, image->height, image->pitch);
	if (fwrite_unlocked(&header_bmp, sizeof(struct BMP_header), 1, ptr_file)) {
		if (fwrite_unlocked(&core_info, sizeof(struct BMP_Core_info), 1, ptr_file)) {
			if (fwrite_unlocked(color_table, sizeof(color_table), 1, ptr_file)) {
				if (fwrite_unlocked(image->memory, image->pitch * image->height, 1, ptr_file)) {
					result = 1;
				}
			}
		}
	}
	read_bmp_reverse_line_no_compression(image->memory, image->memory, image->height, image->pitch);
	return result;
}

int write_BMP_Core_Bit24(FILE* ptr_file, bmpImage_t* image) {
	struct BMP_header header_bmp = {
		 .type_file = BMPLIB_BMP_FILE,
		 .size_file = sizeof(struct BMP_header) + sizeof(struct BMP_Core_info) + image->width * image->height * 3,
		 .reserved_null_0 = 0,
		 .reserved_null_1 = 0,
		 .pixel_offset_header = sizeof(struct BMP_header) + sizeof(struct BMP_Core_info)
	};
	struct BMP_Core_info core_info = {
		.size_struct = BMP_CORE,
		.width = image->width,
		.height = image->height,
		.planes = 1,
		.number_bit_pixel = 24
	};
	if (fwrite_unlocked(&header_bmp, sizeof(struct BMP_header), 1, ptr_file)) {
		if (fwrite_unlocked(&core_info, sizeof(struct BMP_Core_info), 1, ptr_file)) {
			if (fwrite_unlocked(image->memory, image->pitch * image->height, 1, ptr_file))
				return 1;
		}
	}
	return 0;
}

bmpReaderInfo FcBMP_read(const tchar* name_file, bmpImage_t* image) {
	FILE* ptr_file;

	ptr_file = fopen(name_file, TEXT("rb"));
	if(ptr_file){
		if (!fseek(ptr_file, 0, SEEK_END)) {
			size_t size_file = ftell(ptr_file);
			if (!fseek(ptr_file, 0, SEEK_SET)) {
				uint8_t* memory_file = (uint8_t*)malloc(size_file + 64);
				if (memory_file) {
					void* align_ptr_memory_file = (void *) (((size_t) memory_file + 64) & ~(size_t) 64);
					if (fread(align_ptr_memory_file, size_file, 1, ptr_file)) {
						if (read_BMP(align_ptr_memory_file, image)) {
							free(memory_file);
							fclose(ptr_file);
							return BMPLIB_NO_ERROR;
						}
					}
					free(memory_file);
				}
			}
		}
		fclose(ptr_file);
	}
	return BMPLIB_STDIO_ERROR;
}

bmpReaderInfo FcBMP_write_Bin(const tchar* name_file, bmpImage_t* image) {
	FILE* ptr_file = NULL;
	bmpReaderInfo info = BMPLIB_NO_ERROR;
    ptr_file = fopen(name_file, TEXT("wb"));
    if(ptr_file){
		if (write_BMP_Core_Bit1(ptr_file, image))
			info = BMPLIB_NO_ERROR;
		else
			info = BMPLIB_BMP_FILE;
	}
	else
		info = BMPLIB_STDIO_ERROR;
	if (ptr_file)
		fclose(ptr_file);
	return info;
}
bmpReaderInfo FcBMP_write_8(const tchar* name_file, bmpImage_t* image) {
	FILE* ptr_file = NULL;
	bmpReaderInfo info = BMPLIB_NO_ERROR;
	ptr_file = fopen(name_file, TEXT("wb"));
	if (ptr_file) {
		if (write_BMP_Core_Bit8(ptr_file, image))
			info = BMPLIB_NO_ERROR;
		else
			info = BMPLIB_BMP_FILE;
	}
	else
		info = BMPLIB_STDIO_ERROR;
	if (ptr_file)
		fclose(ptr_file);
	return info;
}
bmpReaderInfo FcBMP_write_TrueColor24(const tchar* name_file, bmpImage_t* image) {
	FILE* ptr_file = NULL;
	bmpReaderInfo info = BMPLIB_NO_ERROR;
    ptr_file = fopen(name_file, TEXT("wb"));
    if(ptr_file){
		if (write_BMP_Core_Bit24(ptr_file, image))
			info = BMPLIB_NO_ERROR;
		else
			info = BMPLIB_BMP_FILE;
	}
	else
		info = BMPLIB_STDIO_ERROR;
	if(ptr_file)
		fclose(ptr_file);
	return info;
}

//int main()
//{
//	struct Image_info image;
//	read_file(TEXT("test.bmp"), &image);
//	return 0;
//}