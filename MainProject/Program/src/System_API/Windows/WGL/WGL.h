#ifdef _WIN32
#include <Windows.h>
#ifndef __WGL_H__
#define __WGL_H__
struct wgl_t {
    struct WINAPI_Window_t* p_window;
    HGLRC gl_context;
    unsigned        numberFormats;
    int          pixelFormat;
    unsigned	base;
};
struct wgl_t wgl(struct WINAPI_Window_t* window);
void wgl_free(struct wgl_t* wgl_data);
void wgl_free_context(struct wgl_t* wgl_data);

#endif
#endif