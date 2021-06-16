#ifdef _WIN32

#ifndef __FCWGL_H__
#define __FCWGL_H__

#include <Windows.h>
#include "FcWGL_Functions.h"
#include "WINAPI/WINAPI_Error.h"

#include <FcError.h>

typedef struct FcWGL_t {
    HMODULE m_handle;

    PROC(WINAPI* glGetProcAddress)(LPCSTR);
    BOOL(WINAPI* glCopyContext)(HGLRC, HGLRC, UINT);
    HGLRC(WINAPI* glCreateContext)(HDC);
    HGLRC(WINAPI* glCreateLayerContext)(HDC, INT);
    BOOL(WINAPI* glDeleteContext)(HGLRC);
    HGLRC(WINAPI* glGetCurrentContext)(VOID);
    HDC(WINAPI* glGetCurrentDC)(VOID);
    BOOL(WINAPI* glMakeCurrent)(HDC, HGLRC);
    BOOL(WINAPI* glShareLists)(HGLRC, HGLRC);
    BOOL(WINAPI* glUseFontBitmapsA)(HDC, DWORD, DWORD, DWORD);
    const char* (WINAPI* glGetExtensionsStringARB)(HDC hdc);
    HGLRC(WINAPI* glCreateContextAttribsARB) (HDC hDC, HGLRC hShareContext, const int* attribList);
    BOOL(WINAPI* glChoosePixelFormatARB) (HDC hdc, const int* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats);
    BOOL(WINAPI* glSwapIntervalEXT) (int interval);
    int (WINAPI* glGetSwapIntervalEXT) (void);
} FcWGL_t;

typedef struct FcWGLContext_t {
    HGLRC m_context;
    HDC m_hdc;
} FcWGLContext_t;

static inline FcError_t FcWGL(FcWGL_t* wgl) {
    FcError_t m_error = FC_NO_ERROR;
    INT line = __LINE__;
    if (!wgl->m_handle)
        wgl->m_handle = LoadLibraryA("opengl32.dll");
    if (!wgl->m_handle) {
        line = __LINE__;
        goto fcwgl_error;
    }
    wgl->glGetProcAddress = (PROC(WINAPI*)(LPCSTR))GetProcAddress(wgl->m_handle, "wglGetProcAddress");
    if (!wgl->glGetProcAddress) goto fcwgl_error;
    wgl->glCopyContext = (BOOL(WINAPI*)(HGLRC, HGLRC, UINT))GetProcAddress(wgl->m_handle, "wglCopyContext");
    if (!wgl->glCopyContext) goto fcwgl_error;
    wgl->glCreateContext = (HGLRC(WINAPI*)(HDC))GetProcAddress(wgl->m_handle, "wglCreateContext");
    if (!wgl->glCreateContext) goto fcwgl_error;
    wgl->glCreateLayerContext = (HGLRC(WINAPI*)(HDC, INT))GetProcAddress(wgl->m_handle, "wglCreateLayerContext");
    if (!wgl->glCreateLayerContext) goto fcwgl_error;
    wgl->glDeleteContext = (BOOL(WINAPI*)(HGLRC))GetProcAddress(wgl->m_handle, "wglDeleteContext");
    if (!wgl->glDeleteContext) goto fcwgl_error;
    wgl->glGetCurrentContext = (HGLRC(WINAPI*)(VOID))GetProcAddress(wgl->m_handle, "wglGetCurrentContext");
    if (!wgl->glGetCurrentContext) goto fcwgl_error;
    wgl->glGetCurrentDC = (HDC(WINAPI*)(VOID))GetProcAddress(wgl->m_handle, "wglGetCurrentDC");
    if (!wgl->glGetCurrentDC) goto fcwgl_error;
    wgl->glMakeCurrent = (BOOL(WINAPI*)(HDC, HGLRC))GetProcAddress(wgl->m_handle, "wglMakeCurrent");
    if (!wgl->glMakeCurrent) goto fcwgl_error;
    wgl->glShareLists = (BOOL(WINAPI*)(HGLRC, HGLRC))GetProcAddress(wgl->m_handle, "wglShareLists");
    if (!wgl->glShareLists) goto fcwgl_error;
    wgl->glUseFontBitmapsA = (BOOL(WINAPI*)(HDC, DWORD, DWORD, DWORD))GetProcAddress(wgl->m_handle, "wglUseFontBitmapsA");
    if (!wgl->glUseFontBitmapsA) goto fcwgl_error;

    return m_error;
fcwgl_error:
    getLastErrorMessage(line, __FILE__);
    exit(0);
}

