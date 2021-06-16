//
// Created by human on 05.04.2020.
//

#include "application_menu.h"
#include <ppm_reader.h>

#include "../../System_API/system_window.h"

#define LENGTH(array) (sizeof(array)/sizeof(*array))
#define RADIAN(value) (value / 180 * M_PI)


const char vertex_shader[] = {
#include "application_menu_vertex.glsl.bin"
    ,0
};
const char fragment_shader[] = {
#include "application_menu_fragment.glsl.bin"
    ,0
};
void update_camera_vectors(struct camera_data* camera);
static void resize(size_t width, size_t height, void* data_0, void* data_1);
static void mouse(size_t x, size_t y, unsigned char mouseKeyCode, void* data_0){
    struct application_menu* ptr = (struct application_menu*)data_0;
    if (mouseKeyCode == (unsigned char)UpWheel || mouseKeyCode == (unsigned char)DownWheel) {

        if (ptr->camera_info.fov >= 1.0f && ptr->camera_info.fov <= 45.0f)
            ptr->camera_info.fov -= (int)x;
        else if (ptr->camera_info.fov < 1.0f)
            ptr->camera_info.fov = 1.0f;
        else if (ptr->camera_info.fov >  45.0f)
            ptr->camera_info.fov = 45.0f;
        resize(ptr->m_window->m_width, ptr->m_window->m_height, ptr, NULL);
        return;
    }
    ((unsigned*)((char*)&ptr->uniform_block + ptr->offset_buffer_mouse))[0] = x;
    ((unsigned*)((char*)&ptr->uniform_block + ptr->offset_buffer_mouse))[1] = ptr->m_window->m_height - y;
    {
        ptr->camera_info.horizontalAngle += 0.01f * (float)((ptrdiff_t)ptr->m_window->m_width  / 2  - (ptrdiff_t)x);
        ptr->camera_info.verticalAngle   += 0.01f * (float)((ptrdiff_t)ptr->m_window->m_height / 2 -  (ptrdiff_t)y);
        if (ptr->camera_info.verticalAngle > 89.0f)
            ptr->camera_info.verticalAngle = 89.0f;
        if (ptr->camera_info.verticalAngle < -89.0f)
            ptr->camera_info.verticalAngle = -89.0f;



        update_camera_vectors(&ptr->camera_info);
        vec3_t center = fvec3_add(ptr->camera_info.cameraPosition, ptr->camera_info.cameraFront);
        *((fMatrix4x4_t*)((char*)&ptr->uniform_block + ptr->offset_buffer_VIEW)) = fMatrix4x4_gl_look_at(ptr->camera_info.cameraPosition, center, ptr->camera_info.cameraUp);
        ptr->camera_info.VIEW_MASK = fMatrix4x4_gl_look_at_view_matrix(ptr->camera_info.cameraPosition, center, ptr->camera_info.cameraUp);

        gl_window_setCenterCursorPosition(ptr->m_window);
        //fMatrix4x4_fprintp(*((fMatrix4x4_t*)((char*)&ptr->uniform_block + ptr->offset_buffer_VIEW)), 4, 2);
    }
}
static void resize(size_t width, size_t height, void* data_0, void* data_1 ){
    size_t offset = 0;
    struct application_menu* ptr = (struct application_menu*)data_0;
    float aspect = (float)width / height;
    struct vec3_t center = fvec3_add(ptr->camera_info.cameraPosition, ptr->camera_info.cameraFront);
    float aspectYScale = 1.0;
    if ((float)width / (float)height < 1.7777777777777778) {
        aspectYScale *= (float)width / (float)height / 1.7777777777777778;
    }
    *((fMatrix4x4_t*)((char*)&ptr->uniform_block + ptr->offset_buffer_VIEW)) = fMatrix4x4_gl_look_at(ptr->camera_info.cameraPosition, center, ptr->camera_info.cameraUp);
    ptr->camera_info.VIEW_MASK = fMatrix4x4_gl_look_at_view_matrix(ptr->camera_info.cameraPosition, center, ptr->camera_info.cameraUp);

    *((fMatrix4x4_t*)((char*)&ptr->uniform_block + ptr->offset_buffer_MODELVIEW)) = fMatrix4x4_gl_perspective(atan(tan(ptr->camera_info.fov * 3.14159 / 360.0) / aspectYScale) * 360.0 / 3.14159, aspect, 1.0, 100.0);
    struct main_queue_array* ptr_queue = main_queue_array_find_init_free_array_block(&ptr->m_manager->n_queue, &offset);
    ptr_queue = main_queue_push(ptr_queue, void_function_int_int_int_int_init(glViewport, 0, 0, width, height));

    ptr->m_manager->n_queue.gl_init_command_queue[offset] = ptr_queue;
    while(ptr->m_manager->n_queue.ptr_gl_init_command_queue->number_instructions_thread)
        continue;
    ptr_queue->number_instructions_thread = ptr_queue->number_instructions;
    ptr_queue->used = 0;
    ptr->m_manager->n_queue.ptr_gl_init_command_queue = ptr_queue;
    while(ptr->m_manager->n_queue.ptr_gl_init_command_queue->number_instructions_thread)
        continue;
}

