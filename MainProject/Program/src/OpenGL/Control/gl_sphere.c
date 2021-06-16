#include "gl_sphere.h"

void gl_sphere_init(struct gl_main_manager* manager, struct gl_sphere* sphere, struct gl_sphere_parameters* parameters) {
    size_t offset = 0;
    struct figures_sphere_parameters* figure_memory = malloc(sizeof(struct figures_sphere_parameters));
    
    struct figures_sphere_parameters figure = {
        {
            parameters->offsetVertexPosition,
            0,
            parameters->offsetNormalPosition,
            parameters->offsetTexturePosition,
            parameters->offsetVertex,

            position_xyz,
            colors_nothing,
            parameters->activateNormals,
            parameters->activateTexture,

            parameters->indexVertex,
            0,
            parameters->indexNormal,
            parameters->indexTexture,
            NULL, NULL, NULL,
            0, 0,

            parameters->image_rgb, 
            parameters->width, parameters->height
        },

        parameters->stackCount,
        parameters->sectorCount,
        {parameters->x_center,
        parameters->y_center,
        parameters->z_center},
        parameters->radius
    };
    *figure_memory = figure;
    field_generator_SolidSphere_init(figure_memory);

    struct main_queue_array* ptr_queue = main_queue_array_find_init_free_array_block(&manager->n_queue, &offset);
    ptr_queue = main_queue_push(ptr_queue, void_function_voidP_voidP_init((void (*)(void *, void *)) gl_mesh_init_thread, &figure_memory->mesh, &sphere->mesh_sphere));
    ptr_queue = main_queue_push(ptr_queue, void_function_voidP_init((void (*)(void *)) field_generator_SolidSphere_free, figure_memory));
    ptr_queue = main_queue_push(ptr_queue, void_function_voidP_init(free, figure_memory));
    manager->n_queue.gl_init_command_queue[offset] = ptr_queue;
    sphere->offset_init_queue = offset;
}
void gl_sphere_free(struct gl_main_manager* manager, struct gl_sphere* sphere) {
    if (sphere) {
        size_t offset = 0;
        struct main_queue_array* ptr_queue = main_queue_array_find_init_free_array_block(&manager->n_queue, &offset);
        ptr_queue = main_queue_push(ptr_queue, void_function_voidP_init((void (*)(void *)) gl_mesh_free_thread, &sphere->mesh_sphere));
        manager->n_queue.gl_init_command_queue[offset] = ptr_queue;
        sphere->offset_init_queue = offset;
    }
}
void gl_sphere_synchronize(struct gl_main_manager* manager, struct gl_sphere* sphere) {
    while (manager->n_queue.ptr_gl_init_command_queue->number_instructions_thread)
        continue;
    manager->n_queue.gl_init_command_queue[sphere->offset_init_queue]->number_instructions_thread =
        manager->n_queue.gl_init_command_queue[sphere->offset_init_queue]->number_instructions;
    manager->n_queue.gl_init_command_queue[sphere->offset_init_queue]->used = 0;
    manager->n_queue.ptr_gl_init_command_queue = manager->n_queue.gl_init_command_queue[sphere->offset_init_queue];
    while (manager->n_queue.ptr_gl_init_command_queue->number_instructions_thread)
        continue;
}