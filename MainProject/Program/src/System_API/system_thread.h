//
// Created by human on 02.04.2020.
//

#ifndef GRAPHICSTEST_PROGRAM_THREAD_H
#define GRAPHICSTEST_PROGRAM_THREAD_H
#ifdef __linux__
#include "LINUX_Threads/LINUX_Thread.h"
#elif _WIN32
#include "Windows/WINAPI/WINAPI_Thread.h"
#else
#endif
#endif //GRAPHICSTEST_PROGRAM_THREAD_H