void callbackKeyboard(int keyCode, enum keyboardKeyEvent keyEvent, void* data_0, void* data_1) {
    struct application_menu* ptr = (struct application_menu*)data_0;
    
    struct vec3_t cameraSpeed = fvec3(0.5f, 0.5f, 0.5f);
    if (keyCode == 0x57)
        ptr->camera_info.cameraPosition = fvec3_sub(ptr->camera_info.cameraPosition, fvec3_mul(cameraSpeed, ptr->camera_info.cameraFront));
    if (keyCode == 0x53)
        ptr->camera_info.cameraPosition = fvec3_add(ptr->camera_info.cameraPosition, fvec3_mul(cameraSpeed, ptr->camera_info.cameraFront));
    if (keyCode == 0x41)
        ptr->camera_info.cameraPosition = fvec3_sub(ptr->camera_info.cameraPosition, (fvec3_mul(fvec3_norm(fvec3_cross(ptr->camera_info.cameraUp, ptr->camera_info.cameraFront)), cameraSpeed)));
    if (keyCode == 0x44)
        ptr->camera_info.cameraPosition = fvec3_add(ptr->camera_info.cameraPosition, (fvec3_mul(fvec3_norm(fvec3_cross(ptr->camera_info.cameraUp, ptr->camera_info.cameraFront)), cameraSpeed)));

    struct vec3_t center = fvec3_add(ptr->camera_info.cameraPosition, ptr->camera_info.cameraFront);
    *((fMatrix4x4_t*)((char*)&ptr->uniform_block + ptr->offset_buffer_VIEW)) = fMatrix4x4_gl_look_at(ptr->camera_info.cameraPosition, center, ptr->camera_info.cameraUp);
    ptr->camera_info.VIEW_MASK = fMatrix4x4_gl_look_at_view_matrix(ptr->camera_info.cameraPosition, center, ptr->camera_info.cameraUp);
    //fMatrix4x4_fprintp(*((fMatrix4x4_t*)((char*)&ptr->uniform_block + ptr->offset_buffer_VIEW)), 4, 2);
}


void update_camera_vectors(struct camera_data* camera) {
    camera->cameraFront.f0 = cosf(RADIAN(camera->horizontalAngle)) *cosf(RADIAN(camera->verticalAngle));
    camera->cameraFront.f1 = sinf(RADIAN(camera->verticalAngle));
    camera->cameraFront.f2 = sinf(RADIAN(camera->horizontalAngle)) *cosf(RADIAN(camera->verticalAngle));


    camera->cameraFront = fvec3_norm(camera->cameraFront);
    camera->cameraRight = fvec3_norm(fvec3_cross(camera->cameraFront, fvec3(0.0f, 1.0f, 0.0f)));
    camera->cameraUp = fvec3_norm(fvec3_cross(camera->cameraRight, camera->cameraFront));

}

void* memory_reallocator(void** memory, size_t width, size_t height, size_t pixel_bit_size) {
    *memory = realloc(*memory, width * height * pixel_bit_size / 8 + sizeof(struct menu_image));
    struct menu_image* ptr = *memory;
    ptr->width = width;
    ptr->height = height;
    return ptr->data;
}
void application_draw_init(struct gl_main_manager* manager, struct application_menu* menu) ;

