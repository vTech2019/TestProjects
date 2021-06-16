#ifdef WIN32

#include <FcCore.h>
#include "WINAPI_Window.h"     
#include "FcWindow.h"  


const CHAR classWindow[] = "__GL_WINAPI_WINDOW__";


LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void callbackKeyboard(int keyCode, short keyEvent, void *data_1, void *data_2) {}
void callbackResizeWindow(size_t width, size_t height, void *data_0, void *data_1) {}
void callbackMouse(size_t x, size_t y, short mouseKeyCode, void *data_0) {}

static inline void ScreenSettings(FcGLWindow_t *window, DWORD style, DWORD exStyle, RECT *rect) {
    DEVMODE screenSettings = {0};
    //if (option & FCGLWINDOW_FULLSCREEN) {
        rect->right = GetSystemMetrics(SM_CXSCREEN);
        rect->bottom = GetSystemMetrics(SM_CYSCREEN);
        screenSettings.dmSize = sizeof(screenSettings);
        screenSettings.dmPelsWidth = (DWORD) rect->right;
        screenSettings.dmPelsHeight = (DWORD) rect->bottom;
        screenSettings.dmBitsPerPel = 32;
        screenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
        if (ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
            INT continuePlaying = MessageBoxA(NULL,
                                              "Could not implement fullscreen. Please check your drivers. Do you plan to continue?",
                                              "ERROR", MB_YESNO | MB_ICONEXCLAMATION);
            if (continuePlaying == IDYES) {
                MessageBoxA(NULL, "Will revert back to fullscreen.", "Notifcation", MB_OK);
            } else {
                MessageBoxA(NULL, "The program will now close", "Notification", MB_OK);
                exit(1);
            }
        }
    /*} else {
        AdjustWindowRectEx(rect, style, FALSE, exStyle);
        INT width = rect->right - rect->left;
        INT height = rect->bottom - rect->top;
        rect->left = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
        rect->top = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;
        rect->right = width;
        rect->bottom = height;
    } */
}

void RegisterClassWindow(HINSTANCE hInstance, FcGLWindow_t *window) {
    WORD error = 0;
    WNDCLASSEX wndClass = {0};
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
    wndClass.lpfnWndProc = windowProc;

    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;

    wndClass.lpszClassName = classWindow;
    wndClass.lpszMenuName = NULL;
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hbrBackground = (HBRUSH) GetStockObject(DKGRAY_BRUSH);
    
    if (!(error = RegisterClassEx(&wndClass))) {
        MessageBox(NULL, "Failed to register class.", "ERROR", MB_OK | MB_TASKMODAL | MB_ICONERROR);
        ExitProcess(error);
    }
}

void FcGLWindow(FcCore_t* core, FcGLWindow_t* window, const uint32_t width, const uint32_t height, const TCHAR* name) {
    DWORD exStyle;
    DWORD style;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    RECT rect = {0, 0, width, height};
    RegisterClassWindow(hInstance, window);
    //if (options & FCGLWINDOW_FULLSCREEN) {
    //    exStyle = WS_EX_APPWINDOW;
    //    style = WS_POPUP;
    //} else 
    {
        exStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        style = WS_OVERLAPPEDWINDOW;
    }
    //ScreenSettings(window, options, style, exStyle, &rect);

    FcGLWindow_setCallbackMouse(window, callbackMouse, NULL);
    FcGLWindow_setCallbackResizeWindow(window, callbackResizeWindow, NULL, NULL);
    FcGLWindow_setCallbackKeyboard(window, callbackKeyboard, NULL, NULL);

    if (!(window->hwnd = CreateWindowEx(exStyle, classWindow, name, style, rect.left, rect.top, rect.right, rect.bottom,
                                        NULL, NULL, hInstance, window)))
        getLastErrorMessage(__LINE__, __FILE__),
                exit(0); 
    FcGLWindow_initContext(core, window);
}

void FcGLWindow_show(FcGLWindow_t *window) {
    ShowWindow(window->hwnd, SW_SHOWNORMAL);
    SetForegroundWindow(window->hwnd);
    UpdateWindow(window->hwnd);
    SetFocus(window->hwnd);
}

