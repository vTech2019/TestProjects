//#include "Home.h"
//#include "Launcher.h"
//
//const char vertex[] = {
//#include "../Shaders/BINARY/launcherHomeVertex.glsl.bin"
//        , 0
//};
//const char fragment[] = {
//#include "../Shaders/BINARY/launcherHomeFragment.glsl.bin"
//        , 0
//};
//const float mesh[] = {-1, -1, -1, 1, 1, 1, -1, -1, 1, -1};
//
//
//int Home_mouseWindow(void *launcher) {
//    Launcher_t *m_launcher = (Launcher_t *) launcher;
//
//    //if (m_launcher->mouseCoord[2].i == FCWINDOW_MOUSE_LBUTTONDOWN) {
//        double time = FcGLWindow_GetClockSec();
//        m_launcher->time_speed[0] = time;
//        size_t seconds = time;
//        GLubyte data[3] = {(GLubyte) (255. * (time - seconds)), 255, 127};
//        FcGL_rewrite2DTexture_RGB(m_launcher->m_home.idTextureControlCondition, 0, 0, 1, 1, data);
//   // }
//    return 0;
//}
//
//int Home_resizeWindow(void *launcher) {
//    Launcher_t *m_launcher = (Launcher_t *) launcher;
//    glViewport(0, 0, m_launcher->windowSize[0], m_launcher->windowSize[1]);
//    return 0;
//}
//
//void Home_init(void *launcher) {
//    //wglSwapIntervalEXT(0);
//    glEnable(GL_TEXTURE_2D);
//
//    Launcher_t *m_launcher = (Launcher_t *) launcher;
//    FcGL_Program_parameters_t m_p_parameters;
//    m_p_parameters.codeShaders[0] = vertex;
//    m_p_parameters.codeShaders[1] = fragment;
//    m_p_parameters.typeShaders[0] = FcGL_PROGRAM_VERTEX;
//    m_p_parameters.typeShaders[1] = FcGL_PROGRAM_FRAGMENT;
//    m_launcher->m_home.m_program = FcGL_Program(&m_p_parameters);
//
//    char data[3] = {255, FcGLWindow_GetClockSec(), data[1]};
//    FcGL_Mesh_parameters_t m_m_parameters = {1};
//    FcGL_create2DTexture_RGB8(&m_launcher->m_home.idTextureControlCondition, data, 1, 1);
//    m_launcher->m_home.idControlCondition = FcGL_Program_getUniformId(&m_launcher->m_home.m_program, "controlID");
//    m_launcher->m_home.idTime = FcGL_Program_getUniformId(&m_launcher->m_home.m_program, "time_SpeedAnimation");
//    m_launcher->m_home.idWindowSize = FcGL_Program_getUniformId(&m_launcher->m_home.m_program, "windowSize");
//    m_launcher->m_home.idMVP = FcGL_Program_getUniformId(&m_launcher->m_home.m_program, "MVP");
//    m_launcher->m_home.idMouse = FcGL_Program_getUniformId(&m_launcher->m_home.m_program, "mouse");
//    m_m_parameters.m_vertexIndex = FcGL_Program_getVertexId(&m_launcher->m_home.m_program, "vertex_position");
//    m_m_parameters.m_vertexCount = 5;
//    m_m_parameters.m_vertexOffsetPosition = 0;
//    m_m_parameters.m_vertexLength = 2;
//    m_m_parameters.m_vertexDataLength = 0;
//    m_m_parameters.m_meshMode = GL_TRIANGLE_STRIP;
//    m_m_parameters.m_return_data = (void *) mesh;
//    m_m_parameters.m_return_sizeVertexBuffer = sizeof(mesh);
//    m_launcher->m_home.m_mesh = FcGL_Mesh(&m_m_parameters);
//
//
//}
//
//void Home_draw(void *launcher) {
//    Launcher_t *m_launcher = (Launcher_t *) launcher;
//    glClear(GL_COLOR_BUFFER_BIT);
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//    FcGL_Program_bind(&m_launcher->m_home.m_program);
//    //glUniformMatrix4fv(m_launcher->m_home.idMVP, 1, 0, (const GLfloat *) m_launcher->m_home.m_MVP.m);
//    //glUniform4fv(m_launcher->m_home.idMouse, 1, (const GLfloat *) m_launcher->mouseCoord);
//    //glUniform2fv(m_launcher->m_home.idWindowSize, 1, &m_launcher->windowSize[0]);
//    //glUniform2fv(m_launcher->m_home.idTime, 1, m_launcher->time_speed);
//
//    FcGL_bind2DTexture(m_launcher->m_home.idTextureControlCondition);
//    FcGL_Mesh_drawArrays_v(&m_launcher->m_home.m_mesh);
//    //FcGLWindow_swapBuffers(m_launcher->m_window);
//    Fc_threadProducer(&m_launcher->m_window->glThread,
//                               (Fc_ProducerConsumerData_t) {e_FcGL_callFunction_fp, Home_draw, m_launcher, 0});
//    m_launcher->time_speed[0] = (float) FcGLWindow_GetClockSec();
//    m_launcher->time_speed[1] = (float) m_launcher->animationStep;
//}
//
//void Home(void *launcher) {
//    Launcher_t *m_launcher = (Launcher_t *) launcher;
//    Fc_ProducerConsumerData_t draw_queue_init = {
//            e_FcGL_callFunction_fp, Home_init, m_launcher, 0
//    };
//    Fc_ProducerConsumerData_t draw_queue_draw = {
//            e_FcGL_callFunction_fp, Home_draw, m_launcher, 0
//    };
//    m_launcher->m_home.m_MVP = FcGL_Matrix4x4f_identity();
//    Fc_threadProducer(&m_launcher->m_window->glThread, draw_queue_init);
//    Fc_threadProducer(&m_launcher->m_window->glThread, draw_queue_draw);
//}
//
//void Home_free(Home_t *home) {
//}