void application_menu_init(struct gl_main_manager* manager, struct application_menu* menu, system_window* window){

    struct menu_image* skybox_image = NULL;
    read_ppm_image("/media/human/2A520E98520E68C1/Projects/OpenGL_test/skybox_v2.ppm", (void **) &skybox_image, memory_reallocator);

    struct gl_program_code code[2] = {{GL_VERTEX_SHADER, vertex_shader}, {GL_FRAGMENT_SHADER, fragment_shader}};
    struct gl_program_parameters parameters = {
            2, code
    };
    struct gl_button_parameters button = {1,1,10, 10, 10, 0, 127,0,255,
        position_xyz, colors_nothing, normal_nothing, texture_activate, 0, 0, 0, 3, 5, skybox_image->data, skybox_image->width, skybox_image->height,
        0, 0, 1, 2 };
    struct gl_sphere_parameters skybox = { 0,0,0,1, 80,80, normal_activate, texture_activate,
        0, 3, 6, 8, skybox_image->data, skybox_image->width, skybox_image->height,
        0, 1, 2 };

    gl_program_init(manager, &menu->program, &parameters);
    gl_program_synchronize(manager, &menu->program);

    gl_button_init(manager, &menu->button[0], &button);
    gl_button_synchronize(manager, &menu->button[0]);
    gl_sphere_init(manager, &menu->skybox, &skybox);

    gl_sphere_synchronize(manager, &menu->skybox);
    
    for (size_t i =0; i < menu->program.m_active_uniform_blocks[0].block_active_uniforms; i++){
        if (strcmp(menu->program.m_active_uniform_blocks[0].uniform_names[i], "mouse") ==0){
            menu->offset_buffer_mouse = menu->program.m_active_uniform_blocks[0].offset[i];
        }
        if (strcmp(menu->program.m_active_uniform_blocks[0].uniform_names[i], "MODELVIEW") == 0){
            menu->offset_buffer_MODELVIEW = menu->program.m_active_uniform_blocks[0].offset[i];
        }
        if (strcmp(menu->program.m_active_uniform_blocks[0].uniform_names[i], "VIEW") == 0) {
            menu->offset_buffer_VIEW = menu->program.m_active_uniform_blocks[0].offset[i];
        }
        if (strcmp(menu->program.m_active_uniform_blocks[0].uniform_names[i], "MODEL") == 0) {
            menu->offset_buffer_MODEL = menu->program.m_active_uniform_blocks[0].offset[i];
        }
    }
    menu->camera_info.fov = 30;
    menu->camera_info.horizontalAngle = 0;
    menu->camera_info.verticalAngle = 0.0f;

    menu->camera_info.cameraPosition = fvec3(0.0f, 0.0f, 0.0f);
    menu->camera_info.cameraTarget = fvec3(0.0f, 0.0f, 1.0f);
    menu->camera_info.cameraDirection = fvec3_norm(fvec3_sub(menu->camera_info.cameraPosition, menu->camera_info.cameraTarget));
    menu->camera_info.cameraFront = fvec3(0.0f, 0.0f, -1.0f);

    menu->camera_info.cameraUp = fvec3(0.0f, 1.0f, 0.0f); 
    menu->camera_info.cameraRight = fvec3_norm(fvec3_cross(menu->camera_info.cameraUp, menu->camera_info.cameraDirection));
    menu->camera_info.cameraUp = fvec3_cross(menu->camera_info.cameraDirection, menu->camera_info.cameraRight);

    menu->camera_info.IDENTITY = fMatrix4x4_identity();
    menu->camera_info.VIEW_MASK = fMatrix4x4_identity();
    *((struct fMatrix4x4_t*)((char*)&menu->uniform_block + menu->offset_buffer_MODELVIEW)) = fMatrix4x4_identity();
    *((struct fMatrix4x4_t*)((char*)&menu->uniform_block + menu->offset_buffer_VIEW)) = fMatrix4x4_identity();
    *((struct fMatrix4x4_t*)((char*)&menu->uniform_block + menu->offset_buffer_MODEL)) = fMatrix4x4_identity();

    menu->m_window = window;
    menu->m_manager = manager;
    resize(window->m_width, window->m_height, menu, NULL);

    gl_window_setCallbackKeyboard(window, callbackKeyboard, menu, NULL);
    gl_window_setCallbackMouse(window, mouse, menu);
    gl_window_setCallbackResizeWindow(window, resize, menu, NULL);
    application_draw_init(manager, menu);
    free(skybox_image);
}

void application_menu_free(struct gl_main_manager* manager, struct application_menu* menu){
    size_t i;
    if (menu->m_window){
        gl_window_setCallbackMouse(menu->m_window, NULL, NULL);
        gl_window_setCallbackResizeWindow(menu->m_window, NULL, NULL, NULL);
    }
    menu->m_window = NULL;
    menu->m_manager = NULL;
    gl_program_free(manager, &menu->program);
    for (i=0; i < LENGTH(menu->button); i++){
        gl_button_free(manager, &menu->button[i]);
    }
    gl_sphere_free(manager, &menu->skybox);
    if (manager->n_queue.ptr_gl_draw_command_queue == manager->n_queue.gl_draw_command_queue[menu->offset_draw]){
        manager->n_queue.ptr_gl_draw_command_queue->used = 0xffffffff;
        while (manager->n_queue.ptr_gl_draw_command_queue->number_instructions_thread)
            continue;
    }
    gl_button_synchronize(manager, &menu->button[i-1]);
    
}

