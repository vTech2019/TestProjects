



#ifdef _WIN32
#ifndef __WINAPI_OPENGL_FUNCTIONS__
#define __WINAPI_OPENGL_FUNCTIONS__


#undef GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>
#include <gl/wglext.h>
#include <gl/glext.h>
#include <stdio.h>
#include <windows.h>



static void *winGetProcAddress(const char*name)
{
  void *p = (void *)wglGetProcAddress(name);
  if(p == 0 ||
    (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
    (p == (void*)-1) )
  {
    HMODULE module = LoadLibraryA("opengl32.dll");
    p = (void *)GetProcAddress(module, name);
    FreeLibrary(module);
  }

  return p;
}

PFNWGLGETEXTENSIONSSTRINGARBPROC    wglGetExtensionsStringARB;

static BOOL find_WGL_extensions(const char * pName, HDC hdc)
{
  if (!wglGetExtensionsStringARB)
    wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
  const char * extensions = (const char *)wglGetExtensionsStringARB(hdc);
  size_t size = strlen(pName);
  while(extensions)
  {
    if(!strncmp(extensions, pName, size) && (*(extensions + size)==0 || *(extensions + size)==' '))
      return TRUE;
    extensions=strchr(extensions,' ');
    if(extensions)
      extensions++;
  }
  return FALSE;
}

PFNGLGETSTRINGPROC glGetString;
static BOOL find_GL_extensions(const char * pName)
{
  if (!glGetString)
    glGetString = (PFNGLGETSTRINGPROC)winGetProcAddress("glGetString");
  const char * extensions = (const char *)glGetString(GL_EXTENSIONS);
  size_t size = strlen(pName);
  while(extensions)
  {
    if(!strncmp(extensions, pName, size) && (*(extensions + size)==0 || *(extensions + size)==' '))
      return TRUE;
    extensions=strchr(extensions,' ');
    if(extensions)
      extensions++;
  }
  return FALSE;
}

PFNGLGETINTEGERVPROC glGetIntegerv;
static BOOL find_GL_version(GLint majorVersion, GLint minorVersion)
{
    if (!glGetIntegerv)
        glGetIntegerv = (PFNGLGETINTEGERVPROC)winGetProcAddress("glGetIntegerv");
    GLint m_majorVersion = 0, m_minorVersion = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &m_majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &m_minorVersion);
    if (m_majorVersion > majorVersion)
        return TRUE;
    else if(m_majorVersion == majorVersion)
        if (m_minorVersion >= minorVersion) {
            return TRUE;
        }
    return FALSE;
}

PFNGLBINDBUFFERPROC                 glBindBuffer;
PFNGLBUFFERDATAPROC                 glBufferData;
PFNGLBUFFERSUBDATAPROC              glBufferSubData;
PFNGLDELETEBUFFERSPROC              glDeleteBuffers;
PFNGLGENBUFFERSPROC                 glGenBuffers;
PFNGLGETBUFFERPARAMETERIVARBPROC    glGetBufferParameteriv;
PFNGLGETBUFFERPOINTERVARBPROC       glGetBufferPointerv;
PFNGLGETBUFFERSUBDATAARBPROC        glGetBufferSubData;
PFNGLISBUFFERARBPROC                glIsBuffer;
PFNGLMAPBUFFERARBPROC               glMapBuffer;
PFNGLUNMAPBUFFERARBPROC             glUnmapBuffer;

static GLboolean GET_GL_FUNCTIONS_GL_vertex_buffer_object()
{
    GLboolean r = GL_FALSE;
    r = ((glBindBuffer = (PFNGLBINDBUFFERARBPROC)winGetProcAddress("glBindBuffer")) == NULL) || r;
    r = ((glBufferData = (PFNGLBUFFERDATAARBPROC)winGetProcAddress("glBufferData")) == NULL) || r;
    r = ((glBufferSubData = (PFNGLBUFFERSUBDATAARBPROC)winGetProcAddress("glBufferSubData")) == NULL) || r;
    r = ((glDeleteBuffers = (PFNGLDELETEBUFFERSARBPROC)winGetProcAddress("glDeleteBuffers")) == NULL) || r;
    r = ((glGenBuffers = (PFNGLGENBUFFERSPROC)winGetProcAddress("glGenBuffers")) == NULL) || r;
    r = ((glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVARBPROC)winGetProcAddress("glGetBufferParameteriv")) == NULL) || r;
    r = ((glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVARBPROC)winGetProcAddress("glGetBufferPointerv")) == NULL) || r;
    r = ((glGetBufferSubData = (PFNGLGETBUFFERSUBDATAARBPROC)winGetProcAddress("glGetBufferSubData")) == NULL) || r;
    r = ((glIsBuffer = (PFNGLISBUFFERARBPROC)winGetProcAddress("glIsBuffer")) == NULL) || r;
    r = ((glMapBuffer = (PFNGLMAPBUFFERARBPROC)winGetProcAddress("glMapBuffer")) == NULL) || r;
    r = ((glUnmapBuffer = (PFNGLUNMAPBUFFERARBPROC)winGetProcAddress("glUnmapBuffer")) == NULL) || r;
    return r;
}

PFNGLBINDVERTEXARRAYPROC        glBindVertexArray;
PFNGLDELETEVERTEXARRAYSPROC     glDeleteVertexArrays;
PFNGLGENVERTEXARRAYSPROC        glGenVertexArrays;
PFNGLISVERTEXARRAYPROC          glIsVertexArray;

static GLboolean GET_GL_FUNCTIONS_GL_vertex_array_object()
{
    GLboolean r = GL_FALSE;
    r = ((glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)winGetProcAddress("glBindVertexArray")) == NULL) || r;
    r = ((glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)winGetProcAddress("glDeleteVertexArrays")) == NULL) || r;
    r = ((glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)winGetProcAddress("glGenVertexArrays")) == NULL) || r;
    r = ((glIsVertexArray = (PFNGLISVERTEXARRAYPROC)winGetProcAddress("glIsVertexArray")) == NULL) || r;
    return r;
}

PFNGLBINDVERTEXBUFFERPROC       glBindVertexBuffer;
PFNGLVERTEXATTRIBFORMATPROC     glVertexAttribFormat;
PFNGLVERTEXATTRIBIFORMATPROC    glVertexAttribIFormat;
PFNGLVERTEXATTRIBLFORMATPROC    glVertexAttribLFormat;
PFNGLVERTEXATTRIBBINDINGPROC    glVertexAttribBinding;
PFNGLVERTEXBINDINGDIVISORPROC   glVertexBindingDivisor;

