//
// Created by human on 02.04.2020.
//

#ifndef GRAPHICSTEST_MAINPROGRAM_H
#define GRAPHICSTEST_MAINPROGRAM_H
#include <TrueTypeLibrary.h>

#include "../OpenGL/gl_main_manager.h"
#include "../System_API/system_window.h"
#include "application_menu/application_menu.h"
#include "thread_manager.h"


struct application{
    system_window m_window;
    thread_manager m_manager;
    TrueTypeReader_t* m_reader;

    struct application_menu m_menu;
};
void application_init(struct application* app);
void application_run(struct application* app);
void application_free(struct application* app);



#endif //GRAPHICSTEST_MAINPROGRAM_H
