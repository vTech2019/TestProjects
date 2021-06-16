#ifdef _WIN32
#include "WGL.h"
#include "../WINAPI/WINAPI_Window.h"
#include "WGL_Functions.h"

#include <gl/glcorearb.h>
#include <gl/wgl.h>

void setPixelFormat(struct WINAPI_Window_t* window) {
    INT format;
    PIXELFORMATDESCRIPTOR pfd =
    {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW |
    PFD_SUPPORT_OPENGL |
    PFD_DOUBLEBUFFER |
    PFD_GENERIC_ACCELERATED,
    PFD_TYPE_RGBA,
    32,
    0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    0, 0, 0, 0,
    32,
    8,
    0,
    PFD_MAIN_PLANE,
    0,
    0, 0, 0
    };
    if (!(window->hdc = GetWindowDC(window->hwnd)))
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);
    if (!(format = ChoosePixelFormat(window->hdc, &pfd)))
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);
    if (!DescribePixelFormat(window->hdc, format, sizeof(pfd), &pfd))
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);
    if (!SetPixelFormat(window->hdc, format, &pfd))
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);
}

struct wgl_t wgl(struct WINAPI_Window_t* window) {
    struct wgl_t wgl_data = { 0 };
    wgl_data.p_window = window;
    HGLRC HRC_tmp;
    PIXELFORMATDESCRIPTOR pfd =
    {
	    sizeof(PIXELFORMATDESCRIPTOR),
	    1,
	    PFD_DRAW_TO_WINDOW |
	    PFD_SUPPORT_OPENGL |
	    PFD_DOUBLEBUFFER |
	    PFD_GENERIC_ACCELERATED,
	    PFD_TYPE_RGBA,
	    32,
	    0, 0, 0, 0, 0, 0,
	    0,
	    0,
	    0,
	    0, 0, 0, 0,
	    32,
	    8,
	    0,
	    PFD_MAIN_PLANE,
	    0,
	    0, 0, 0
    };
    const int attributeList[] =
    {
	    WGL_DRAW_TO_WINDOW_ARB  , GL_TRUE,
	    WGL_SUPPORT_OPENGL_ARB  , GL_TRUE,
	    WGL_DOUBLE_BUFFER_ARB   , GL_TRUE,
	    WGL_ACCELERATION_ARB,		WGL_FULL_ACCELERATION_ARB,
	    WGL_PIXEL_TYPE_ARB      , WGL_TYPE_RGBA_ARB,
	    WGL_COLOR_BITS_ARB      , 32,
	    WGL_DEPTH_BITS_ARB      , 24,
	    WGL_STENCIL_BITS_ARB    , 8,
	    0,
    };
    const int contextList[] =
    {
	    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
	    WGL_CONTEXT_MINOR_VERSION_ARB, 3,
	    WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB,
	    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB ,
	    0
    };
    setPixelFormat(window);
    if (wgl_data.gl_context != NULL) {
        if (!wglMakeCurrent(NULL, NULL))
            getLastErrorMessage(__LINE__, __FILE__),
            exit(0);
        if (!wglDeleteContext(wgl_data.gl_context))
            getLastErrorMessage(__LINE__, __FILE__),
            exit(0);
    }
    if ((HRC_tmp = wglCreateContext(window->hdc)) == 0)
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);
    if (!wglMakeCurrent(window->hdc, HRC_tmp))
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");

    if (!wglChoosePixelFormatARB)
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);
    if (!wglCreateContextAttribsARB)
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);

    if (!wglChoosePixelFormatARB(window->hdc, attributeList, NULL, 1, &wgl_data.pixelFormat, &wgl_data.numberFormats))
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);
    if (!wglMakeCurrent(NULL, NULL))
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);

    if (!SetPixelFormat(window->hdc, wgl_data.pixelFormat, &pfd))
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);
    if ((wgl_data.gl_context = wglCreateContextAttribsARB(window->hdc, NULL, contextList)) == 0)
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);
    if (!wglDeleteContext(HRC_tmp))
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);
    if (!wglMakeCurrent(window->hdc, wgl_data.gl_context))
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);
    if (!get_OpenGL_functions())
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);

    //wgl_data.base = glGenLists(256);
    //if (wgl_data.font = CreateFont(-MulDiv(point_size, GetDeviceCaps(wgl_data.hdc, LOGPIXELSY), 72), 0, 0, 0,
    //	FW_DONTCARE,
    //	0, 0, 0,
    //	RUSSIAN_CHARSET,
    //	OUT_DEFAULT_PRECIS,
    //	CLIP_DEFAULT_PRECIS,
    //	ANTIALIASED_QUALITY,
    //	DEFAULT_PITCH,
    //	"Comic Sans MS")) {
    //	MessageBox(HWND_DESKTOP, "Failed to create font.", 0, 0);
    //	return wgl_data;
    //}
    //SelectObject(wgl_data.hdc, wgl_data.font);
    //GetTextMetrics(wgl_data.hdc, &wgl_data.metrix);
    //wgl_data.font_width = wgl_data.metrix.tmAveCharWidth + 1;

    //wglUseFontOutlines(wgl_data.hdc,
    //	0,					// Starting Character
    //	255,				// Number Of Display Lists To Build
    //	wgl_data.base,				// Starting Display Lists
    //	1.0f,				// Deviation From The True Outlines
    //	0.0f,				// Font Thickness In The Z Direction
    //	WGL_FONT_POLYGONS,	// Use Polygons, Not Lines
    //	wgl_data.gmf);				// Address Of Buffer To Recieve Data

    //wglUseFontBitmaps (wgl_data.hdc, 0, 255, wgl_data.base);
    return wgl_data;
}

void wgl_free_context(struct wgl_t* wgl_data) {
    if (wgl_data->gl_context) {
        if (!wglMakeCurrent(wgl_data->p_window->hdc, NULL))
            getLastErrorMessage(__LINE__, __FILE__),
            exit(0);
        if (!wglDeleteContext(wgl_data->gl_context))
            getLastErrorMessage(__LINE__, __FILE__),
            exit(0);
        wgl_data->gl_context = NULL;
    }
}
void wgl_free(struct wgl_t* wgl_data) {
    //DeleteObject(wgl_data->font);
    wgl_free_context(wgl_data);
}

#endif