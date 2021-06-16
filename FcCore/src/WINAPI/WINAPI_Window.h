
#ifdef _WIN32
#ifndef _WINAPI_WINDOW_T_
#define _WINAPI_WINDOW_T_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <Windowsx.h>

#include "WINAPI_Error.h"
#include "../Algorithm/Fc_ProducerConsumer.h"
#include "FcGL/FcWGL.h"

enum FCWINDOWMOUSE {
    FCWINDOW_MOUSE_LBUTTONDOWN  = WM_LBUTTONDOWN,
    FCWINDOW_MOUSE_RBUTTONDOWN  = WM_RBUTTONDOWN,
    FCWINDOW_MOUSE_MBUTTONDOWN  = WM_MBUTTONDOWN,
    FCWINDOW_MOUSE_UPWHEEL      ,
    FCWINDOW_MOUSE_DOWNWHEEL    
};
#define FCGLWINDOW_FULLSCREEN 0x0001

typedef struct _FcGLWindow_t {
    Fc_ProducerConsumer_t glThread;
    FcWGLContext_t m_wgl;
    HWND hwnd;
    DWORD tickCount;
    uint16_t m_width, m_height;

    void *dataKeyboardCallback[2];
    void (*callbackKeyboard)(int keyCode, unsigned int  keyEvent, void *data_0, void *data_1);
    void *dataMouseCallback;
    void (*callbackMouse)(unsigned int  x, unsigned int  y, unsigned int  mouseKeyCode, void *data_0);
    void *dataResizeCallback[2];
    void (*callbackResizeWindow)(unsigned int  width, unsigned int  height, void *data_0, void *data_1);
} FcGLWindow_t;

static inline void FcGLWindow_swapBuffers(FcCore_t* core, FcGLWindow_t* window) { SwapBuffers(window->m_wgl.m_hdc); };
#endif //_WINAPI_WINDOW_T_
#endif