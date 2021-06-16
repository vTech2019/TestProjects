#include "application.h"
#include <string.h>


void application_init(struct application* app){
    memset(app, 0, sizeof(struct application));

    thread_manager_init(&app->m_manager);

    app->m_reader = TrueTypeReader("C:\\Windows\\Fonts\\arial.ttf");
    
    gl_window(&app->m_window, 1280, 720);
    gl_main_manager_init(&app->m_manager, &app->m_window);


}
void application_run(struct application* app){
    application_menu_init(&app->m_manager, &app->m_menu, &app->m_window);
    gl_window_dispatch(&app->m_window);
}
void application_free(struct application* app){
    if (app){
        application_menu_free(&app->m_manager, &app->m_menu);
        gl_main_manager_free(&app->m_manager);


        gl_window_free(&app->m_window);
    }
}