static GLboolean GET_GL_FUNCTIONS_GL_vertex_attrib_binding()
{
    GLboolean r = GL_FALSE;
    r = ((glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)winGetProcAddress("glBindVertexBuffer")) == NULL) || r;
    r = ((glVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC)winGetProcAddress("glVertexAttribFormat")) == NULL) || r;
    r = ((glVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC)winGetProcAddress("glVertexAttribIFormat")) == NULL) || r;
    r = ((glVertexAttribLFormat = (PFNGLVERTEXATTRIBLFORMATPROC)winGetProcAddress("glVertexAttribLFormat")) == NULL) || r;
    r = ((glVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC)winGetProcAddress("glVertexAttribBinding")) == NULL) || r;
    r = ((glVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC)winGetProcAddress("glVertexBindingDivisor")) == NULL) || r;
    return r;
}

PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
PFNGLMULTITEXCOORD1DARBPROC glMultiTexCoord1dARB;
PFNGLMULTITEXCOORD1DVARBPROC glMultiTexCoord1dvARB;
PFNGLMULTITEXCOORD1FARBPROC glMultiTexCoord1fARB;
PFNGLMULTITEXCOORD1FVARBPROC glMultiTexCoord1fvARB;
PFNGLMULTITEXCOORD1IARBPROC glMultiTexCoord1iARB;
PFNGLMULTITEXCOORD1IVARBPROC glMultiTexCoord1ivARB;
PFNGLMULTITEXCOORD1SARBPROC glMultiTexCoord1sARB;
PFNGLMULTITEXCOORD1SVARBPROC glMultiTexCoord1svARB;
PFNGLMULTITEXCOORD2DARBPROC glMultiTexCoord2dARB;
PFNGLMULTITEXCOORD2DVARBPROC glMultiTexCoord2dvARB;
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
PFNGLMULTITEXCOORD2FVARBPROC glMultiTexCoord2fvARB;
PFNGLMULTITEXCOORD2IARBPROC glMultiTexCoord2iARB;
PFNGLMULTITEXCOORD2IVARBPROC glMultiTexCoord2ivARB;
PFNGLMULTITEXCOORD2SARBPROC glMultiTexCoord2sARB;
PFNGLMULTITEXCOORD2SVARBPROC glMultiTexCoord2svARB;
PFNGLMULTITEXCOORD3DARBPROC glMultiTexCoord3dARB;
PFNGLMULTITEXCOORD3DVARBPROC glMultiTexCoord3dvARB;
PFNGLMULTITEXCOORD3FARBPROC glMultiTexCoord3fARB;
PFNGLMULTITEXCOORD3FVARBPROC glMultiTexCoord3fvARB;
PFNGLMULTITEXCOORD3IARBPROC glMultiTexCoord3iARB;
PFNGLMULTITEXCOORD3IVARBPROC glMultiTexCoord3ivARB;
PFNGLMULTITEXCOORD3SARBPROC glMultiTexCoord3sARB;
PFNGLMULTITEXCOORD3SVARBPROC glMultiTexCoord3svARB;
PFNGLMULTITEXCOORD4DARBPROC glMultiTexCoord4dARB;
PFNGLMULTITEXCOORD4DVARBPROC glMultiTexCoord4dvARB;
PFNGLMULTITEXCOORD4FARBPROC glMultiTexCoord4fARB;
PFNGLMULTITEXCOORD4FVARBPROC glMultiTexCoord4fvARB;
PFNGLMULTITEXCOORD4IARBPROC glMultiTexCoord4iARB;
PFNGLMULTITEXCOORD4IVARBPROC glMultiTexCoord4ivARB;
PFNGLMULTITEXCOORD4SARBPROC glMultiTexCoord4sARB;
PFNGLMULTITEXCOORD4SVARBPROC glMultiTexCoord4svARB;

