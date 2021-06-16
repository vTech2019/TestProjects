//
// Created by human on 06.04.2020.
//

#include "gl_button.h"
#include "../../Figures/field_generator.h"

void gl_button_init(struct gl_main_manager* manager, struct gl_button* button, struct gl_button_parameters* parameters){
    size_t offset = 0;
    struct figures_field_parameters* figure_memory = malloc(sizeof(struct figures_field_parameters));
    const register struct figures_field_parameters figure = {
        {
            parameters->offsetVertexPosition,
            parameters->offsetColorPosition,
            parameters->offsetNormalPosition,
            parameters->offsetTexturePosition,
            parameters->offsetVertex,

            parameters->numberPositions,
            parameters->activateColors,
            parameters->activateNormals,
            parameters->activateTexture,

            parameters->indexVertex,
            parameters->indexColor,
            parameters->indexNormal,
            parameters->indexTexture,

            NULL, NULL, NULL,
            0, 0,

            parameters->image_rgb, parameters->image_width, parameters->image_height
        },
        2, 2,
            {parameters->color[0],
             parameters->color[1],
             parameters->color[2],
             parameters->color[3]},
            {
                parameters->x_center - parameters->width / 2,
                parameters->y_center - parameters->height / 2,
                parameters->z_center },
            {
                parameters->width,
                parameters->height }
    };

    *figure_memory = figure;
    field_generator_plane_init(figure_memory);
    
    struct main_queue_array* ptr_queue = main_queue_array_find_init_free_array_block(&manager->n_queue, &offset);
    ptr_queue = main_queue_push(ptr_queue, void_function_voidP_voidP_init((void (*)(void *,void*))gl_mesh_init_thread, &figure_memory->mesh, &button->mesh_button));
    ptr_queue = main_queue_push(ptr_queue, void_function_voidP_init((void (*)(void *)) field_generator_plane_free, figure_memory));
    ptr_queue = main_queue_push(ptr_queue, void_function_voidP_init(free, figure_memory));
    manager->n_queue.gl_init_command_queue[offset] = ptr_queue;
    button->offset_init_queue = offset;
}
void gl_button_free(struct gl_main_manager* manager, struct gl_button* button){
    if (button){
        size_t offset = 0;
        struct main_queue_array* ptr_queue = main_queue_array_find_init_free_array_block(&manager->n_queue, &offset);
        ptr_queue = main_queue_push(ptr_queue, void_function_voidP_init((void (*)(void *)) gl_mesh_free_thread, &button->mesh_button));
        manager->n_queue.gl_init_command_queue[offset] = ptr_queue;
        button->offset_init_queue = offset;
    }
}


void gl_button_synchronize(struct gl_main_manager* manager, struct gl_button* button){
    while(manager->n_queue.ptr_gl_init_command_queue->number_instructions_thread)
        continue;
    manager->n_queue.gl_init_command_queue[button->offset_init_queue]->number_instructions_thread =
            manager->n_queue.gl_init_command_queue[button->offset_init_queue]->number_instructions;
    manager->n_queue.gl_init_command_queue[button->offset_init_queue]->used = 0;
    manager->n_queue.ptr_gl_init_command_queue = manager->n_queue.gl_init_command_queue[button->offset_init_queue];
    while(manager->n_queue.ptr_gl_init_command_queue->number_instructions_thread)
        continue;
}