void application_draw_init(struct gl_main_manager* manager, struct application_menu* menu) {
    size_t offset = 0;
    struct main_queue_array* ptr_queue = main_queue_array_find_draw_free_array_block(&manager->n_queue, &offset);
    ptr_queue->number_instructions = 0;
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glClear, (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)));
    ptr_queue = main_queue_push(ptr_queue, void_function_float_float_float_float_init(glClearColor, 0.5f, 0.5f, 0.5f, 1.0f));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glEnableVertexAttribArrayARB, 0));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glEnableVertexAttribArrayARB, 1));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glEnableVertexAttribArrayARB, 2));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glUseProgram, menu->program.m_program_id));  

    ptr_queue = main_queue_push(ptr_queue, void_function_uchar_init(glDepthMask, GL_FALSE));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_uint_uint_init(glBindBufferBase, GL_UNIFORM_BUFFER, menu->program.m_active_uniform_blocks[0].index, menu->program.m_active_uniform_blocks[0].id));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_ptrdiff_ptrdiff_voidPtr_init((void (*)(unsigned int, ptrdiff_t, ptrdiff_t, void*))(glBufferSubData), GL_UNIFORM_BUFFER, menu->offset_buffer_MODEL, sizeof(struct fMatrix4x4_t), &menu->camera_info.IDENTITY));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_ptrdiff_ptrdiff_voidPtr_init((void (*)(unsigned int, ptrdiff_t, ptrdiff_t, void*))(glBufferSubData), GL_UNIFORM_BUFFER, menu->offset_buffer_VIEW, sizeof(struct fMatrix4x4_t), &menu->camera_info.VIEW_MASK));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glActiveTexture, GL_TEXTURE0));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_uint_init(glBindTexture, GL_TEXTURE_2D, menu->skybox.mesh_sphere.m_textureId));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glBindVertexArray, menu->skybox.mesh_sphere.m_VAO));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_int_uint_voidPtr_init((void (*)(unsigned int, int, unsigned int, void*))glDrawElements, GL_TRIANGLE_STRIP, menu->skybox.mesh_sphere.m_indexCount, GL_UNSIGNED_INT, NULL));
    ptr_queue = main_queue_push(ptr_queue, void_function_uchar_init(glDepthMask, GL_TRUE));


    //ptr_queue = main_queue_push(ptr_queue, void_function_uint_uint_uint_init(glBindBufferBase, GL_UNIFORM_BUFFER, menu->program.m_active_uniform_blocks[0].index, menu->program.m_active_uniform_blocks[0].id));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_ptrdiff_ptrdiff_voidPtr_init((void (*)(unsigned int, ptrdiff_t, ptrdiff_t, void*))(glBufferSubData), GL_UNIFORM_BUFFER, 0, sizeof(struct application_menu_uniform), &menu->uniform_block));

    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glActiveTexture, GL_TEXTURE0));
    for (size_t i = 0; i < LENGTH(menu->button); i++){
        ptr_queue = main_queue_push(ptr_queue, void_function_uint_uint_init(glBindTexture, GL_TEXTURE_2D, menu->button[i].mesh_button.m_textureId));
        ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glBindVertexArray, menu->button[i].mesh_button.m_VAO));
        ptr_queue = main_queue_push(ptr_queue, void_function_uint_int_uint_voidPtr_init((void (*)(unsigned int, int, unsigned int, void*))glDrawElements, GL_TRIANGLE_STRIP, menu->button[i].mesh_button.m_indexCount, GL_UNSIGNED_INT, NULL));
    }
 


    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glDisableVertexAttribArrayARB, 2));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glDisableVertexAttribArrayARB, 1));
    ptr_queue = main_queue_push(ptr_queue, void_function_uint_init(glDisableVertexAttribArrayARB, 0));
    ptr_queue->used = 0;
    menu->offset_draw = offset;

    manager->n_queue.ptr_gl_draw_command_queue = ptr_queue;
    ptr_queue->number_instructions_thread = ptr_queue->number_instructions;
}