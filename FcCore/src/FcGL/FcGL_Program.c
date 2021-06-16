#include "src/FcGL/FcGL_Program.h"
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(value) (sizeof(value) / sizeof(*value))

void checkErrorShader(GLuint shader, const char *text, GLuint status) {
    GLint infoLength = 1;
    GLint messageLength = 0;
    glGetShaderiv(shader, status, &infoLength);
    if (infoLength == GL_FALSE) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
        GLchar *infoLog = (GLchar *) malloc(infoLength * sizeof(GLchar));
        glGetShaderInfoLog(shader, infoLength, &messageLength, infoLog);
        fprintf(stderr, "%s - %s\n", text, infoLog);
        free(infoLog);
    }
}

void programInfoLog(GLuint shader) {
    GLint infoLength = 0;
    GLint lengthWriteInfo = 0;
    glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
    if (infoLength > 0) {
        GLchar *log = (GLchar *) malloc(infoLength * sizeof(GLchar));
        glGetProgramInfoLog(shader, infoLength, &lengthWriteInfo, log);
        fprintf(stderr, "Information - %s	\n", log);
        free(log);
    }
}

void programValidateLog(GLuint shader) {
    GLint infoLength = 0;
    GLint lengthWriteInfo = 0;
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &infoLength);
    if (infoLength == GL_FALSE) {
        GLint infoLength = 1;
        GLint messageLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
        GLchar *infoLog = (GLchar *) malloc(infoLength * sizeof(GLchar));
        glGetShaderInfoLog(shader, infoLength, &messageLength, infoLog);
        fprintf(stderr, "%s\n", infoLog);
        free(infoLog);
    }
}

GLuint createProgram(FcGL_Program_parameters_t *parameters) {
    GLuint i;
    GLuint glProgram = 0;
    GLuint vertexShaders = 0;
    GLuint fragmentShaders = 0;
    GLuint computeShaders = 0;
    for (i = 0; i < LENGTH(parameters->typeShaders); i++) {
        switch (parameters->typeShaders[i]) {
            case FcGL_PROGRAM_VERTEX: {
                vertexShaders = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexShaders, 1, &parameters->codeShaders[i], NULL);
                glCompileShader(vertexShaders);
                checkErrorShader(vertexShaders, "GL_VERTEX_SHADER", GL_COMPILE_STATUS);
                break;
            }
            case FcGL_PROGRAM_FRAGMENT: {
                fragmentShaders = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentShaders, 1, &parameters->codeShaders[i], NULL);
                glCompileShader(fragmentShaders);
                checkErrorShader(fragmentShaders, "GL_FRAGMENT_SHADER", GL_COMPILE_STATUS);
                break;
            }
            case GL_TESS_CONTROL_SHADER:
            case GL_TESS_EVALUATION_SHADER:
            case GL_GEOMETRY_SHADER:
            case GL_COMPUTE_SHADER:
                break;
            default: {
                break;
            }
        }
    }
    glProgram = glCreateProgram();
    if (fragmentShaders) glAttachShader(glProgram, fragmentShaders);
    if (vertexShaders) glAttachShader(glProgram, vertexShaders);
    if (computeShaders) glAttachShader(glProgram, computeShaders);
    glLinkProgram(glProgram);
    programInfoLog(glProgram);
    programValidateLog(glProgram);

    if (fragmentShaders) glDeleteShader(fragmentShaders);
    if (vertexShaders) glDeleteShader(vertexShaders);
    if (computeShaders) glDeleteShader(computeShaders);
    return glProgram;
}

FcGL_Program_t FcGL_Program(FcGL_Program_parameters_t *parameters) {
    FcGL_Program_t m_program;
    m_program.m_program_id = createProgram(parameters);
    return m_program;
}

void FcGL_Program_free(FcGL_Program_t *program) {
    glDeleteProgram(program->m_program_id);

}