//
// Created by human on 03.04.2020.
//

#ifdef __linux__
//#include "X11_Window.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <include/FcCore.h>
#include "X11_Window.h"

extern Display *FcDisplay;
extern uint8_t FcInitWindowData;

#define INIT_THREAD  (1 << 0)
#define INIT_DISPLAY (1 << 1)

void FcGLWindow_initContext(FcCore_t *core, FcGLWindow_t *window);

FcError_t FcGLWindow(FcCore_t *core, FcGLWindow_t *window, uint32_t width, uint32_t height) {
    XSetWindowAttributes m_attrib = {0};
    FcError_t mError = FC_NO_ERROR;
    int m_rootWindow;

    errno = 0;
    if (!(FcInitWindowData & INIT_THREAD) && (XInitThreads() != 0))
        FcInitWindowData |= INIT_THREAD;
    else{
        mError = FC_XLIB_NOTTHREADSAFE;
        goto gError;
    }
    printf("%d\n", errno);

    errno = 0;
    FcDisplay = XOpenDisplay(NULL);

    //Display* display = XOpenDisplay(NULL);
    if (!(FcInitWindowData & INIT_DISPLAY) && (FcDisplay))
        FcInitWindowData |= INIT_DISPLAY;
    else{
        mError = FC_XLIB_XOPENDISPLAY;
        goto gError;
    }

    XFlush(FcDisplay);

    printf("%d\n", errno);
    errno = 0;

    window->screenId = DefaultScreen(FcDisplay);
    m_rootWindow = DefaultRootWindow(FcDisplay);

    errno = 0;
    FcGLX_chooseVisual(&core->m_gl, FcDisplay, window->screenId, &window->m_visual, &window->m_colorMap);

    //window->m_colorMap = XCreateColormap(FcDisplay, m_rootWindow, window->m_visual->visual, AllocNone);
    printf("%d\n", errno);


    m_attrib.border_pixel = BlackPixel(FcDisplay, window->screenId);
    m_attrib.background_pixel = WhitePixel(FcDisplay, window->screenId);
    m_attrib.colormap = window->m_colorMap;
    m_attrib.override_redirect = True;
    m_attrib.event_mask = StructureNotifyMask |
                          EnterWindowMask |
                          LeaveWindowMask |
                          ExposureMask |
                          OwnerGrabButtonMask |
                          Button5MotionMask |
                          Button4MotionMask |
                          Button3MotionMask |
                          Button2MotionMask |
                          Button1MotionMask |
                          ButtonMotionMask |
                          ButtonPressMask |
                          ButtonReleaseMask |
                          KeyPressMask |
                          KeyReleaseMask |
                          PointerMotionMask;
    errno = 0;
    window->window = XCreateWindow(FcDisplay, m_rootWindow, 0, 0, width, height, 0, window->m_visual->depth,
                                   InputOutput, window->m_visual->visual,
                                   CWBackPixel | CWOverrideRedirect | CWColormap | CWBorderPixel | CWEventMask, &m_attrib);
    printf("%d\n", errno);
    window->m_width = width;
    window->m_height = height;
    errno = 0;
    window->m_wmDeleteWindow = XInternAtom(FcDisplay, "WM_DELETE_WINDOW", False);
    printf("%d\n", errno);
    errno = 0;
    int error = XMapWindow(FcDisplay, window->window);
    printf("%d %d\n", errno, error);
    errno = 0;
    error = XSetWMProtocols(FcDisplay, window->window, &window->m_wmDeleteWindow, 1);
    printf("%d %d\n", errno, error);
    FcGLWindow_initContext(core, window);
    gError:
    return mError;
}

void FcGLWindow_freeThreadContext(FcCore_t *core, FcGLWindow_t *window) {
    FcGLX_freeContext(&core->m_gl, &window->m_glx, FcDisplay);
}

