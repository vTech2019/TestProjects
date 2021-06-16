#pragma once

#ifndef __FCGL_BUTTON_H__
#define __FCGL_BUTTON_H__


#include "../FcGL_Functions.h"
#include "../FcGL_Program.h"
#include <include/FcWindow.h>
#include "FcImage/FcImage.h"

typedef struct _FcGL_Button_options_t {
    GLuint width, height;
    GLuint x, y;
    GLuint color;
    GLuint fontSize;
    GLbyte *text;
} FcGL_Button_options_t;

typedef struct _FcGL_Button_t {
    GLfloat m_width, m_height;
    GLfloat m_x, m_y;
    GLint m_texture;
    FcGL_Program_t *m_program;
} FcGL_Button_t;

FcGL_Button_t FcGL_Button(FcGL_Button_options_t *options, FcImage_t *image, FcGLWindow_t *window);

void FcGL_Button_free(FcGL_Button_t *button);

GLint FcGL_Button_IsWithinRegion(const GLuint x, const GLuint y);

#endif