#ifdef _WIN32

#ifndef __FCWGL_FUNCTIONS__
#define __FCWGL_FUNCTIONS__

#include <GL/glcorearb.h>
#include <GL/wglext.h>
#include <stdlib.h>		
#include <stdio.h>

static const char* OpenGL_STANDARD[] = {
        "GL_VERSION_1_0",
        "GL_VERSION_1_1",
        "GL_VERSION_1_3",
        "GL_VERSION_1_5",
        "GL_VERSION_2_0",
        "GL_ARB_vertex_array_object",
        "GL_ARB_vertex_attrib_binding",
        "GL_ARB_uniform_buffer_object",
        "GL_KHR_debug"
};


static inline BOOL find_WGL_extensions(const char* pName, HDC hdc, const char* (WINAPI* glGetExtensionsStringARB)(HDC hdc)) {
    const char* extensions = (const char*)glGetExtensionsStringARB(hdc);
    size_t size = strlen(pName);
    while (extensions) {
        if (!strncmp(extensions, pName, size) && (*(extensions + size) == 0 || *(extensions + size) == ' '))
            return TRUE;
        extensions = strchr(extensions, ' ');
        if (extensions)
            extensions++;
    }
    return FALSE;
}

void (APIENTRYP glCullFace)(GLenum mode);

void (APIENTRYP glFrontFace)(GLenum mode);

void (APIENTRYP glHint)(GLenum target, GLenum mode);

void (APIENTRYP glLineWidth)(GLfloat width);

void (APIENTRYP glPointSize)(GLfloat size);

void (APIENTRYP glPolygonMode)(GLenum face, GLenum mode);

void (APIENTRYP glScissor)(GLint x, GLint y, GLsizei width, GLsizei height);

void (APIENTRYP glTexParameterf)(GLenum target, GLenum pname, GLfloat param);

void (APIENTRYP glTexParameterfv)(GLenum target, GLenum pname, const GLfloat* params);

void (APIENTRYP glTexParameteri)(GLenum target, GLenum pname, GLint param);

void (APIENTRYP glTexParameteriv)(GLenum target, GLenum pname, const GLint* params);

void
(APIENTRYP glTexImage1D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format,
    GLenum type, const void* pixels);

void
(APIENTRYP glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border,
    GLenum format, GLenum type, const void* pixels);

void (APIENTRYP glDrawBuffer)(GLenum buf);

void (APIENTRYP glClear)(GLbitfield mask);

