#pragma once


#ifndef __FCWINDOW_H__
#define __FCWINDOW_H__

#include "include/FcCore.h"

#include "UNIX/X11_Window/X11_Window.h"
#include "WINAPI/WINAPI_Window.h"

#ifndef TCHAR
#define TCHAR char
#endif

typedef void (*PFNCALLBACKKEYBOARDPROC)(unsigned int keyCode, unsigned int keyEvent, void *data_1, void *data_2);

typedef void (*PFNCALLBACKMOUSEPROC)(unsigned int keyCode, unsigned int keyEvent, void *data_1, void *data_2);

typedef void (*PFNCALLBACKRESIZEWINDOWPROC)(unsigned int keyCode, unsigned int keyEvent, void *data_1, void *data_2);

FcError_t FcGLWindow(FcCore_t *core, FcGLWindow_t *window, uint32_t width, uint32_t height);

void FcGLWindow_dispatch(FcGLWindow_t *window);

void FcGLWindow_initContext(FcCore_t *core, FcGLWindow_t *window);

void FcGLWindow_show(FcGLWindow_t *window);

void FcGLWindow_getClientSize(const FcGLWindow_t *window, int *width, int *height);

void FcGLWindow_getWindowSize(const FcGLWindow_t *window, int *width, int *height);

void FcGLWindow_hide(FcGLWindow_t *window);     //WINAPI
void FcGLWindow_free(FcCore_t *core, FcGLWindow_t *window);

void FcGLWindow_freeContext(FcCore_t *core, FcGLWindow_t *window);

void FcGLWindow_setCallbackMouse(FcGLWindow_t *window,
                                 void (*callbackMouse)(size_t x, size_t y, short mouseKeyCode, void *data_0),
                                 void *data_0);

void FcGLWindow_setCallbackResizeWindow(FcGLWindow_t *window,
                                        void (*callbackResizeWindow)(size_t width, size_t height, void *data_0,
                                                                     void *data_1), void *data_0, void *data_1);

void FcGLWindow_setCallbackKeyboard(FcGLWindow_t *window,
                                    void (*callbackKeyboard)(int keyCode, short keyEvent, void *data_1, void *data_2),
                                    void *data_0, void *data_1);

void FcGLWindow_setCenterCursorPosition(FcGLWindow_t *window);


#endif
