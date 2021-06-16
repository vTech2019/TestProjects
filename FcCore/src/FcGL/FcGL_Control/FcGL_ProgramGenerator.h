#pragma once


#ifndef __FCGL_PROGRAMGENERATOR_H__
#define __FCGL_PROGRAMGENERATOR_H__

#include "../FcGL_Functions.h"
#include "../FcGL_Program.h"
#include "FcImage/FcImage.h"

#include "include/FcWindow.h"
#include "FcGL_Button.h"

enum FcGL_CONTROLS {
    FcGL_Button_control = 1,
    FcGL_Switch_control
};
typedef GLuint FcGL_controls;

typedef struct _FcGL_ProgramGenerator_t {
    FcImage_t *image;
    GLubyte *code;
    GLuint vertexLength;
    GLuint fragmentLength;
} FcGL_ProgramGenerator_t;

typedef struct _FcGL_ProgramGenerator_options_t {
    GLuint numberControls;
    GLuint numberButtons;
    struct {
        FcGL_controls type;
        union {
            FcGL_Button_options_t m_button;
        } code;
    } typeControl[];
} FcGL_ProgramGenerator_options_t;

FcGL_ProgramGenerator_t FcGL_GeneratorGUI(const FcGL_ProgramGenerator_options_t *options, const FcGLWindow_t *window);


#endif