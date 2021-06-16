//
// Created by human on 21.02.2021.
//

#ifndef _FCGL_TRUETYPE_H
#define _FCGL_TRUETYPE_H

#include <stdint.h>
#include "include/FcWindow.h"
#include "include/FcCore.h"
#include "FcGL/FcGL_Program.h"
#include "include/FcMath.h"
#include "TrueTypeLibrary.h"

typedef  int32_t FcTrueTypeError;
enum FCGL_TRUETYPE_ERRORS{
    FCGL_TRUETYPE_NOERROR,
    FCGL_TRUETYPE_PROGRAM
};

struct TrueTypeGlyf_simple_t;
typedef struct _FcTrueTypeGL_t{
    FcCore_t* m_core;
    FcGLWindow_t* m_window;
    struct TrueTypeGlyf_simple_t* m_glyph;
    char* m_font;
    //FcVec2_t m_prevMouse;
    FcVec2_t m_mouse;
    FcVec2_t m_windowSize;
    FcMatrix4x4_t m_MVP;
    TrueTypeReader_t* m_reader;
    FcGL_Program_t m_program;
    int m_middlePress;
    float m_maxVertex;
    float m_numberVertex;
    //float m_aspect;
    float m_shiftButtonX;
    float m_shiftButtonY;
    GLuint m_VAO[2];
    GLuint m_textureBuffers[2];
    GLuint m_vertexBuffers[2];
    GLuint m_vertexColor;
    GLint m_idWindow;
    GLint m_idTexture[2];
    GLint m_idVertex;
    GLint m_idColor;
    GLint m_idSelector;
    GLint m_idMVP;
    GLint m_idMouse;
    uint16_t m_unicode;
    //uint16_t m_buttonDown;

    //GLint m_idTestCurveTransform;
    //GLint m_idTestCurve;
   // float m_testAngle;
    //union FcMatrix3x3_t testMatrixCurve;
    //float testCurve[4][4];
}FcTrueTypeGL_t;

FcTrueTypeError FcTrueTypeGL_malloc(FcCore_t* core, FcGLWindow_t* window, struct _FcTrueTypeGL_t* truetype, char* font);
FcTrueTypeError FcTrueTypeGL_free(struct _FcTrueTypeGL_t* truetype);

#endif

