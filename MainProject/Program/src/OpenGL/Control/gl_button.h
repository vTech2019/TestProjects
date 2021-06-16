//
// Created by human on 06.04.2020.
//

#ifndef GRAPHICSTEST_GL_BUTTON_H
#define GRAPHICSTEST_GL_BUTTON_H

#include "../gl_mesh.h"
#include "../gl_main_manager.h"
#include "../Figures/field_generator.h"

struct gl_button_parameters{
    float x_center;
    float y_center;
    float z_center;
    float width;
    float height;
    unsigned char color[4];

    int    numberPositions;
    int      activateColors;
    int     activateNormals;
    int    activateTexture;

    size_t offsetVertexPosition;
    size_t offsetNormalPosition;
    size_t offsetColorPosition;
    size_t offsetTexturePosition;
    size_t offsetVertex;
    char* image_rgb;
    size_t image_width;
    size_t image_height;
    char indexVertex;
    char indexColor;
    char indexNormal;
    char indexTexture;
};
struct gl_button{
    struct gl_mesh mesh_button;
    size_t offset_init_queue;
};
void gl_button_init(struct gl_main_manager* manager, struct gl_button* button, struct gl_button_parameters* parameters);
void gl_button_free(struct gl_main_manager* manager, struct gl_button* button);
void gl_button_synchronize(struct gl_main_manager* manager, struct gl_button* button);
#endif //GRAPHICSTEST_GL_BUTTON_H
