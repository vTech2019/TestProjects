
#ifdef linux
#ifndef __FCGLX_H_
#define __FCGLX_H_
#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#endif

#include "include/FcError.h"

#include <GL/glcorearb.h>
#include <GL/glx.h>
#include <GL/glxtokens.h>

#include <dlfcn.h>
#include <stdio.h>

/* GLX 1.0 and later */
typedef XVisualInfo *(*PFNGLXCHOOSEVISUALPROC)(Display *dpy, int screen, int *attribList);

typedef GLXContext (*PFNGLXCREATECONTEXTPROC)(Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct);

typedef void (*PFNGLXDESTROYCONTEXTPROC)(Display *dpy, GLXContext ctx);

typedef Bool (*PFNGLXMAKECURRENTPROC)(Display *dpy, GLXDrawable drawable, GLXContext ctx);

typedef void (*PFNGLXCOPYCONTEXTPROC)(Display *dpy, GLXContext src, GLXContext dst, unsigned long mask);

typedef void (*PFNGLXSWAPBUFFERSPROC)(Display *dpy, GLXDrawable drawable);

typedef GLXPixmap (*PFNGLXCREATEGLXPIXMAPPROC)(Display *dpy, XVisualInfo *visual, Pixmap pixmap);

typedef void (*PFNGLXDETROYGLXPIXMAPPROC)(Display *dpy, GLXPixmap pixmap);

typedef Bool (*PFNGLXQUERYEXTENSIONPROC)(Display *dpy, int *errorb, int *event);

typedef Bool (*PFNGLXQUERYVERSIONPROC)(Display *dpy, int *maj, int *min);

typedef Bool (*PFNGLXISDIRECTPROC)(Display *dpy, GLXContext ctx);

typedef int (*PFNGLXGETCONFIGPROC)(Display *dpy, XVisualInfo *visual, int attrib, int *value);

typedef GLXContext (*PFNGLXGETCURRENTCONTEXTPROC)(void);

typedef GLXDrawable (*PFNGLXGETCURRENTDRAWABLEPROC)(void);

typedef void (*PFNGLXWAITGLPROC)(void);

typedef void (*PFNGLXWAITXPROC)(void);

typedef void (*PFNGLXUSEXFONTPROC)(Font font, int first, int count, int list);

/* GLX 1.1 and later */
typedef const char *(*PFNGLXQUERYEXTENSIONSSTRINGPROC)(Display *dpy, int screen);

typedef const char *(*PFNGLXQUERYSERVERSTRINGPROC)(Display *dpy, int screen, int name);

typedef const char *(*PFNGLXGETCLIENTSTRINGPROC)(Display *dpy, int name);

/* GLX 1.2 and later */
typedef Display *(*PFNGLXGETCURRENTDISPLAYPROC)(void);

/* GLX 1.3 and later */
typedef GLXFBConfig *(*PFNGLXGETFBCONFIGSPROC)(Display *dpy, int screen, int *nelements);

typedef GLXFBConfig *(*PFNGLXCHOOSEFBCONFIGPROC)(Display *dpy, int screen, const int *attrib_list, int *nelements);

typedef int (*PFNGLXGETFBCONFIGATTRIBPROC)(Display *dpy, GLXFBConfig config, int attribute, int *value);

typedef XVisualInfo *(*PFNGLXGETVISUALFROMFBCONFIGPROC)(Display *dpy, GLXFBConfig config);

typedef GLXWindow (*PFNGLXCREATEWINDOWPROC)(Display *dpy, GLXFBConfig config, Window win, const int *attrib_list);

typedef void (*PFNGLXDESTROYWINDOWPROC)(Display *dpy, GLXWindow win);

typedef GLXPixmap (*PFNGLXCREATEPIXMAPPROC)(Display *dpy, GLXFBConfig config, Pixmap pixmap, const int *attrib_list);

typedef void (*PFNGLXDESTROYPIXMAPPROC)(Display *dpy, GLXPixmap pixmap);