static GLboolean GET_GL_FUNCTIONS_GL_multitexture()
{
    GLboolean r = GL_FALSE;
    r = ((glActiveTexture = (PFNGLACTIVETEXTUREPROC)winGetProcAddress("glActiveTexture")) == NULL) || r;
    r = ((glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)winGetProcAddress("glClientActiveTextureARB")) == NULL) || r;
    r = ((glMultiTexCoord1dARB = (PFNGLMULTITEXCOORD1DARBPROC)winGetProcAddress("glMultiTexCoord1dARB")) == NULL) || r;
    r = ((glMultiTexCoord1dvARB = (PFNGLMULTITEXCOORD1DVARBPROC)winGetProcAddress("glMultiTexCoord1dvARB")) == NULL) || r;
    r = ((glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC)winGetProcAddress("glMultiTexCoord1fARB")) == NULL) || r;
    r = ((glMultiTexCoord1fvARB = (PFNGLMULTITEXCOORD1FVARBPROC)winGetProcAddress("glMultiTexCoord1fvARB")) == NULL) || r;
    r = ((glMultiTexCoord1iARB = (PFNGLMULTITEXCOORD1IARBPROC)winGetProcAddress("glMultiTexCoord1iARB")) == NULL) || r;
    r = ((glMultiTexCoord1ivARB = (PFNGLMULTITEXCOORD1IVARBPROC)winGetProcAddress("glMultiTexCoord1ivARB")) == NULL) || r;
    r = ((glMultiTexCoord1sARB = (PFNGLMULTITEXCOORD1SARBPROC)winGetProcAddress("glMultiTexCoord1sARB")) == NULL) || r;
    r = ((glMultiTexCoord1svARB = (PFNGLMULTITEXCOORD1SVARBPROC)winGetProcAddress("glMultiTexCoord1svARB")) == NULL) || r;
    r = ((glMultiTexCoord2dARB = (PFNGLMULTITEXCOORD2DARBPROC)winGetProcAddress("glMultiTexCoord2dARB")) == NULL) || r;
    r = ((glMultiTexCoord2dvARB = (PFNGLMULTITEXCOORD2DVARBPROC)winGetProcAddress("glMultiTexCoord2dvARB")) == NULL) || r;
    r = ((glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)winGetProcAddress("glMultiTexCoord2fARB")) == NULL) || r;
    r = ((glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC)winGetProcAddress("glMultiTexCoord2fvARB")) == NULL) || r;
    r = ((glMultiTexCoord2iARB = (PFNGLMULTITEXCOORD2IARBPROC)winGetProcAddress("glMultiTexCoord2iARB")) == NULL) || r;
    r = ((glMultiTexCoord2ivARB = (PFNGLMULTITEXCOORD2IVARBPROC)winGetProcAddress("glMultiTexCoord2ivARB")) == NULL) || r;
    r = ((glMultiTexCoord2sARB = (PFNGLMULTITEXCOORD2SARBPROC)winGetProcAddress("glMultiTexCoord2sARB")) == NULL) || r;
    r = ((glMultiTexCoord2svARB = (PFNGLMULTITEXCOORD2SVARBPROC)winGetProcAddress("glMultiTexCoord2svARB")) == NULL) || r;
    r = ((glMultiTexCoord3dARB = (PFNGLMULTITEXCOORD3DARBPROC)winGetProcAddress("glMultiTexCoord3dARB")) == NULL) || r;
    r = ((glMultiTexCoord3dvARB = (PFNGLMULTITEXCOORD3DVARBPROC)winGetProcAddress("glMultiTexCoord3dvARB")) == NULL) || r;
    r = ((glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC)winGetProcAddress("glMultiTexCoord3fARB")) == NULL) || r;
    r = ((glMultiTexCoord3fvARB = (PFNGLMULTITEXCOORD3FVARBPROC)winGetProcAddress("glMultiTexCoord3fvARB")) == NULL) || r;
    r = ((glMultiTexCoord3iARB = (PFNGLMULTITEXCOORD3IARBPROC)winGetProcAddress("glMultiTexCoord3iARB")) == NULL) || r;
    r = ((glMultiTexCoord3ivARB = (PFNGLMULTITEXCOORD3IVARBPROC)winGetProcAddress("glMultiTexCoord3ivARB")) == NULL) || r;
    r = ((glMultiTexCoord3sARB = (PFNGLMULTITEXCOORD3SARBPROC)winGetProcAddress("glMultiTexCoord3sARB")) == NULL) || r;
    r = ((glMultiTexCoord3svARB = (PFNGLMULTITEXCOORD3SVARBPROC)winGetProcAddress("glMultiTexCoord3svARB")) == NULL) || r;
    r = ((glMultiTexCoord4dARB = (PFNGLMULTITEXCOORD4DARBPROC)winGetProcAddress("glMultiTexCoord4dARB")) == NULL) || r;
    r = ((glMultiTexCoord4dvARB = (PFNGLMULTITEXCOORD4DVARBPROC)winGetProcAddress("glMultiTexCoord4dvARB")) == NULL) || r;
    r = ((glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC)winGetProcAddress("glMultiTexCoord4fARB")) == NULL) || r;
    r = ((glMultiTexCoord4fvARB = (PFNGLMULTITEXCOORD4FVARBPROC)winGetProcAddress("glMultiTexCoord4fvARB")) == NULL) || r;
    r = ((glMultiTexCoord4iARB = (PFNGLMULTITEXCOORD4IARBPROC)winGetProcAddress("glMultiTexCoord4iARB")) == NULL) || r;
    r = ((glMultiTexCoord4ivARB = (PFNGLMULTITEXCOORD4IVARBPROC)winGetProcAddress("glMultiTexCoord4ivARB")) == NULL) || r;
    r = ((glMultiTexCoord4sARB = (PFNGLMULTITEXCOORD4SARBPROC)winGetProcAddress("glMultiTexCoord4sARB")) == NULL) || r;
    r = ((glMultiTexCoord4svARB = (PFNGLMULTITEXCOORD4SVARBPROC)winGetProcAddress("glMultiTexCoord4svARB")) == NULL) || r;
    return r;
}
PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl;
PFNGLDEBUGMESSAGEINSERTPROC glDebugMessageInsert;
PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback;
PFNGLGETDEBUGMESSAGELOGPROC glGetDebugMessageLog;
PFNGLGETPOINTERVPROC glGetPointerv;
PFNGLPUSHDEBUGGROUPPROC glPushDebugGroup;
PFNGLPOPDEBUGGROUPPROC glPopDebugGroup;
PFNGLOBJECTLABELPROC glObjectLabel;
PFNGLGETOBJECTLABELPROC glGetObjectLabel;
PFNGLOBJECTPTRLABELPROC glObjectPtrLabel;
PFNGLGETOBJECTPTRLABELPROC glGetObjectPtrLabel;

static GLboolean GET_GL_FUNCTIONS_GL_KHR_debug()
{
    GLboolean r = GL_FALSE;
    r = ((glDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)winGetProcAddress("glDebugMessageControl")) == NULL) || r;
    r = ((glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)winGetProcAddress("glDebugMessageInsert")) == NULL) || r;
    r = ((glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)winGetProcAddress("glDebugMessageCallback")) == NULL) || r;
    r = ((glGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC)winGetProcAddress("glGetDebugMessageLog")) == NULL) || r;
    r = ((glGetPointerv = (PFNGLGETPOINTERVPROC)winGetProcAddress("glGetPointerv")) == NULL) || r;
    r = ((glPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC)winGetProcAddress("glPushDebugGroup")) == NULL) || r;
    r = ((glPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC)winGetProcAddress("glPopDebugGroup")) == NULL) || r;
    r = ((glObjectLabel = (PFNGLOBJECTLABELPROC)winGetProcAddress("glObjectLabel")) == NULL) || r;
    r = ((glGetObjectLabel = (PFNGLGETOBJECTLABELPROC)winGetProcAddress("glGetObjectLabel")) == NULL) || r;
    r = ((glObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC)winGetProcAddress("glObjectPtrLabel")) == NULL) || r;
    r = ((glGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC)winGetProcAddress("glGetObjectPtrLabel")) == NULL) || r;
    return r;
}

