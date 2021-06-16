
#ifdef __linux__

#ifndef _X11_WINDOW_H
#define _X11_WINDOW_H

#include <FcGL//FcGLX.h>
#include "Algorithm/Fc_ProducerConsumer.h"

#include <X11/Xutil.h>
#include <X11/keysymdef.h>

extern Display *FcDisplay;

enum mouseKeyCode {
    FCWINDOW_MOUSE_LBUTTONDOWN = 1,
    FCWINDOW_MOUSE_MBUTTONDOWN = 2,
    FCWINDOW_MOUSE_RBUTTONDOWN = 3,
    FCWINDOW_MOUSE_UPWHEEL = 4,
    FCWINDOW_MOUSE_DOWNWHEEL = 5
};
enum keyboardKeyEvent {
    KeyUp = KeyRelease, KeyDown = KeyPress
};

typedef struct FcGLWindow_t {

    XVisualInfo *m_visual;
    Atom m_wmDeleteWindow;
    FcGLXContext_t m_glx;
    Colormap m_colorMap;
    Window window;
    XEvent event;
    int screenId;
    unsigned m_width, m_height;

    Fc_ProducerConsumer_t glThread;
    void *dataKeyboardCallback[2];

    void (*callbackKeyboard)(unsigned int keyCode, unsigned int keyEvent, void *data_0, void *data_1);

    void *dataMouseCallback;

    void (*callbackMouse)(unsigned int x, unsigned int y, unsigned int mouseKeyCode, void *data_0);

    void *dataResizeCallback[2];

    void (*callbackResizeWindow)(unsigned int width, unsigned int height, void *data_0, void *data_1);
} FcGLWindow_t;

static inline void FcGLWindow_swapBuffers(FcCore_t *core, FcGLWindow_t *window) {
    core->m_gl.m_glXSwapBuffers(FcDisplay, window->window);
};

#endif //_X11_WINDOW_H
#endif