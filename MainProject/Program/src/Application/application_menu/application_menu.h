//
// Created by human on 05.04.2020.
//

#ifndef GRAPHICSTEST_APPLICATION_MENU_H
#define GRAPHICSTEST_APPLICATION_MENU_H
#include "../../OpenGL/Control/gl_button.h"
#include "../../OpenGL/Control/gl_sphere.h"
#include "../../OpenGL/gl_mesh.h"
#include "../../OpenGL/gl_main_manager.h"
#include "../../OpenGL/gl_program.h"

#include "../Matrix/Matrix4x4.h"
#include "../Matrix/vector4.h"
struct application_menu_uniform{
    struct vec4_t mouse_data;
    fMatrix4x4_t MODEL;
    fMatrix4x4_t MODELVIEW;
    fMatrix4x4_t VIEW;
};
struct camera_data {
    fMatrix4x4_t IDENTITY;
    fMatrix4x4_t VIEW_MASK;
    struct vec3_t cameraPosition;
    struct vec3_t cameraTarget;
    struct vec3_t cameraDirection;

    struct vec3_t cameraRight;
    struct vec3_t cameraFront;
    struct vec3_t cameraUp;

    float horizontalAngle;
    float verticalAngle;
    float dx, dy;
    float fov;
};
struct menu_image {
    size_t width, height;
    char data[0];
};
struct application_menu{
    struct application_menu_uniform uniform_block;
    struct camera_data camera_info;

    struct gl_sphere skybox;
    struct gl_button button[1];
    struct gl_program program;
    struct gl_main_manager* m_manager;
    system_window* m_window;

    size_t offset_draw;
    size_t offset_buffer_mouse;
    size_t offset_buffer_MODELVIEW;
    size_t offset_buffer_VIEW;
    size_t offset_buffer_MODEL;
};


void application_menu_init(struct gl_main_manager* manager, struct application_menu* menu, system_window* window);
void application_menu_free(struct gl_main_manager* manager, struct application_menu* menu);
#endif //GRAPHICSTEST_APPLICATION_MENU_H