static inline void setPixelFormat(HWND hwnd, FcWGLContext_t* wgl, INT* format) {
    INT line;
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
    if (!wgl->m_hdc)
        if (!(wgl->m_hdc = GetWindowDC(hwnd))) {
            line = __LINE__;
            goto fcwgl_error;
        }
    if (!*format)
        if (!(*format = ChoosePixelFormat(wgl->m_hdc, &pfd))) {
            line = __LINE__;
            goto fcwgl_error;
        }
    if (!DescribePixelFormat(wgl->m_hdc, *format, sizeof(pfd), &pfd)) {
        line = __LINE__;
        goto fcwgl_error;
    }
    if (!SetPixelFormat(wgl->m_hdc, *format, &pfd)) {
        line = __LINE__;
        goto fcwgl_error;
    }
    return;
fcwgl_error:
    getLastErrorMessage(line, __FILE__);
    exit(0);
}
//"WGL_ARB_pixel_format"
//"WGL_ARB_multisample"
static inline int FcWGL_supportExtension(const char* extensions, const char* find) {


    while (extensions != NULL) {
        char* next = strstr(extensions, find);
        if (next == NULL)
            return 0;
        next = next + strlen(find);
        if (*next == ' ')
            return 1;
        extensions = next;
    }
    return 0;
}
static inline void FcWGL_initDebugContext(FcWGL_t* wgl, FcWGLContext_t* context, HWND hwnd) {
    char* file;
    HGLRC HRC_tmp;
    INT line;
    INT pixelFormat = 0;
    UINT numberFormats = 0;
    UINT base = 0;
    int pixelFormats[32];
    float fAttributes[] = { 0,0 };
    const int attributeList[] =
    {
         WGL_DRAW_TO_WINDOW_ARB,		GL_TRUE,
         WGL_DRAW_TO_BITMAP_ARB,		GL_FALSE,
         WGL_ACCELERATION_ARB,			WGL_FULL_ACCELERATION_ARB,
         WGL_NEED_PALETTE_ARB,			GL_FALSE,
         WGL_NEED_SYSTEM_PALETTE_ARB,	GL_FALSE, //256
         WGL_SWAP_LAYER_BUFFERS_ARB,	GL_FALSE,
         WGL_SWAP_METHOD_ARB,           WGL_SWAP_UNDEFINED_ARB,
         //WGL_NUMBER_OVERLAYS_ARB        integer     minimum
         //WGL_NUMBER_UNDERLAYS_ARB       integer     minimum
         WGL_SHARE_DEPTH_ARB,           GL_FALSE,
         WGL_SHARE_STENCIL_ARB,         GL_FALSE,
         WGL_SHARE_ACCUM_ARB,           GL_FALSE,
         WGL_SUPPORT_GDI_ARB,           GL_FALSE,
         WGL_SUPPORT_OPENGL_ARB,		GL_TRUE,
         WGL_DOUBLE_BUFFER_ARB,			GL_TRUE,
         WGL_STEREO_ARB,				GL_FALSE,
         WGL_PIXEL_TYPE_ARB,            WGL_TYPE_RGBA_ARB,
         WGL_COLOR_BITS_ARB,			32,
         WGL_RED_BITS_ARB,				8,
         WGL_GREEN_BITS_ARB,			8,
         WGL_BLUE_BITS_ARB,				8,
         WGL_ALPHA_BITS_ARB,			8,
         WGL_ACCUM_BITS_ARB,			0,
         WGL_ACCUM_RED_BITS_ARB,		0,
         WGL_ACCUM_GREEN_BITS_ARB,		0,
         WGL_ACCUM_BLUE_BITS_ARB,		0,
         WGL_ACCUM_ALPHA_BITS_ARB,		0,
         WGL_DEPTH_BITS_ARB,			32,
         WGL_STENCIL_BITS_ARB,			0,
         WGL_AUX_BUFFERS_ARB,			0,
         0, 0
    };
    const int contextList[] =
    {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
            0
    };

    setPixelFormat(hwnd, context, &pixelFormat);
    if (context->m_context != NULL) {
        if (!wgl->glMakeCurrent(NULL, NULL)) {
            file = __FILE__;
            line = __LINE__;
            goto fcwgl_error;
        }
        if (!wgl->glDeleteContext(context->m_context)) {
            file = __FILE__;
            line = __LINE__;
            goto fcwgl_error;
        }
    }
    if ((HRC_tmp = wgl->glCreateContext(context->m_hdc)) == 0) {
        file = __FILE__;
        line = __LINE__;
        goto fcwgl_error;
    }
    if (!wgl->glMakeCurrent(context->m_hdc, HRC_tmp)) {
        file = __FILE__;
        line = __LINE__;
        goto fcwgl_error;
    }

    wgl->glGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wgl->glGetProcAddress("wglGetExtensionsStringARB");
    if (!wgl->glGetExtensionsStringARB) goto fcwgl_error;
    wgl->glCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wgl->glGetProcAddress("wglCreateContextAttribsARB");
    if (!wgl->glCreateContextAttribsARB) goto fcwgl_error;
    wgl->glChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wgl->glGetProcAddress("wglChoosePixelFormatARB");
    if (!wgl->glChoosePixelFormatARB) goto fcwgl_error;
    wgl->glSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wgl->glGetProcAddress("wglSwapIntervalEXT");
    if (!wgl->glSwapIntervalEXT) goto fcwgl_error;
    wgl->glGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wgl->glGetProcAddress("wglGetSwapIntervalEXT");
    if (!wgl->glGetSwapIntervalEXT) goto fcwgl_error;
    file = get_OpenGL_functions(wgl->m_handle, wgl->glGetProcAddress);

    //const char* m_ext = wgl->glGetExtensionsStringARB(context->m_hdc);

    //if (!wgl->glChoosePixelFormatARB(context->m_hdc, attributeList, fAttributes, 32, pixelFormats, &numberFormats)) {
    //	file = __FILE__;
    //	line = __LINE__;
    //	goto fcwgl_error;
    //}
    //if (pixelFormats[0] >= numberFormats)
    //	pixelFormats[0] = pixelFormat;
    if (!wgl->glMakeCurrent(NULL, NULL)) {
        file = __FILE__;
        line = __LINE__;
        goto fcwgl_error;
    }
    //setPixelFormat(hwnd, context, &pixelFormats[0]);
    if ((context->m_context = wgl->glCreateContextAttribsARB(context->m_hdc, NULL, contextList)) == 0) {
        file = __FILE__;
        line = __LINE__;
        goto fcwgl_error;
    }
    if (!wgl->glDeleteContext(HRC_tmp)) {
        file = __FILE__;
        line = __LINE__;
        goto fcwgl_error;
    }
    if (!wgl->glMakeCurrent(context->m_hdc, context->m_context)) {
        file = __FILE__;
        line = __LINE__;
        goto fcwgl_error;
    }
    if (file = (char*)get_OpenGL_functions(wgl->m_handle, wgl->glGetProcAddress)) {
        line = __LINE__;
        goto fcwgl_error;
    }
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    return;
fcwgl_error:
    getLastErrorMessage(line, file);
    exit(0);
}

