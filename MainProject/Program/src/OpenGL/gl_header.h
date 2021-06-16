//
// Created by human on 28.07.2020.
//

#ifndef GRAPHICSTEST_GL_HEADER_H
#define GRAPHICSTEST_GL_HEADER_H

#ifdef _WIN32
#undef GL_GLEXT_PROTOTYPES
#include <../System_API/Windows/WGL/WGL_Functions.h>
#include <gl/glext.h>
#elif __linux__
#include <GL/glcorearb.h>
#else
#endif
#endif //GRAPHICSTEST_GL_HEADER_H