void (APIENTRYP glClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

void (APIENTRYP glClearStencil)(GLint s);

void (APIENTRYP glClearDepth)(GLdouble depth);

void (APIENTRYP glStencilMask)(GLuint mask);

void (APIENTRYP glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

void (APIENTRYP glDepthMask)(GLboolean flag);

void (APIENTRYP glDisable)(GLenum cap);

void (APIENTRYP glEnable)(GLenum cap);

void (APIENTRYP glFinish)(void);

void (APIENTRYP glFlush)(void);

void (APIENTRYP glBlendFunc)(GLenum sfactor, GLenum dfactor);

void (APIENTRYP glLogicOp)(GLenum opcode);

void (APIENTRYP glStencilFunc)(GLenum func, GLint ref, GLuint mask);

void (APIENTRYP glStencilOp)(GLenum fail, GLenum zfail, GLenum zpass);

void (APIENTRYP glDepthFunc)(GLenum func);

void (APIENTRYP glPixelStoref)(GLenum pname, GLfloat param);

void (APIENTRYP glPixelStorei)(GLenum pname, GLint param);

void (APIENTRYP glReadBuffer)(GLenum src);

void
(APIENTRYP glReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);

void (APIENTRYP glGetBooleanv)(GLenum pname, GLboolean* data);

void (APIENTRYP glGetDoublev)(GLenum pname, GLdouble* data);

GLenum(APIENTRYP glGetError)(void);

void (APIENTRYP glGetFloatv)(GLenum pname, GLfloat* data);

void (APIENTRYP glGetIntegerv)(GLenum pname, GLint* data);

const GLubyte* (APIENTRYP glGetString)(GLenum name);

void (APIENTRYP glGetTexImage)(GLenum target, GLint level, GLenum format, GLenum type, void* pixels);

void (APIENTRYP glGetTexParameterfv)(GLenum target, GLenum pname, GLfloat* params);

void (APIENTRYP glGetTexParameteriv)(GLenum target, GLenum pname, GLint* params);

void (APIENTRYP glGetTexLevelParameterfv)(GLenum target, GLint level, GLenum pname, GLfloat* params);

void (APIENTRYP glGetTexLevelParameteriv)(GLenum target, GLint level, GLenum pname, GLint* params);

GLboolean(APIENTRYP glIsEnabled)(GLenum cap);

void (APIENTRYP glDepthRange)(GLdouble n, GLdouble f);

void (APIENTRYP glViewport)(GLint x, GLint y, GLsizei width, GLsizei height);

static GLboolean GET_GL_FUNCTIONS_GL_VERSION_1_0(HMODULE lib) {
    GLboolean r = GL_FALSE;
    r = ((glCullFace = (PFNGLCULLFACEPROC)GetProcAddress(lib, "glCullFace")) == NULL) || r;
    r = ((glFrontFace = (PFNGLFRONTFACEPROC)GetProcAddress(lib, "glFrontFace")) == NULL) || r;
    r = ((glHint = (PFNGLHINTPROC)GetProcAddress(lib, "glHint")) == NULL) || r;
    r = ((glLineWidth = (PFNGLLINEWIDTHPROC)GetProcAddress(lib, "glLineWidth")) == NULL) || r;
    r = ((glPointSize = (PFNGLPOINTSIZEPROC)GetProcAddress(lib, "glPointSize")) == NULL) || r;
    r = ((glPolygonMode = (PFNGLPOLYGONMODEPROC)GetProcAddress(lib, "glPolygonMode")) == NULL) || r;
    r = ((glScissor = (PFNGLSCISSORPROC)GetProcAddress(lib, "glScissor")) == NULL) || r;
    r = ((glTexParameterf = (PFNGLTEXPARAMETERFPROC)GetProcAddress(lib, "glTexParameterf")) == NULL) || r;
    r = ((glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)GetProcAddress(lib, "glTexParameterfv")) == NULL) || r;
    r = ((glTexParameteri = (PFNGLTEXPARAMETERIPROC)GetProcAddress(lib, "glTexParameteri")) == NULL) || r;
    r = ((glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)GetProcAddress(lib, "glTexParameteriv")) == NULL) || r;
    r = ((glTexImage1D = (PFNGLTEXIMAGE1DPROC)GetProcAddress(lib, "glTexImage1D")) == NULL) || r;
    r = ((glTexImage2D = (PFNGLTEXIMAGE2DPROC)GetProcAddress(lib, "glTexImage2D")) == NULL) || r;
    r = ((glDrawBuffer = (PFNGLDRAWBUFFERPROC)GetProcAddress(lib, "glDrawBuffer")) == NULL) || r;
    r = ((glClear = (PFNGLCLEARPROC)GetProcAddress(lib, "glClear")) == NULL) || r;
    r = ((glClearColor = (PFNGLCLEARCOLORPROC)GetProcAddress(lib, "glClearColor")) == NULL) || r;
    r = ((glClearStencil = (PFNGLCLEARSTENCILPROC)GetProcAddress(lib, "glClearStencil")) == NULL) || r;
    r = ((glClearDepth = (PFNGLCLEARDEPTHPROC)GetProcAddress(lib, "glClearDepth")) == NULL) || r;
    r = ((glStencilMask = (PFNGLSTENCILMASKPROC)GetProcAddress(lib, "glStencilMask")) == NULL) || r;
    r = ((glColorMask = (PFNGLCOLORMASKPROC)GetProcAddress(lib, "glColorMask")) == NULL) || r;
    r = ((glDepthMask = (PFNGLDEPTHMASKPROC)GetProcAddress(lib, "glDepthMask")) == NULL) || r;
    r = ((glDisable = (PFNGLDISABLEPROC)GetProcAddress(lib, "glDisable")) == NULL) || r;
    r = ((glEnable = (PFNGLENABLEPROC)GetProcAddress(lib, "glEnable")) == NULL) || r;
    r = ((glFinish = (PFNGLFINISHPROC)GetProcAddress(lib, "glFinish")) == NULL) || r;
    r = ((glFlush = (PFNGLFLUSHPROC)GetProcAddress(lib, "glFlush")) == NULL) || r;
    r = ((glBlendFunc = (PFNGLBLENDFUNCPROC)GetProcAddress(lib, "glBlendFunc")) == NULL) || r;
    r = ((glLogicOp = (PFNGLLOGICOPPROC)GetProcAddress(lib, "glLogicOp")) == NULL) || r;
    r = ((glStencilFunc = (PFNGLSTENCILFUNCPROC)GetProcAddress(lib, "glStencilFunc")) == NULL) || r;
    r = ((glStencilOp = (PFNGLSTENCILOPPROC)GetProcAddress(lib, "glStencilOp")) == NULL) || r;
    r = ((glDepthFunc = (PFNGLDEPTHFUNCPROC)GetProcAddress(lib, "glDepthFunc")) == NULL) || r;
    r = ((glPixelStoref = (PFNGLPIXELSTOREFPROC)GetProcAddress(lib, "glPixelStoref")) == NULL) || r;
    r = ((glPixelStorei = (PFNGLPIXELSTOREIPROC)GetProcAddress(lib, "glPixelStorei")) == NULL) || r;
    r = ((glReadBuffer = (PFNGLREADBUFFERPROC)GetProcAddress(lib, "glReadBuffer")) == NULL) || r;
    r = ((glReadPixels = (PFNGLREADPIXELSPROC)GetProcAddress(lib, "glReadPixels")) == NULL) || r;
    r = ((glGetBooleanv = (PFNGLGETBOOLEANVPROC)GetProcAddress(lib, "glGetBooleanv")) == NULL) || r;
    r = ((glGetDoublev = (PFNGLGETDOUBLEVPROC)GetProcAddress(lib, "glGetDoublev")) == NULL) || r;
    r = ((glGetError = (PFNGLGETERRORPROC)GetProcAddress(lib, "glGetError")) == NULL) || r;
    r = ((glGetFloatv = (PFNGLGETFLOATVPROC)GetProcAddress(lib, "glGetFloatv")) == NULL) || r;
    r = ((glGetIntegerv = (PFNGLGETINTEGERVPROC)GetProcAddress(lib, "glGetIntegerv")) == NULL) || r;
    r = ((glGetString = (PFNGLGETSTRINGPROC)GetProcAddress(lib, "glGetString")) == NULL) || r;
    r = ((glGetTexImage = (PFNGLGETTEXIMAGEPROC)GetProcAddress(lib, "glGetTexImage")) == NULL) || r;
    r = ((glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)GetProcAddress(lib, "glGetTexParameterfv")) == NULL) || r;
    r = ((glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)GetProcAddress(lib, "glGetTexParameteriv")) == NULL) || r;
    r = ((glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC)GetProcAddress(lib, "glGetTexLevelParameterfv")) == NULL) || r;
    r = ((glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC)GetProcAddress(lib, "glGetTexLevelParameteriv")) == NULL) || r;
    r = ((glIsEnabled = (PFNGLISENABLEDPROC)GetProcAddress(lib, "glIsEnabled")) == NULL) || r;
    r = ((glDepthRange = (PFNGLDEPTHRANGEPROC)GetProcAddress(lib, "glDepthRange")) == NULL) || r;
    r = ((glViewport = (PFNGLVIEWPORTPROC)GetProcAddress(lib, "glViewport")) == NULL) || r;
    return r;
}

static BOOL find_GL_extensions(const char* pName) {
    const char* extensions = (const char*)glGetString(GL_EXTENSIONS);
    size_t size = strlen(pName);
    while (extensions) {
        if (!strncmp(extensions, pName, size) && (*(extensions + size) == 0 || *(extensions + size) == ' '))
            return TRUE;
        extensions = strchr(extensions, ' ');
        if (extensions)
            extensions++;
    }
    return FALSE;
}

