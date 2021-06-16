//// ProjectMania.cpp: определяет точку входа для приложения.
////
//
//#include "App.h"
//
//#define WINDOW_WIDTH 1280
//#define WINDOW_HEIGHT 720
//
//#include <FcGL/FcGL_Control/FcGL_ProgramGenerator.h>
//
//void App_init(App_t *app) {
//
//    FcGLWindow(&app->m_window, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
//
//
//    //FcGL_ProgramGenerator_t generator = {0};
//    //FcGL_ProgramGenerator_options_t param = {0};
//    //FcGL_GeneratorGUI(&generator, &app->m_window);
//
//    FcGLWindow_show(&app->m_window);
//    //FcGLWindow_initContext(&app->m_window);
//}
//
//void App_run(App_t *app) {
//    Launcher(&app->m_launcher, &app->m_window);
//    FcGLWindow_dispatch(&app->m_window);
//}
//
//void App_free(App_t *app) {
//    //FcThread_functionCall(&app->m_glThread, FcGLWindow_freeContext, &app->m_window);
//    FcGLWindow_free(&app->m_window);
//}
