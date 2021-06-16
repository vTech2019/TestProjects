

#include "FcPPM.h"
#include <math.h>
int read_file(const tchar* name_file, unsigned char** memory_file, size_t* size_file) {
	FILE* ptr_file = NULL;
	int result = - 1;
	if ((ptr_file = fopen(name_file, TEXT("rb"))) != 0) {
		if (!(result = fseek(ptr_file, 0, SEEK_END))) {
			*size_file = ftell(ptr_file);
			if (!(result = fseek(ptr_file, 0, SEEK_SET))) {
				*memory_file = (unsigned char*)realloc(*memory_file, *size_file);
				if (*memory_file) {
					size_t length = fread(*memory_file, 1, *size_file, ptr_file);
					if (length != *size_file) {
						result = -1;
						free(*memory_file);
						*memory_file = NULL;
					}
				}
			}
		}
		fclose(ptr_file);
	}
	return result;
}
const unsigned char* strtosize_t(const unsigned char* ptr, size_t* number) {
	*number = 0;
	size_t offset = 0;
	while (ptr[offset] == '#') {
		while (ptr[offset] != '\n')
			offset++;
		offset++;
	}
	while (ptr[offset] >= '0' && ptr[offset] <= '9') {
		*number *= 10;
		*number += ptr[offset] - '0';
		offset++;
	}
	return ptr + offset;
}
unsigned char* size_ttostr(unsigned char* ptr, const size_t number) {
	size_t offset = 0;
#ifdef _WIN64
	size_t shift = 10000000000000000000u;
#else
	size_t shift = 1000000000u;
#endif

	size_t copy_number = number;
	while (ptr[offset] != 0 && shift != 0) {
		size_t value = copy_number / shift;
		copy_number = value > 0 ? copy_number - (value * shift) : copy_number;
		ptr[offset] = (unsigned char)value + 48;
		shift /= 10;
		offset++;
	}
	return ptr + offset;
}
unsigned char* convert_pgm_to_ppm(const unsigned char* image_pgm, const size_t size_data)
{
	unsigned char* image_ppm = (unsigned char*)malloc(size_data * 3);
	if (image_ppm) {
		for (unsigned int i = 0; i < size_data; i++) {
			image_ppm[i * 3] = image_pgm[i];
			image_ppm[i * 3 + 1] = image_pgm[i];
			image_ppm[i * 3 + 2] = image_pgm[i];
		}
	}
	return image_ppm;
}