typedef GLXPbuffer (*PFNGLXCREATEPBUFFERPROC)(Display *dpy, GLXFBConfig config, const int *attrib_list);

typedef void (*PFNGLXDESTROYPBUFFERPROC)(Display *dpy, GLXPbuffer pbuf);

typedef void (*PFNGLXQUERYDRAWABLEPROC)(Display *dpy, GLXDrawable draw, int attribute, unsigned int *value);

typedef GLXContext (*PFNGLXCREATENEWCONTEXTPROC)(Display *dpy, GLXFBConfig config, int render_type,
                                                 GLXContext share_list, Bool direct);

typedef Bool (*PFNGLXMAKECONTEXTCURRENTPROC)(Display *dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx);

typedef GLXDrawable (*PFNGLXGETCURRENTREADDRAWABLEPROC)(void);

typedef Display *(*PFNGLXGETCURRENTDISPLAYPROC)(void);

typedef int (*PFNGLXQUERYCONTEXTPROC)(Display *dpy, GLXContext ctx, int attribute, int *value);

typedef void (*PFNGLXSELECTEVENTPROC)(Display *dpy, GLXDrawable draw, unsigned long event_mask);

typedef void (*PFNGLXGETSELECTEDEVENTPROC)(Display *dpy, GLXDrawable draw, unsigned long *event_mask);

typedef struct FcGLXContext_t {
    GLXContext context;
    GLXWindow window;
} FcGLXContext_t;

typedef struct FcGLX_t {
    void *m_handle;

    //1.0
    PFNGLXCHOOSEVISUALPROC m_glXChooseVisual;
    PFNGLXCREATECONTEXTPROC m_glXCreateContext;
    PFNGLXDESTROYCONTEXTPROC m_glXDestroyContext;
    PFNGLXMAKECURRENTPROC m_glXMakeCurrent;
    PFNGLXCOPYCONTEXTPROC m_glXCopyContext;
    PFNGLXSWAPBUFFERSPROC m_glXSwapBuffers;
    PFNGLXCREATEGLXPIXMAPPROC m_glXCreateGLXPixmap;
    PFNGLXDETROYGLXPIXMAPPROC m_glXDestroyGLXPixmap;
    PFNGLXQUERYEXTENSIONPROC m_glXQueryExtension;
    PFNGLXQUERYVERSIONPROC m_glXQueryVersion;
    PFNGLXISDIRECTPROC m_glXIsDirect;
    PFNGLXGETCONFIGPROC m_glXGetConfig;
    PFNGLXGETCURRENTCONTEXTPROC m_glXGetCurrentContext;
    PFNGLXGETCURRENTDRAWABLEPROC m_glXGetCurrentDrawable;
    PFNGLXWAITGLPROC m_glXWaitGL;
    PFNGLXWAITXPROC m_glXWaitX;
    PFNGLXUSEXFONTPROC m_glXUseXFont;
    //1.1
    PFNGLXQUERYEXTENSIONSSTRINGPROC m_glXQueryExtensionsString;
    PFNGLXQUERYSERVERSTRINGPROC m_glXQueryServerString;
    PFNGLXGETCLIENTSTRINGPROC m_glXGetClientString;
    //1.2
    PFNGLXGETCURRENTDISPLAYPROC m_glXGetCurrentDisplay;
    //1.3
    PFNGLXCHOOSEFBCONFIGPROC m_glXChooseFBConfig;
    PFNGLXGETFBCONFIGATTRIBPROC m_glXGetFBConfigAttrib;
    PFNGLXGETFBCONFIGSPROC m_glXGetFBConfigs;
    PFNGLXGETVISUALFROMFBCONFIGPROC m_glXGetVisualFromFBConfig;
    PFNGLXCREATEWINDOWPROC m_glXCreateWindow;
    PFNGLXDESTROYWINDOWPROC m_glXDestroyWindow;
    PFNGLXCREATEPIXMAPPROC m_glXCreatePixmap;
    PFNGLXDESTROYPIXMAPPROC m_glXDestroyPixmap;
    PFNGLXCREATEPBUFFERPROC m_glXCreatePbuffer;
    PFNGLXDESTROYPBUFFERPROC m_glXDestroyPbuffer;
    PFNGLXQUERYDRAWABLEPROC m_glXQueryDrawable;
    PFNGLXCREATENEWCONTEXTPROC m_glXCreateNewContext;
    PFNGLXMAKECONTEXTCURRENTPROC m_glXMakeContextCurrent;
    PFNGLXGETCURRENTREADDRAWABLEPROC m_glXGetCurrentReadDrawable;
    PFNGLXQUERYCONTEXTPROC m_glXQueryContext;
    PFNGLXSELECTEVENTPROC m_glXSelectEvent;
    PFNGLXGETSELECTEDEVENTPROC m_glXGetSelectedEvent;
    //1.4
    PFNGLXGETPROCADDRESSPROC m_glXGetProcAddress;
    //ARB
    PFNGLXCREATECONTEXTATTRIBSARBPROC m_glXCreateContextAttribsARB;
    PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT;

} FcGLX_t;


