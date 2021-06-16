//
// Created by human on 2/5/20.
//

#ifndef SYSTEM_WINDOW_H
#define SYSTEM_WINDOW_H
#ifdef __linux__
#include "X11_Window/X11_Window.h"
typedef X11_gl_Window system_window;
#elif _WIN32
#include "Windows/WINAPI/WINAPI_Window.h"
#include "Windows/WGL/WGL_Functions.h"
typedef WINAPI_Window_t system_window;

#else
#endif


#endif //SYSTEM_WINDOW_H
