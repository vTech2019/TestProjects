#include <string.h>
#include "Fc_ProducerConsumer.h"

#ifdef WIN32
DWORD __stdcall Fc_ThreadConsumer(void* m_window);
#elif (__linux)

void *Fc_ThreadConsumer(void *m_window);

#endif

FcError_t Fc_ProducerConsumer(Fc_ProducerConsumer_t *glThread) {
    FcError_t l_error = FC_NO_ERROR;
    memset(glThread, 0, sizeof(Fc_ProducerConsumer_t));
    l_error = FcMutex(&glThread->m_mutex);
    if (l_error) goto g_error;
    l_error = FcSemaphore(&glThread->m_full, QUEUE_SIZE);
    if (l_error) goto g_error;
    l_error = FcSemaphore(&glThread->m_empty, 0);
    if (l_error) goto g_error;
    l_error = FcThread_create(&glThread->m_thread, Fc_ThreadConsumer, glThread);
    g_error:
    return l_error;
}

FcError_t Fc_ProducerConsumer_freeLock(Fc_ProducerConsumer_t *m_thread) {
    FcError_t l_error = FC_NO_ERROR;
    Fc_threadProducer(m_thread, (Fc_ProducerConsumerData_t) {e_FcGL_exit, 0, 0, 0});
    l_error = FcThread_join(&m_thread->m_thread);
    if (l_error) goto g_error;
    l_error = FcMutex_Free(&m_thread->m_mutex);
    if (l_error) goto g_error;
    l_error = FcSemaphore_Free(&m_thread->m_full);
    if (l_error) goto g_error;
    l_error = FcSemaphore_Free(&m_thread->m_empty);
    memset(m_thread, 0, sizeof(*m_thread));
    g_error:
    return l_error;
}

#ifdef WIN32
DWORD __stdcall Fc_ThreadConsumer(void* thread) {
#elif (__linux)

void *Fc_ThreadConsumer(void *thread) {
#endif
    Fc_ProducerConsumer_t *m_thread = (Fc_ProducerConsumer_t *) thread;
    Fc_ProducerConsumerData_t value;
    Fc_ProducerConsumerData_t callback = {0};
    size_t i = 0;
    while (1) {
        FcSemaphore_Dec(&m_thread->m_empty);
        FcMutex_Lock(&m_thread->m_mutex);
        m_thread->i--;
        value = m_thread->m_queue[i];
        i = m_thread->i ? i + 1 : 0;
        FcMutex_Unlock(&m_thread->m_mutex);
        FcSemaphore_Inc(&m_thread->m_full);
        switch (value.id) {
            case e_FcGL_exit:
                return 0;
            case e_FcGL_callFunction_fp:
                ((void (*)(void *)) value.s0.v)(value.s1.v);
                break;
            case e_FcGL_callFunction_fpp:
                ((void (*)(void *, void *)) value.s0.v)(value.s1.v, value.s2.v);
                break;
            case e_FcGL_callFunction_fup:
                ((void (*)(unsigned, void *)) value.s0.v)(value.s1.u, value.s2.v);
                break;
            case e_FcGL_callFunction_fff:
                ((void (*)(float, float)) value.s0.v)(value.s1.f, value.s2.f);
                break;
            case e_FcGL_callbackFunction_exit:
                callback = (Fc_ProducerConsumerData_t) {0, 0, 0, 0};
                break;
            case e_FcGL_callbackFunction_fp:
            case e_FcGL_callbackFunction_fpp:
            case e_FcGL_callbackFunction_fup:
            case e_FcGL_callbackFunction_fff:
                callback = value;
                break;
        }
        while (m_thread->i == 0 && callback.id) {
            switch (callback.id) {
                case e_FcGL_callbackFunction_fp:
                    ((void (*)(void *)) callback.s0.v)(callback.s1.v);
                    break;
                case e_FcGL_callbackFunction_fpp:
                    ((void (*)(void *, void *)) callback.s0.v)(callback.s1.v, callback.s2.v);
                    break;
                case e_FcGL_callbackFunction_fup:
                    ((void (*)(unsigned, void *)) callback.s0.v)(callback.s1.u, callback.s2.v);
                    break;
                case e_FcGL_callbackFunction_fff:
                    ((void (*)(float, float)) callback.s0.v)(callback.s1.f, callback.s2.f);
                    break;
            }
        }
    }

    return 0;
}

FcError_t Fc_threadProducer(Fc_ProducerConsumer_t *glThread, Fc_ProducerConsumerData_t value) {
    FcError_t l_error = FC_NO_ERROR;
    l_error = FcSemaphore_Dec(&glThread->m_full);
    if (l_error) goto g_error;
    l_error = FcMutex_Lock(&glThread->m_mutex);
    if (l_error) goto g_error;
    glThread->offset = glThread->i ? glThread->offset + 1 : 0;
    glThread->m_queue[glThread->offset] = value;
    glThread->i++;
    l_error = FcMutex_Unlock(&glThread->m_mutex);
    if (l_error) goto g_error;
    l_error = FcSemaphore_Inc(&glThread->m_empty);
    g_error:
    return l_error;
}