static BOOL find_GL_version(GLint majorVersion, GLint minorVersion) {
    GLint m_majorVersion = 0, m_minorVersion = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &m_majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &m_minorVersion);
    if (m_majorVersion > majorVersion)
        return TRUE;
    else if (m_majorVersion == majorVersion)
        if (m_minorVersion >= minorVersion) {
            return TRUE;
        }
    return FALSE;
}

void (APIENTRYP glDrawArrays)(GLenum mode, GLint first, GLsizei count);

void (APIENTRYP glDrawElements)(GLenum mode, GLsizei count, GLenum type, const void* indices);

void (APIENTRYP glGetPointerv)(GLenum pname, void** params);

void (APIENTRYP glPolygonOffset)(GLfloat factor, GLfloat units);

void (APIENTRYP glCopyTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width,
    GLint border);

void (APIENTRYP glCopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width,
    GLsizei height, GLint border);

void (APIENTRYP glCopyTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);

void (APIENTRYP glCopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y,
    GLsizei width, GLsizei height);

void (APIENTRYP glTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type,
    const void* pixels);

void
(APIENTRYP glTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
    GLenum format, GLenum type, const void* pixels);

void (APIENTRYP glBindTexture)(GLenum target, GLuint texture);

void (APIENTRYP glDeleteTextures)(GLsizei n, const GLuint* textures);

void (APIENTRYP glGenTextures)(GLsizei n, GLuint* textures);

GLboolean(APIENTRYP glIsTexture)(GLuint texture);

static GLboolean GET_GL_FUNCTIONS_GL_VERSION_1_1(HMODULE lib) {
    GLboolean r = GL_FALSE;
    r = ((glDrawArrays = (PFNGLDRAWARRAYSPROC)GetProcAddress(lib, "glDrawArrays")) == NULL) || r;
    r = ((glDrawElements = (PFNGLDRAWELEMENTSPROC)GetProcAddress(lib, "glDrawElements")) == NULL) || r;
    r = ((glGetPointerv = (PFNGLGETPOINTERVPROC)GetProcAddress(lib, "glGetPointerv")) == NULL) || r;
    r = ((glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)GetProcAddress(lib, "glPolygonOffset")) == NULL) || r;
    r = ((glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC)GetProcAddress(lib, "glCopyTexImage1D")) == NULL) || r;
    r = ((glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)GetProcAddress(lib, "glCopyTexImage2D")) == NULL) || r;
    r = ((glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC)GetProcAddress(lib, "glCopyTexSubImage1D")) ==
        NULL) || r;
    r = ((glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)GetProcAddress(lib, "glCopyTexSubImage2D")) ==
        NULL) || r;
    r = ((glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC)GetProcAddress(lib, "glTexSubImage1D")) == NULL) || r;
    r = ((glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)GetProcAddress(lib, "glTexSubImage2D")) == NULL) || r;
    r = ((glBindTexture = (PFNGLBINDTEXTUREPROC)GetProcAddress(lib, "glBindTexture")) == NULL) || r;
    r = ((glDeleteTextures = (PFNGLDELETETEXTURESPROC)GetProcAddress(lib, "glDeleteTextures")) == NULL) || r;
    r = ((glGenTextures = (PFNGLGENTEXTURESPROC)GetProcAddress(lib, "glGenTextures")) == NULL) || r;
    r = ((glIsTexture = (PFNGLISTEXTUREPROC)GetProcAddress(lib, "glIsTexture")) == NULL) || r;
    return r;
}

void (APIENTRYP glActiveTexture)(GLenum texture);

void (APIENTRYP glSampleCoverage)(GLfloat value, GLboolean invert);

void
(APIENTRYP glCompressedTexImage3D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height,
    GLsizei depth, GLint border, GLsizei imageSize, const void* data);

void
(APIENTRYP glCompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height,
    GLint border, GLsizei imageSize, const void* data);

void (APIENTRYP glCompressedTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border,
    GLsizei imageSize, const void* data);

void (APIENTRYP glCompressedTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
    GLsizei width, GLsizei height, GLsizei depth, GLenum format,
    GLsizei imageSize, const void* data);

void (APIENTRYP glCompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
    GLsizei height, GLenum format, GLsizei imageSize, const void* data);

void (APIENTRYP glCompressedTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format,
    GLsizei imageSize, const void* data);

void (APIENTRYP glGetCompressedTexImage)(GLenum target, GLint level, void* img);

static GLboolean GET_GL_FUNCTIONS_GL_VERSION_1_3(PROC(WINAPI* glGetProcAddress)(LPCSTR)) {
    GLboolean r = GL_FALSE;
    r = ((glActiveTexture = (PFNGLACTIVETEXTUREPROC)glGetProcAddress("glActiveTexture")) == NULL) || r;
    r = ((glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)glGetProcAddress("glSampleCoverage")) == NULL) || r;
    r = ((glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)glGetProcAddress("glCompressedTexImage3D")) == NULL) || r;
    r = ((glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)glGetProcAddress("glCompressedTexImage2D")) == NULL) || r;
    r = ((glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)glGetProcAddress("glCompressedTexImage1D")) == NULL) || r;
    r = ((glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)glGetProcAddress("glCompressedTexSubImage3D")) == NULL) || r;
    r = ((glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)glGetProcAddress("glCompressedTexSubImage2D")) == NULL) || r;
    r = ((glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)glGetProcAddress("glCompressedTexSubImage1D")) == NULL) || r;
    r = ((glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)glGetProcAddress("glGetCompressedTexImage")) == NULL) || r;
    return r;
}

void (APIENTRYP glBindBuffer)(GLenum target, GLuint buffer);

void (APIENTRYP glDeleteBuffers)(GLsizei n, const GLuint* buffers);

void (APIENTRYP glGenBuffers)(GLsizei n, GLuint* buffers);

GLboolean(APIENTRYP glIsBuffer)(GLuint buffer);

void (APIENTRYP glBufferData)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);

void (APIENTRYP glBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);

