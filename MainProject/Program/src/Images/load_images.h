

#ifndef GRAPHICSTEST_LOADIMAGES_H
#define GRAPHICSTEST_LOADIMAGES_H
#include <stddef.h>
#include <stdint.h>
#include "ppm_reader.h"
#include "../System_API/system_filesystem.h"
struct image_matrix{
    size_t width;
    size_t height;
    size_t numberBytePixel;
    uint8_t data[0];
};
struct images_matrix{
    struct image_matrix** images;
    size_t numberImages;
};

struct images_matrix images_load_ppm(char* path);
void images_free(struct images_matrix* images);



#endif //GRAPHICSTEST_LOADIMAGES_H
