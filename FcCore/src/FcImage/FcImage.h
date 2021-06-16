#pragma once

#ifndef __FCIMAGE_H__
#define __FCIMAGE_H__

#include <stdint.h>
#include <stdlib.h>
#include "FcGL/FcGL_Matrix/FcGL_Vec4.h"

typedef uint32_t FcImageType_t;

#define FCIMAGE_WIDTH_STRIDE 16

enum e_FCIMAGE_TYPE {
    FCIMAGE_R = 1,
    FCIMAGE_RG = 2,
    FCIMAGE_RGB = 3,
    FCIMAGE_RGBA = 4
};
typedef struct _FcImage_t {
    uint32_t width, height, numberBytePixel, widthStride;
    uint8_t data[0];
} FcImage_t;

static inline FcImage_t *FcImage(uint32_t width, uint32_t height, FcImageType_t numberBytePixel) {
    FcImage_t *image = (FcImage_t *) calloc(1, ((width * numberBytePixel) | FCIMAGE_WIDTH_STRIDE) * height +
                                               sizeof(FcImage_t));
    if (image) {
        image->width = width;
        image->height = height;
        image->numberBytePixel = numberBytePixel;
        image->widthStride = (width * numberBytePixel) | FCIMAGE_WIDTH_STRIDE;
    }
    return image;
}

#endif