void FcGLWindow_initThreadContext(FcCore_t *core, FcGLWindow_t *window) {
    FcGLX_initDebugContext(&core->m_gl, &window->m_glx, FcDisplay, window->m_visual, window->window);
    printf("GL Renderer: %s\n", glGetString(GL_RENDERER));
    printf("GL Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void FcGLWindow_initContext(FcCore_t *core, FcGLWindow_t *window) {

    Fc_ProducerConsumer(&window->glThread);
    Fc_ProducerConsumerData_t init = {e_FcGL_callFunction_fpp, FcGLWindow_initThreadContext, core, window};
    Fc_threadProducer(&window->glThread, init);
}

void FcGLWindow_freeContext(FcCore_t *core, FcGLWindow_t *window) {
    Fc_ProducerConsumerData_t init = {e_FcGL_callFunction_fpp, FcGLWindow_freeThreadContext, core, window};
    Fc_threadProducer(&window->glThread, init);
}

void FcGLWindow_show(FcGLWindow_t *window) {
    int error = 0;
    //BadRequest
    error = XClearWindow(FcDisplay, window->window);
    error = XMapWindow(FcDisplay, window->window);
    error = 0;
}

void FcGLWindow_free(FcCore_t *core, FcGLWindow_t *window) {
    int m_result = FC_NO_ERROR;
    Fc_ProducerConsumerData_t init = {e_FcGL_callFunction_fpp, FcGLWindow_freeContext, core, window};
    Fc_threadProducer(&window->glThread, init);
    Fc_ProducerConsumer_freeLock(&window->glThread);

    if (FcDisplay) {
        m_result = XFree(window->m_visual);
        m_result = XFreeColormap(FcDisplay, window->m_colorMap);
        m_result = XDestroyWindow(FcDisplay, window->window);
        m_result = XCloseDisplay(FcDisplay);
    }
}

void FcGLWindow_setCenterCursorPosition(FcGLWindow_t *window) {
    XSelectInput(FcDisplay, window->window, KeyReleaseMask);
    XWarpPointer(FcDisplay, None, window->window, 0, 0, window->m_width, window->m_height, 100, 100);
    XFlush(FcDisplay);
}

void FcGLWindow_setCallbackResizeWindow(FcGLWindow_t *window,
                                        void (*callbackResizeWindow)(unsigned int width, unsigned int height,
                                                                     void *data_0, void *data_1), void *data_0,
                                        void *data_1) {
    window->callbackResizeWindow = callbackResizeWindow;
    window->dataResizeCallback[0] = data_0;
    window->dataResizeCallback[1] = data_1;
}

void FcGLWindow_setCallbackKeyboard(FcGLWindow_t *window,
                                    void (*callbackKeyboard)(unsigned int keyCode, unsigned int keyEvent, void *data_1,
                                                             void *data_2),
                                    void *data_0, void *data_1) {
    window->callbackKeyboard = callbackKeyboard;
    window->dataResizeCallback[0] = data_0;
    window->dataResizeCallback[1] = data_1;
}

void FcGLWindow_setCallbackMouse(FcGLWindow_t *window,
                                 void (*callbackMouse)(unsigned int x, unsigned int y, unsigned int mouseKeyCode,
                                                       void *data_0),
                                 void *data_0) {
    window->callbackMouse = callbackMouse;
    window->dataMouseCallback = data_0;
}

void FcGLWindow_getClientSize(const FcGLWindow_t *window, int *width, int *height) {
    XWindowAttributes attributes;
    XGetWindowAttributes(FcDisplay, window->window, &attributes);
    *height = attributes.height;
    *width = attributes.width;

}

void FcGLWindow_getWindowSize(const FcGLWindow_t *window, int *width, int *height) {
    XWindowAttributes attributes;
    XGetWindowAttributes(FcDisplay, window->window, &attributes);
    *height = attributes.height;
    *width = attributes.width + 2 * attributes.border_width;
}

void FcGLWindow_dispatch(FcGLWindow_t *window) {
    XWindowAttributes attributes;
    long long i = 0;
    int exit = 0;
    if (window->window && FcDisplay)
        while (!exit) {
            if (XPending(FcDisplay) > 0) {
                XNextEvent(FcDisplay, &window->event);
                switch (window->event.type) {
                    case ConfigureNotify:
                        window->m_width = window->event.xconfigure.width;
                        window->m_height = window->event.xconfigure.height;
                        if (window->callbackResizeWindow)
                            window->callbackResizeWindow(window->m_width, window->m_height,
                                                         window->dataResizeCallback[0], window->dataResizeCallback[1]);
                        break;
                    case Expose:
                        //XGetWindowAttributes(window->ptr_display, window->window, &attributes);
                        //if (window->callbackResizeWindow)
                        //    window->callbackResizeWindow(attributes.width, attributes.height, window->dataResizeCallback[0], window->dataResizeCallback[1]);
                        // window->m_width = attributes.width;
                        //window->m_height = attributes.height;
                        break;
                    case LeaveNotify:
                        break;
                    case EnterNotify:
                        break;
                    case ClientMessage:
                        if (window->event.xclient.data.l[0] == window->m_wmDeleteWindow)
                            exit = 1;
                        break;
                    case DestroyNotify:
                        exit = 1;
                        break;
                        //case ButtonRelease:
                    case MotionNotify:
                    case ButtonPress :
                        if (window->callbackMouse)
                            window->callbackMouse(window->event.xmotion.x, window->m_height - window->event.xmotion.y,
                                                  window->event.xbutton.button, window->dataMouseCallback);
                        break;
                    case KeyPress :
                        if (window->callbackKeyboard)
                            window->callbackKeyboard(window->event.xkey.keycode, window->event.xkey.state,
                                                     window->dataKeyboardCallback[0], window->dataKeyboardCallback[1]);
                        break;
                }
            }
        }
    //FcGLWindow_free(window);
}

#endif
