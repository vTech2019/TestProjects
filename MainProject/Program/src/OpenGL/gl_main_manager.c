//
// Created by human on 2/4/20.
//

#include "gl_main_manager.h"
#include "gl_main_thread.h"


#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include <ThreadLibrary/ThreadLibrary.h>

GLvoid APIENTRY glDebugProcCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam){
#ifdef _WIN32
    HANDLE mutex = thread_create_mutex(userParam);
    #endif
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
             type, severity, message );
#ifdef _WIN32
    thread_release_mutex(mutex);
#endif
}



void init_OpenGL_options(struct gl_main_manager* manager){
    size_t offset;
    struct main_queue_array* ptr_queue = main_queue_array_find_init_free_array_block(&manager->n_queue, &offset);
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glEnable, GL_DEBUG_OUTPUT));
    ptr_queue = main_queue_push(ptr_queue, void_function_voidP_voidP_init(
            (void (*)(void *, void *)) glDebugMessageCallback, glDebugProcCallback, &manager->m_glThread));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glEnable, GL_DEBUG_OUTPUT_SYNCHRONOUS));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glEnable, GL_TEXTURE_2D));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glEnable, GL_DEPTH_TEST)); 
   // ptr_queue = main_queue_push(ptr_queue, void_function_uint_uint_init(glPolygonMode, GL_FRONT_AND_BACK, GL_LINE));
   // ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glEnable, GL_CULL_FACE));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glEnable, GL_BLEND));
    ptr_queue = main_queue_push(ptr_queue, void_function_uchar_init(glDepthMask, GL_TRUE));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glDepthFunc, GL_LEQUAL));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_uint_init(glBlendFunc, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    ptr_queue->used = 0;
    manager->n_queue.gl_init_command_queue[offset] = ptr_queue;
    manager->n_queue.ptr_gl_init_command_queue = ptr_queue;
    ptr_queue->number_instructions_thread = ptr_queue->number_instructions;
}
void init_OpenGL_draw_queue(struct gl_main_manager* manager) {
    size_t offset;
    struct main_queue_array* ptr_queue = main_queue_array_find_draw_free_array_block(&manager->n_queue, &offset);
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glClear, (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)));
    ptr_queue = main_queue_push(ptr_queue, void_function_float_float_float_float_init(glClearColor, 1.0f, 1.0f, 1.0f, 1.0f));
    ptr_queue->used = 0;
    manager->n_queue.gl_draw_command_queue[offset] = ptr_queue;
    manager->n_queue.ptr_gl_draw_command_queue = ptr_queue;
    ptr_queue->number_instructions_thread = ptr_queue->number_instructions;

    /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0,1,0,1);*/
}

void gl_main_manager_init(struct gl_main_manager* manager, system_window* window){
    
    manager->m_window = window;
    main_queue_array_calloc(&manager->n_queue, 24);
    thread_init(&manager->m_glThread, gl_main_thread, manager);
    while (!manager->opengl_init)
        continue;
    init_OpenGL_options(manager);
    init_OpenGL_draw_queue(manager);

}
void gl_main_manager_free(struct gl_main_manager* manager){
    manager->m_window->thread_status_window = 0;
    if (thread_is_running(&manager->m_glThread))
        thread_join(manager->m_glThread);
    while (!manager->m_window->thread_success_exit)
        continue;
    main_queue_array_free(&manager->n_queue);
    manager->m_window = NULL;
    thread_free_resource(&manager->m_glThread);
}

#include <../Matrix/vector4.h>

void glTranslate(GLfloat* matrix, float x, float y, float z) {
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
    matrix[15] = 1.0f;
}
void gl_Ortho(GLfloat *matrix, float left, float right, float bottom, float top, float m_far, float m_near) {
    float tx = -(right + left) / (right - left);
    float ty = -(top + bottom) / (top - bottom);
    float tz = -(m_far + m_near) / (m_far - m_near);
    matrix[0] = 2.0f / (right - left);
    matrix[5] = 2.0f / (top - bottom);
    matrix[10] = -2.0f / (m_far - m_near);
    matrix[12] = tx;
    matrix[13] = ty;
    matrix[14] = tz;
    matrix[15] = 1.0f;
}
void gl_Frustum(GLfloat* matrix, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearVal, GLfloat farVal) {
    GLfloat A = (right + left) / (right - left);
    GLfloat B = (top + bottom) / (top - bottom);
    GLfloat C = -(farVal + nearVal) / (farVal - nearVal);
    GLfloat D = -(2.0f * farVal * nearVal) / (farVal - nearVal);
    matrix[0] = 2.0f * nearVal / (right - left);
    matrix[1] = 0;
    matrix[2] = A;
    matrix[3] = 0;
    matrix[4] = 0;
    matrix[5] = 2.0f * nearVal / (top - bottom);
    matrix[6] = B;
    matrix[7] = 0;
    matrix[8] = 0;
    matrix[9] = 0;
    matrix[10] = C;
    matrix[11] = D;
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = -1.0f;
    matrix[15] = 0;
}
void gl_LookAt(GLfloat* matrix, struct vec4_t eye, struct vec4_t center, struct vec4_t up) {
    struct vec4_t F = fvec4_sub(center, eye);
    struct vec4_t norm_F = fvec4_normalize(F);
    struct vec4_t norm_UP = fvec4_normalize(up);
    if (fabsf(F.f0) < 0.000001f && fabsf(F.f2) < 0.000001f)
    {
        if (F.f1 > 0)
            up = fvec4(0, 0, -1, 0);
        else
            up = fvec4(0, 0, 1, 0);
    }
    else
    {
        up = fvec4(0, 1, 0, 0);
    }  
    struct vec4_t s = fvec4_cross3(norm_F, norm_UP);
    struct vec4_t norm_s = fvec4_normalize(s);
    struct vec4_t u = fvec4_cross3(norm_s, norm_F);
    matrix[0] = s.f0;
    matrix[1] = s.f1;
    matrix[2] = s.f2;
    matrix[3] = s.f3;
    matrix[4] = u.f0;
    matrix[5] = u.f1;
    matrix[6] = u.f2;
    matrix[7] = u.f3;
    matrix[8] = -norm_F.f0;
    matrix[9] = -norm_F.f1;
    matrix[10] = -norm_F.f2;
    matrix[11] = -norm_F.f3;
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}

void gl_Perspective(GLfloat* matrix, GLfloat fovY, GLfloat aspect, GLfloat nearZ, GLfloat farZ)
{         
    GLfloat YMax = nearZ * tan(fovY / 360.0 * 3.1415926535897932384626433832795);
    GLfloat YMin = -YMax;
    GLfloat XMin = YMin * aspect;
    GLfloat XMax = YMax * aspect;

    gl_Frustum(matrix, XMin, XMax, YMin, YMax, nearZ, farZ);
}