PFNGLVERTEXATTRIB1FARBPROC glVertexAttrib1fARB;
PFNGLVERTEXATTRIB1SARBPROC glVertexAttrib1sARB;
PFNGLVERTEXATTRIB1DARBPROC glVertexAttrib1dARB;
PFNGLVERTEXATTRIB2FARBPROC glVertexAttrib2fARB;
PFNGLVERTEXATTRIB2SARBPROC glVertexAttrib2sARB;
PFNGLVERTEXATTRIB2DARBPROC glVertexAttrib2dARB;
PFNGLVERTEXATTRIB3FARBPROC glVertexAttrib3fARB;
PFNGLVERTEXATTRIB3SARBPROC glVertexAttrib3sARB;
PFNGLVERTEXATTRIB3DARBPROC glVertexAttrib3dARB;
PFNGLVERTEXATTRIB4FARBPROC glVertexAttrib4fARB;
PFNGLVERTEXATTRIB4SARBPROC glVertexAttrib4sARB;
PFNGLVERTEXATTRIB4DARBPROC glVertexAttrib4dARB;
PFNGLVERTEXATTRIB4NUBARBPROC glVertexAttrib4NubARB;
PFNGLVERTEXATTRIB1FVARBPROC glVertexAttrib1fvARB;
PFNGLVERTEXATTRIB1SVARBPROC glVertexAttrib1svARB;
PFNGLVERTEXATTRIB1DVARBPROC glVertexAttrib1dvARB;
PFNGLVERTEXATTRIB2FVARBPROC glVertexAttrib2fvARB;
PFNGLVERTEXATTRIB2SVARBPROC glVertexAttrib2svARB;
PFNGLVERTEXATTRIB2DVARBPROC glVertexAttrib2dvARB;
PFNGLVERTEXATTRIB3FVARBPROC glVertexAttrib3fvARB;
PFNGLVERTEXATTRIB3SVARBPROC glVertexAttrib3svARB;
PFNGLVERTEXATTRIB3DVARBPROC glVertexAttrib3dvARB;
PFNGLVERTEXATTRIB4FVARBPROC glVertexAttrib4fvARB;
PFNGLVERTEXATTRIB4SVARBPROC glVertexAttrib4svARB;
PFNGLVERTEXATTRIB4DVARBPROC glVertexAttrib4dvARB;
PFNGLVERTEXATTRIB4IVARBPROC glVertexAttrib4ivARB;
PFNGLVERTEXATTRIB4BVARBPROC glVertexAttrib4bvARB;
PFNGLVERTEXATTRIB4UBVARBPROC glVertexAttrib4ubvARB;
PFNGLVERTEXATTRIB4USVARBPROC glVertexAttrib4usvARB;
PFNGLVERTEXATTRIB4UIVARBPROC glVertexAttrib4uivARB;
PFNGLVERTEXATTRIB4NBVARBPROC glVertexAttrib4NbvARB;
PFNGLVERTEXATTRIB4NSVARBPROC glVertexAttrib4NsvARB;
PFNGLVERTEXATTRIB4NIVARBPROC glVertexAttrib4NivARB;
PFNGLVERTEXATTRIB4NUBVARBPROC glVertexAttrib4NubvARB;
PFNGLVERTEXATTRIB4NUSVARBPROC glVertexAttrib4NusvARB;
PFNGLVERTEXATTRIB4NUIVARBPROC glVertexAttrib4NuivARB;
PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB;
PFNGLBINDATTRIBLOCATIONARBPROC glBindAttribLocationARB;
PFNGLGETACTIVEATTRIBARBPROC glGetActiveAttribARB;
PFNGLGETATTRIBLOCATIONARBPROC glGetAttribLocationARB;
PFNGLGETVERTEXATTRIBDVARBPROC glGetVertexAttribdvARB;
PFNGLGETVERTEXATTRIBFVARBPROC glGetVertexAttribfvARB;
PFNGLGETVERTEXATTRIBIVARBPROC glGetVertexAttribivARB;

#define glEnableVertexAttribArray   glEnableVertexAttribArrayARB 
#define glVertexAttribPointer       glVertexAttribPointerARB 

