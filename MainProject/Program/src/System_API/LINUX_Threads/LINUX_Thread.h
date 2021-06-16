//
// Created by human on 02.04.2020.
//

#ifdef __linux__
#ifndef GRAPHICSTEST_X11_THREAD_H
#define GRAPHICSTEST_X11_THREAD_H
#define  __USE_GNU
#include <pthread.h>
typedef pthread_t thread_t;

char* thread_init(thread_t* thread_id, void *(*function) (void *), void* args);
char* thread_join(thread_t thread_id);
int thread_free_resource(thread_t* m_thread);
int thread_is_running(const thread_t* m_thread);

#endif //GRAPHICSTEST_X11_THREAD_H
#endif