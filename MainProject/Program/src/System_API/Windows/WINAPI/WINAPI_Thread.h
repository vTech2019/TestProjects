#pragma once
#ifdef _WIN32


#include <windows.h>
#include <stdio.h>

struct win_thread {
	LPDWORD thread_id;
	HANDLE thread_h;
};
typedef struct win_thread thread_t;

static inline HANDLE thread_create_mutex(thread_t* m_thread) {
	char name[32];
	//sprintf(name, "%d", m_thread->thread_id);
	return CreateMutex(NULL, TRUE, name);
}
static inline void thread_release_mutex(HANDLE m_mutex) {
	ReleaseMutex(m_mutex);
}
char* thread_init(thread_t* m_thread, void* (*function) (void*), void* args);
char* thread_join(thread_t m_thread);
int thread_free_resource(thread_t* m_thread);
int thread_is_running(thread_t* m_thread);





#endif