static GLboolean GET_GL_FUNCTIONS_GL_ARB_vertex_shader()
{
    GLboolean r = GL_FALSE;
    r = ((glVertexAttrib1fARB = (PFNGLVERTEXATTRIB1FARBPROC)winGetProcAddress("glVertexAttrib1fARB")) == NULL) || r;
    r = ((glVertexAttrib1sARB = (PFNGLVERTEXATTRIB1SARBPROC)winGetProcAddress("glVertexAttrib1sARB")) == NULL) || r;
    r = ((glVertexAttrib1dARB = (PFNGLVERTEXATTRIB1DARBPROC)winGetProcAddress("glVertexAttrib1dARB")) == NULL) || r;
    r = ((glVertexAttrib2fARB = (PFNGLVERTEXATTRIB2FARBPROC)winGetProcAddress("glVertexAttrib2fARB")) == NULL) || r;
    r = ((glVertexAttrib2sARB = (PFNGLVERTEXATTRIB2SARBPROC)winGetProcAddress("glVertexAttrib2sARB")) == NULL) || r;
    r = ((glVertexAttrib2dARB = (PFNGLVERTEXATTRIB2DARBPROC)winGetProcAddress("glVertexAttrib2dARB")) == NULL) || r;
    r = ((glVertexAttrib3fARB = (PFNGLVERTEXATTRIB3FARBPROC)winGetProcAddress("glVertexAttrib3fARB")) == NULL) || r;
    r = ((glVertexAttrib3sARB = (PFNGLVERTEXATTRIB3SARBPROC)winGetProcAddress("glVertexAttrib3sARB")) == NULL) || r;
    r = ((glVertexAttrib3dARB = (PFNGLVERTEXATTRIB3DARBPROC)winGetProcAddress("glVertexAttrib3dARB")) == NULL) || r;
    r = ((glVertexAttrib4fARB = (PFNGLVERTEXATTRIB4FARBPROC)winGetProcAddress("glVertexAttrib4fARB")) == NULL) || r;
    r = ((glVertexAttrib4sARB = (PFNGLVERTEXATTRIB4SARBPROC)winGetProcAddress("glVertexAttrib4sARB")) == NULL) || r;
    r = ((glVertexAttrib4dARB = (PFNGLVERTEXATTRIB4DARBPROC)winGetProcAddress("glVertexAttrib4dARB")) == NULL) || r;
    r = ((glVertexAttrib4NubARB = (PFNGLVERTEXATTRIB4NUBARBPROC)winGetProcAddress("glVertexAttrib4NubARB")) == NULL) || r;
    r = ((glVertexAttrib1fvARB = (PFNGLVERTEXATTRIB1FVARBPROC)winGetProcAddress("glVertexAttrib1fvARB")) == NULL) || r;
    r = ((glVertexAttrib1svARB = (PFNGLVERTEXATTRIB1SVARBPROC)winGetProcAddress("glVertexAttrib1svARB")) == NULL) || r;
    r = ((glVertexAttrib1dvARB = (PFNGLVERTEXATTRIB1DVARBPROC)winGetProcAddress("glVertexAttrib1dvARB")) == NULL) || r;
    r = ((glVertexAttrib2fvARB = (PFNGLVERTEXATTRIB2FVARBPROC)winGetProcAddress("glVertexAttrib2fvARB")) == NULL) || r;
    r = ((glVertexAttrib2svARB = (PFNGLVERTEXATTRIB2SVARBPROC)winGetProcAddress("glVertexAttrib2svARB")) == NULL) || r;
    r = ((glVertexAttrib2dvARB = (PFNGLVERTEXATTRIB2DVARBPROC)winGetProcAddress("glVertexAttrib2dvARB")) == NULL) || r;
    r = ((glVertexAttrib3fvARB = (PFNGLVERTEXATTRIB3FVARBPROC)winGetProcAddress("glVertexAttrib3fvARB")) == NULL) || r;
    r = ((glVertexAttrib3svARB = (PFNGLVERTEXATTRIB3SVARBPROC)winGetProcAddress("glVertexAttrib3svARB")) == NULL) || r;
    r = ((glVertexAttrib3dvARB = (PFNGLVERTEXATTRIB3DVARBPROC)winGetProcAddress("glVertexAttrib3dvARB")) == NULL) || r;
    r = ((glVertexAttrib4fvARB = (PFNGLVERTEXATTRIB4FVARBPROC)winGetProcAddress("glVertexAttrib4fvARB")) == NULL) || r;
    r = ((glVertexAttrib4svARB = (PFNGLVERTEXATTRIB4SVARBPROC)winGetProcAddress("glVertexAttrib4svARB")) == NULL) || r;
    r = ((glVertexAttrib4dvARB = (PFNGLVERTEXATTRIB4DVARBPROC)winGetProcAddress("glVertexAttrib4dvARB")) == NULL) || r;
    r = ((glVertexAttrib4ivARB = (PFNGLVERTEXATTRIB4IVARBPROC)winGetProcAddress("glVertexAttrib4ivARB")) == NULL) || r;
    r = ((glVertexAttrib4bvARB = (PFNGLVERTEXATTRIB4BVARBPROC)winGetProcAddress("glVertexAttrib4bvARB")) == NULL) || r;
    r = ((glVertexAttrib4ubvARB = (PFNGLVERTEXATTRIB4UBVARBPROC)winGetProcAddress("glVertexAttrib4ubvARB")) == NULL) || r;
    r = ((glVertexAttrib4usvARB = (PFNGLVERTEXATTRIB4USVARBPROC)winGetProcAddress("glVertexAttrib4usvARB")) == NULL) || r;
    r = ((glVertexAttrib4uivARB = (PFNGLVERTEXATTRIB4UIVARBPROC)winGetProcAddress("glVertexAttrib4uivARB")) == NULL) || r;
    r = ((glVertexAttrib4NbvARB = (PFNGLVERTEXATTRIB4NBVARBPROC)winGetProcAddress("glVertexAttrib4NbvARB")) == NULL) || r;
    r = ((glVertexAttrib4NsvARB = (PFNGLVERTEXATTRIB4NSVARBPROC)winGetProcAddress("glVertexAttrib4NsvARB")) == NULL) || r;
    r = ((glVertexAttrib4NivARB = (PFNGLVERTEXATTRIB4NIVARBPROC)winGetProcAddress("glVertexAttrib4NivARB")) == NULL) || r;
    r = ((glVertexAttrib4NubvARB = (PFNGLVERTEXATTRIB4NUBVARBPROC)winGetProcAddress("glVertexAttrib4NubvARB")) == NULL) || r;
    r = ((glVertexAttrib4NusvARB = (PFNGLVERTEXATTRIB4NUSVARBPROC)winGetProcAddress("glVertexAttrib4NusvARB")) == NULL) || r;
    r = ((glVertexAttrib4NuivARB = (PFNGLVERTEXATTRIB4NUIVARBPROC)winGetProcAddress("glVertexAttrib4NuivARB")) == NULL) || r;
    r = ((glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC)winGetProcAddress("glVertexAttribPointerARB")) == NULL) || r;
    r = ((glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)winGetProcAddress("glEnableVertexAttribArrayARB")) == NULL) || r;
    r = ((glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)winGetProcAddress("glDisableVertexAttribArrayARB")) == NULL) || r;
    r = ((glBindAttribLocationARB = (PFNGLBINDATTRIBLOCATIONARBPROC)winGetProcAddress("glBindAttribLocationARB")) == NULL) || r;
    r = ((glGetActiveAttribARB = (PFNGLGETACTIVEATTRIBARBPROC)winGetProcAddress("glGetActiveAttribARB")) == NULL) || r;
    r = ((glGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC)winGetProcAddress("glGetAttribLocationARB")) == NULL) || r;
    r = ((glGetVertexAttribdvARB = (PFNGLGETVERTEXATTRIBDVARBPROC)winGetProcAddress("glGetVertexAttribdvARB")) == NULL) || r;
    r = ((glGetVertexAttribfvARB = (PFNGLGETVERTEXATTRIBFVARBPROC)winGetProcAddress("glGetVertexAttribfvARB")) == NULL) || r;
    r = ((glGetVertexAttribivARB = (PFNGLGETVERTEXATTRIBIVARBPROC)winGetProcAddress("glGetVertexAttribivARB")) == NULL) || r;
    return r;
}

PFNGLGETUNIFORMINDICESPROC    glGetUniformIndices;
PFNGLGETACTIVEUNIFORMSIVPROC    glGetActiveUniformsiv;
PFNGLGETACTIVEUNIFORMNAMEPROC    glGetActiveUniformName;
PFNGLGETUNIFORMBLOCKINDEXPROC    glGetUniformBlockIndex;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC    glGetActiveUniformBlockiv;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC    glGetActiveUniformBlockName;
PFNGLBINDBUFFERRANGEPROC    glBindBufferRange;
PFNGLBINDBUFFERBASEPROC    glBindBufferBase;
PFNGLGETINTEGERI_VPROC   glGetIntegeri_v;
PFNGLUNIFORMBLOCKBINDINGPROC    glUniformBlockBinding;