void (APIENTRYP glGetBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, void* data);

void* (APIENTRYP glMapBuffer)(GLenum target, GLenum access);

GLboolean(APIENTRYP glUnmapBuffer)(GLenum target);

void (APIENTRYP glGetBufferParameteriv)(GLenum target, GLenum pname, GLint* params);

void (APIENTRYP glGetBufferPointerv)(GLenum target, GLenum pname, void** params);

static GLboolean GET_GL_FUNCTIONS_GL_VERSION_1_5(PROC(WINAPI* glGetProcAddress)(LPCSTR)) {
    GLboolean r = GL_FALSE;
    r = ((glBindBuffer = (PFNGLBINDBUFFERPROC)glGetProcAddress("glBindBuffer")) == NULL) || r;
    r = ((glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glGetProcAddress("glDeleteBuffers")) == NULL) || r;
    r = ((glGenBuffers = (PFNGLGENBUFFERSPROC)glGetProcAddress("glGenBuffers")) == NULL) || r;
    r = ((glIsBuffer = (PFNGLISBUFFERPROC)glGetProcAddress("glIsBuffer")) == NULL) || r;
    r = ((glBufferData = (PFNGLBUFFERDATAPROC)glGetProcAddress("glBufferData")) == NULL) || r;
    r = ((glBufferSubData = (PFNGLBUFFERSUBDATAPROC)glGetProcAddress("glBufferSubData")) == NULL) || r;
    r = ((glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)glGetProcAddress("glGetBufferSubData")) == NULL) ||
        r;
    r = ((glMapBuffer = (PFNGLMAPBUFFERPROC)glGetProcAddress("glMapBuffer")) == NULL) || r;
    r = ((glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)glGetProcAddress("glUnmapBuffer")) == NULL) || r;
    r = ((glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)glGetProcAddress("glGetBufferParameteriv")) == NULL) || r;
    r = ((glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)glGetProcAddress("glGetBufferPointerv")) ==
        NULL) || r;
    return r;
}

void (APIENTRYP glBlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha);

void (APIENTRYP glDrawBuffers)(GLsizei n, const GLenum* bufs);

void (APIENTRYP glStencilOpSeparate)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);

void (APIENTRYP glStencilFuncSeparate)(GLenum face, GLenum func, GLint ref, GLuint mask);

void (APIENTRYP glStencilMaskSeparate)(GLenum face, GLuint mask);

void (APIENTRYP glAttachShader)(GLuint program, GLuint shader);

void (APIENTRYP glBindAttribLocation)(GLuint program, GLuint index, const GLchar* name);

void (APIENTRYP glCompileShader)(GLuint shader);

GLuint(APIENTRYP glCreateProgram)(void);

GLuint(APIENTRYP glCreateShader)(GLenum type);

void (APIENTRYP glDeleteProgram)(GLuint program);

void (APIENTRYP glDeleteShader)(GLuint shader);

void (APIENTRYP glDetachShader)(GLuint program, GLuint shader);

void (APIENTRYP glDisableVertexAttribArray)(GLuint index);

void (APIENTRYP glEnableVertexAttribArray)(GLuint index);

void
(APIENTRYP glGetActiveAttrib)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type,
    GLchar* name);

void (APIENTRYP glGetActiveUniform)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size,
    GLenum* type, GLchar* name);

void (APIENTRYP glGetAttachedShaders)(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders);

GLint(APIENTRYP glGetAttribLocation)(GLuint program, const GLchar* name);

void (APIENTRYP glGetProgramiv)(GLuint program, GLenum pname, GLint* params);

void (APIENTRYP glGetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);

void (APIENTRYP glGetShaderiv)(GLuint shader, GLenum pname, GLint* params);

void (APIENTRYP glGetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);

void (APIENTRYP glGetShaderSource)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source);

GLint(APIENTRYP glGetUniformLocation)(GLuint program, const GLchar* name);

void (APIENTRYP glGetUniformfv)(GLuint program, GLint location, GLfloat* params);

void (APIENTRYP glGetUniformiv)(GLuint program, GLint location, GLint* params);

void (APIENTRYP glGetVertexAttribdv)(GLuint index, GLenum pname, GLdouble* params);

void (APIENTRYP glGetVertexAttribfv)(GLuint index, GLenum pname, GLfloat* params);

void (APIENTRYP glGetVertexAttribiv)(GLuint index, GLenum pname, GLint* params);

void (APIENTRYP glGetVertexAttribPointerv)(GLuint index, GLenum pname, void** pointer);

GLboolean(APIENTRYP glIsProgram)(GLuint program);

GLboolean(APIENTRYP glIsShader)(GLuint shader);

void (APIENTRYP glLinkProgram)(GLuint program);

void (APIENTRYP glShaderSource)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);

void (APIENTRYP glUseProgram)(GLuint program);

void (APIENTRYP glUniform1f)(GLint location, GLfloat v0);

void (APIENTRYP glUniform2f)(GLint location, GLfloat v0, GLfloat v1);

void (APIENTRYP glUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);

