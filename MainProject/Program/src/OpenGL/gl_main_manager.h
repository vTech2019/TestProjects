//
// Created by human on 2/4/20.
//

#ifndef __GLMAINMANAGER_H___
#define __GLMAINMANAGER_H__

#include "../System_API/system_thread.h"
#include "../System_API/system_window.h"

#include "../MainEvents/main_queue.h"

#include "../Matrix//vector4.h"
#include "gl_header.h"
struct gl_main_manager{

    thread_t m_glThread;

    system_window* m_window;

    struct main_queue_arrays n_queue;

    char opengl_init;
}; 

void glTranslate(GLfloat* matrix, float x, float y, float z);
void gl_Ortho(GLfloat* matrix, float left, float right, float bottom, float top, float m_far, float m_near);
void gl_Frustum(GLfloat* matrix, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearVal, GLfloat farVal);
void gl_LookAt(GLfloat* matrix, struct vec4_t eye, struct vec4_t center, struct vec4_t up);
void gl_Perspective(GLfloat* matrix, GLfloat fovY, GLfloat aspect, GLfloat nearZ, GLfloat farZ);

void gl_main_manager_init(struct gl_main_manager* manager, system_window* window);
void gl_main_manager_free(struct gl_main_manager* manager);



#endif
