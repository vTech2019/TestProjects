//
// Created by human on 04.04.2020.
//

#ifndef GRAPHICSTEST_SYSTEM_FILESYSTEM_H
#define GRAPHICSTEST_SYSTEM_FILESYSTEM_H
#ifdef __linux__
#include "X11_Window/X11_Filesystem.h"
#elif _WIN32
#include "Windows/WINAPI/WINAPI_Filesystem.h"
#else
#endif
#endif //GRAPHICSTEST_SYSTEM_FILESYSTEM_H