void (APIENTRYP glUniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

void (APIENTRYP glUniform1i)(GLint location, GLint v0);

void (APIENTRYP glUniform2i)(GLint location, GLint v0, GLint v1);

void (APIENTRYP glUniform3i)(GLint location, GLint v0, GLint v1, GLint v2);

void (APIENTRYP glUniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);

void (APIENTRYP glUniform1fv)(GLint location, GLsizei count, const GLfloat* value);

void (APIENTRYP glUniform2fv)(GLint location, GLsizei count, const GLfloat* value);

void (APIENTRYP glUniform3fv)(GLint location, GLsizei count, const GLfloat* value);

void (APIENTRYP glUniform4fv)(GLint location, GLsizei count, const GLfloat* value);

void (APIENTRYP glUniform1iv)(GLint location, GLsizei count, const GLint* value);

void (APIENTRYP glUniform2iv)(GLint location, GLsizei count, const GLint* value);

void (APIENTRYP glUniform3iv)(GLint location, GLsizei count, const GLint* value);

void (APIENTRYP glUniform4iv)(GLint location, GLsizei count, const GLint* value);

void (APIENTRYP glUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

void (APIENTRYP glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

void (APIENTRYP glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

void (APIENTRYP glValidateProgram)(GLuint program);

void (APIENTRYP glVertexAttrib1d)(GLuint index, GLdouble x);

void (APIENTRYP glVertexAttrib1dv)(GLuint index, const GLdouble* v);

void (APIENTRYP glVertexAttrib1f)(GLuint index, GLfloat x);

void (APIENTRYP glVertexAttrib1fv)(GLuint index, const GLfloat* v);

void (APIENTRYP glVertexAttrib1s)(GLuint index, GLshort x);

void (APIENTRYP glVertexAttrib1sv)(GLuint index, const GLshort* v);

void (APIENTRYP glVertexAttrib2d)(GLuint index, GLdouble x, GLdouble y);

void (APIENTRYP glVertexAttrib2dv)(GLuint index, const GLdouble* v);

void (APIENTRYP glVertexAttrib2f)(GLuint index, GLfloat x, GLfloat y);

void (APIENTRYP glVertexAttrib2fv)(GLuint index, const GLfloat* v);

void (APIENTRYP glVertexAttrib2s)(GLuint index, GLshort x, GLshort y);

void (APIENTRYP glVertexAttrib2sv)(GLuint index, const GLshort* v);

void (APIENTRYP glVertexAttrib3d)(GLuint index, GLdouble x, GLdouble y, GLdouble z);

void (APIENTRYP glVertexAttrib3dv)(GLuint index, const GLdouble* v);

void (APIENTRYP glVertexAttrib3f)(GLuint index, GLfloat x, GLfloat y, GLfloat z);

void (APIENTRYP glVertexAttrib3fv)(GLuint index, const GLfloat* v);

void (APIENTRYP glVertexAttrib3s)(GLuint index, GLshort x, GLshort y, GLshort z);

void (APIENTRYP glVertexAttrib3sv)(GLuint index, const GLshort* v);

void (APIENTRYP glVertexAttrib4Nbv)(GLuint index, const GLbyte* v);

void (APIENTRYP glVertexAttrib4Niv)(GLuint index, const GLint* v);

void (APIENTRYP glVertexAttrib4Nsv)(GLuint index, const GLshort* v);

void (APIENTRYP glVertexAttrib4Nub)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);

void (APIENTRYP glVertexAttrib4Nubv)(GLuint index, const GLubyte* v);

void (APIENTRYP glVertexAttrib4Nuiv)(GLuint index, const GLuint* v);

void (APIENTRYP glVertexAttrib4Nusv)(GLuint index, const GLushort* v);

void (APIENTRYP glVertexAttrib4bv)(GLuint index, const GLbyte* v);

void (APIENTRYP glVertexAttrib4d)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);

void (APIENTRYP glVertexAttrib4dv)(GLuint index, const GLdouble* v);

void (APIENTRYP glVertexAttrib4f)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

void (APIENTRYP glVertexAttrib4fv)(GLuint index, const GLfloat* v);

void (APIENTRYP glVertexAttrib4iv)(GLuint index, const GLint* v);

void (APIENTRYP glVertexAttrib4s)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);

void (APIENTRYP glVertexAttrib4sv)(GLuint index, const GLshort* v);

void (APIENTRYP glVertexAttrib4ubv)(GLuint index, const GLubyte* v);

void (APIENTRYP glVertexAttrib4uiv)(GLuint index, const GLuint* v);

void (APIENTRYP glVertexAttrib4usv)(GLuint index, const GLushort* v);

void (APIENTRYP glVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
    const void* pointer);

static GLboolean GET_GL_FUNCTIONS_GL_VERSION_2_0(PROC(WINAPI* glGetProcAddress)(LPCSTR)) {
    GLboolean r = GL_FALSE;
    r = ((glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)glGetProcAddress("glBlendEquationSeparate")) == NULL) || r;
    r = ((glDrawBuffers = (PFNGLDRAWBUFFERSPROC)glGetProcAddress("glDrawBuffers")) == NULL) || r;
    r = ((glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)glGetProcAddress("glStencilOpSeparate")) ==
        NULL) || r;
    r = ((glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)glGetProcAddress("glStencilFuncSeparate")) ==
        NULL) || r;
    r = ((glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)glGetProcAddress("glStencilMaskSeparate")) ==
        NULL) || r;
    r = ((glAttachShader = (PFNGLATTACHSHADERPROC)glGetProcAddress("glAttachShader")) == NULL) || r;
    r = ((glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)glGetProcAddress("glBindAttribLocation")) ==
        NULL) || r;
    r = ((glCompileShader = (PFNGLCOMPILESHADERPROC)glGetProcAddress("glCompileShader")) == NULL) || r;
    r = ((glCreateProgram = (PFNGLCREATEPROGRAMPROC)glGetProcAddress("glCreateProgram")) == NULL) || r;
    r = ((glCreateShader = (PFNGLCREATESHADERPROC)glGetProcAddress("glCreateShader")) == NULL) || r;
    r = ((glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glGetProcAddress("glDeleteProgram")) == NULL) || r;
    r = ((glDeleteShader = (PFNGLDELETESHADERPROC)glGetProcAddress("glDeleteShader")) == NULL) || r;
    r = ((glDetachShader = (PFNGLDETACHSHADERPROC)glGetProcAddress("glDetachShader")) == NULL) || r;
    r = ((glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)glGetProcAddress(
        "glDisableVertexAttribArray")) == NULL) || r;
    r = ((glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glGetProcAddress("glEnableVertexAttribArray")) == NULL) || r;
    r = ((glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)glGetProcAddress("glGetActiveAttrib")) == NULL) || r;
    r = ((glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)glGetProcAddress("glGetActiveUniform")) == NULL) ||
        r;
    r = ((glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)glGetProcAddress("glGetAttachedShaders")) ==
        NULL) || r;
    r = ((glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)glGetProcAddress("glGetAttribLocation")) ==
        NULL) || r;
    r = ((glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glGetProcAddress("glGetProgramiv")) == NULL) || r;
    r = ((glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glGetProcAddress("glGetProgramInfoLog")) ==
        NULL) || r;
    r = ((glGetShaderiv = (PFNGLGETSHADERIVPROC)glGetProcAddress("glGetShaderiv")) == NULL) || r;
    r = ((glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glGetProcAddress("glGetShaderInfoLog")) == NULL) ||
        r;
    r = ((glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)glGetProcAddress("glGetShaderSource")) == NULL) || r;
    r = ((glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glGetProcAddress("glGetUniformLocation")) ==
        NULL) || r;
    r = ((glGetUniformfv = (PFNGLGETUNIFORMFVPROC)glGetProcAddress("glGetUniformfv")) == NULL) || r;
    r = ((glGetUniformiv = (PFNGLGETUNIFORMIVPROC)glGetProcAddress("glGetUniformiv")) == NULL) || r;
    r = ((glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)glGetProcAddress("glGetVertexAttribdv")) ==
        NULL) || r;
    r = ((glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)glGetProcAddress("glGetVertexAttribfv")) ==
        NULL) || r;
    r = ((glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)glGetProcAddress("glGetVertexAttribiv")) ==
        NULL) || r;
    r = ((glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)glGetProcAddress("glGetVertexAttribPointerv")) == NULL) || r;
    r = ((glIsProgram = (PFNGLISPROGRAMPROC)glGetProcAddress("glIsProgram")) == NULL) || r;
    r = ((glIsShader = (PFNGLISSHADERPROC)glGetProcAddress("glIsShader")) == NULL) || r;
    r = ((glLinkProgram = (PFNGLLINKPROGRAMPROC)glGetProcAddress("glLinkProgram")) == NULL) || r;
    r = ((glShaderSource = (PFNGLSHADERSOURCEPROC)glGetProcAddress("glShaderSource")) == NULL) || r;
    r = ((glUseProgram = (PFNGLUSEPROGRAMPROC)glGetProcAddress("glUseProgram")) == NULL) || r;
    r = ((glUniform1f = (PFNGLUNIFORM1FPROC)glGetProcAddress("glUniform1f")) == NULL) || r;
    r = ((glUniform2f = (PFNGLUNIFORM2FPROC)glGetProcAddress("glUniform2f")) == NULL) || r;
    r = ((glUniform3f = (PFNGLUNIFORM3FPROC)glGetProcAddress("glUniform3f")) == NULL) || r;
    r = ((glUniform4f = (PFNGLUNIFORM4FPROC)glGetProcAddress("glUniform4f")) == NULL) || r;
    r = ((glUniform1i = (PFNGLUNIFORM1IPROC)glGetProcAddress("glUniform1i")) == NULL) || r;
    r = ((glUniform2i = (PFNGLUNIFORM2IPROC)glGetProcAddress("glUniform2i")) == NULL) || r;
    r = ((glUniform3i = (PFNGLUNIFORM3IPROC)glGetProcAddress("glUniform3i")) == NULL) || r;
    r = ((glUniform4i = (PFNGLUNIFORM4IPROC)glGetProcAddress("glUniform4i")) == NULL) || r;
    r = ((glUniform1fv = (PFNGLUNIFORM1FVPROC)glGetProcAddress("glUniform1fv")) == NULL) || r;
    r = ((glUniform2fv = (PFNGLUNIFORM2FVPROC)glGetProcAddress("glUniform2fv")) == NULL) || r;
    r = ((glUniform3fv = (PFNGLUNIFORM3FVPROC)glGetProcAddress("glUniform3fv")) == NULL) || r;
    r = ((glUniform4fv = (PFNGLUNIFORM4FVPROC)glGetProcAddress("glUniform4fv")) == NULL) || r;
    r = ((glUniform1iv = (PFNGLUNIFORM1IVPROC)glGetProcAddress("glUniform1iv")) == NULL) || r;
    r = ((glUniform2iv = (PFNGLUNIFORM2IVPROC)glGetProcAddress("glUniform2iv")) == NULL) || r;
    r = ((glUniform3iv = (PFNGLUNIFORM3IVPROC)glGetProcAddress("glUniform3iv")) == NULL) || r;
    r = ((glUniform4iv = (PFNGLUNIFORM4IVPROC)glGetProcAddress("glUniform4iv")) == NULL) || r;
    r = ((glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)glGetProcAddress("glUniformMatrix2fv")) == NULL) ||
        r;
    r = ((glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)glGetProcAddress("glUniformMatrix3fv")) == NULL) ||
        r;
    r = ((glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glGetProcAddress("glUniformMatrix4fv")) == NULL) ||
        r;
    r = ((glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)glGetProcAddress("glValidateProgram")) == NULL) || r;
    r = ((glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)glGetProcAddress("glVertexAttrib1d")) == NULL) || r;
    r = ((glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)glGetProcAddress("glVertexAttrib1dv")) == NULL) || r;
    r = ((glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)glGetProcAddress("glVertexAttrib1f")) == NULL) || r;
    r = ((glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)glGetProcAddress("glVertexAttrib1fv")) == NULL) || r;
    r = ((glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)glGetProcAddress("glVertexAttrib1s")) == NULL) || r;
    r = ((glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)glGetProcAddress("glVertexAttrib1sv")) == NULL) || r;
    r = ((glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)glGetProcAddress("glVertexAttrib2d")) == NULL) || r;
    r = ((glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)glGetProcAddress("glVertexAttrib2dv")) == NULL) || r;
    r = ((glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)glGetProcAddress("glVertexAttrib2f")) == NULL) || r;
    r = ((glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)glGetProcAddress("glVertexAttrib2fv")) == NULL) || r;
    r = ((glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)glGetProcAddress("glVertexAttrib2s")) == NULL) || r;
    r = ((glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)glGetProcAddress("glVertexAttrib2sv")) == NULL) || r;
    r = ((glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)glGetProcAddress("glVertexAttrib3d")) == NULL) || r;
    r = ((glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)glGetProcAddress("glVertexAttrib3dv")) == NULL) || r;
    r = ((glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)glGetProcAddress("glVertexAttrib3f")) == NULL) || r;
    r = ((glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)glGetProcAddress("glVertexAttrib3fv")) == NULL) || r;
    r = ((glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)glGetProcAddress("glVertexAttrib3s")) == NULL) || r;
    r = ((glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)glGetProcAddress("glVertexAttrib3sv")) == NULL) || r;
    r = ((glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)glGetProcAddress("glVertexAttrib4Nbv")) == NULL) ||
        r;
    r = ((glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)glGetProcAddress("glVertexAttrib4Niv")) == NULL) ||
        r;
    r = ((glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)glGetProcAddress("glVertexAttrib4Nsv")) == NULL) ||
        r;
    r = ((glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)glGetProcAddress("glVertexAttrib4Nub")) == NULL) ||
        r;
    r = ((glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)glGetProcAddress("glVertexAttrib4Nubv")) ==
        NULL) || r;
    r = ((glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)glGetProcAddress("glVertexAttrib4Nuiv")) ==
        NULL) || r;
    r = ((glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)glGetProcAddress("glVertexAttrib4Nusv")) ==
        NULL) || r;
    r = ((glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)glGetProcAddress("glVertexAttrib4bv")) == NULL) || r;
    r = ((glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)glGetProcAddress("glVertexAttrib4d")) == NULL) || r;
    r = ((glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)glGetProcAddress("glVertexAttrib4dv")) == NULL) || r;
    r = ((glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)glGetProcAddress("glVertexAttrib4f")) == NULL) || r;
    r = ((glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)glGetProcAddress("glVertexAttrib4fv")) == NULL) || r;
    r = ((glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)glGetProcAddress("glVertexAttrib4iv")) == NULL) || r;
    r = ((glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)glGetProcAddress("glVertexAttrib4s")) == NULL) || r;
    r = ((glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)glGetProcAddress("glVertexAttrib4sv")) == NULL) || r;
    r = ((glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)glGetProcAddress("glVertexAttrib4ubv")) == NULL) ||
        r;
    r = ((glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)glGetProcAddress("glVertexAttrib4uiv")) == NULL) ||
        r;
    r = ((glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)glGetProcAddress("glVertexAttrib4usv")) == NULL) ||
        r;
    r = ((glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glGetProcAddress("glVertexAttribPointer")) ==
        NULL) || r;
    return r;
}

PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLISVERTEXARRAYPROC glIsVertexArray;

static GLboolean GET_GL_FUNCTIONS_GL_vertex_array_object(PROC(WINAPI* glGetProcAddress)(LPCSTR)) {
    GLboolean r = GL_FALSE;
    r = ((glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glGetProcAddress("glBindVertexArray")) == NULL) || r;
    r = ((glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glGetProcAddress("glDeleteVertexArrays")) ==
        NULL) || r;
    r = ((glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glGetProcAddress("glGenVertexArrays")) == NULL) || r;
    r = ((glIsVertexArray = (PFNGLISVERTEXARRAYPROC)glGetProcAddress("glIsVertexArray")) == NULL) || r;
    return r;
}

PFNGLBINDVERTEXBUFFERPROC glBindVertexBuffer;
PFNGLVERTEXATTRIBFORMATPROC glVertexAttribFormat;
PFNGLVERTEXATTRIBIFORMATPROC glVertexAttribIFormat;
PFNGLVERTEXATTRIBLFORMATPROC glVertexAttribLFormat;
PFNGLVERTEXATTRIBBINDINGPROC glVertexAttribBinding;
PFNGLVERTEXBINDINGDIVISORPROC glVertexBindingDivisor;

static GLboolean GET_GL_FUNCTIONS_GL_vertex_attrib_binding(PROC(WINAPI* glGetProcAddress)(LPCSTR)) {
    GLboolean r = GL_FALSE;
    r = ((glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)glGetProcAddress("glBindVertexBuffer")) == NULL) ||
        r;
    r = ((glVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC)glGetProcAddress("glVertexAttribFormat")) ==
        NULL) || r;
    r = ((glVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC)glGetProcAddress("glVertexAttribIFormat")) ==
        NULL) || r;
    r = ((glVertexAttribLFormat = (PFNGLVERTEXATTRIBLFORMATPROC)glGetProcAddress("glVertexAttribLFormat")) ==
        NULL) || r;
    r = ((glVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC)glGetProcAddress("glVertexAttribBinding")) ==
        NULL) || r;
    r = ((glVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC)glGetProcAddress("glVertexBindingDivisor")) == NULL) || r;
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

