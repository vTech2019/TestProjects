#ifdef _WIN32
#include "WINAPI_Thread.h"
#include <synchapi.h>
char* thread_init(thread_t* m_thread, void* (*function) (void*), void* args) {
    m_thread->thread_h = CreateThread(NULL, NULL, function, args, 0, &m_thread->thread_id);
    if (m_thread->thread_h) return NULL;
    return "CreateThread error!";
}
char* thread_join(thread_t m_thread) {
    if (WAIT_FAILED == WaitForSingleObject(m_thread.thread_h, INFINITE))
        return "WaitForSingleObject error!";
    return NULL;
}
int thread_free_resource(thread_t* m_thread) {
    int result = CloseHandle(m_thread->thread_h);
    m_thread->thread_h = 0;
    m_thread->thread_id = 0;
    return result;
}

int thread_is_running(thread_t* m_thread)
{
    DWORD exitCode = 0;
    GetExitCodeThread(m_thread->thread_h, &exitCode);
    if (exitCode == STILL_ACTIVE)
        return TRUE;
    return FALSE;
}
#endif