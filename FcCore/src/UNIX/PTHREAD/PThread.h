//
// Created by human on 31.12.2020.
//

#ifdef linux
#ifndef FC_PTHREAD_H
#define FC_PTHREAD_H

#define __USE_GNU

#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include "include/FcError.h"

#ifndef O_CREAT
#define O_CREAT 0x0008
#endif

#ifndef O_EXCL
#define O_EXCL 0x0010
#endif

#ifndef EOWNERTERM
#define EOWNERTERM 3462
#endif

#ifndef EDESTROYED
#define EDESTROYED 3463
#endif
#ifndef ERECURSE
#define ERECURSE 3419
#endif

#define FcSemaphoreN_Dec FcSemaphore_Dec
#define FcSemaphoreN_Inc FcSemaphore_Inc
typedef pthread_t FcThread_t;
typedef pthread_mutex_t FcMutex_t;
typedef sem_t FcSemaphore_t;

static FcError_t FcThread_Error(int m_error) {
    FcError_t l_error = FC_NO_ERROR;
    switch (m_error) {
        case EINVAL:
            l_error = FC_THREAD_INCORRECT_VALUE;
            break;
        case EAGAIN:
            l_error = FC_THREAD_MAXIMUM_NUMBER_OF_THREADS_FOR_THIS_JOB_HAS_BEEN_REACHED;
            break;
        case EBUSY:
            l_error = FC_THREAD_SYSTEM_CANNOT_ALLOW_THREAD_CREATION_IN_THIS_PROCESS_AT_THIS_TIME;
            break;
        case ESRCH:
            l_error = FC_THREAD_THE_THREAD_SPECIFIED_COULD_NOT_BE_FOUND;
            break;
        case ETIMEDOUT:
            l_error = FC_THREAD_THE_CALL_TIMES_OUT_BEFORE_THREAD_TERMINATED;
            break;
    }
    return l_error;
}

static inline FcError_t FcThread_create(FcThread_t *thread, void *(*f)(void *), void *arg) {
    FcError_t l_error = pthread_create(thread, NULL, f, arg);
    return FcThread_Error(l_error);
}

static inline FcError_t FcThread_join(const FcThread_t *thread_id) {
    FcError_t l_error = pthread_join(*thread_id, NULL);
    return FcThread_Error(l_error);
}

static inline FcError_t FcThread_running(const FcThread_t *thread) {
    int l_error = pthread_tryjoin_np(*thread, NULL);
    if (l_error == EBUSY)
        return FC_THREAD_RUNNING;
    return FcThread_Error(l_error);
}

static FcError_t FcMutex_Error(int m_error) {
    FcError_t l_error = FC_NO_ERROR;
    switch (m_error) {
        case EINVAL:
            l_error = FC_MUTEX_INCORRECT_VALUE;
            break;
        case ENOMEM:
            l_error = FC_MUTEX_NO_MEMORY;
            break;
        case EOWNERTERM:
            l_error = FC_MUTEX_OBJECT_NO_LONGER_EXISTS_BECAUSE_THE_OWNER_IS_NOT_LONGER_RUNNING;
            break;
        case EDESTROYED:
            l_error = FC_MUTEX_OBJECT_WAS_DESTROYED_NO_LONGER_EXISTS;
            break;
        case EDEADLK:
            l_error = FC_MUTEX_RESOURCE_DEADLOCK_AVOIDED;
            break;
        case ERECURSE:
            l_error = FC_MUTEX_RECURSIVE_ATTEMPT_REJECTED;
            break;
        case EPERM:
            l_error = FC_MUTEX_IS_NOT_CURRENTLY_HELD_BY_THE_CALLER;
            break;
        case EBUSY:
            l_error = FC_MUTEX_CURRENTLY_OWNED_BY_ANOTHER_THREAD;
            break;
    }
    return l_error;
}

static inline FcError_t FcMutex(FcMutex_t *mutex) {
    FcError_t l_error = pthread_mutex_init(mutex, NULL);
    return FcMutex_Error(l_error);
}

static inline FcError_t FcMutex_Lock(FcMutex_t *mutex) {
    FcError_t l_error = pthread_mutex_lock(mutex);
    return FcMutex_Error(l_error);
}

static inline FcError_t FcMutex_Unlock(FcMutex_t *mutex) {
    FcError_t l_error = pthread_mutex_unlock(mutex);
    return FcMutex_Error(l_error);
}

static inline FcError_t FcMutex_Free(FcMutex_t *mutex) {
    FcThread_t l_error = pthread_mutex_destroy(mutex);
    return FcMutex_Error(l_error);
}

static FcError_t FcSemaphore_Error(int m_error) {
    FcError_t l_error = FC_NO_ERROR;
    switch (m_error) {
        case EACCES:
            l_error = FC_SEMAPHORE_ACCES_DENIED;
            break;
        case EEXIST:
            l_error = FC_SEMAPHORE_EXIST;
            break;
        case EINVAL:
            l_error = FC_SEMAPHORE_INCORRECT_VALUE;
            break;
        case ENAMETOOLONG:
            l_error = FC_SEMAPHORE_NAME_TO_LONG;
            break;
        case ENOENT:
            l_error = FC_SEMAPHORE_NO_SUCH_PATH_OR_DIRECTORY;
            break;
        case ENOSPC:
            l_error = FC_SEMAPHORE_NO_SPACE_AVAILABLE;
            break;
        case EINTR:
            l_error = FC_SEMAPHORE_INTERRUPTED_FUNCTION_CALL;
            break;
        case EBUSY:
            l_error = FC_SEMAPHORE_RESOURCE_BUSY;
            break;
    }
    return l_error;
}

static inline FcError_t FcSemaphore(FcSemaphore_t *semaphore, unsigned int initCounter) {
    FcError_t l_error = FC_NO_ERROR;
    errno = 0;
    if (sem_init(semaphore, 0, initCounter) == -1)
        l_error = FcSemaphore_Error(errno);
    return l_error;
}

static inline FcError_t FcSemaphore_Dec(FcSemaphore_t *semaphore) {
    FcError_t l_error = FC_NO_ERROR;
    errno = 0;
    if (sem_wait(semaphore) == -1)
        l_error = FcSemaphore_Error(errno);
    return l_error;
}

static inline FcError_t FcSemaphore_Inc(FcSemaphore_t *semaphore) {
    FcError_t l_error = FC_NO_ERROR;
    errno = 0;
    if (sem_post(semaphore) == -1)
        l_error = FcSemaphore_Error(errno);
    return l_error;
}

static inline FcError_t FcSemaphore_Free(FcSemaphore_t *semaphore) {
    FcError_t l_error = FC_NO_ERROR;
    errno = 0;
    if (sem_destroy(semaphore) == -1)
        l_error = FcSemaphore_Error(errno);
    return l_error;
}

static inline FcError_t FcSemaphoreN(FcSemaphore_t *semaphore, const char *name, unsigned int initCounter) {
    FcError_t l_error = FC_NO_ERROR;
    errno = 0;
    if ((semaphore = sem_open(name, O_CREAT | O_EXCL, initCounter)) == SEM_FAILED)
        l_error = FcSemaphore_Error(errno);
    return l_error;
}

static inline FcError_t FcSemaphoreN_Free(FcSemaphore_t *semaphore) {
    FcError_t l_error = FC_NO_ERROR;
    errno = 0;
    if (sem_close(semaphore) == -1)
        l_error = FcSemaphore_Error(errno);
    return l_error;
}

#endif
#endif //FC_PTHREAD_H
