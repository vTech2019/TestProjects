//
// Created by human on 2/8/20.
//

#include "load_images.h"
#include <string.h>
#include <stdio.h>
void* reallocator(void** memory, size_t width, size_t height, size_t numberBitPixel){
    *memory = (void*)realloc(*memory, width * height * numberBitPixel / 8 + sizeof(struct image_matrix));
    struct image_matrix* ptr = *memory;
    ptr->height = height;
    ptr->width = width;
    ptr->numberBytePixel = numberBitPixel / 8;
    return ptr->data;
}

struct images_matrix images_load_ppm(char* path){
    struct images_matrix m_images = { 0 };
    system_name_files* names = system_get_name_files(path);
    size_t numberImages = 0;
    size_t path_length = strlen(path) + 1;
    size_t max_length = 0;
    size_t length = 0;
    for (size_t i = 0; i < names->number_names; i++){
        if (strstr(names->names[i], ".ppm")){
            length = strlen(names->names[i]);
            max_length = max_length < length ? length : max_length;
            numberImages++;
        }
    }
    length = path_length;
    path_length += max_length;
    char* path_name = malloc(path_length);
    memcpy(path_name, path, length);
    path_name[path_length - max_length] = '/';

    m_images.numberImages = numberImages;
    if (numberImages){
        m_images.images = (struct image_matrix**)realloc(m_images.images, numberImages * sizeof(struct image_matrix*));
        numberImages = 0;
    }
    for (size_t i = 0; i < m_images.numberImages; i++) {
        if (strstr(names->names[i], ".ppm")){
            memcpy(path_name + length, names->names[i], strlen(names->names[i]));
            struct image_matrix* ptr = NULL;
            if (read_ppm_image(path_name, (void **) &ptr, reallocator) == 0){
                m_images.images[numberImages++] = ptr;
            }
        }
    }
    if (numberImages){
        m_images.images = (struct image_matrix**)realloc(m_images.images, numberImages * sizeof(struct image_matrix*));
        m_images.numberImages = numberImages;
    }
    if (path_name) free(path_name);
    return m_images;
}
void images_free(struct images_matrix* images){
    for (size_t i = 0; i < images->numberImages; i++){
        free(images->images[i]);
    }
    if (images->images)
        free(images->images);
    images->numberImages = 0;
    images->images = NULL;
}