static GLboolean GET_GL_FUNCTIONS_GL_ARB_uniform_buffer_object()
{
    GLboolean r = GL_FALSE;
    r = ((glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)winGetProcAddress("glGetUniformIndices")) == NULL) || r;
    r = ((glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)winGetProcAddress("glGetActiveUniformsiv")) == NULL) || r;
    r = ((glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)winGetProcAddress("glGetActiveUniformName")) == NULL) || r;
    r = ((glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)winGetProcAddress("glGetUniformBlockIndex")) == NULL) || r;
    r = ((glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)winGetProcAddress("glGetActiveUniformBlockiv")) == NULL) || r;
    r = ((glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)winGetProcAddress("glGetActiveUniformBlockName")) == NULL) || r;
    r = ((glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)winGetProcAddress("glBindBufferRange")) == NULL) || r;
    r = ((glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)winGetProcAddress("glBindBufferBase")) == NULL) || r;
    r = ((glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)winGetProcAddress("glGetIntegeri_v")) == NULL) || r;
    r = ((glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)winGetProcAddress("glUniformBlockBinding")) == NULL) || r;
    return r;
}

 PFNGLDELETEOBJECTARBPROC           glDeleteObjectARB;
 PFNGLGETHANDLEARBPROC              glGetHandleARB;
 PFNGLDETACHOBJECTARBPROC           glDetachObjectARB;
 PFNGLCREATESHADEROBJECTARBPROC     glCreateShaderObjectARB;
 PFNGLSHADERSOURCEARBPROC              glShaderSourceARB;
 PFNGLCOMPILESHADERARBPROC          glCompileShaderARB;
 PFNGLCREATEPROGRAMOBJECTARBPROC    glCreateProgramObjectARB;
 PFNGLATTACHOBJECTARBPROC           glAttachObjectARB;
 PFNGLLINKPROGRAMARBPROC            glLinkProgramARB;
 PFNGLUSEPROGRAMOBJECTARBPROC       glUseProgramObjectARB;
 PFNGLVALIDATEPROGRAMARBPROC        glValidateProgramARB;
 PFNGLUNIFORM1FARBPROC              glUniform1fARB;
 PFNGLUNIFORM2FARBPROC              glUniform2fARB;
 PFNGLUNIFORM3FARBPROC              glUniform3fARB;
 PFNGLUNIFORM4FARBPROC              glUniform4fARB;
 PFNGLUNIFORM1IARBPROC              glUniform1iARB;
 PFNGLUNIFORM2IARBPROC              glUniform2iARB;
 PFNGLUNIFORM3IARBPROC              glUniform3iARB;
 PFNGLUNIFORM4IARBPROC              glUniform4iARB;
 PFNGLUNIFORM1FVARBPROC             glUniform1fvARB;
 PFNGLUNIFORM2FVARBPROC             glUniform2fvARB;
 PFNGLUNIFORM3FVARBPROC             glUniform3fvARB;
 PFNGLUNIFORM4FVARBPROC             glUniform4fvARB;
 PFNGLUNIFORM1IVARBPROC             glUniform1ivARB;
 PFNGLUNIFORM2IVARBPROC             glUniform2ivARB;
 PFNGLUNIFORM3IVARBPROC             glUniform3ivARB;
 PFNGLUNIFORM4IVARBPROC             glUniform4ivARB;
 PFNGLUNIFORMMATRIX2FVARBPROC       glUniformMatrix2fvARB;
 PFNGLUNIFORMMATRIX3FVARBPROC       glUniformMatrix3fvARB;
 PFNGLUNIFORMMATRIX4FVARBPROC       glUniformMatrix4fvARB;
 PFNGLGETOBJECTPARAMETERFVARBPROC   glGetObjectParameterfvARB;
 PFNGLGETOBJECTPARAMETERIVARBPROC   glGetObjectParameterivARB;
 PFNGLGETINFOLOGARBPROC             glGetInfoLogARB;
 PFNGLGETATTACHEDOBJECTSARBPROC     glGetAttachedObjectsARB;
 PFNGLGETUNIFORMLOCATIONARBPROC     glGetUniformLocationARB;
 PFNGLGETACTIVEUNIFORMARBPROC       glGetActiveUniformARB;
 PFNGLGETUNIFORMFVARBPROC           glGetUniformfvARB;
 PFNGLGETUNIFORMIVARBPROC           glGetUniformivARB;
 PFNGLGETSHADERSOURCEARBPROC        glGetShaderSourceARB;

static GLboolean GET_GL_FUNCTIONS_GL_ARB_shader_objects()
{
    GLboolean r = GL_FALSE;
    r = ((glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)winGetProcAddress("glDeleteObjectARB")) == NULL) || r;
    r = ((glGetHandleARB = (PFNGLGETHANDLEARBPROC)winGetProcAddress("glGetHandleARB")) == NULL) || r;
    r = ((glDetachObjectARB = (PFNGLDETACHOBJECTARBPROC)winGetProcAddress("glDetachObjectARB")) == NULL) || r;
    r = ((glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)winGetProcAddress("glCreateShaderObjectARB")) == NULL) || r;
    r = ((glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)winGetProcAddress("glShaderSourceARB")) == NULL) || r;
    r = ((glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)winGetProcAddress("glCompileShaderARB")) == NULL) || r;
    r = ((glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)winGetProcAddress("glCreateProgramObjectARB")) == NULL) || r;
    r = ((glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)winGetProcAddress("glAttachObjectARB")) == NULL) || r;
    r = ((glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)winGetProcAddress("glLinkProgramARB")) == NULL) || r;
    r = ((glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)winGetProcAddress("glUseProgramObjectARB")) == NULL) || r;
    r = ((glValidateProgramARB = (PFNGLVALIDATEPROGRAMARBPROC)winGetProcAddress("glValidateProgramARB")) == NULL) || r;

    r = ((glUniform1fARB = (PFNGLUNIFORM1FARBPROC)winGetProcAddress("glUniform1fARB")) == NULL) || r;
    r = ((glUniform2fARB = (PFNGLUNIFORM2FARBPROC)winGetProcAddress("glUniform2fARB")) == NULL) || r;
    r = ((glUniform3fARB = (PFNGLUNIFORM3FARBPROC)winGetProcAddress("glUniform3fARB")) == NULL) || r;
    r = ((glUniform4fARB = (PFNGLUNIFORM4FARBPROC)winGetProcAddress("glUniform4fARB")) == NULL) || r;

    r = ((glUniform1iARB = (PFNGLUNIFORM1IARBPROC)winGetProcAddress("glUniform1iARB")) == NULL) || r;
    r = ((glUniform2iARB = (PFNGLUNIFORM2IARBPROC)winGetProcAddress("glUniform2iARB")) == NULL) || r;
    r = ((glUniform3iARB = (PFNGLUNIFORM3IARBPROC)winGetProcAddress("glUniform3iARB")) == NULL) || r;
    r = ((glUniform4iARB = (PFNGLUNIFORM4IARBPROC)winGetProcAddress("glUniform4iARB")) == NULL) || r;

    r = ((glUniform1fvARB = (PFNGLUNIFORM1FVARBPROC)winGetProcAddress("glUniform1fvARB")) == NULL) || r;
    r = ((glUniform2fvARB = (PFNGLUNIFORM2FVARBPROC)winGetProcAddress("glUniform2fvARB")) == NULL) || r;
    r = ((glUniform3fvARB = (PFNGLUNIFORM3FVARBPROC)winGetProcAddress("glUniform3fvARB")) == NULL) || r;
    r = ((glUniform4fvARB = (PFNGLUNIFORM4FVARBPROC)winGetProcAddress("glUniform4fvARB")) == NULL) || r;

    r = ((glUniform1ivARB = (PFNGLUNIFORM1IVARBPROC)winGetProcAddress("glUniform1ivARB")) == NULL) || r;
    r = ((glUniform2ivARB = (PFNGLUNIFORM2IVARBPROC)winGetProcAddress("glUniform2ivARB")) == NULL) || r;
    r = ((glUniform3ivARB = (PFNGLUNIFORM3IVARBPROC)winGetProcAddress("glUniform3ivARB")) == NULL) || r;
    r = ((glUniform4ivARB = (PFNGLUNIFORM4IVARBPROC)winGetProcAddress("glUniform4ivARB")) == NULL) || r;

    r = ((glUniformMatrix2fvARB = (PFNGLUNIFORMMATRIX2FVARBPROC)winGetProcAddress("glUniformMatrix2fvARB")) == NULL) || r;
    r = ((glUniformMatrix3fvARB = (PFNGLUNIFORMMATRIX3FVARBPROC)winGetProcAddress("glUniformMatrix3fvARB")) == NULL) || r;
    r = ((glUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC)winGetProcAddress("glUniformMatrix4fvARB")) == NULL) || r;

    r = ((glGetObjectParameterfvARB = (PFNGLGETOBJECTPARAMETERFVARBPROC)winGetProcAddress("glGetObjectParameterfvARB")) == NULL) || r;
    r = ((glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)winGetProcAddress("glGetObjectParameterivARB")) == NULL) || r;
    r = ((glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)winGetProcAddress("glGetInfoLogARB")) == NULL) || r;
    r = ((glGetAttachedObjectsARB = (PFNGLGETATTACHEDOBJECTSARBPROC)winGetProcAddress("glGetAttachedObjectsARB")) == NULL) || r;
    r = ((glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC)winGetProcAddress("glGetUniformLocationARB")) == NULL) || r;
    r = ((glGetActiveUniformARB = (PFNGLGETACTIVEUNIFORMARBPROC)winGetProcAddress("glGetActiveUniformARB")) == NULL) || r;
    r = ((glGetUniformfvARB = (PFNGLGETUNIFORMFVARBPROC)winGetProcAddress("glGetUniformfvARB")) == NULL) || r;
    r = ((glGetUniformivARB = (PFNGLGETUNIFORMIVARBPROC)winGetProcAddress("glGetUniformivARB")) == NULL) || r;
    r = ((glGetShaderSourceARB = (PFNGLGETSHADERSOURCEARBPROC)winGetProcAddress("glGetShaderSourceARB")) == NULL) || r;
    return r;
}

