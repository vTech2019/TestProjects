//
//
//#include "Launcher.h"
//
//void CallbackMouse(size_t x, size_t y, short mouseCode, void *data) {
//    Launcher_t *m_launcher = (Launcher_t *) data;
//    m_launcher->mouseCoord[0].f = (float) x;
//    m_launcher->mouseCoord[1].f = m_launcher->windowSize[1] - (float) y;
//    m_launcher->mouseCoord[2].i = mouseCode;
//    Fc_ProducerConsumerData_t init = {e_FcGL_callFunction_fp, Home_mouseWindow, m_launcher, 0};
//    Fc_threadProducer(&m_launcher->m_window->glThread, init);
//
//    //printf("%f \n", m_launcher->mouseCoord[2].f);
//}
//
//void CallbackResizeWindow(size_t width, size_t height, void *data_0, void *data_1) {
//    Launcher_t *m_launcher = (Launcher_t *) data_0;
//    //glViewport(0, 0, width, height);
//    m_launcher->windowSize[0] = width;
//    m_launcher->windowSize[1] = height;
//    Fc_ProducerConsumerData_t init = {e_FcGL_callFunction_fp, Home_resizeWindow, m_launcher, 0};
//    Fc_threadProducer(&m_launcher->m_window->glThread, init);
//}
//
//void Launcher(Launcher_t *m_launcher, FcGLWindow_t *m_window) {
//    m_launcher->m_window = m_window;
//    FcGLWindow_getClientSize(m_launcher->m_window, (int *) (m_launcher->windowSize + 0),
//                             (int *) (m_launcher->windowSize + 1));
//    m_launcher->windowSize[0] = *((int *) m_launcher->windowSize + 0);
//    m_launcher->windowSize[1] = *((int *) m_launcher->windowSize + 1);
//    m_launcher->animationStep = 1.0;
//    m_launcher->time_speed[0] = FcGLWindow_GetClockSec();
//    m_launcher->time_speed[1] = m_launcher->animationStep;
//    Home(m_launcher);
//    FcGLWindow_setCallbackMouse(m_window, CallbackMouse, m_launcher);
//    FcGLWindow_setCallbackResizeWindow(m_window, CallbackResizeWindow, m_launcher, NULL);
//
//    //FcThread_functionCall(app->m_glThread, FcGLWindow_initContext, &app->m_window);
//
//}
//
//void Launcher_free(Launcher_t *launcher) {
//
//
//}