GLenum glCheckError(const char *file, int line);

#define Fc_glCheckError() glCheckError(__FILE__, __LINE__)

void APIENTRY FcGLX_glDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity,
                                   GLsizei length, const GLchar *message, const void *userParam);

static inline FcError_t FcGLX(FcGLX_t *glx);

static inline FcError_t FcGLX_chooseVisual(const FcGLX_t *glx, Display *display, int screenId, XVisualInfo **visual,
                                           Colormap *color);


static inline FcError_t
FcGLX_initDebugContext(FcGLX_t *glx, FcGLXContext_t *context, Display *display, XVisualInfo *visual, Window window);

static inline FcError_t
FcGLX_initContext(FcGLX_t *glx, FcGLXContext_t *context, Display *display, XVisualInfo *visual, Window window);

static inline FcError_t FcGLX_freeContext(FcGLX_t *glx, FcGLXContext_t *context, Display *display);

static inline FcError_t FcGLX_free(FcGLX_t *glx);


static inline FcError_t FcGLX(FcGLX_t *glx) {
    unsigned i;
    const char *m_libs[] = {
            "libGL.so.1",
            "libGL.so",
            "libGL.so.1.0.0",
            "libGL-1.so"
    };
    for (i = 0; i < sizeof(*glx); i++)
        ((unsigned char *) glx)[i] = 0;
    for (i = 0; i < 4 && glx->m_handle == NULL; i++)
        glx->m_handle = dlopen(m_libs[i], RTLD_LAZY | RTLD_LOCAL);
    if (glx->m_handle == NULL)
        return FC_GLX_LoadLibrary;

    glx->m_glXChooseVisual = (PFNGLXCHOOSEVISUALPROC) dlsym(glx->m_handle, "glXChooseVisual");
    glx->m_glXCreateContext = (PFNGLXCREATECONTEXTPROC) dlsym(glx->m_handle, "glXCreateContext");
    glx->m_glXDestroyContext = (PFNGLXDESTROYCONTEXTPROC) dlsym(glx->m_handle, "glXDestroyContext");
    glx->m_glXMakeCurrent = (PFNGLXMAKECURRENTPROC) dlsym(glx->m_handle, "glXMakeCurrent");
    glx->m_glXCopyContext = (PFNGLXCOPYCONTEXTPROC) dlsym(glx->m_handle, "glXCopyContext");
    glx->m_glXSwapBuffers = (PFNGLXSWAPBUFFERSPROC) dlsym(glx->m_handle, "glXSwapBuffers");
    glx->m_glXCreateGLXPixmap = (PFNGLXCREATEGLXPIXMAPPROC) dlsym(glx->m_handle, "glXCreateGLXPixmap");
    glx->m_glXDestroyGLXPixmap = (PFNGLXDETROYGLXPIXMAPPROC) dlsym(glx->m_handle, "glXDestroyGLXPixmap");
    glx->m_glXQueryExtension = (PFNGLXQUERYEXTENSIONPROC) dlsym(glx->m_handle, "glXQueryExtension");
    glx->m_glXQueryVersion = (PFNGLXQUERYVERSIONPROC) dlsym(glx->m_handle, "glXQueryVersion");
    glx->m_glXIsDirect = (PFNGLXISDIRECTPROC) dlsym(glx->m_handle, "glXIsDirect");
    glx->m_glXGetConfig = (PFNGLXGETCONFIGPROC) dlsym(glx->m_handle, "glXGetConfig");
    glx->m_glXGetCurrentContext = (PFNGLXGETCURRENTCONTEXTPROC) dlsym(glx->m_handle, "glXGetCurrentContext");
    glx->m_glXGetCurrentDrawable = (PFNGLXGETCURRENTDRAWABLEPROC) dlsym(glx->m_handle, "glXGetCurrentDrawable");
    glx->m_glXWaitGL = (PFNGLXWAITGLPROC) dlsym(glx->m_handle, "glXWaitGL");
    glx->m_glXWaitX = (PFNGLXWAITXPROC) dlsym(glx->m_handle, "glXWaitX");
    glx->m_glXUseXFont = (PFNGLXUSEXFONTPROC) dlsym(glx->m_handle, "glXUseXFont");

    glx->m_glXQueryExtensionsString = (PFNGLXQUERYEXTENSIONSSTRINGPROC) dlsym(glx->m_handle,
                                                                              "glXQueryExtensionsString");
    glx->m_glXQueryServerString = (PFNGLXQUERYSERVERSTRINGPROC) dlsym(glx->m_handle, "glXQueryServerString");
    glx->m_glXGetClientString = (PFNGLXGETCLIENTSTRINGPROC) dlsym(glx->m_handle, "glXGetClientString");

    glx->m_glXGetCurrentDisplay = (PFNGLXGETCURRENTDISPLAYPROC) dlsym(glx->m_handle, "glXGetCurrentDisplay");

    glx->m_glXChooseFBConfig = (PFNGLXCHOOSEFBCONFIGPROC) dlsym(glx->m_handle, "glXChooseFBConfig");
    glx->m_glXGetFBConfigAttrib = (PFNGLXGETFBCONFIGATTRIBPROC) dlsym(glx->m_handle, "glXGetFBConfigAttrib");
    glx->m_glXGetFBConfigs = (PFNGLXGETFBCONFIGSPROC) dlsym(glx->m_handle, "glXGetFBConfigs");
    glx->m_glXGetVisualFromFBConfig = (PFNGLXGETVISUALFROMFBCONFIGPROC) dlsym(glx->m_handle,
                                                                              "glXGetVisualFromFBConfig");
    glx->m_glXCreateWindow = (PFNGLXCREATEWINDOWPROC) dlsym(glx->m_handle, "glXCreateWindow");
    glx->m_glXDestroyWindow = (PFNGLXDESTROYWINDOWPROC) dlsym(glx->m_handle, "glXDestroyWindow");
    glx->m_glXCreatePixmap = (PFNGLXCREATEPIXMAPPROC) dlsym(glx->m_handle, "glXCreatePixmap");
    glx->m_glXDestroyPixmap = (PFNGLXDESTROYPIXMAPPROC) dlsym(glx->m_handle, "glXDestroyPixmap");
    glx->m_glXCreatePbuffer = (PFNGLXCREATEPBUFFERPROC) dlsym(glx->m_handle, "glXCreatePbuffer");
    glx->m_glXDestroyPbuffer = (PFNGLXDESTROYPBUFFERPROC) dlsym(glx->m_handle, "glXDestroyPbuffer");
    glx->m_glXQueryDrawable = (PFNGLXQUERYDRAWABLEPROC) dlsym(glx->m_handle, "glXQueryDrawable");
    glx->m_glXCreateNewContext = (PFNGLXCREATENEWCONTEXTPROC) dlsym(glx->m_handle, "glXCreateNewContext");
    glx->m_glXMakeContextCurrent = (PFNGLXMAKECONTEXTCURRENTPROC) dlsym(glx->m_handle, "glXMakeContextCurrent");
    glx->m_glXGetCurrentReadDrawable = (PFNGLXGETCURRENTREADDRAWABLEPROC) dlsym(glx->m_handle,
                                                                                "glXGetCurrentReadDrawable");
    glx->m_glXQueryContext = (PFNGLXQUERYCONTEXTPROC) dlsym(glx->m_handle, "glXQueryContext");
    glx->m_glXSelectEvent = (PFNGLXSELECTEVENTPROC) dlsym(glx->m_handle, "glXSelectEvent");
    glx->m_glXGetSelectedEvent = (PFNGLXGETSELECTEDEVENTPROC) dlsym(glx->m_handle, "glXGetSelectedEvent");

    glx->m_glXGetProcAddress = (PFNGLXGETPROCADDRESSPROC) dlsym(glx->m_handle, "glXGetProcAddress");

    if (glx->m_glXGetProcAddress == NULL)
        return FC_GLX_Version14IsRequired;

    //GLX_ARB_create_context_profile

    glx->m_glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC) glx->m_glXGetProcAddress(
            (const GLubyte *) "glXCreateContextAttribsARB");


    return FC_NO_ERROR;
}

