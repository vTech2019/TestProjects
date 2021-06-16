//
// Created by human on 02.04.2020.
//

#ifdef __linux__
#include <errno.h>
#include "LINUX_Thread.h"
char* get_pthread_error(int code){
    switch (code) {
        case EAGAIN:
            return "Status error = EAGAIN";
        case EINVAL:
            return "Status error = EINVAL";
        case EPERM:
            return "Status error = EPERM";
    }
    return NULL;
}
char* thread_init(thread_t* thread_id, void *(*function) (void *), void* args){
    return get_pthread_error(pthread_create(thread_id, NULL, function, args));
}
char* thread_join(thread_t thread_id){
    return get_pthread_error(pthread_join(thread_id, NULL));
}
int thread_free_resource(thread_t* m_thread) {
    return 0;
}

int thread_is_running(const thread_t* m_thread)
{
    int iret = pthread_tryjoin_np(*m_thread,NULL);
    if((iret != 0) && (iret != EBUSY)) {
        return 0; //error
    }
    if(iret == EBUSY) {
        return 1;
    }
    return 0;
}
#endif