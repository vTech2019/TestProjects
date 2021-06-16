//
// Created by human on 2/8/20.
//

#ifdef __linux__
#include <string.h>
#include <stdlib.h>
#include "X11_Filesystem.h"

system_name_files* system_get_name_files(const char* path){
    size_t number_files = 0;
    size_t length_names = 0;
    system_name_files* names;
    DIR* parameters = opendir(path);
    DIR* parameters_copy = opendir(path);
    struct dirent* file = NULL;
    if (parameters) file = readdir(parameters);
    while(file){
        if ( strcmp(file->d_name, ".")!=0 && strcmp(file->d_name, "..")!=0 ){
            length_names += strlen(file->d_name) + 1;
            number_files++;
        }
        file = readdir(parameters);
    }
    names = calloc(1, length_names + sizeof(system_name_files) + number_files * sizeof(char*));
    (names)->number_names = number_files;
    (names)->names = (char **) (names)->memory;
    number_files = 0;
    length_names = 0;
    if (parameters_copy) file = readdir(parameters_copy);
    while(file){
        if ( strcmp(file->d_name, ".")!=0 && strcmp(file->d_name, "..")!=0 ){
            memcpy((names)->names[number_files++], file->d_name, file->d_reclen);
            length_names += file->d_reclen;
            (names)->names[number_files] = (names)->memory + length_names;
        }
        file = readdir(parameters);
    }
    closedir(parameters);
    closedir(parameters_copy);
    return names;
}
#endif