static inline FcError_t FcWGL_initContext(FcWGL_t* wgl, FcWGLContext_t* context, HWND hwnd) {
    INT line = 0;
    const char* file = __FILE__;
    setPixelFormat(hwnd, context, 0);
    if ((context->m_context = wgl->glCreateContext(context->m_hdc)) == 0) {
        line = __LINE__;
        goto fcwgl_error;
    }
    if (!wgl->glMakeCurrent(context->m_hdc, context->m_context)) {
        line = __LINE__;
        goto fcwgl_error;
    }
    wgl->glCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wgl->glGetProcAddress("wglCreateContextAttribsARB");
    if (!wgl->glCreateContextAttribsARB) goto fcwgl_error;
    wgl->glGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wgl->glGetProcAddress("wglGetExtensionsStringARB");
    if (!wgl->glGetExtensionsStringARB) goto fcwgl_error;
    wgl->glChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wgl->glGetProcAddress("wglChoosePixelFormatARB");
    if (!wgl->glChoosePixelFormatARB) goto fcwgl_error;
    wgl->glSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wgl->glGetProcAddress("wglSwapIntervalEXT");
    if (!wgl->glSwapIntervalEXT) goto fcwgl_error;
    wgl->glGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wgl->glGetProcAddress("wglGetSwapIntervalEXT");
    if (!wgl->glGetSwapIntervalEXT) goto fcwgl_error;
    file = get_OpenGL_functions(wgl->m_handle, wgl->glGetProcAddress);
    if (file) {
        line = __LINE__;
        goto fcwgl_error;
    }
    return FC_NO_ERROR;
fcwgl_error:
    getLastErrorMessage(line, file);
    exit(0);
}
static inline FcError_t FcWGL_freeContext(FcWGL_t* wgl, FcWGLContext_t* context, HWND hwnd) {
    if (context->m_context) {
        if (!wgl->glMakeCurrent(context->m_hdc, NULL))
            getLastErrorMessage(__LINE__, __FILE__),
            exit(0);
        ReleaseDC(hwnd, context->m_hdc);
        if (!wgl->glDeleteContext(context->m_context))
            getLastErrorMessage(__LINE__, __FILE__),
            exit(0);
        context->m_context = NULL;
        context->m_hdc = NULL;
    }
}

static inline void FcWGL_free(FcWGL_t* wgl) {
    if (wgl->m_handle)
        FreeLibrary(wgl->m_handle);
    ZeroMemory(wgl, sizeof(*wgl));
}

#endif
#endif