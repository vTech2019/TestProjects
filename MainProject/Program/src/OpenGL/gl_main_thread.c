//
// Created by human on 02.04.2020.
//

#include "../System_API/system_window.h"
#include "gl_main_manager.h"
#include "gl_main_thread.h"
#include <stdio.h>

static inline void call_function(enum main_function type_function, union function_type ptr_function,
        union function_parameter p_0, union function_parameter p_1,
        union function_parameter p_2, union function_parameter p_3,
                union function_parameter* return_parameter){
    switch(type_function){
        case void_function_int:
            ptr_function.v_i(p_0.i); break;
        case void_function_int_int:
            ptr_function.v_ii(p_0.i, p_1.i); break;
        case void_function_int_int_int:
            ptr_function.v_iii(p_0.i, p_1.i, p_2.i); break;
        case void_function_int_int_int_int:
            ptr_function.v_iiii(p_0.i, p_1.i, p_2.i, p_3.i); break;
        case void_function_float:
            ptr_function.v_f(p_0.f); break;
        case void_function_float_float:
            ptr_function.v_ff(p_0.f, p_1.f); break;
        case void_function_float_float_float:
            ptr_function.v_fff(p_0.f, p_1.f, p_2.f); break;
        case void_function_float_float_float_float:
            ptr_function.v_ffff(p_0.f, p_1.f, p_2.f, p_3.f); break;
        case void_function_char:
            ptr_function.v_c(p_0.c); break;
        case void_function_uchar:
            ptr_function.v_uC(p_0.uc); break;
        case void_function_uint:
            ptr_function.v_u(p_0.ui); break;
        case void_function_uint_uint:
            ptr_function.v_uu(p_0.ui,p_1.ui); break;
        case void_function_uint_uint_uint:
            ptr_function.v_uuu(p_0.ui,p_1.ui,p_2.ui); break;
        case void_function_uint_uint_uint_uint:
            ptr_function.v_uuuu(p_0.ui,p_1.ui,p_2.ui,p_3.ui); break;
        case void_function_uint_uint_uint_voidPtr:
            ptr_function.v_uuuvP(p_0.ui,p_1.ui,p_2.ui,p_3.p); break;
        case void_function_uint_int_uint_voidPtr:
            ptr_function.v_uiuvP(p_0.ui, p_1.i, p_2.ui, p_3.p); break;
        case void_function_voidPtr_voidPtr:
            ptr_function.v_vPvP(p_0.p, p_1.p); break;
        case void_function_voidPtr:
            ptr_function.v_vP(p_0.p); break;
        case void_function_uint_ptrdiff_ptrdiff_voidPtr:
            ptr_function.v_uiSiSvP(p_0.ui, p_1.ptrdiff, p_2.ptrdiff, p_3.p); break;
        default: 
        break;
    }
}
void* gl_main_thread(void* args){
    size_t i;
    struct gl_main_manager* manager = (struct gl_main_manager*)(args);
    system_window* ptr_window = manager->m_window;
    gl_window_init_context(ptr_window);


        manager->opengl_init = 0xff;
        while (ptr_window->thread_status_window & ((size_t)manager->n_queue.ptr_gl_init_command_queue | (size_t)manager->n_queue.ptr_gl_draw_command_queue)){
            if (!manager->n_queue.ptr_gl_init_command_queue->used){
                if (manager->n_queue.ptr_gl_init_command_queue->number_instructions_thread){

                    for (i = 0; i < manager->n_queue.ptr_gl_init_command_queue->number_instructions_thread; i++){
                        call_function(manager->n_queue.ptr_gl_init_command_queue->memory[i].type_function,
                                    manager->n_queue.ptr_gl_init_command_queue->memory[i].call_function,
                                    manager->n_queue.ptr_gl_init_command_queue->memory[i].parameter_0,
                                    manager->n_queue.ptr_gl_init_command_queue->memory[i].parameter_1,
                                    manager->n_queue.ptr_gl_init_command_queue->memory[i].parameter_2,
                                    manager->n_queue.ptr_gl_init_command_queue->memory[i].parameter_3,
                                    &manager->n_queue.ptr_gl_init_command_queue->memory[i].parameter_return);
                    }
                    manager->n_queue.ptr_gl_init_command_queue->used = 0xffffffffffffffff;
                    manager->n_queue.ptr_gl_init_command_queue->number_instructions_thread = 0;
                    manager->n_queue.ptr_gl_init_command_queue->number_instructions = 0;
                }
            }
            if (!manager->n_queue.ptr_gl_draw_command_queue->used){
                if (manager->n_queue.ptr_gl_draw_command_queue->number_instructions_thread > 3)
                for (i = 0; i < manager->n_queue.ptr_gl_draw_command_queue->number_instructions_thread; i++){
                    call_function(manager->n_queue.ptr_gl_draw_command_queue->memory[i].type_function,
                                manager->n_queue.ptr_gl_draw_command_queue->memory[i].call_function,
                                manager->n_queue.ptr_gl_draw_command_queue->memory[i].parameter_0,
                                manager->n_queue.ptr_gl_draw_command_queue->memory[i].parameter_1,
                                manager->n_queue.ptr_gl_draw_command_queue->memory[i].parameter_2,
                                manager->n_queue.ptr_gl_draw_command_queue->memory[i].parameter_3,
                                &manager->n_queue.ptr_gl_draw_command_queue->memory[i].parameter_return);
                   // fprintf(stderr, "%d\n", i);
                }
            }else{
                manager->n_queue.ptr_gl_draw_command_queue->number_instructions_thread = 0;
            }
            gl_window_swap_buffers(ptr_window);
        }
    gl_window_free_context(ptr_window);
    ptr_window->thread_success_exit = 1;
    return 0;
}