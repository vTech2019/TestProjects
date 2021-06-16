
#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <GL/gl.h>
#include <GL/glx.h>
//#include <GL/glext.h>
//#include <GL/glxext.h>

enum mouseKeyCode {LeftKey = 1, MiddleKey = 2, RightKey = 3, UpWheel = 4, DownWheel = 5};
enum keyboardKeyEvent { KeyUp = KeyRelease, KeyDown = KeyPress };

#ifndef X11_WINDOW_H
#define X11_WINDOW_H
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
typedef struct X11_gl_Window{
    Window window;
    XSetWindowAttributes window_attributes;
    Display* ptr_display;
    Screen* ptr_screen;
    XEvent event;
    XVisualInfo* visual_info;
    GLXContext glx_context;
    GLXFBConfig fbc_config;
    Atom wm_delete_window;
    int screenId;
    unsigned thread_status_window;
    unsigned thread_success_exit;
    unsigned m_width, m_height;

    void* dataKeyboardCallback[2];
    void (*callbackKeyboard)(int keyCode, enum keyboardKeyEvent keyEvent, void* data_0, void* data_1);
    void* dataMouseCallback;
    void (*callbackMouse)(size_t x, size_t y, unsigned char mouseKeyCode, void* data_0);
    void* dataResizeCallback[2];
    void (*callbackResizeWindow)(size_t width, size_t height, void* data_0, void* data_1 );
}X11_gl_Window;
char* gl_window(X11_gl_Window* window, size_t width, size_t height);
void gl_window_init_context(X11_gl_Window* window);
void gl_window_show(X11_gl_Window* window);
char* gl_window_dispatch(X11_gl_Window* window);
void gl_window_setCenterCursorPosition(X11_gl_Window* window);
void gl_window_free(X11_gl_Window* window);
void gl_window_free_context(X11_gl_Window* window);
void gl_window_setCallbackKeyboard(X11_gl_Window* window, void (*callbackKeyboard)(int keyCode, enum keyboardKeyEvent keyEvent, void* data_1, void* data_2), void* data_0, void* data_1);
void gl_window_setCallbackMouse(X11_gl_Window* window, void (*callbackMouse)(size_t x, size_t y, unsigned char mouseKeyCode, void* data_0), void* data_0);
void gl_window_setCallbackResizeWindow(X11_gl_Window* window, void (*callbackResizeWindow)(size_t width, size_t height, void* data_0, void* data_1 ), void* data_0, void* data_1);
static inline void gl_window_swap_buffers(X11_gl_Window* window){ glXSwapBuffers(window->ptr_display, window->window); };


#endif 

#endif