//
// Created by human on 2/8/20.
//

#ifdef _WIN32

#include <stddef.h>
#include <string.h>
#include <memory.h>
#include "WINAPI_Filesystem.h"

system_name_files* system_get_name_files(const char* path) {
    size_t i = 0;
    size_t number_files = 0;
    size_t length_names = strlen(path);
    system_name_files* names;
    char* path_name = _alloca(length_names + 2);
    for (i = 0; i < length_names; i++) path_name[i] = path[i];
    path_name[i++] = '/';
    path_name[i] = '*';
    length_names = 0;
    WIN32_FIND_DATA data;
    HANDLE hFind = FindFirstFile(path_name, &data);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            length_names += strlen(data.cFileName);
            number_files++;
        } while (FindNextFile(hFind, &data));
        FindClose(hFind);
    }
    hFind = FindFirstFile(path_name, &data);
    names = calloc(1, length_names + sizeof(system_name_files) + number_files * sizeof(char*));
    (names)->number_names = number_files;
    (names)->names = (char**)(names)->memory;
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            memcpy((names)->names[number_files++], data.cFileName, strlen(data.cFileName));
            length_names += strlen(data.cFileName);
            (names)->names[number_files] = (names)->memory + length_names;
        } while (FindNextFile(hFind, &data));
        FindClose(hFind);
    }

    return names;
}
#endif