static GLboolean GET_GL_FUNCTIONS_GL_KHR_debug(PROC(WINAPI* glGetProcAddress)(LPCSTR)) {
    GLboolean r = GL_FALSE;
    r = ((glDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)glGetProcAddress("glDebugMessageControl")) ==
        NULL) || r;
    r = ((glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)glGetProcAddress("glDebugMessageInsert")) ==
        NULL) || r;
    r = ((glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)glGetProcAddress("glDebugMessageCallback")) == NULL) || r;
    r = ((glGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC)glGetProcAddress("glGetDebugMessageLog")) ==
        NULL) || r;
    r = ((glGetPointerv = (PFNGLGETPOINTERVPROC)glGetProcAddress("glGetPointerv")) == NULL) || r;
    r = ((glPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC)glGetProcAddress("glPushDebugGroup")) == NULL) || r;
    r = ((glPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC)glGetProcAddress("glPopDebugGroup")) == NULL) || r;
    r = ((glObjectLabel = (PFNGLOBJECTLABELPROC)glGetProcAddress("glObjectLabel")) == NULL) || r;
    r = ((glGetObjectLabel = (PFNGLGETOBJECTLABELPROC)glGetProcAddress("glGetObjectLabel")) == NULL) || r;
    r = ((glObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC)glGetProcAddress("glObjectPtrLabel")) == NULL) || r;
    r = ((glGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC)glGetProcAddress("glGetObjectPtrLabel")) ==
        NULL) || r;
    return r;
}

