#ifndef _WINAPI_MUTEX_H_
#define _WINAPI_MUTEX_H_
#include <windows.h>
#include <stdio.h>

typedef struct _WINAPI_Mutex_t {
    HANDLE h_mutex;
}WINAPI_Mutex_t;

WINAPI_Mutex_t ThreadLibrary_Mutex(LPTSTR name)
{
    WINAPI_Mutex_t m_mutex;
    if ((m_mutex.h_mutex = CreateMutex(NULL, FALSE, name) == NULL) {
        printf("Format message failed with 0x%x\n", GetLastError());
    }
}
void ThreadLibrary_Mutex_Lock(WINAPI_Mutex_t mutex)
{
    if (WaitForSingleObject(mutex.h_mutex, INFINITE) != WAIT_OBJECT_0)
    {
        printf("Format message failed with 0x%x\n", GetLastError());
    }
}
void ThreadLibrary_Mutex_Unlock(WINAPI_Mutex_t* mutex)
{
    ReleaseMutex(mutex->h_mutex);
}
void ThreadLibrary_Mutex(WINAPI_Mutex_t* mutex)
{
    CloseHandle(mutex->h_mutex);
    mutex->h_mutex = NULL;
}
#endif
