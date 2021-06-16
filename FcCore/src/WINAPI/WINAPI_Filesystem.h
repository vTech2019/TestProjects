//
// Created by human on 2/8/20.
//

#ifdef _WIN32
#ifndef WINAPI_FILESYSTEM_H
#define WINAPI_FILESYSTEM_H
#include <windows.h>
#include "FcError.h"
struct system_name_files;
typedef struct system_name_files system_name_files;
struct system_name_files {
    char** names;
    size_t number_names;
    char memory[0];
};
system_name_files* system_get_name_files(const char* path);
inline void system_free(system_name_files* data) { if (data) free(data); };



static inline FcError_t FcFilesystem_createFolder(const TCHAR directory[])
{
    if (CreateDirectory(directory, NULL)) {
        return FC_NO_ERROR;
    }
    switch (GetLastError()) {
    case ERROR_ALREADY_EXISTS:  return FC_WINAPI_EXISTS;
    case ERROR_PATH_NOT_FOUND:  return FC_WINAPI_PATH_NOT_FOUND;
    default:       return FC_WINAPI_UNKNOWN;
    }
}

#endif //GRAPHICSTEST_WINAPI_FILESYSTEM_H
#endif