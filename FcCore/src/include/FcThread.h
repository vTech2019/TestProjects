

#pragma once
#ifndef __FCTHREAD_H__
#define __FCTHREAD_H__


#include "UNIX/PTHREAD/PThread.h"
#include "WINAPI/WINAPI_Thread.h"

#include <time.h>

static inline double FcGLWindow_GetClockSec() {
    return (double) clock() / CLOCKS_PER_SEC;
}

#endif