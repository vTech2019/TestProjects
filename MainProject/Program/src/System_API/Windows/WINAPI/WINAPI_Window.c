#ifdef _WIN32
#include "WINAPI_Window.h"
#include "../WGL/WGL.h"
#include <Windows.h>
#include <string.h>
#include <stdio.h>

#include <gl/glcorearb.h>
#include <gl/wgl.h>

static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LONG gl_window_ScreenSettings(struct WINAPI_Window_t* window);

HRESULT RegisterClassWindow(HINSTANCE hInstance, struct WINAPI_Window_t* window)
{
    const char* name_window = "__GL_WINAPI_WINDOW__";
    HRESULT result = 0;
    window->window_class.cbSize = sizeof(WNDCLASSEX);
    window->window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window->window_class.lpfnWndProc = windowProc;

    window->window_class.cbClsExtra = 0;
    window->window_class.cbWndExtra = 0;
    window->window_class.hInstance = hInstance;

    window->window_class.lpszClassName = name_window;
    window->window_class.lpszMenuName = NULL;
    window->window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window->window_class.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    window->window_class.hbrBackground = GetSysColorBrush(WHITE_BRUSH);
    if (!(result = RegisterClassEx(&window->window_class)))
    {
        MessageBox(NULL, "Failed to register class.", "ERROR", MB_OK | MB_ICONINFORMATION);
    }
    return result;
}

char* gl_window(struct WINAPI_Window_t* window, int width, int height) {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    window->rect.left = (long)0;
    window->rect.right = (long)width;
    window->rect.top = (long)0;
    window->rect.bottom = (long)height;
    window->fullscreen = 1;

    RegisterClassWindow(hInstance, window);
    gl_window_ScreenSettings(window);
    if (window->fullscreen) {
        window->exStyle = WS_EX_APPWINDOW;
        window->style = WS_POPUP;
        ShowCursor(FALSE);
    }
    else {
        window->exStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        window->style = WS_OVERLAPPEDWINDOW;
    }
    AdjustWindowRectEx(&window->rect, window->style, FALSE, window->exStyle);
    if (!(window->hwnd = CreateWindowEx(window->exStyle, window->window_class.lpszClassName, "", window->style, CW_USEDEFAULT, CW_USEDEFAULT, window->rect.right, window->rect.bottom, NULL, NULL, hInstance, NULL)))
        getLastErrorMessage(__LINE__, __FILE__),
        exit(0);

    gl_window_show(window);
    window->thread_status_window = 0xffffffff;
    window->m_width = window->rect.right;
    window->m_height = window->rect.bottom;
    return NULL;
}

void gl_window_getScreenSize(int* width, int* height)
{
    RECT rect;
    if (GetWindowRect(GetDesktopWindow(), &rect)) {
        *width = rect.right - rect.left;
        *height = rect.bottom - rect.top;
    }
}

void gl_window_getWindowSize(struct WINAPI_Window_t* window, int* width, int* height)
{
    RECT rect;
    if (GetWindowRect(window->hwnd, &rect)) {
        *width = rect.right - rect.left;
        *height = rect.bottom - rect.top;
    }
}

void gl_window_hide(struct WINAPI_Window_t* window)
{
    ShowWindow(window->hwnd, SW_HIDE);
}

LONG gl_window_ScreenSettings(struct WINAPI_Window_t* window)
{
    LONG result = DISP_CHANGE_SUCCESSFUL;
    DEVMODE screenSettings = { 0 };
    if (window->fullscreen) {
        window->rect.left = 0;
        window->rect.top = 0;
        window->rect.right = GetSystemMetrics(SM_CXSCREEN);
        window->rect.bottom = GetSystemMetrics(SM_CYSCREEN);
        screenSettings.dmSize = sizeof(screenSettings);
        screenSettings.dmPelsWidth = (unsigned long)window->rect.right;
        screenSettings.dmPelsHeight = (unsigned long)window->rect.bottom;
        screenSettings.dmBitsPerPel = 32;
        screenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
        if (ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            const int continuePlaying = MessageBoxA(NULL, "Could not implement fullscreen. Please check your drivers. Do you plan to continue?",
	"ERROR", MB_YESNO | MB_ICONEXCLAMATION);

            if (continuePlaying == IDYES)
            {
	MessageBoxA(NULL, "Will revert back to fullscreen.", "Notifcation", MB_OK);
	window->fullscreen = 0;
            }
            else
            {
	MessageBoxA(NULL, "The program will now close", "Notification", MB_OK);
	exit(1);
            }
        }
    }
    else {
        window->rect.left = (GetSystemMetrics(SM_CXSCREEN) - window->rect.right) * 0.5f;
        window->rect.top = (GetSystemMetrics(SM_CYSCREEN) - window->rect.bottom) * 0.5f;
    }
    return result;
}

