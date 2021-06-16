//
// Created by human on 06.04.2020.
//

#include "gl_program.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void checkErrorShader(GLuint shader, const char* text, GLuint status)
{
    GLint infoLength = 1;
    GLint messageLength = 0;
    glGetShaderiv(shader, status, &infoLength);
    if (infoLength == GL_FALSE) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
        GLchar* infoLog = (GLchar*)alloca(infoLength * sizeof(GLchar));
        glGetShaderInfoLog(shader, infoLength, &messageLength, infoLog);
        fprintf(stderr, "%s - %s\n", text, infoLog);
    }
}
void programInfoLog(GLuint shader)
{
    GLint infoLength = 0;
    GLint lengthWriteInfo = 0;
    glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
    if (infoLength > 0)
    {
        GLchar* log = (GLchar*)alloca(infoLength * sizeof(GLchar));
        glGetProgramInfoLog(shader, infoLength, &lengthWriteInfo, log);
        fprintf(stderr, "Information - %s	\n", log);
    }
}
static inline GLuint createProgram(struct gl_program_parameters* parameters)
{
    GLuint glProgram = 0;
    GLuint vertexShaders = 0;
    GLuint fragmentShaders = 0;
    GLuint computeShaders = 0;
    for (size_t i = 0; i < parameters->numberShaders; i++){
        switch (parameters->code[i].typeShader) {
            case GL_VERTEX_SHADER: {
                vertexShaders = glCreateShader(GL_VERTEX_SHADER);
                glShaderSourceARB(vertexShaders, 1, &parameters->code[i].codeShader, NULL);
                glCompileShaderARB(vertexShaders);
                checkErrorShader(vertexShaders, "GL_VERTEX_SHADER", GL_COMPILE_STATUS);
                break;
            }
            case GL_FRAGMENT_SHADER: {
                fragmentShaders = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSourceARB(fragmentShaders, 1, &parameters->code[i].codeShader, NULL);
                glCompileShaderARB(fragmentShaders);
                checkErrorShader(fragmentShaders, "GL_FRAGMENT_SHADER", GL_COMPILE_STATUS);
                break;
            }
            case GL_TESS_CONTROL_SHADER:
            case GL_TESS_EVALUATION_SHADER:
            case GL_GEOMETRY_SHADER:
                break;
            case GL_COMPUTE_SHADER: {
                computeShaders = glCreateShader(GL_COMPUTE_SHADER);
                glShaderSourceARB(computeShaders, 1, &parameters->code[i].codeShader, NULL);
                glCompileShaderARB(computeShaders);
                checkErrorShader(computeShaders, "GL_COMPUTE_SHADER", GL_COMPILE_STATUS);
            }
            default: {
                break;
            }
        }
    }
    if (parameters->numberShaders){
        glProgram = glCreateProgram();
        if (fragmentShaders)
            glAttachShader(glProgram, fragmentShaders);
        if (vertexShaders)
            glAttachShader(glProgram, vertexShaders);
        if (computeShaders)
            glAttachShader(glProgram, computeShaders);
        glLinkProgramARB(glProgram);
        programInfoLog(glProgram);
        if (fragmentShaders)
            glDeleteShader(fragmentShaders);
        if (vertexShaders)
            glDeleteShader(vertexShaders);
        if (computeShaders)
            glDeleteShader(computeShaders);
    }
    return glProgram;
}
void gl_program_init_thread(struct gl_program* program, struct gl_program_parameters* parameters){
    GLuint i, j, memory_allocate = 0, offset_allocate = 0;
    GLsizei length = 0, written_data = 0;
    GLenum type_uniform;
    GLchar uniformName[128];
    GLint maxUniforms = 0, block_size;
    program->m_program_id = createProgram(parameters);
    glGetProgramiv( program->m_program_id, GL_ACTIVE_UNIFORM_BLOCKS, &program->m_number_active_uniform_blocks );
    glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &maxUniforms);
    program->m_number_active_uniform_blocks = program->m_number_active_uniform_blocks < maxUniforms ? program->m_number_active_uniform_blocks : maxUniforms;

    GLint* block_active_uniforms = (GLint *) alloca(program->m_number_active_uniform_blocks * sizeof(GLint));
    GLuint* block_id = alloca(program->m_number_active_uniform_blocks * sizeof(GLuint));
    GLuint* block_index = alloca(program->m_number_active_uniform_blocks * sizeof(GLuint));
    GLint* block_name_size = alloca(program->m_number_active_uniform_blocks * sizeof(GLint));
    size_t number_block_uniforms = 0;
    glGenBuffers(program->m_number_active_uniform_blocks, block_id);
    for (i = 0; i < program->m_number_active_uniform_blocks; i++) {

        glGetActiveUniformBlockName(program->m_program_id, i, sizeof(uniformName), &length, uniformName);
        //if (!length) getGLErrorLog();
        block_index[i] = glGetUniformBlockIndex(program->m_program_id, uniformName);
        glGetActiveUniformBlockiv(program->m_program_id, block_index[i], GL_UNIFORM_BLOCK_DATA_SIZE, &block_size);

        glUniformBlockBinding(program->m_program_id, block_index[i], i);
        glBindBuffer(GL_UNIFORM_BUFFER, block_id[i]);
        //glBindBufferBase(GL_UNIFORM_BUFFER, i, block_id[i]);

        glBufferData(GL_UNIFORM_BUFFER, block_size, NULL, GL_DYNAMIC_DRAW);
        
        glGetActiveUniformBlockiv(program->m_program_id, block_index[i], GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &block_active_uniforms[i]);
        glGetActiveUniformBlockiv(program->m_program_id, block_index[i], GL_UNIFORM_BLOCK_NAME_LENGTH, &block_name_size[i]);
        /*for (i = 0; i < count; i++)
        {
            glGetActiveUniform(program, (GLuint)i, bufSize, &length, &size, &type, name);
            memory_allocate
            printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
        }*/
        number_block_uniforms += block_active_uniforms[i];
        memory_allocate += sizeof(struct ubo_data) + block_name_size[i] + (size_t)block_active_uniforms[i] * 2 * sizeof(GLuint);
    }
    GLint* block_name_indices = (GLint *) alloca(number_block_uniforms * sizeof(GLuint));
    GLint* block_name_offset = (GLint *) alloca(number_block_uniforms * sizeof(GLuint));
    GLint* block_uniforms_name_size = (GLint *) alloca(number_block_uniforms * sizeof(GLint));

    GLint* ptr_block_name_indices = block_name_indices;
    GLint* ptr_block_name_offset = block_name_offset;
    GLint* ptr_block_uniforms_name_size = block_uniforms_name_size;

    for (i = 0; i < program->m_number_active_uniform_blocks; i++) {
        glGetActiveUniformBlockiv(program->m_program_id, block_index[i], GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, ptr_block_name_indices);
        glGetActiveUniformsiv(program->m_program_id, block_active_uniforms[i], ptr_block_name_indices, GL_UNIFORM_OFFSET, ptr_block_name_offset);

        glGetActiveUniformsiv (program->m_program_id, block_active_uniforms[i], ptr_block_name_indices, GL_UNIFORM_NAME_LENGTH, ptr_block_uniforms_name_size);
        for (j = 0; j < block_active_uniforms[i]; j++){
             memory_allocate += ptr_block_uniforms_name_size[j];
        }
        memory_allocate += block_active_uniforms[i] * sizeof(GLchar**);
        ptr_block_name_indices += block_active_uniforms[i];
        ptr_block_name_offset += block_active_uniforms[i];
        ptr_block_uniforms_name_size += block_active_uniforms[i];
    }
    ptr_block_name_indices = block_name_indices;
    ptr_block_name_offset = block_name_offset;
    ptr_block_uniforms_name_size = block_uniforms_name_size;

    program->m_memory = realloc(program->m_memory, memory_allocate);
    program->m_active_uniform_blocks = (struct ubo_data *) program->m_memory;
    program->memory_allocate = memory_allocate;
    for (i = 0; i < program->m_number_active_uniform_blocks; i++) {
        offset_allocate += sizeof(struct ubo_data);
        program->m_active_uniform_blocks[i].id = block_id[i];
        program->m_active_uniform_blocks[i].block_active_uniforms = block_active_uniforms[i];
        program->m_active_uniform_blocks[i].index = block_index[i];
        program->m_active_uniform_blocks[i].block_name = (GLchar *) (program->m_memory + offset_allocate);
        offset_allocate += block_name_size[i] * sizeof(GLchar);
        program->m_active_uniform_blocks[i].indices = (GLuint *) (program->m_memory + offset_allocate);
        offset_allocate += block_active_uniforms[i] * sizeof(GLuint);
        program->m_active_uniform_blocks[i].offset = (GLuint *) (program->m_memory + offset_allocate);
        offset_allocate += block_active_uniforms[i] * sizeof(GLuint);
        program->m_active_uniform_blocks[i].uniform_names = (GLchar **) (program->m_memory + offset_allocate);
        offset_allocate += block_active_uniforms[i] * sizeof(GLchar*);

        glGetActiveUniformBlockName(program->m_program_id, i, block_name_size[i], 0, program->m_active_uniform_blocks[i].block_name);
        for (j = 0; j < block_active_uniforms[i]; j++){
            program->m_active_uniform_blocks[i].indices[j] = ptr_block_name_indices[j];
            program->m_active_uniform_blocks[i].offset[j] = ptr_block_name_offset[j];
            program->m_active_uniform_blocks[i].uniform_names[j] = (GLchar *) (program->m_memory + offset_allocate);
            offset_allocate += ptr_block_uniforms_name_size[j] * sizeof(GLchar);
            glGetActiveUniformARB(program->m_program_id, ptr_block_name_indices[j], ptr_block_uniforms_name_size[j], &written_data, &written_data, &type_uniform, program->m_active_uniform_blocks[i].uniform_names[j]);

        }
        ptr_block_name_indices += block_active_uniforms[i];
        ptr_block_name_offset += block_active_uniforms[i];
        ptr_block_uniforms_name_size += block_active_uniforms[i];
    }
}
void gl_program_free_thread(struct gl_program* program){
    if (program){
        for (size_t i =0; i < program->m_number_active_uniform_blocks; i++){
            glDeleteBuffers(1, &program->m_active_uniform_blocks[i].id);
        }
        if (program->m_program_id) glDeleteProgram(program->m_program_id);
        if (program->m_memory) free(program->m_memory);
        program->m_memory = NULL;
        program->m_active_uniform_blocks = NULL;
        program->m_program_id = 0;
        program->memory_allocate = 0;
        program->m_number_active_uniform_blocks = 0;
    }
}
void gl_program_init(struct gl_main_manager* manager, struct gl_program* program, struct gl_program_parameters* parameters){
    size_t offset = 0;
    struct main_queue_array* ptr_queue = main_queue_array_find_init_free_array_block(&manager->n_queue, &offset);
    ptr_queue = main_queue_push(ptr_queue, void_function_voidP_voidP_init(
            (void (*)(void *, void *)) gl_program_init_thread, program, parameters));
    manager->n_queue.gl_init_command_queue[offset] = ptr_queue;
    program->offset_init_queue = offset;
}
void gl_program_free(struct gl_main_manager* manager, struct gl_program* program){
    size_t offset = 0;
    struct main_queue_array* ptr_queue = main_queue_array_find_init_free_array_block(&manager->n_queue, &offset);
    ptr_queue = main_queue_push(ptr_queue, void_function_voidP_init((void (*)(void *)) gl_program_free_thread, program));
    manager->n_queue.gl_init_command_queue[offset] = ptr_queue;
    program->offset_init_queue = offset;
}
void gl_program_synchronize(struct gl_main_manager* manager, struct gl_program* program){
    while(manager->n_queue.ptr_gl_init_command_queue->number_instructions_thread)
        continue;

    manager->n_queue.gl_init_command_queue[program->offset_init_queue]->number_instructions_thread =
            manager->n_queue.gl_init_command_queue[program->offset_init_queue]->number_instructions;
    manager->n_queue.gl_init_command_queue[program->offset_init_queue]->used = 0;
    manager->n_queue.ptr_gl_init_command_queue = manager->n_queue.gl_init_command_queue[program->offset_init_queue];

    while(manager->n_queue.ptr_gl_init_command_queue->number_instructions_thread)
        continue;
}