PFNGLCREATESHADERPROC           glCreateShader;
PFNGLSHADERSOURCEPROC           glShaderSource;
PFNGLCOMPILESHADERPROC          glCompileShader;
PFNGLRELEASESHADERCOMPILERPROC  glReleaseShaderCompiler;
PFNGLDELETESHADERPROC           glDeleteShader;
PFNGLISSHADERPROC               glIsShader;
PFNGLSHADERBINARYPROC           glShaderBinary;

PFNGLGETSHADERIVPROC        glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC   glGetShaderInfoLog;
PFNGLATTACHSHADERPROC       glAttachShader;

static GLboolean GET_GL_FUNCTIONS_shader_object() {
    GLboolean r = GL_FALSE;
    r = ((glCreateShader = (PFNGLCREATESHADERPROC)winGetProcAddress("glCreateShader")) == NULL) || r;
    r = ((glShaderSource = (PFNGLSHADERSOURCEPROC)winGetProcAddress("glShaderSource")) == NULL) || r;
    r = ((glCompileShader = (PFNGLCOMPILESHADERPROC)winGetProcAddress("glCompileShader")) == NULL) || r;
    r = ((glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)winGetProcAddress("glReleaseShaderCompiler")) == NULL) || r;
    r = ((glDeleteShader = (PFNGLDELETESHADERPROC)winGetProcAddress("glDeleteShader")) == NULL) || r;
    r = ((glIsShader = (PFNGLISSHADERPROC)winGetProcAddress("glIsShader")) == NULL) || r;
    r = ((glShaderBinary = (PFNGLSHADERBINARYPROC)winGetProcAddress("glShaderBinary")) == NULL) || r;

    r = ((glGetShaderiv = (PFNGLGETSHADERIVPROC)winGetProcAddress("glGetShaderiv")) == NULL) || r;
    r = ((glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)winGetProcAddress("glGetShaderInfoLog")) == NULL) || r;
    r = ((glAttachShader = (PFNGLATTACHSHADERPROC)winGetProcAddress("glAttachShader")) == NULL) || r;
    return r;
}

PFNGLCREATEPROGRAMPROC      glCreateProgram;
PFNGLUSEPROGRAMPROC         glUseProgram;
PFNGLGETPROGRAMIVPROC       glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC  glGetProgramInfoLog;
PFNGLDELETEPROGRAMPROC      glDeleteProgram;

static GLboolean GET_GL_FUNCTIONS_program_object() {
    GLboolean r = GL_FALSE;
    r = ((glCreateProgram = (PFNGLCREATEPROGRAMPROC)winGetProcAddress("glCreateProgram")) == NULL) || r;
    r = ((glUseProgram = (PFNGLUSEPROGRAMPROC)winGetProcAddress("glUseProgram")) == NULL) || r;
    r = ((glGetProgramiv = (PFNGLGETPROGRAMIVPROC)winGetProcAddress("glGetProgramiv")) == NULL) || r;
    r = ((glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)winGetProcAddress("glGetProgramInfoLog")) == NULL) || r;
    r = ((glDeleteProgram = (PFNGLDELETEPROGRAMPROC)winGetProcAddress("glDeleteProgram")) == NULL) || r;
    return r;
}

PFNGLCLEARPROC                  glClear;
PFNGLCLEARCOLORPROC             glClearColor;
PFNGLCLEARDEPTHPROC             glClearDepth;
PFNGLCLEARSTENCILPROC           glClearStencil;

