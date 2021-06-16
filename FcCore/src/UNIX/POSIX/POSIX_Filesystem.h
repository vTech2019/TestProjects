//
// Created by human on 03.04.2021.
//

#ifndef POSIX_FILESYSTEM
#define POSIX_FILESYSTEM

#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

static inline FcError_t FcFilesystem_createFolder(const char directory[]) {

    struct stat st = {0};

    if (stat(directory, &st) == -1) {
        errno = 0;
        if (mkdir(directory, 0755) == -1) {
            switch (errno) {
                case EACCES:
                    return FC_POSIX_EACCES;
                case EDQUOT:
                    return FC_POSIX_EDQUOT;
                case EFAULT:
                    return FC_POSIX_EFAULT;
                case EINVAL:
                    return FC_POSIX_EINVAL;
                case ELOOP:
                    return FC_POSIX_ELOOP;
                case EMLINK:
                    return FC_POSIX_EMLINK;
                case ENAMETOOLONG:
                    return FC_POSIX_ENAMETOOLONG;
                case ENOENT:
                    return FC_POSIX_ENOENT;
                case ENOMEM:
                    return FC_POSIX_ENOMEM;
                case ENOSPC:
                    return FC_POSIX_ENOSPC;
                case ENOTDIR:
                    return FC_POSIX_ENOTDIR;
                case EPERM:
                    return FC_POSIX_EPERM;
                case EROFS:
                    return FC_POSIX_EROFS;
                case EBADF:
                    return FC_POSIX_EBADF;
            }
        }
        return FC_NO_ERROR;
    }
    switch (st.st_mode & S_IFMT) {
        case S_IFBLK:
            return FC_POSIX_BlockDevice;
        case S_IFCHR:
            return FC_POSIX_CharacterDevice;
        case S_IFDIR:
            return FC_POSIX_Directory;
        case S_IFIFO:
            return FC_POSIX_FIFO_PIPE;
        case S_IFLNK:
            return FC_POSIX_Symlink;
        case S_IFREG:
            return FC_POSIX_RegularFile;
        case S_IFSOCK:
            return FC_POSIX_Socket;
        default:
            return FC_POSIX_Unknown;
    }
}

#endif //