static inline FcError_t FcGLX_free(FcGLX_t *glx) {
    FcError_t mError;
    unsigned i;
    mError = dlclose(glx->m_handle);
    for (i = 0; i < sizeof(*glx); i++)
        ((unsigned char *) glx)[i] = 0;
    return mError;
}

/*static GLFWbool chooseGLXFBConfig(const _GLFWfbconfig* desired,
                                  GLXFBConfig* result)
{
    GLXFBConfig* nativeConfigs;
    _GLFWfbconfig* usableConfigs;
    const _GLFWfbconfig* closest;
    int i, nativeCount, usableCount;
    const char* vendor;
    GLFWbool trustWindowBit = GLFW_TRUE;


    vendor = glXGetClientString(_glfw.x11.display, GLX_VENDOR);
    if (vendor && strcmp(vendor, "Chromium") == 0)
        trustWindowBit = GLFW_FALSE;

    nativeConfigs =
            glXGetFBConfigs(_glfw.x11.display, _glfw.x11.screen, &nativeCount);
    if (!nativeConfigs || !nativeCount)
    {
        _glfwInputError(GLFW_API_UNAVAILABLE, "GLX: No GLXFBConfigs returned");
        return GLFW_FALSE;
    }

    usableConfigs = calloc(nativeCount, sizeof(_GLFWfbconfig));
    usableCount = 0;

    for (i = 0;  i < nativeCount;  i++)
    {
        const GLXFBConfig n = nativeConfigs[i];
        _GLFWfbconfig* u = usableConfigs + usableCount;

        // Only consider RGBA GLXFBConfigs
        if (!(getGLXFBConfigAttrib(n, GLX_RENDER_TYPE) & GLX_RGBA_BIT))
            continue;

        // Only consider window GLXFBConfigs
        if (!(getGLXFBConfigAttrib(n, GLX_DRAWABLE_TYPE) & GLX_WINDOW_BIT))
        {
            if (trustWindowBit)
                continue;
        }

        if (getGLXFBConfigAttrib(n, GLX_DOUBLEBUFFER) != desired->doublebuffer)
            continue;

        if (desired->transparent)
        {
            XVisualInfo* vi = glXGetVisualFromFBConfig(_glfw.x11.display, n);
            if (vi)
            {
                u->transparent = _glfwIsVisualTransparentX11(vi->visual);
                XFree(vi);
            }
        }

        u->redBits = getGLXFBConfigAttrib(n, GLX_RED_SIZE);
        u->greenBits = getGLXFBConfigAttrib(n, GLX_GREEN_SIZE);
        u->blueBits = getGLXFBConfigAttrib(n, GLX_BLUE_SIZE);

        u->alphaBits = getGLXFBConfigAttrib(n, GLX_ALPHA_SIZE);
        u->depthBits = getGLXFBConfigAttrib(n, GLX_DEPTH_SIZE);
        u->stencilBits = getGLXFBConfigAttrib(n, GLX_STENCIL_SIZE);

        u->accumRedBits = getGLXFBConfigAttrib(n, GLX_ACCUM_RED_SIZE);
        u->accumGreenBits = getGLXFBConfigAttrib(n, GLX_ACCUM_GREEN_SIZE);
        u->accumBlueBits = getGLXFBConfigAttrib(n, GLX_ACCUM_BLUE_SIZE);
        u->accumAlphaBits = getGLXFBConfigAttrib(n, GLX_ACCUM_ALPHA_SIZE);

        u->auxBuffers = getGLXFBConfigAttrib(n, GLX_AUX_BUFFERS);

        if (getGLXFBConfigAttrib(n, GLX_STEREO))
            u->stereo = GLFW_TRUE;

        if (_glfw.glx.ARB_multisample)
            u->samples = getGLXFBConfigAttrib(n, GLX_SAMPLES);

        if (_glfw.glx.ARB_framebuffer_sRGB || _glfw.glx.EXT_framebuffer_sRGB)
            u->sRGB = getGLXFBConfigAttrib(n, GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB);

        u->handle = (uintptr_t) n;
        usableCount++;
    }

    closest = _glfwChooseFBConfig(desired, usableConfigs, usableCount);
    if (closest)
        *result = (GLXFBConfig) closest->handle;

    XFree(nativeConfigs);
    free(usableConfigs);

    return closest != NULL;
}
*/

