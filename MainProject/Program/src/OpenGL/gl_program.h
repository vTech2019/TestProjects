//
// Created by human on 06.04.2020.
//

#ifndef GRAPHICSTEST_GL_PROGRAM_H
#define GRAPHICSTEST_GL_PROGRAM_H
#include <stddef.h>
#include "gl_header.h"
#include "gl_main_manager.h"

struct ubo_data{
    GLuint block_active_uniforms;
    GLuint id;
    GLint index;
    GLchar* block_name;
    GLchar** uniform_names;
    GLuint* indices;
    GLuint* offset;
};

struct gl_program{
    GLuint m_program_id;

    GLint m_number_active_uniform_blocks;

    size_t memory_allocate;
    size_t offset_init_queue;

    char* m_memory;

    struct ubo_data*  m_active_uniform_blocks;
};

struct gl_program_code{
        GLuint typeShader;
        const char* codeShader;
};
struct gl_program_parameters{
    GLuint numberShaders;
    struct gl_program_code* code;
};
void gl_program_init(struct gl_main_manager* manager, struct gl_program* program, struct gl_program_parameters* parameters);
void gl_program_free(struct gl_main_manager* manager, struct gl_program* program);
void gl_program_init_thread(struct gl_program* program, struct gl_program_parameters* parameters);
void gl_program_free_thread(struct gl_program* program);
void gl_program_synchronize(struct gl_main_manager* manager, struct gl_program* program);

#endif //GRAPHICSTEST_GL_PROGRAM_H
