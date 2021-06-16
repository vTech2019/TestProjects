//
// Created by human on 03.04.2020.
//

#ifdef __linux__
#include "X11_Window.h"
#include <stdio.h>

char* gl_window_set_messages(X11_gl_Window* window);
char* initGLX(Display* display, XVisualInfo** visual, GLXFBConfig* bestFbc, int screenId){

    int majorGLX, minorGLX = 0;
    int fbConfig_count = 0;
    int sample_buffer, samples;
    int best_fbc = -1, best_num_sample = -1;
    GLXFBConfig* fbConfigs;
    GLint glxAttribs[] = {
            GLX_X_RENDERABLE    , True,
            GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
            GLX_RENDER_TYPE     , GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
            GLX_RED_SIZE        , 8,
            GLX_GREEN_SIZE      , 8,
            GLX_BLUE_SIZE       , 8,
            GLX_ALPHA_SIZE      , 8,
            GLX_DEPTH_SIZE      , 24,
            GLX_STENCIL_SIZE    , 8,
            GLX_DOUBLEBUFFER    , True,
            None
    };
    if (!glXQueryVersion(display, &majorGLX, &minorGLX)){
        return "ERROR glXQueryVersion!";
    }
    if (majorGLX <= 1 && minorGLX < 2) {
        return "GLX 1.2 or greater is required.\n";
    }
    if (!(fbConfigs = glXChooseFBConfig(display, screenId, glxAttribs, &fbConfig_count))) {
        return "Failed to retrieve framebuffer.\n";
    }
    for (int i = 0; i < fbConfig_count; ++i) {
        *visual = glXGetVisualFromFBConfig( display, fbConfigs[i] );
        if ( *visual != 0) {
            glXGetFBConfigAttrib( display, fbConfigs[i], GLX_SAMPLE_BUFFERS, &sample_buffer );
            glXGetFBConfigAttrib( display, fbConfigs[i], GLX_SAMPLES       , &samples  );
            if ( best_fbc < 0 || (sample_buffer && samples > best_num_sample) ) {
                best_fbc = i;
                best_num_sample = samples;
            }
        }
        XFree( *visual );
    }
    *bestFbc = fbConfigs[ best_fbc ];
    XFree( fbConfigs );
    *visual = glXGetVisualFromFBConfig( display, *bestFbc );

    if (*visual == NULL) {
        return "Could not create correct visual window.\n";
    }
    if (screenId != (*visual)->screen) {
        return "screenId does not match visual->screen).\n";
    }
    return NULL;
}
char* initGLContext(Display* display, GLXContext* context, const Window* window, GLXFBConfig* bestFbc, int screenId){
    char* message;
    *context = glXCreateNewContext( display, *bestFbc, GLX_RGBA_TYPE, 0, True );
    XSync( display, False );
    if (!glXIsDirect (display, *context)) {
        message= "Indirect GLX rendering context obtained\n";
    }else
        message= "Direct GLX rendering context obtained\n";
    glXMakeCurrent(display, *window, *context);
    return message;
}
char* gl_window_set_messages(X11_gl_Window* window){
    window->wm_delete_window = XInternAtom(window->ptr_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(window->ptr_display, window->window, &window->wm_delete_window, 1);
}
char* gl_window(X11_gl_Window* window, size_t width, size_t height){
    XInitThreads();
    char* errorMessage = NULL;
    if ((window->ptr_display = XOpenDisplay(NULL)) == NULL) {
        return "Could not open display\n";
    }
    window->ptr_screen = DefaultScreenOfDisplay(window->ptr_display);
    window->screenId = DefaultScreen(window->ptr_display);
    if ((errorMessage = (char*)initGLX(window->ptr_display, &window->visual_info, &window->fbc_config, window->screenId))!= NULL){
        gl_window_free(window);
        return errorMessage;
    }
    window->window_attributes.border_pixel = BlackPixel(window->ptr_display, window->screenId);
    window->window_attributes.background_pixel = WhitePixel(window->ptr_display, window->screenId);
    window->window_attributes.override_redirect = True;
    window->window_attributes.colormap = XCreateColormap(window->ptr_display, RootWindow(window->ptr_display, window->screenId), window->visual_info->visual, AllocNone);
    window->window_attributes.event_mask = ExposureMask;
    window->window = XCreateWindow(window->ptr_display, RootWindow(window->ptr_display, window->screenId), 0, 0, width, height, 0, window->visual_info->depth, InputOutput, window->visual_info->visual, CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &window->window_attributes);

    gl_window_set_messages(window);
    XClearWindow(window->ptr_display, window->window);
    XMapWindow (window->ptr_display, window->window);
    window->thread_status_window = 0xffffffff;
    return errorMessage;

}
void gl_window_init_context(X11_gl_Window* window){
    printf("%s\n", initGLContext(window->ptr_display, &window->glx_context, &window->window, &window->fbc_config, window->screenId));
    printf("GL Renderer: %s\n", glGetString(GL_RENDERER));
    printf("GL Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}
void gl_window_free_context(X11_gl_Window* window){
    if (window->glx_context){
        glXDestroyContext(window->ptr_display, window->glx_context);
        window->glx_context = NULL;
    }
}
void gl_window_show(X11_gl_Window* window){
    XClearWindow(window->ptr_display, window->window);
    XMapWindow (window->ptr_display, window->window);
}
void gl_window_free(X11_gl_Window* window){

    window->thread_status_window = 0;
    while (!window->thread_success_exit)
        continue;
    if (window->glx_context)
        glXDestroyContext(window->ptr_display, window->glx_context);
    if (window->visual_info)
        XFree(window->visual_info);
    if (window->ptr_display){
        XFreeColormap(window->ptr_display, window->window_attributes.colormap);
        XDestroyWindow(window->ptr_display, window->window);
        XCloseDisplay(window->ptr_display);
    }
}
void gl_window_setCenterCursorPosition(X11_gl_Window* window){
    XSelectInput(window->ptr_display, window->window, KeyReleaseMask);
    XWarpPointer(window->ptr_display, None, window->window, 0, 0, window->m_width, window->m_height, 100, 100);
    XFlush(window->ptr_display);
}
void gl_window_setCallbackResizeWindow(X11_gl_Window* window, void (*callbackResizeWindow)(size_t width, size_t height, void* data_0, void* data_1 ), void* data_0, void* data_1) {
    window->callbackResizeWindow = callbackResizeWindow;
    window->dataResizeCallback[0] = data_0;
    window->dataResizeCallback[1] = data_1;
}
void gl_window_setCallbackKeyboard(X11_gl_Window* window, void (*callbackKeyboard)(int keyCode, enum keyboardKeyEvent keyEvent, void* data_1, void* data_2), void* data_0, void* data_1){
    window->callbackKeyboard = callbackKeyboard;
    window->dataResizeCallback[0] = data_0;
    window->dataResizeCallback[1] = data_1;
}
void gl_window_setCallbackMouse(X11_gl_Window* window, void (*callbackMouse)(size_t x, size_t y, unsigned char mouseKeyCode, void* data_0), void* data_0) {
    window->callbackMouse = callbackMouse;
    window->dataMouseCallback = data_0;
}
char* gl_window_dispatch(X11_gl_Window* window){
    XWindowAttributes attributes;
    if (window->window && window->ptr_display)
        while (1) {
            while (XPending(window->ptr_display) > 0) {
                XNextEvent(window->ptr_display, &window->event);
                switch(window->event.type){
                    case Expose:
                        XGetWindowAttributes(window->ptr_display, window->window, &attributes);
                        if (window->callbackResizeWindow)
                            window->callbackResizeWindow(attributes.width, attributes.height, window->dataResizeCallback[0], window->dataResizeCallback[1]);
                        break;
                    case ClientMessage:
                        if (window->event.xclient.data.l[0] == window->wm_delete_window)
                            goto exit;
                        break;
                    case DestroyNotify:
                        goto exit;
                    case ButtonRelease:
                    case MotionNotify:
                    case ButtonPress :
                        if (window->callbackMouse)
                            window->callbackMouse(window->event.xmotion.x, attributes.height - window->event.xmotion.y, window->event.xbutton.button, window->dataMouseCallback);
                        break;
                    case KeyPress :
                        if (window->callbackKeyboard)
                            window->callbackKeyboard(window->event.xkey.keycode, window->event.xkey.state, window->dataKeyboardCallback[0], window->dataKeyboardCallback[1]);

                        goto exit;
                }
            }
        }
    exit:
    return NULL;
}
#endif