static inline FcError_t FcGLX_chooseVisual(const FcGLX_t *glx,
                                           Display *display,
                                           int screenId,
                                           XVisualInfo **visual,
                                           Colormap *color) {
    GLXFBConfig *mFBConfigs;
    int mCount, i;
    FcError_t mError;
    mError = FC_NO_ERROR;
    mFBConfigs = NULL;

    mFBConfigs = glx->m_glXGetFBConfigs(display, screenId, &mCount);
    if (!mFBConfigs || !mCount) {
        mError = FC_GLX_FBConfigsNotFound;
        goto gError;
    }
    int mRenderType;
    int mWindow;
    int mDoublebuffer;
    int mRGBA_DS_ARGBA[4 + 2 + 4];
    for (i = 0; i < mCount; i++) {
        const GLXFBConfig n = mFBConfigs[i];

        glx->m_glXGetFBConfigAttrib(display, n, GLX_RENDER_TYPE,        &mRenderType);
        glx->m_glXGetFBConfigAttrib(display, n, GLX_DRAWABLE_TYPE,      &mWindow);
        glx->m_glXGetFBConfigAttrib(display, n, GLX_DOUBLEBUFFER,       &mDoublebuffer);
        glx->m_glXGetFBConfigAttrib(display, n, GLX_RED_SIZE,           mRGBA_DS_ARGBA + 0);
        glx->m_glXGetFBConfigAttrib(display, n, GLX_GREEN_SIZE,         mRGBA_DS_ARGBA + 1);
        glx->m_glXGetFBConfigAttrib(display, n, GLX_BLUE_SIZE,          mRGBA_DS_ARGBA + 2);
        glx->m_glXGetFBConfigAttrib(display, n, GLX_ALPHA_SIZE,         mRGBA_DS_ARGBA + 3);
        glx->m_glXGetFBConfigAttrib(display, n, GLX_DEPTH_SIZE,         mRGBA_DS_ARGBA + 4);
        glx->m_glXGetFBConfigAttrib(display, n, GLX_STENCIL_SIZE,       mRGBA_DS_ARGBA + 5);
        glx->m_glXGetFBConfigAttrib(display, n, GLX_ACCUM_RED_SIZE,     mRGBA_DS_ARGBA + 6);
        glx->m_glXGetFBConfigAttrib(display, n, GLX_ACCUM_GREEN_SIZE,   mRGBA_DS_ARGBA + 7);
        glx->m_glXGetFBConfigAttrib(display, n, GLX_ACCUM_BLUE_SIZE,    mRGBA_DS_ARGBA + 8);
        glx->m_glXGetFBConfigAttrib(display, n, GLX_ACCUM_ALPHA_SIZE,   mRGBA_DS_ARGBA + 9);

        u->auxBuffers = glx->m_glXGetFBConfigAttrib(display, n, GLX_AUX_BUFFERS);
        if (!(mRenderType & GLX_RGBA_BIT))
            continue;
        if (!(mWindow & GLX_WINDOW_BIT))
            continue;
        if (!(mDoublebuffer))
            continue;


        if (desired->transparent) {
            XVisualInfo *vi = glXGetVisualFromFBConfig(_glfw.x11.display, n);
            if (vi) {
                u->transparent = _glfwIsVisualTransparentX11(vi->visual);
                XFree(vi);
            }
        }

        if (getGLXFBConfigAttrib(n, GLX_STEREO))
            u->stereo = GLFW_TRUE;

        if (_glfw.glx.ARB_multisample)
            u->samples = getGLXFBConfigAttrib(n, GLX_SAMPLES);

        if (_glfw.glx.ARB_framebuffer_sRGB || _glfw.glx.EXT_framebuffer_sRGB)
            u->sRGB = getGLXFBConfigAttrib(n, GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB);

        u->handle = (uintptr_t) n;
        usableCount++;
    }

    closest = _glfwChooseFBConfig(desired, usableConfigs, usableCount);
    if (closest)
        *result = (GLXFBConfig) closest->handle;


    //result = glXGetVisualFromFBConfig(display, native);
    //if (!result)
    //{
    //}

    gError:
    if (mFBConfigs) XFree(mFBConfigs);
    return mError;
}