void gl_window_free(struct WINAPI_Window_t* window) {
    window->thread_status_window = 0;
    while (!window->thread_success_exit)
        continue;
    gl_window_free_context(window);

    if (window->fullscreen) ChangeDisplaySettings(NULL, 0);
    if (IsWindow(window->hwnd))
        if (!DestroyWindow(window->hwnd)) getLastErrorMessage(__LINE__, __FILE__);
    if (!UnregisterClass(window->window_class.lpszClassName, GetModuleHandle(NULL))) {
        MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    }
    memset(window, 0, sizeof(struct WINAPI_Window_t));
}
void gl_window_show(struct WINAPI_Window_t* window) {
    ShowWindow(window->hwnd, SW_SHOWNORMAL);
    SetForegroundWindow(window->hwnd);
    UpdateWindow(window->hwnd);
    SetFocus(window->hwnd);
}
char* gl_window_dispatch(struct WINAPI_Window_t* window) {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return NULL;
}
void gl_window_init_context(struct WINAPI_Window_t* window) {
    window->wgl_data = wgl(window);
    SetProp(window->hwnd, TEXT("WINAPI_Window_t"), window);
}
void gl_window_free_context(struct WINAPI_Window_t* window) {
    ReleaseDC(window->hwnd, window->hdc);
    wgl_free_context(&window->wgl_data);
}
void gl_window_setCallbackMouse(struct WINAPI_Window_t* window, void (*callbackMouse)(size_t x, size_t y, unsigned char mouseKeyCode, void* data_0), void* data_0) {
    window->callbackMouse = callbackMouse;
    window->dataMouseCallback = data_0;
}
void gl_window_setCallbackResizeWindow(struct WINAPI_Window_t* window, void (*callbackResizeWindow)(size_t width, size_t height, void* data_0, void* data_1), void* data_0, void* data_1) {
    window->callbackResizeWindow = callbackResizeWindow;
    window->dataResizeCallback[0] = data_0;
    window->dataResizeCallback[1] = data_1;
}
void gl_window_setCallbackKeyboard(struct WINAPI_Window_t* window, void (*callbackKeyboard)(int keyCode, enum keyboardKeyEvent keyEvent, void* data_1, void* data_2), void* data_0, void* data_1) {
    window->callbackKeyboard = callbackKeyboard;
    window->dataKeyboardCallback[0] = data_0;
    window->dataKeyboardCallback[1] = data_1;
}

void gl_window_setCenterCursorPosition(struct WINAPI_Window_t* window) {
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
static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    struct WINAPI_Window_t* window = GetProp(hWnd, TEXT("WINAPI_Window_t"));
    if (window != 0) {
        switch (uMsg) {
        case WM_CREATE:
            break;
        case WM_SETFOCUS:
        {
            //_glfwInputWindowFocus(window, GLFW_TRUE);

            //// HACK: Do not disable cursor while the user is interacting with
            ////       a caption button
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
            if (window->callbackMouse)
	if ((short)HIWORD(wParam) > 0)
	    window->callbackMouse(GET_WHEEL_DELTA_WPARAM(wParam) / 120, (lParam), UpWheel, window->dataMouseCallback);
	else
	    window->callbackMouse(GET_WHEEL_DELTA_WPARAM(wParam) / 120, (lParam), DownWheel, window->dataMouseCallback);
            break;
        case WM_MOUSEMOVE:
            if (window->callbackMouse)
	window->callbackMouse(LOWORD(lParam), HIWORD(lParam), MouseMove, window->dataMouseCallback);
            break;
        case WM_MBUTTONDOWN:
            if (window->callbackMouse)
	window->callbackMouse(LOWORD(lParam), HIWORD(lParam), MiddleKey, window->dataMouseCallback);
            break;
        case WM_RBUTTONDOWN:
            if (window->callbackMouse)
	window->callbackMouse(LOWORD(lParam), HIWORD(lParam), RightKey, window->dataMouseCallback);
            break;
        case WM_LBUTTONDOWN:
            if (window->callbackMouse)
	window->callbackMouse(LOWORD(lParam), HIWORD(lParam), LeftKey, window->dataMouseCallback);
            break;
        case WM_MBUTTONUP:
            if (window->callbackMouse)
	window->callbackMouse(LOWORD(lParam), HIWORD(lParam), MiddleKey, window->dataMouseCallback);
            break;
        case WM_RBUTTONUP:
            if (window->callbackMouse)
	window->callbackMouse(LOWORD(lParam), HIWORD(lParam), RightKey, window->dataMouseCallback);
            break;
        case WM_LBUTTONUP:
            if (window->callbackMouse)
	window->callbackMouse(LOWORD(lParam), HIWORD(lParam), LeftKey, window->dataMouseCallback);
            break;
        case WM_KEYDOWN:
        {
            if (window->callbackKeyboard)
	window->callbackKeyboard((int)wParam, KeyDown, window->dataKeyboardCallback[0], window->dataKeyboardCallback[1]);
        }
        break;
        case WM_KEYUP:
        {
            int vkey = (int)wParam;
        }
        break;
        case WM_WINDOWPOSCHANGED:
            break;
        case WM_SIZE:
            window->m_width = LOWORD(lParam);
            window->m_height = HIWORD(lParam);
            if (window->callbackResizeWindow)
	window->callbackResizeWindow(window->m_width, window->m_height, window->dataResizeCallback[0], window->dataResizeCallback[1]);
            break;
        case WM_SIZING:
            break;
        case WM_ERASEBKGND:
            break;
        case WM_CLOSE:
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#endif