unsigned char* convert_pgm_to_pbm(const unsigned char* image_pgm, const size_t size_data)
{
	unsigned char* image_pbm = (unsigned char*)malloc((size_data / 8) + 7);
	if (image_pbm) {
		unsigned char value = image_pgm[0] > 128 ? 0 : 1;
		for (unsigned int i = 1, j = 0; i < size_data; i++) {
			value <<= 1;
			value |= image_pgm[i] > 128 ? 0 : 1;
			if (i % 8 == 0) {
				image_pbm[j++] = value;
			}
		}
	}
	return image_pbm;
}
#ifdef _WIN32
int FcPBM_write(tchar* name_file, char* image, size_t width_bit, size_t height_bit) {
	HANDLE file;
	if (INVALID_HANDLE_VALUE != (file = CreateFile(name_file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_WRITE_THROUGH, NULL))) {
		UINT length = (height_bit * width_bit) / 8;
		UINT last_byte = 8 - (height_bit * width_bit) % 8;
		UCHAR last_value = length > 0 ? image[length + 1] : *image;
		last_value >>= last_byte;
		last_value <<= last_byte;
		UCHAR write_info[] = { "P4\n10000000000000000000 10000000000000000000\n" };

		char* next_ptr = size_ttostr(write_info + 3, width_bit);
		*next_ptr = ' ';
		next_ptr = size_ttostr(next_ptr + 1, height_bit);
		*next_ptr = '\n';
		DWORD BytesWritten;

		WriteFile(file, write_info, (DWORD) (next_ptr + 1 - (size_t) write_info), &BytesWritten, NULL);
		WriteFile(file, image, length, &BytesWritten, NULL);
		WriteFile(file, &last_value, 1, &BytesWritten, NULL);
		CloseHandle(file);
		if (width_bit % 8) {
			size_t length_name = strlen(name_file);
			tchar* name = (tchar*)malloc(sizeof(tchar) * length_name + sizeof(TEXT(" Width must be multiple of 8!")));
			memcpy(name, name_file, length_name * sizeof(tchar));
			memcpy(name + length_name, TEXT(" Width must be multiple of 8!"), sizeof(TEXT(" Width must be multiple of 8!")));
			if (!MoveFile(name_file, name)) {
				length_name = 0;
			}
			free(name);
			return -1;
		}
	}
	return 0;
}
#else
int FcPBM_write(tchar* name_file, char* image, size_t width_bit, size_t height_bit) {
	FILE* file = NULL;
	if ((file = fopen(name_file, TEXT("wb")))!=NULL) {
		size_t length = (height_bit * width_bit) / 8;
		size_t last_byte = 8 - (height_bit * width_bit) % 8;
		char last_value = length > 0 ? image[length + 1] : *image;
		last_value >>= last_byte;
		last_value <<= last_byte;
		if (width_bit % 8)
			fprintf(file, "P4\n#Width must be multiple of 8\n%zd %zd\n", width_bit, height_bit);
		else
			fprintf(file, "P4\n%zd %zd\n", width_bit, height_bit);
		fwrite(image, length, 1, file);
		fprintf(file, "%c", last_value);
		fclose(file);
		if (width_bit % 8) {
			size_t length_name = strlen(name_file);
			tchar* name = (tchar*)malloc(sizeof(tchar) * length_name + sizeof(TEXT(" Width must be multiple of 8!")));
			memcpy(name, name_file, length_name * sizeof(tchar));
			memcpy(name + length_name, TEXT(" Width must be multiple of 8!"), sizeof(TEXT(" Width must be multiple of 8!")));
			if (!rename(name_file, name)) {
				length_name = 0;
			}
			free(name);
			return -1;
		}
	}
	return 0;
}
#endif
#ifdef _WIN32
int FcPGM_write(tchar* name_file, char* image, size_t width, size_t height, size_t max_color_component_pixel) {
	HANDLE file;
	if (INVALID_HANDLE_VALUE != (file = CreateFile(name_file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_WRITE_THROUGH, NULL))) {
		UCHAR write_info[] = { "P5\n10000000000000000000 10000000000000000000\n10000000000000000000\n" };

		char* next_ptr = size_ttostr(write_info + 3, width);
		*next_ptr = ' ';
		next_ptr = size_ttostr(next_ptr + 1, height);
		*next_ptr = '\n';
		next_ptr = size_ttostr(next_ptr + 1, max_color_component_pixel);
		*next_ptr = '\n';
		DWORD BytesWritten;
		WriteFile(file, write_info, (DWORD) (next_ptr + 1 - (size_t) write_info), &BytesWritten, NULL);
		WriteFile(file, image, width * height, &BytesWritten, NULL);
		CloseHandle(file);
	}
	return 0;
}
#else
int FcPGM_write(tchar* name_file, char* image, size_t width, size_t height, size_t max_color_component_pixel) {
	if (max_color_component_pixel < 256) {
		FILE* file = NULL;
		if ((file = fopen(name_file, TEXT("wb")))!=NULL) {
			fprintf(file, "P5\n%zd %zd\n%zd\n", width, height, max_color_component_pixel);
			fwrite(image, width * height, 1, file);
			fclose(file);
		}
	}
	return 0;
}
#endif
#ifdef _WIN32
int FcPPM_write(tchar* name_file, char* image, size_t width, size_t height, size_t max_color_component_pixel) {
	HANDLE file;
	if (INVALID_HANDLE_VALUE != (file = CreateFile(name_file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_WRITE_THROUGH, NULL))) {
		UCHAR write_info[] = { "P6\n10000000000000000000 10000000000000000000\n10000000000000000000\n" };

		char* next_ptr = size_ttostr(write_info + 3, width);
		*next_ptr = ' ';
		next_ptr = size_ttostr(next_ptr + 1, height);
		*next_ptr = '\n';
		next_ptr = size_ttostr(next_ptr + 1, max_color_component_pixel);
		*next_ptr = '\n';
		DWORD BytesWritten;
		WriteFile(file, write_info, (DWORD) (next_ptr + 1 - (size_t) write_info), &BytesWritten, NULL);
		WriteFile(file, image, 3 * width * height, &BytesWritten, NULL);
		CloseHandle(file);
	}
	return 0;
}
#else
int FcPPM_write(tchar* name_file, char* image, size_t width, size_t height, size_t max_color_component_pixel) {
	if (max_color_component_pixel < 256) {
		FILE* file;
		if ((file = fopen(name_file, TEXT("wb")))!=NULL) {
			fprintf(file, "P6\n%zd %zd\n%zd\n", width, height, max_color_component_pixel);
			fwrite(image, width * height, 3, file);
			fclose(file);
		}
	}
	return 0;
}
#endif
void convert_sRGB_to_RGB_255(unsigned char* image, size_t width, size_t height) {
	const float vectorX[] = { 3.2406f, -1.5372f, -0.4986f, 0.0f };
	const float vectorY[] = { -0.9689f,  1.8758f,  0.0415f, 0.0f };
	const float vectorZ[] = { 0.0557f, -0.2040f,  1.0570f, 0.0f };
	for (size_t i = 0; i < height; i++) {
		size_t offset_hw = (i * width) * 3;
		for (size_t j = 0; j < width; j++) {
			float R = image[offset_hw + 0];
			float G = image[offset_hw + 1];
			float B = image[offset_hw + 2];
			R = vectorX[0] * R + vectorX[1] * G + vectorX[2] * B + 0 * vectorX[3];
			G = vectorY[0] * R + vectorY[1] * G + vectorY[2] * B + 0 * vectorY[3];
			B = vectorZ[0] * R + vectorZ[1] * G + vectorZ[2] * B + 0 * vectorZ[3];
			R = R <= 0.0031308f ? R * 12.92 : (1 + 0.055) * powf(R, (1.0f / 2.4f)) - 0.055f;
			G = G <= 0.0031308f ? G * 12.92 : (1 + 0.055) * powf(G, (1.0f / 2.4f)) - 0.055f;
			B = B <= 0.0031308f ? B * 12.92 : (1 + 0.055) * powf(B, (1.0f / 2.4f)) - 0.055f;
			image[offset_hw++] = (unsigned char)(R * 255.0f);
			image[offset_hw++] = (unsigned char)(G * 255.0f);
			image[offset_hw++] = (unsigned char)(B * 255.0f);
		}
	}
}


