

#ifndef __THREADMANAGER_H__
#define __THREADMANAGER_H__

#define MAX_THREAD 32

#include <ThreadLibrary/ThreadLibrary.h>

typedef struct _thread_manager{
    thread_t m_thread[MAX_THREAD];
}thread_manager;

void thread_manager_init(thread_manager* manager) {
    size_t i;
    for (i = 0; i < MAX_THREAD; i++) {
        manager->m_thread[i] = thread_init(NULL);
    }
}

void thread_manager_callFunction(thread_manager* manager) {
    size_t i;
    for (i = 0; i < MAX_THREAD; i++) {
        manager->m_thread[i] = thread_init(NULL);
    }
}

void thread_manager_free(thread_manager* manager) {
    size_t i;
    for (i = 0; i < MAX_THREAD; i++) {
        thread_free(manager->m_thread[i]);
    }
}

#endif
