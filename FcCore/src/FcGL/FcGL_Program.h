#pragma once

#ifndef __FCGL_PROGRAM_H__
#define __FCGL_PROGRAM_H__

#include "FcGL_Functions.h"

typedef GLint FcGL_ProgramType;

enum FCGL_PPROGRAMTYPE {
    FcGL_PROGRAM_VERTEX,
    FcGL_PROGRAM_FRAGMENT
};

struct ubo_data {
    GLuint block_active_uniforms;
    GLuint id;
    GLint index;
    GLchar *block_name;
    GLchar **uniform_names;
    GLuint *indices;
    GLuint *offset;
};

typedef struct _FcGL_Program_t {
    GLuint m_program_id;
} FcGL_Program_t;

typedef struct _FcGL_Program_parameters_t {
    FcGL_ProgramType typeShaders[2];
    const char *codeShaders[2];
} FcGL_Program_parameters_t;

FcGL_Program_t FcGL_Program(FcGL_Program_parameters_t *parameters);

static inline void FcGL_Program_bind(FcGL_Program_t *program) { glUseProgram(program->m_program_id); };

static inline GLint FcGL_Program_getVertexId(FcGL_Program_t *program, const char *name) {
    return glGetAttribLocation(program->m_program_id, name);
};

static inline GLint FcGL_Program_getUniformId(FcGL_Program_t *program, const char *name) {
    return glGetUniformLocation(program->m_program_id, name);
};

void FcGL_Program_free(FcGL_Program_t *program);


#endif