/*static inline XVisualInfo *FcGLX_chooseVisual(FcGLX_t *glx, Display *display, int screenId) {
    int attributes[] = {
            GLX_RGBA,
            GLX_RED_SIZE, 1,
            GLX_GREEN_SIZE, 1,
            GLX_BLUE_SIZE, 1,
            GLX_DOUBLEBUFFER, True,
            GLX_DEPTH_SIZE, 24,
            None };
    int att[] = {
            GLX_USE_GL, True,
            GLX_BUFFER_SIZE, 0,
            GLX_LEVEL, 0,
            GLX_RGBA, True,
            GLX_DOUBLEBUFFER, False,
            GLX_STEREO, False,
            GLX_AUX_BUFFERS, 0,
            GLX_RED_SIZE, 0,
            GLX_GREEN_SIZE, 0,
            GLX_BLUE_SIZE, 0,
            GLX_ALPHA_SIZE, 0,
            GLX_DEPTH_SIZE, 0,
            GLX_STENCIL_SIZE, 0,
            GLX_ACCUM_RED_SIZE, 0,
            GLX_ACCUM_GREEN_SIZE, 0,
            GLX_ACCUM_BLUE_SIZE, 0,
            GLX_ACCUM_ALPHA_SIZE, 0,
            GLX_SAMPLE_BUFFERS, 0,
            GLX_SAMPLES, 0,
            None };
    XVisualInfo *mInfo = glx->m_glXChooseVisual(display, screenId, NULL);
    XFree(mInfo);
    return glx->m_glXChooseVisual(display, screenId, att);
}*/


