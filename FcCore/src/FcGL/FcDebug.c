//
// Created by human on 22.03.2021.
//
#include "FcGLX.h"
#include "FcWGL.h"

GLenum glCheckError(const char *file, int line) {
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        char *error;
        switch (errorCode) {
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                error = "STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                error = "STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
            default:
                error = NULL;
                break;
        }
        printf("%s | %s ( %d )\n", error, file, line);
    }
    return errorCode;
}

#define Fc_glCheckError() glCheckError(__FILE__, __LINE__)

void APIENTRY FcGLX_glDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity,
                                   GLsizei length, const GLchar *message, const void *userParam) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("OpenGL Error: %x \n", err);
    switch (source) {
        case GL_DEBUG_SOURCE_API:
            printf("Source : API,");
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            printf(" Source : Shader,");
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            printf(" Source : Window,");
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            printf(" Source : Third party,");
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            printf(" Source : Application,");
            break;
        case GL_DEBUG_SOURCE_OTHER:
            printf(" Source : Other,");
            break;
    }
    printf(" ID = %d,", id);
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            printf(" Type : ERROR,");
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            printf(" Type : DEPRECATED_BEHAVIOR,");
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            printf(" Type : UNDEFINED_BEHAVIOR,");
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            printf(" Type : PERFORMANCE,");
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            printf(" Type : PORTABILITY,");
            break;
        case GL_DEBUG_TYPE_MARKER:
            printf(" Type : MARKER,");
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            printf(" Type : PUSH_GROUP,");
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            printf(" Type : POP_GROUP,");
            break;
        case GL_DEBUG_TYPE_OTHER:
            printf(" Type : OTHER,");
            break;
    }
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            printf(" Severity : High,");
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            printf(" Severity : Medium,");
            break;
        case GL_DEBUG_SEVERITY_LOW:
            printf(" Severity : Low,");
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            printf(" Severity : Notification,");
            break;
    }
    printf(" Message: %s \n", message);
}