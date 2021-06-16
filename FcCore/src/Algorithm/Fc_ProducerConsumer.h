//
// Created by human on 02.01.2021.
//

#ifndef FcCore_PRODUCERCONSUMER_H
#define FcCore_PRODUCERCONSUMER_H

#include "include/FcThread.h"
#include <stdint.h>

#define QUEUE_SIZE 256

enum FcGLWindow_graphicsQueue {
    e_FcGL_exit,
    e_FcGL_callFunction_fp,
    e_FcGL_callFunction_fpp,
    e_FcGL_callFunction_fup,
    e_FcGL_callFunction_fff,

    e_FcGL_callbackFunction_fp,
    e_FcGL_callbackFunction_fpp,
    e_FcGL_callbackFunction_fup,
    e_FcGL_callbackFunction_fff,
    e_FcGL_callbackFunction_exit
};
union _Fc_ProducerConsumerTypeData_t {
    void *v;
    float f;
    unsigned u;
};
typedef struct _Fc_ProducerConsumerData_t {
    uintptr_t id;
    union _Fc_ProducerConsumerTypeData_t s0;
    union _Fc_ProducerConsumerTypeData_t s1;
    union _Fc_ProducerConsumerTypeData_t s2;
} Fc_ProducerConsumerData_t;

typedef struct _Fc_ProducerConsumer_t {
    FcThread_t m_thread;
    FcMutex_t m_mutex;
    FcSemaphore_t m_full;
    FcSemaphore_t m_empty;
    uint8_t i, offset;
    Fc_ProducerConsumerData_t m_callbackFunction;
    Fc_ProducerConsumerData_t m_queue[QUEUE_SIZE];
} Fc_ProducerConsumer_t;


FcError_t Fc_ProducerConsumer(Fc_ProducerConsumer_t *glThread);

FcError_t Fc_ProducerConsumer_freeLock(Fc_ProducerConsumer_t *m_thread);

FcError_t Fc_threadProducer(Fc_ProducerConsumer_t *glThread, Fc_ProducerConsumerData_t value);

#endif //FcCore_PRODUCERCONSUMER_H