static inline FcError_t
FcGLX_initDebugContext(FcGLX_t *glx, FcGLXContext_t *context, Display *display, XVisualInfo *visual, Window window) {
    int i, n;
    GLint flags;
    FcError_t m_error;
    int m_FBConfigAttrib[] = {
            GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
            GLX_RENDER_TYPE, GLX_RGBA_BIT,
            GLX_RED_SIZE, 8,
            GLX_GREEN_SIZE, 8,
            GLX_BLUE_SIZE, 8,
            GLX_DOUBLEBUFFER, True,
            GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
            GLX_X_RENDERABLE, True,
            None};
    int m_contextAttrib0[] = {
            GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
            0, 0
    };
    int m_contextAttrib1[] =
            {
                    GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
                    GLX_CONTEXT_MINOR_VERSION_ARB, 0,
                    GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
                    GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
                    0, 0
            };
    GLXFBConfig *m_FBConfigs = NULL;
    m_error = FC_NO_ERROR;
    if (glx->m_glXCreateContextAttribsARB == NULL) {
        m_error = FC_GLX_ARBCreateContextProfile;
        goto g_error;
    }

    m_FBConfigs = glx->m_glXChooseFBConfig(display, visual->screen, m_FBConfigAttrib, &n);

    if (n < 1) {
        m_error = FC_GLX_FBConfigsNotFound;
        goto g_error;
    }

    for (int aLowVer4 = 6; aLowVer4 >= 0 && context->context == NULL; --aLowVer4) {
        m_contextAttrib1[1] = 4;
        m_contextAttrib1[3] = aLowVer4;
        context->context = glx->m_glXCreateContextAttribsARB(display, *m_FBConfigs, NULL, True, m_contextAttrib1);
    }
    for (int aLowVer3 = 3; aLowVer3 >= 0 && context->context == NULL; --aLowVer3) {
        m_contextAttrib1[1] = 3;
        m_contextAttrib1[3] = aLowVer3;
        context->context = glx->m_glXCreateContextAttribsARB(display, *m_FBConfigs, NULL, True, m_contextAttrib1);
    }
    if (context->context == NULL)
        context->context = glx->m_glXCreateContextAttribsARB(display, *m_FBConfigs, NULL, True, m_contextAttrib0);
    if (context->context == NULL) {
        m_error = FC_GLX_ContextNotDebug;
        goto g_error;
    }
    XSync(display, False);
    if (!glx->m_glXIsDirect(display, context->context)) {
        m_error = FC_GLX_ContextNotDirect;
        goto g_error;
    }
    if (glXMakeCurrent(display, window, context->context) == False) {
        m_error = FC_GLX_MakeCurrent;
        goto g_error;
    }
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(FcGLX_glDebugMessage, NULL);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    }
    if (m_FBConfigs) XFree(m_FBConfigs);
    return m_error;
    g_error:
    if (context->context) FcGLX_freeContext(glx, context, display);
    if (m_FBConfigs) XFree(m_FBConfigs);
    return m_error;
}

static inline FcError_t
FcGLX_initContext(FcGLX_t *glx, FcGLXContext_t *context, Display *display, XVisualInfo *visual, Window window) {
    FcError_t m_error = FC_NO_ERROR;
    context->context = glx->m_glXCreateContext(display, visual, NULL, True);
    XSync(display, False);
    if (glx->m_glXIsDirect(display, context->context) == False) {
        m_error = FC_GLX_ContextNotDirect;
        goto g_error;
    }
    if (glx->m_glXMakeCurrent(display, window, context->context) == False) {
        m_error = FC_GLX_MakeCurrent;
        goto g_error;
    }
    return m_error;
    g_error:
    if (context->context) FcGLX_freeContext(glx, context, display);
    return m_error;
}

static inline FcError_t FcGLX_freeContext(FcGLX_t *glx, FcGLXContext_t *context, Display *display) {
    if (context->context)
        glXDestroyContext(display, context->context);
    if (context->window)
        glXDestroyWindow(display, context->window);
    return FC_NO_ERROR;
}

#endif //_FCGLX_H

#endif