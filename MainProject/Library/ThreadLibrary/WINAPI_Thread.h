#ifndef _WINAPI_THREAD_H_
#define _WINAPI_THREAD_H_
#include <windows.h>

#define WM_USER_CALL_FUNCTION_THREAD WM_USER + 1

typedef struct _WINAPI_Thread_t {
    HANDLE threadH;
    DWORD threadId;
}WINAPI_Thread_t;

WINAPI_Thread_t thread_init(LPVOID parameters);
void thread_functionCall(WINAPI_Thread_t thread, void (*ptrFunction)(VOID* data), LPVOID parameters);
WINAPI_Thread_t thread_free(WINAPI_Thread_t thread);

DWORD WINAPI WINAPI_Function(LPVOID parameters);




WINAPI_Thread_t thread_init(LPVOID parameters)
{
    WINAPI_Thread_t m_thread;
    m_thread.threadH = CreateThread(NULL, 0, WINAPI_Function, parameters, 0, &m_thread.threadId);
    return m_thread;
}
void thread_functionCall(WINAPI_Thread_t thread, void (*ptrFunction)(VOID* data), LPVOID parameters)
{
    while (PostThreadMessage(thread.threadId, WM_USER_CALL_FUNCTION_THREAD, (WPARAM)ptrFunction, (LPARAM)parameters) == 0)
        Sleep(0);
}
WINAPI_Thread_t thread_free(WINAPI_Thread_t thread)
{
    while (PostThreadMessage(thread.threadId, WM_QUIT, 0, 0) == 0)
        Sleep(0);
    WaitForSingleObject(thread.threadH, INFINITE);
    CloseHandle(thread.threadH);
}

DWORD WINAPI WINAPI_Function(LPVOID parameters)
{
    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            switch (msg.message)
            {
            case WM_USER_CALL_FUNCTION_THREAD:
	((void (*)(VOID * data)) msg.wParam)((void*)msg.lParam);
	break;
            default:
	Sleep(0);
            }
        }
    }
    return 0;
}
#endif