void FcGLWindow_dispatch(FcGLWindow_t *window) {
    MSG msg;
    BOOL result = 0;
    //printf("\n\n");
    while ((result = GetMessage(&msg, window->hwnd, 0, 0)) > 0) {
        printf("%x\n", msg.message);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    //if (result == -1)
    //    getLastErrorMessage(__LINE__, __FILE__);
    //printf("%d %x\n", result, msg.message);
}


void initContext(FcWGL_t *wgl, FcGLWindow_t *window) {
    FcWGL_initDebugContext(wgl, &window->m_wgl, window->hwnd);
}
void freeContext(FcWGL_t* wgl, FcGLWindow_t* window) {
    FcWGL_freeContext(wgl, &window->m_wgl, window->hwnd);
}
            
void FcGLWindow_initContext(FcCore_t* core, FcGLWindow_t* window) {
    Fc_ProducerConsumer(&window->glThread);
    Fc_ProducerConsumerData_t init = { e_FcGL_callFunction_fpp, initContext, core, window };
    Fc_threadProducer(&window->glThread, init);
}
void FcGLWindow_freeContext(FcCore_t* core, FcGLWindow_t* window) {
    Fc_ProducerConsumerData_t init = { e_FcGL_callFunction_fpp, freeContext, core, window };
    Fc_threadProducer(&window->glThread, init);
}


void FcGLWindow_getClientSize(const FcGLWindow_t *window, int *width, int *height) {
    RECT rect;
    if (GetClientRect(window->hwnd, &rect)) {
        *width = rect.right - rect.left;
        *height = rect.bottom - rect.top;
    }
}

void FcGLWindow_getWindowSize(const FcGLWindow_t *window, int *width, int *height) {
    RECT rect;
    if (GetWindowRect(window->hwnd, &rect)) {
        *width = rect.right - rect.left;
        *height = rect.bottom - rect.top;
    }
}

void FcGLWindow_hide(FcGLWindow_t *window) {
    ShowWindow(window->hwnd, SW_HIDE);
}

void FcGLWindow_free(FcCore_t* core, FcGLWindow_t* window) {
    int m_result = FC_NO_ERROR;
    FcGLWindow_freeContext(core, window);
    if (Fc_ProducerConsumer_freeLock(&window->glThread))
        getLastErrorMessage(__LINE__, __FILE__);

    //if (window->options & FCGLWINDOW_FULLSCREEN) ChangeDisplaySettings(NULL, 0);
    if (IsWindow(window->hwnd))
        if (!DestroyWindow(window->hwnd)) 
            getLastErrorMessage(__LINE__, __FILE__);
    if (!UnregisterClass(classWindow, GetModuleHandle(NULL))) {
        getLastErrorMessage(__LINE__, __FILE__);
        exit(0);
    }
    //memset(window, 0, sizeof(*window));
}

void FcGLWindow_setCallbackMouse(FcGLWindow_t *window,
                                 void (*callbackMouse)(size_t x, size_t y, short mouseKeyCode, void *data_0),
                                 void *data_0) {
    window->callbackMouse = callbackMouse;
    window->dataMouseCallback = data_0;
}

void FcGLWindow_setCallbackResizeWindow(FcGLWindow_t *window,
                                        void (*callbackResizeWindow)(size_t width, size_t height, void *data_0,
                                                                     void *data_1), void *data_0, void *data_1) {
    window->callbackResizeWindow = callbackResizeWindow;
    window->dataResizeCallback[0] = data_0;
    window->dataResizeCallback[1] = data_1;
}

void FcGLWindow_setCallbackKeyboard(FcGLWindow_t *window,
                                    void (*callbackKeyboard)(int keyCode, short keyEvent, void *data_1, void *data_2),
                                    void *data_0, void *data_1) {
    window->callbackKeyboard = callbackKeyboard;
    window->dataKeyboardCallback[0] = data_0;
    window->dataKeyboardCallback[1] = data_1;
}

void FcGLWindow_setCenterCursorPosition(FcGLWindow_t *window) {
    RECT clientRect;
    RECT windowRect;
    GetWindowRect(window->hwnd, &windowRect);
    GetClientRect(window->hwnd, &clientRect);
    LONG width = clientRect.right - clientRect.left;
    LONG height = clientRect.bottom - clientRect.top;
    LONG offset_X = (windowRect.right - clientRect.right - windowRect.left) / 2;
    LONG offset_Y = (windowRect.bottom - clientRect.bottom - windowRect.top) - offset_X;
    SetCursorPos(width / 2 + windowRect.left + offset_X, height / 2 + windowRect.top + offset_Y);
}

LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    ptrdiff_t m_i;
    static FcGLWindow_t *window;
    switch (uMsg) {
        case WM_CREATE:
            window = (FcGLWindow_t *) ((LPCREATESTRUCT) lParam)->lpCreateParams;
            break;
        case WM_SETFOCUS: {
            //_glfwInputWindowFocus(window, GLFW_TRUE);

            //if (window->win32.frameAction)
            //    break;

            //if (window->cursorMode == GLFW_CURSOR_DISABLED)
            //    disableCursor(window);

            //return 0;
        }
        case WM_KILLFOCUS:
            //ShowCursor(TRUE);
            break;
        case WM_MOUSEWHEEL:
            m_i = GET_WHEEL_DELTA_WPARAM(wParam);
            for (; m_i >= WHEEL_DELTA; m_i -= WHEEL_DELTA) 
                window->callbackMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), FCWINDOW_MOUSE_UPWHEEL,
                                  window->dataMouseCallback);
            
            for (; m_i < 0; m_i += WHEEL_DELTA)
                window->callbackMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), FCWINDOW_MOUSE_DOWNWHEEL,
                    window->dataMouseCallback);
            break;
        case WM_MOUSEMOVE:
            window->callbackMouse(LOWORD(lParam), HIWORD(lParam), WM_MOUSEMOVE, window->dataMouseCallback);
            break;
        case WM_MBUTTONDOWN:
            window->callbackMouse(LOWORD(lParam), HIWORD(lParam), WM_MBUTTONDOWN, window->dataMouseCallback);
            break;
        case WM_RBUTTONDOWN:
            window->callbackMouse(LOWORD(lParam), HIWORD(lParam), WM_RBUTTONDOWN, window->dataMouseCallback);
            break;
        case WM_LBUTTONDBLCLK:
            window->callbackMouse(LOWORD(lParam), HIWORD(lParam), WM_LBUTTONDOWN, window->dataMouseCallback);
        case WM_LBUTTONDOWN:
            window->callbackMouse(LOWORD(lParam), HIWORD(lParam), WM_LBUTTONDOWN, window->dataMouseCallback);
            break;
        case WM_MBUTTONUP:
            window->callbackMouse(LOWORD(lParam), HIWORD(lParam), WM_MBUTTONUP, window->dataMouseCallback);
            break;
        case WM_RBUTTONUP:
            window->callbackMouse(LOWORD(lParam), HIWORD(lParam), WM_RBUTTONUP, window->dataMouseCallback);
            break;
        case WM_LBUTTONUP:
            window->callbackMouse(LOWORD(lParam), HIWORD(lParam), WM_LBUTTONUP, window->dataMouseCallback);
            break;
        case WM_KEYDOWN:
            window->callbackKeyboard((int) wParam, WM_KEYDOWN, window->dataKeyboardCallback[0],
                                     window->dataKeyboardCallback[1]);
            break;
        case WM_KEYUP: {
            switch (wParam) {
                case VK_ESCAPE:
                    PostMessage(hWnd, WM_QUIT, 0, 0);
                    break;
            }
        }
            break;
            //case WM_WINDOWPOSCHANGED:
            //    break;
        case WM_SIZING:
            break;
        case WM_SIZE:      
            window->m_height = HIWORD(lParam);
            window->m_width = LOWORD(lParam);
            window->callbackResizeWindow(LOWORD(lParam), HIWORD(lParam), window->dataResizeCallback[0],
                                         window->dataResizeCallback[1]);
            break;
        case WM_ERASEBKGND:
            return TRUE;
        //case WM_DESTROY:
        //    PostQuitMessage(0);
        //    break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


#endif