static GLboolean GET_GL_FUNCTIONS_clear_buffer() {
    GLboolean r = GL_FALSE;
    r = ((glClear = (PFNGLCLEARPROC)winGetProcAddress("glClear")) == NULL) || r;
    r = ((glClearColor = (PFNGLCLEARCOLORPROC)winGetProcAddress("glClearColor")) == NULL) || r;
    r = ((glClearDepth = (PFNGLCLEARDEPTHPROC)winGetProcAddress("glClearDepth")) == NULL) || r;
    r = ((glClearStencil = (PFNGLCLEARSTENCILPROC)winGetProcAddress("glClearStencil")) == NULL) || r;
    return r;
} 
PFNGLCOMPRESSEDTEXIMAGE3DARBPROC glCompressedTexImage3DARB;
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB;
PFNGLCOMPRESSEDTEXIMAGE1DARBPROC glCompressedTexImage1DARB;
PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC glCompressedTexSubImage3DARB;
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC glCompressedTexSubImage2DARB;
PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC glCompressedTexSubImage1DARB;
PFNGLGETCOMPRESSEDTEXIMAGEARBPROC glGetCompressedTexImageARB;
static GLboolean GET_GL_FUNCTIONS_GL_ARB_texture_compression() {
    GLboolean r = GL_FALSE;
    r = ((glCompressedTexImage3DARB = (PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)winGetProcAddress("glCompressedTexImage3DARB")) == NULL) || r;
    r = ((glCompressedTexImage2DARB = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)winGetProcAddress("glCompressedTexImage2DARB")) == NULL) || r;
    r = ((glCompressedTexImage1DARB = (PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)winGetProcAddress("glCompressedTexImage1DARB")) == NULL) || r;
    r = ((glCompressedTexSubImage3DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC)winGetProcAddress("glCompressedTexSubImage3DARB")) == NULL) || r;
    r = ((glCompressedTexSubImage2DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC)winGetProcAddress("glCompressedTexSubImage2DARB")) == NULL) || r;
    r = ((glCompressedTexSubImage1DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC)winGetProcAddress("glCompressedTexSubImage1DARB")) == NULL) || r;
    r = ((glGetCompressedTexImageARB = (PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)winGetProcAddress("glGetCompressedTexImageARB")) == NULL) || r;
    return r;
}
PFNGLBINDTEXTUREPROC        glBindTexture;
PFNGLGENTEXTURESPROC        glGenTextures;
PFNGLTEXPARAMETERIPROC      glTexParameteri;
PFNGLTEXIMAGE2DPROC         glTexImage2D;
PFNGLDELETETEXTURESPROC     glDeleteTextures;
static GLboolean GET_GL_FUNCTIONS_texture_object() {

    GLboolean r = GL_FALSE;
    r = ((glBindTexture = (PFNGLBINDTEXTUREPROC)winGetProcAddress("glBindTexture")) == NULL) || r;
    r = ((glGenTextures = (PFNGLGENTEXTURESPROC)winGetProcAddress("glGenTextures")) == NULL) || r;
    r = ((glTexParameteri = (PFNGLTEXPARAMETERIPROC)winGetProcAddress("glTexParameteri")) == NULL) || r;
    r = ((glTexImage2D = (PFNGLTEXIMAGE2DPROC)winGetProcAddress("glTexImage2D")) == NULL) || r;
    r = ((glDeleteTextures = (PFNGLDELETETEXTURESPROC)winGetProcAddress("glDeleteTextures")) == NULL) || r;

    return r;
}


PFNGLENABLEPROC             glEnable;
PFNGLDISABLEPROC             glDisable;
PFNGLDEPTHMASKPROC          glDepthMask;
PFNGLDEPTHFUNCPROC          glDepthFunc;
PFNGLBLENDFUNCPROC          glBlendFunc;
PFNGLVIEWPORTPROC           glViewport;
PFNGLDRAWELEMENTSPROC       glDrawElements;
PFNGLGETERRORPROC           glGetError;
PFNGLPOLYGONMODEPROC        glPolygonMode;

static BOOL get_OpenGL_functions()
{

    if (!find_GL_extensions("GL_KHR_debug")) return FALSE;
    else GET_GL_FUNCTIONS_GL_KHR_debug();
    if (!find_GL_extensions("GL_ARB_multitexture")) return FALSE;
    else GET_GL_FUNCTIONS_GL_multitexture();
    if (!find_GL_extensions("GL_ARB_vertex_buffer_object")) return FALSE;
    else GET_GL_FUNCTIONS_GL_vertex_buffer_object();
    if (!find_GL_extensions("GL_ARB_vertex_array_object"))  return FALSE;
    else GET_GL_FUNCTIONS_GL_vertex_array_object(); 
    if (!find_GL_extensions("GL_ARB_vertex_attrib_binding"))  return FALSE;
    else GET_GL_FUNCTIONS_GL_vertex_attrib_binding();
    if (!find_GL_extensions("GL_ARB_vertex_shader")) return FALSE;
    else GET_GL_FUNCTIONS_GL_ARB_vertex_shader();
    if (!find_GL_extensions("GL_ARB_uniform_buffer_object")) return FALSE;
    else GET_GL_FUNCTIONS_GL_ARB_uniform_buffer_object();
    if (!find_GL_extensions("GL_ARB_shader_objects")) return FALSE;
    else GET_GL_FUNCTIONS_GL_ARB_shader_objects();
    if (!find_GL_extensions("GL_ARB_texture_compression")) return FALSE;
    else GET_GL_FUNCTIONS_GL_ARB_texture_compression();
    if (!find_GL_version(2, 0)) return FALSE;
    else {
        GET_GL_FUNCTIONS_shader_object();
        GET_GL_FUNCTIONS_program_object();
        GET_GL_FUNCTIONS_texture_object();
    }
    if (!find_GL_version(1, 0)) return FALSE;
    else GET_GL_FUNCTIONS_clear_buffer();

    glBindTexture = (PFNGLBINDTEXTUREPROC)winGetProcAddress("glBindTexture");
    glPolygonMode = (PFNGLPOLYGONMODEPROC)winGetProcAddress("glPolygonMode");
    glGetError = (PFNGLGETERRORPROC)winGetProcAddress("glGetError");
    glEnable = (PFNGLENABLEPROC)winGetProcAddress("glEnable");
    glDisable = (PFNGLDISABLEPROC)winGetProcAddress("glDisable");
    glDepthMask =  (PFNGLDEPTHMASKPROC)winGetProcAddress("glDepthMask");
    glDepthFunc = (PFNGLDEPTHFUNCPROC)winGetProcAddress("glDepthFunc");
    glBlendFunc = (PFNGLBLENDFUNCPROC)winGetProcAddress("glBlendFunc");
    glViewport = (PFNGLVIEWPORTPROC)winGetProcAddress("glViewport");
    
    glDrawElements = (PFNGLDRAWELEMENTSPROC)winGetProcAddress("glDrawElements");


    return TRUE;
}

#endif
#endif