int FcPBM_read(tchar* name_file, void** image, void* (*memory_reallocator)(void** memory, size_t width, size_t height, size_t pixel_bit_size)) {
	int error = 0;
	size_t size_file = 0;
	size_t l_width_bit, l_height_bit;
	unsigned char* memory_file = NULL;
	if (!(error = read_file(name_file, &memory_file, &size_file))) {
		if (*((unsigned short*)memory_file) == *((unsigned short*)"P4")) {
			const char* info = strtosize_t(strtosize_t(memory_file + 3, &l_width_bit) + 1, &l_height_bit);
			size_t size_data = size_file - (size_t)((info + 1) - (size_t)memory_file);
			if (memory_reallocator) {
				void* data = memory_reallocator(image, l_width_bit, l_height_bit, 1);
				memcpy(data, info + 1, size_data);
			}
			else
				return -2;
		}
		else
			error = -1;
		free(memory_file);
	}
	return error;
}
int FcPGM_read(tchar* name_file, void** image, void* (*memory_reallocator)(void** memory, size_t width, size_t height, size_t pixel_bit_size)) {
	int error = 0;
	FILE* file = NULL;
	size_t size_file;
	size_t l_width, l_height, l_max_color_component_pixel;
	unsigned char* memory_file = NULL;
	if (!(error = read_file(name_file, &memory_file, &size_file))) {
		if (*((unsigned short*)memory_file) == *((unsigned short*)"P5")) {
			const char* info = strtosize_t(strtosize_t(strtosize_t(memory_file + 3, &l_width) + 1, &l_height) + 1, &l_max_color_component_pixel);
			if (l_max_color_component_pixel > 1 && l_max_color_component_pixel < 65536) {
				size_t size_data = size_file - (size_t)((info + 1) - (size_t)memory_file);
				if (memory_reallocator) {
					void* data = memory_reallocator(image, l_width, l_height, l_max_color_component_pixel < 256 ? 1 * 8 : 2 * 8);
					memcpy(data, info + 1, size_data);
				}
				else
					return -2;
			}
		}
		else
			error = -1;
		free(memory_file);
	}
	return error;
}
int FcPPM_read(tchar* name_file, void** image, void* (*memory_reallocator)(void** memory, size_t width, size_t height, size_t pixel_bit_size)) {
	int error = 0;
	size_t size_file;
	size_t l_width, l_height, l_max_color_component_pixel;
	unsigned char* memory_file = NULL;
	if (!(error = read_file(name_file, &memory_file, &size_file))) {
		if (*((unsigned short*)memory_file) == *((unsigned short*)"P6")) {
			const char* info = strtosize_t(strtosize_t(strtosize_t(memory_file + 3, &l_width) + 1, &l_height) + 1, &l_max_color_component_pixel);
			if (l_max_color_component_pixel > 1 && l_max_color_component_pixel < 65536) {
				size_t size_data = size_file - (size_t)((info + 1) - (size_t)memory_file);
				if (memory_reallocator) {
					if (l_max_color_component_pixel < 256) {
						void* data = memory_reallocator(image, l_width, l_height, 3 * 8);
						memcpy(data, info + 1, size_data);
						//convert_sRGB_to_RGB_255(data, l_width, l_height);
					}
					else {
						void* data = memory_reallocator(image, l_width, l_height, 6 * 8);
						memcpy(data, info + 1, size_data);
					}
				}
				else
					return -2;
			}
		}
		else
			error = -1;
		free(memory_file);
	}
	return error;
}
