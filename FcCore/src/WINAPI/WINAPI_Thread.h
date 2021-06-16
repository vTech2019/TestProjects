#pragma once

#ifdef _WIN32
#ifndef _WINAPI_THREAD_H_
#define _WINAPI_THREAD_H_	 

#include <windows.h>    
#include "FcError.h"    
#include "WINAPI_Error.h"

#define SEM_VALUE_MAX 32767

enum FcThread_Manager {
    FcThread_Manager_repeatLastIfQueueEmpty = 1
};
typedef HANDLE FcMutex_t;
typedef HANDLE FcSemaphore_t;
typedef struct {
    DWORD threadId;
    HANDLE threadHandle;
} FcThread_t;

#define WM_USER_CALL_FUNCTION_THREAD WM_USER + 1


static inline FcError_t FcThread_create(FcThread_t* thread, DWORD(*f)(void*), void* arg) {
    FcError_t l_error = FC_NO_ERROR;
    thread->threadHandle = CreateThread(NULL, 0, f, arg, 0, &thread->threadId);
    if (!thread->threadHandle) {
        l_error = getLastErrorMessage(__LINE__, __FILE__);
    }
    return l_error;
}

static inline FcError_t  FcThread_join(FcThread_t* thread) {
    FcError_t l_error = FC_NO_ERROR;
    if (WaitForSingleObject(thread->threadHandle, INFINITE) == WAIT_FAILED) {
        l_error = getLastErrorMessage(__LINE__, __FILE__);
    }
    return l_error;
}
                             
static inline FcError_t FcThread_running(const FcThread_t* thread) {
    FcError_t l_error = FC_NO_ERROR;
    DWORD exitCode = 0;
    l_error = GetExitCodeThread(thread->threadHandle, &exitCode);
    if (!l_error) 
        l_error = getLastErrorMessage(__LINE__, __FILE__);
    if (exitCode == STILL_ACTIVE)
        return FC_THREAD_RUNNING;
    return l_error;
}

static void FcThread_exit(FcThread_t thread) {
    while (PostThreadMessage(thread.threadId, WM_QUIT, 0, 0) == 0)
        Sleep(0);
}

static void FcThread_exitLock(FcThread_t thread) {
    while (PostThreadMessage(thread.threadId, WM_QUIT, 0, 0) == 0)
        Sleep(0);
    WaitForSingleObject(thread.threadHandle, INFINITE);
    CloseHandle(thread.threadHandle);
}

extern DWORD WINAPI FcThread_exec();
static inline DWORD WINAPI FcThread_exec() {
    MSG msg = { 0 };
    int manager = 0;
    int tmp_manager;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_USER_CALL_FUNCTION_THREAD) {
                tmp_manager = ((int (*)(LPVOID data)) msg.wParam)((void*)msg.lParam);
                if (tmp_manager & FcThread_Manager_repeatLastIfQueueEmpty)
                    manager = tmp_manager,
                    message = msg.message,
                    wParam = msg.wParam,
                    lParam = msg.lParam;
            }
        }
        else if (manager & FcThread_Manager_repeatLastIfQueueEmpty) {
            manager = ((int (*)(LPVOID data)) wParam)((void*)lParam);
        }
        // WaitMessage();
    }
    return 0;
}

static inline FcError_t FcMutex(FcMutex_t* mutex)
{
    FcError_t l_error = FC_NO_ERROR;
    *mutex = CreateMutex(NULL, FALSE, NULL);
    if (*mutex == NULL)
        l_error = getLastErrorMessage(__LINE__, __FILE__);
    return l_error;
}

static inline FcError_t FcMutex_Lock(FcMutex_t* mutex) {
    FcError_t l_error = FC_NO_ERROR;
    if (WaitForSingleObject(*mutex, INFINITE) != WAIT_OBJECT_0)
        l_error = getLastErrorMessage(__LINE__, __FILE__);
    return l_error;
}

static inline FcError_t FcMutex_Unlock(FcMutex_t* mutex) {
    FcError_t l_error = FC_NO_ERROR;
    if (ReleaseMutex(*mutex) == NULL)
        l_error = getLastErrorMessage(__LINE__, __FILE__);
    return l_error;
}

static inline FcError_t FcMutex_Free(FcMutex_t* mutex) {
    FcError_t l_error = FC_NO_ERROR;
    if (CloseHandle(*mutex) == NULL)
        l_error = getLastErrorMessage(__LINE__, __FILE__);
    return l_error;

}

static inline FcError_t FcSemaphore(FcSemaphore_t* semaphore, long initCounter) {
    FcError_t l_error = FC_NO_ERROR;
    *semaphore = CreateSemaphore(NULL, initCounter, SEM_VALUE_MAX, NULL);
    if (*semaphore == NULL)
        l_error = getLastErrorMessage(__LINE__, __FILE__);
    return l_error;
}

static inline FcError_t FcSemaphoreN(FcSemaphore_t* semaphore, const char* name, long initCounter) {
    FcError_t l_error = FC_NO_ERROR;
    *semaphore = CreateSemaphore(NULL, initCounter, SEM_VALUE_MAX, name);
    if (*semaphore == NULL)
        l_error = getLastErrorMessage(__LINE__, __FILE__);
    return l_error;
}

static inline FcError_t  FcSemaphore_Dec(FcSemaphore_t* semaphore) {
    FcError_t l_error = FC_NO_ERROR;
    if (WaitForSingleObject(*semaphore, INFINITE) != WAIT_OBJECT_0)
        l_error = getLastErrorMessage(__LINE__, __FILE__);
    return l_error;
}

static inline FcError_t  FcSemaphore_Inc(FcSemaphore_t* semaphore) {
    FcError_t l_error = FC_NO_ERROR;
    if (ReleaseSemaphore(*semaphore, 1, NULL) == NULL)
        l_error = getLastErrorMessage(__LINE__, __FILE__);
    return l_error;
}

static inline BOOL FcSemaphore_Signal(FcSemaphore_t* semaphore) {
    if (WaitForSingleObject(*semaphore, 0) == WAIT_TIMEOUT)
        return 0;
    return 1;
}

static inline FcError_t  FcSemaphore_Free(FcSemaphore_t* semaphore) {
    FcError_t l_error = FC_NO_ERROR;
    if (CloseHandle(*semaphore) == NULL)
        l_error = getLastErrorMessage(__LINE__, __FILE__);
    return l_error;
}

#endif //_WINAPI_THREAD_H_
#endif