PFNGLGETUNIFORMINDICESPROC glGetUniformIndices;
PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv;
PFNGLGETACTIVEUNIFORMNAMEPROC glGetActiveUniformName;
PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName;
PFNGLBINDBUFFERRANGEPROC glBindBufferRange;
PFNGLBINDBUFFERBASEPROC glBindBufferBase;
PFNGLGETINTEGERI_VPROC glGetIntegeri_v;
PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding;

static GLboolean GET_GL_FUNCTIONS_GL_ARB_uniform_buffer_object(PROC(WINAPI* glGetProcAddress)(LPCSTR)) {
    GLboolean r = GL_FALSE;
    r = ((glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)glGetProcAddress("glGetUniformIndices")) ==
        NULL) || r;
    r = ((glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)glGetProcAddress("glGetActiveUniformsiv")) ==
        NULL) || r;
    r = ((glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)glGetProcAddress("glGetActiveUniformName")) == NULL) || r;
    r = ((glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)glGetProcAddress("glGetUniformBlockIndex")) == NULL) || r;
    r = ((glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)glGetProcAddress("glGetActiveUniformBlockiv")) == NULL) || r;
    r = ((glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)glGetProcAddress(
        "glGetActiveUniformBlockName")) == NULL) || r;
    r = ((glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)glGetProcAddress("glBindBufferRange")) == NULL) || r;
    r = ((glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)glGetProcAddress("glBindBufferBase")) == NULL) || r;
    r = ((glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)glGetProcAddress("glGetIntegeri_v")) == NULL) || r;
    r = ((glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)glGetProcAddress("glUniformBlockBinding")) ==
        NULL) || r;
    return r;
}

static void APIENTRY
glCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
    const void* userParam) {
    GLuint i_0, i_1, i_2;
    GLchar* glCallbackMessages[] = {
        "Not found\n",
        "Calls to the OpenGL API\n",
        "Calls to a window-system API\n",
        "A compiler for a shading language\n",
        "An application associated with OpenGL \n",
        "Generated by the user of this application\n",
        "Some source that isn't one of these\n",
        "An error, typically from the API\n",
        "Some behavior marked deprecated has been used\n",
        "Something has invoked undefined behavior\n",
        "Some functionality the user relies upon is not portable\n",
        "Code has triggered possible performance issues\n",
        "Command stream annotation\n",
        "Group pushing\n",
        "Pop Group\n",
        "Some type that isn't one of these ",
        "All OpenGL Errors, shader compilation/linking errors, or highly-dangerous undefined behavior\n",
        "Major performance warnings, shader compilation/linking warnings, or the use of deprecated functionality\n",
        "Redundant state change performance warning, or unimportant undefined behavior\n",
        "Anything that isn't an error or performance issue.\n"
    };
    i_0 = i_1 = i_2 = 0;
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
    printf("\n---------------\nDebug message (%i): %s\n", id, message);
    switch (source)
    {
    case GL_DEBUG_SOURCE_API: i_0 = 1; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM: i_0 = 2; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: i_0 = 3; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY: i_0 = 4; break;
    case GL_DEBUG_SOURCE_APPLICATION: i_0 = 5; break;
    case GL_DEBUG_SOURCE_OTHER: i_0 = 6; break;
    }
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR: i_1 = 7; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: i_1 = 8; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: i_1 = 9; break;
    case GL_DEBUG_TYPE_PORTABILITY: i_1 = 10; break;
    case GL_DEBUG_TYPE_PERFORMANCE: i_1 = 11; break;
    case GL_DEBUG_TYPE_MARKER: i_1 = 12; break;
    case GL_DEBUG_TYPE_PUSH_GROUP: i_1 = 13; break;
    case GL_DEBUG_TYPE_POP_GROUP: i_1 = 14; break;
    case GL_DEBUG_TYPE_OTHER: i_1 = 15; break;
    }
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH: i_2 = 16; break;
    case GL_DEBUG_SEVERITY_MEDIUM: i_2 = 17; break;
    case GL_DEBUG_SEVERITY_LOW: i_2 = 18; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: i_2 = 19; break;
    }
    printf("%s %s %s", glCallbackMessages[i_0], glCallbackMessages[i_1], glCallbackMessages[i_2]);
}

static const char* get_OpenGL_functions(HMODULE lib, PROC(WINAPI* glGetProcAddress)(LPCSTR)) {
    GET_GL_FUNCTIONS_GL_VERSION_1_0(lib);
    if (!find_GL_version(1, 1)) return OpenGL_STANDARD[1];
    GET_GL_FUNCTIONS_GL_VERSION_1_1(lib);
    if (!find_GL_version(1, 3)) return OpenGL_STANDARD[2];
    GET_GL_FUNCTIONS_GL_VERSION_1_3(glGetProcAddress);
    if (!find_GL_version(1, 5)) return OpenGL_STANDARD[3];
    GET_GL_FUNCTIONS_GL_VERSION_1_5(glGetProcAddress);
    if (!find_GL_version(2, 0)) return OpenGL_STANDARD[4];
    GET_GL_FUNCTIONS_GL_VERSION_2_0(glGetProcAddress);
    if (!find_GL_extensions(OpenGL_STANDARD[5])) return OpenGL_STANDARD[5];
    GET_GL_FUNCTIONS_GL_vertex_array_object(glGetProcAddress);
    if (!find_GL_extensions(OpenGL_STANDARD[6])) return OpenGL_STANDARD[6];
    GET_GL_FUNCTIONS_GL_vertex_attrib_binding(glGetProcAddress);
    if (!find_GL_extensions(OpenGL_STANDARD[7])) return OpenGL_STANDARD[7];
    GET_GL_FUNCTIONS_GL_ARB_uniform_buffer_object(glGetProcAddress);
    if (!find_GL_extensions(OpenGL_STANDARD[8])) return OpenGL_STANDARD[8];
    GET_GL_FUNCTIONS_GL_KHR_debug(glGetProcAddress);
    glDebugMessageCallback(glCallback, NULL);
    return NULL;
}

#endif
#endif