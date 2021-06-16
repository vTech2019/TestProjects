#ifdef _WIN32
#include "windows.h"
#include "../WGL/WGL.h"

#ifndef __WINAPI_WINDOW__
#define __WINAPI_WINDOW__

static UINT getLastErrorMessage(UINT line, const char file[]) {
    UINT errorCode = GetLastError();
    LPVOID buffer;
    CHAR str[128] = "LINE =                     File =";
    sprintf(str + 6, "%.20d", line);
    str[26] = ' ';
    sprintf(str + 33, "%.96s\n", file);

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&buffer, 0, NULL);
    MessageBox(NULL, (LPCTSTR)buffer, str, MB_OK | MB_ICONERROR | MB_TOPMOST | MB_SETFOREGROUND);
    LocalFree(buffer);
    return errorCode;
}

enum mouseKeyCode { MouseMove = 0, LeftKey = 1, MiddleKey = 2, RightKey = 3, UpWheel = 4, DownWheel = 5 };
enum keyboardKeyEvent { KeyUp = 0, KeyDown = 1 };
typedef struct WINAPI_Window_t {
    WNDCLASSEX window_class;
    HWND hwnd;
    HDC hdc;
    RECT            rect;
    DEVMODEA     screenSettings;

    struct wgl_t       wgl_data;
    UINT        m_width;
    UINT        m_height;
    UINT        thread_status_window;
    UINT        thread_success_exit;
    UINT        fullscreen;
    UINT        exStyle;
    UINT        style;
    UINT         active;

    void* dataKeyboardCallback[2];
    void (*callbackKeyboard)(int keyCode, enum keyboardKeyEvent keyEvent, void* data_0, void* data_1);
    void* dataMouseCallback;
    void (*callbackMouse)(size_t x, size_t y, unsigned char mouseKeyCode, void* data_0);
    void* dataResizeCallback[2];
    void (*callbackResizeWindow)(size_t width, size_t height, void* data_0, void* data_1);
}WINAPI_Window_t;

char* gl_window(struct WINAPI_Window_t* window, int width, int height);
char* gl_window_dispatch(struct WINAPI_Window_t* window);
void gl_window_init_context(struct WINAPI_Window_t* window);
void gl_window_show(struct WINAPI_Window_t* window);

void gl_window_getScreenSize(int* width, int* height);
void gl_window_getWindowSize(struct WINAPI_Window_t* window, int* width, int* height);
void gl_window_hide(struct WINAPI_Window_t* window);

void gl_window_free(struct WINAPI_Window_t* window);
void gl_window_free_context(struct WINAPI_Window_t* window);

void gl_window_setCallbackKeyboard(struct WINAPI_Window_t* window, void (*callbackKeyboard)(int keyCode, enum keyboardKeyEvent keyEvent, void* data_1, void* data_2), void* data_0, void* data_1);
void gl_window_setCallbackMouse(struct WINAPI_Window_t* window, void (*callbackMouse)(size_t x, size_t y, unsigned char mouseKeyCode, void* data_0), void* data_0);
void gl_window_setCallbackResizeWindow(struct WINAPI_Window_t* window, void (*callbackResizeWindow)(size_t width, size_t height, void* data_0, void* data_1), void* data_0, void* data_1);
void gl_window_setCenterCursorPosition(struct WINAPI_Window_t* window);

static inline void gl_window_swap_buffers(struct WINAPI_Window_t* window) { SwapBuffers(window->hdc); };
#endif
#endif