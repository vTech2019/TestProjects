//
// Created by human on 2/8/20.
//

#ifdef _WIN32
#ifndef GRAPHICSTEST_WINAPI_FILESYSTEM_H
#define GRAPHICSTEST_WINAPI_FILESYSTEM_H
#include <windows.h>
struct system_name_files;
typedef struct system_name_files system_name_files;
struct system_name_files {
    char** names;
    size_t number_names;
    char memory[0];
};
system_name_files* system_get_name_files(const char* path);
inline void system_free(system_name_files* data) { if (data) free(data); };


#endif //GRAPHICSTEST_WINAPI_FILESYSTEM_H
#endif