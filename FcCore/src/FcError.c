#include "include/FcError.h"
#include <stdio.h>
#include <stdlib.h>
#include <config.h>
#include <string.h>

#define FC_FILE_ERROR(file) PROJECT_NAME #file
extern FILE *eFileError;

void FcErrorOpen(FcError_t error) {
    enum FcError mError = error;
    char *mErrorString = NULL;
    if (!eFileError)
        eFileError = fopen(FC_FILE_ERROR(ERROR), "wb");
    if (!eFileError)
        exit(errno);
    switch (mError) {
        default:
            mErrorString = "FC_NO_ERROR_REGISTER";
            break;
        case FC_NO_ERROR:
            mErrorString = "FC_NO_ERROR";
            break;
        case FC_PNG_NOTPNG:
            mErrorString = "FC_PNG_NOTPNG";
            break;
        case FC_PNG_CRCERROR:
            mErrorString = "FC_PNG_CRCERROR";
            break;
        case FC_PNG_UNSUPPORTED:
            mErrorString = "FC_PNG_UNSUPPORTED";
            break;
        case FC_IO_EPERM:
            mErrorString = "FC_IO_EPERM";
            break;
        case FC_IO_ENOENT:
            mErrorString = "FC_IO_ENOENT";
            break;
        case FC_IO_ESRCH:
            mErrorString = "FC_IO_ESRCH";
            break;
        case FC_IO_EINTR:
            mErrorString = "FC_IO_EINTR";
            break;
        case FC_IO_EIO:
            mErrorString = "FC_IO_EIO";
            break;
        case FC_IO_ENXIO:
            mErrorString = "FC_IO_ENXIO";
            break;
        case FC_IO_E2BIG:
            mErrorString = "FC_IO_E2BIG";
            break;
        case FC_IO_ENOEXEC:
            mErrorString = "FC_IO_ENOEXEC";
            break;
        case FC_IO_EBADF:
            mErrorString = "FC_IO_EBADF";
            break;
        case FC_IO_ECHILD:
            mErrorString = "FC_IO_ECHILD";
            break;
        case FC_IO_EAGAIN:
            mErrorString = "FC_IO_EAGAIN";
            break;
        case FC_IO_ENOMEM:
            mErrorString = "FC_IO_ENOMEM";
            break;
        case FC_IO_EACCES:
            mErrorString = "FC_IO_EACCES";
            break;
        case FC_IO_EFAULT:
            mErrorString = "FC_IO_EFAULT";
            break;
        case FC_IO_EBUSY:
            mErrorString = "FC_IO_EBUSY";
            break;
        case FC_IO_EEXIST:
            mErrorString = "FC_IO_EEXIST";
            break;
        case FC_IO_EXDEV:
            mErrorString = "FC_IO_EXDEV";
            break;
        case FC_IO_ENODEV:
            mErrorString = "FC_IO_ENODEV";
            break;
        case FC_IO_ENOTDIR:
            mErrorString = "FC_IO_ENOTDIR";
            break;
        case FC_IO_EISDIR:
            mErrorString = "FC_IO_EISDIR";
            break;
        case FC_IO_EINVAL:
            mErrorString = "FC_IO_EINVAL";
            break;
        case FC_IO_ENFILE:
            mErrorString = "FC_IO_ENFILE";
            break;
        case FC_IO_EMFILE:
            mErrorString = "FC_IO_EMFILE";
            break;
        case FC_IO_ENOTTY:
            mErrorString = "FC_IO_ENOTTY";
            break;
        case FC_IO_EFBIG:
            mErrorString = "FC_IO_EFBIG";
            break;
        case FC_IO_ENOSPC:
            mErrorString = "FC_IO_ENOSPC";
            break;
        case FC_IO_ESPIPE:
            mErrorString = "FC_IO_ESPIPE";
            break;
        case FC_IO_EROFS:
            mErrorString = "FC_IO_EROFS";
            break;
        case FC_IO_EMLINK:
            mErrorString = "FC_IO_EMLINK";
            break;
        case FC_IO_EPIPE:
            mErrorString = "FC_IO_EPIPE";
            break;
        case FC_IO_EDOM:
            mErrorString = "FC_IO_EDOM";
            break;
        case FC_IO_ERANGE:
            mErrorString = "FC_IO_ERANGE";
            break;
        case FC_IO_EDEADLK:
            mErrorString = "FC_IO_EDEADLK";
            break;
#ifdef MSVC
        case FC_IO_EDEADLOCK:
            mErrorString = "FC_IO_EDEADLOCK";
            break;
#endif
        case FC_IO_ENAMETOOLONG:
            mErrorString = "FC_IO_ENAMETOOLONG";
            break;
        case FC_IO_ENOLCK:
            mErrorString = "FC_IO_ENOLCK";
            break;
        case FC_IO_ENOSYS:
            mErrorString = "FC_IO_ENOSYS";
            break;
        case FC_IO_ENOTEMPTY:
            mErrorString = "FC_IO_ENOTEMPTY";
            break;
        case FC_IO_EILSEQ:
            mErrorString = "FC_IO_EILSEQ";
            break;

#ifdef WIN32
            FC_IO_STRUNCATE = case STRUNCATE: mErrorString = "STRUNCATE"; break; //String was truncated
#endif

        case FC_THREAD_RUNNING:
            mErrorString = "FC_THREAD_RUNNING";
            break;
        case FC_THREAD_INCORRECT_VALUE:
            mErrorString = "FC_THREAD_INCORRECT_VALUE";
            break;
        case FC_THREAD_MAXIMUM_NUMBER_OF_THREADS_FOR_THIS_JOB_HAS_BEEN_REACHED:
            mErrorString = "FC_THREAD_MAXIMUM_NUMBER_OF_THREADS_FOR_THIS_JOB_HAS_BEEN_REACHED";
            break;
        case FC_THREAD_SYSTEM_CANNOT_ALLOW_THREAD_CREATION_IN_THIS_PROCESS_AT_THIS_TIME:
            mErrorString = "FC_THREAD_SYSTEM_CANNOT_ALLOW_THREAD_CREATION_IN_THIS_PROCESS_AT_THIS_TIME";
            break;
        case FC_THREAD_THE_THREAD_SPECIFIED_COULD_NOT_BE_FOUND:
            mErrorString = "FC_THREAD_THE_THREAD_SPECIFIED_COULD_NOT_BE_FOUND";
            break;
        case FC_THREAD_THE_CALL_TIMES_OUT_BEFORE_THREAD_TERMINATED:
            mErrorString = "FC_THREAD_THE_CALL_TIMES_OUT_BEFORE_THREAD_TERMINATED";
            break;

        case FC_SEMAPHORE_ACCES_DENIED:
            mErrorString = "FC_SEMAPHORE_ACCES_DENIED";
            break;
        case FC_SEMAPHORE_EXIST:
            mErrorString = "FC_SEMAPHORE_EXIST";
            break;
        case FC_SEMAPHORE_INCORRECT_VALUE:
            mErrorString = "FC_SEMAPHORE_INCORRECT_VALUE";
            break;
        case FC_SEMAPHORE_NAME_TO_LONG:
            mErrorString = "FC_SEMAPHORE_NAME_TO_LONG";
            break;
        case FC_SEMAPHORE_NO_SUCH_PATH_OR_DIRECTORY:
            mErrorString = "FC_SEMAPHORE_NO_SUCH_PATH_OR_DIRECTORY";
            break;
        case FC_SEMAPHORE_NO_SPACE_AVAILABLE:
            mErrorString = "FC_SEMAPHORE_NO_SPACE_AVAILABLE";
            break;
        case FC_SEMAPHORE_INTERRUPTED_FUNCTION_CALL:
            mErrorString = "FC_SEMAPHORE_INTERRUPTED_FUNCTION_CALL";
            break;
        case FC_SEMAPHORE_RESOURCE_BUSY:
            mErrorString = "FC_SEMAPHORE_RESOURCE_BUSY";
            break;

        case FC_MUTEX_INCORRECT_VALUE:
            mErrorString = "FC_MUTEX_INCORRECT_VALUE";
            break;
        case FC_MUTEX_NO_MEMORY:
            mErrorString = "FC_MUTEX_NO_MEMORY";
            break;
        case FC_MUTEX_OBJECT_WAS_DESTROYED_NO_LONGER_EXISTS:
            mErrorString = "FC_MUTEX_OBJECT_WAS_DESTROYED_NO_LONGER_EXISTS";
            break;
        case FC_MUTEX_OBJECT_NO_LONGER_EXISTS_BECAUSE_THE_OWNER_IS_NOT_LONGER_RUNNING:
            mErrorString = "FC_MUTEX_OBJECT_NO_LONGER_EXISTS_BECAUSE_THE_OWNER_IS_NOT_LONGER_RUNNING";
            break;
        case FC_MUTEX_RESOURCE_DEADLOCK_AVOIDED:
            mErrorString = "FC_MUTEX_RESOURCE_DEADLOCK_AVOIDED";
            break;
        case FC_MUTEX_RECURSIVE_ATTEMPT_REJECTED:
            mErrorString = "FC_MUTEX_RECURSIVE_ATTEMPT_REJECTED";
            break;
        case FC_MUTEX_IS_NOT_CURRENTLY_HELD_BY_THE_CALLER:
            mErrorString = "FC_MUTEX_IS_NOT_CURRENTLY_HELD_BY_THE_CALLER";
            break;
        case FC_MUTEX_CURRENTLY_OWNED_BY_ANOTHER_THREAD:
            mErrorString = "FC_MUTEX_CURRENTLY_OWNED_BY_ANOTHER_THREAD";
            break;
#ifdef WIN32
            case FC_WINAPI_EXISTS: mErrorString = "FC_WINAPI_EXISTS"; break;
            case FC_WINAPI_PATH_NOT_FOUND: mErrorString = "FC_WINAPI_PATH_NOT_FOUND"; break;
            case FC_WINAPI_UNKNOWN: mErrorString = "FC_WINAPI_UNKNOWN"; break;
#endif
#ifdef linux
        case FC_GLX_LoadLibrary:
            mErrorString = "FC_GLX_LoadLibrary";
            break;
        case FC_GLX_Version14IsRequired:
            mErrorString = "FC_GLX_Version14IsRequired";
            break;
        case FC_GLX_ARBCreateContextProfile:
            mErrorString = "FC_GLX_ARBCreateContextProfile";
            break;
        case FC_GLX_FBConfigsNotFound:
            mErrorString = "FC_GLX_FBConfigsNotFound";
            break;
        case FC_GLX_ContextNotDebug:
            mErrorString = "FC_GLX_ContextNotDebug";
            break;
        case FC_GLX_ContextNotDirect:
            mErrorString = "FC_GLX_ContextNotDirect";
            break;
        case FC_GLX_MakeCurrent:
            mErrorString = "FC_GLX_MakeCurrent";
            break;
        case FC_GLX_BadContext:
            mErrorString = "FC_GLX_BadContext";
            break;
        case FC_GLX_BadContextState:
            mErrorString = "FC_GLX_BadContextState";
            break;
        case FC_GLX_BadCurrentDrawable:
            mErrorString = "FC_GLX_BadCurrentDrawable";
            break;
        case FC_GLX_BadCurrentWindow:
            mErrorString = "FC_GLX_BadCurrentWindow";
            break;
        case FC_GLX_BadDrawable:
            mErrorString = "FC_GLX_BadDrawable";
            break;
        case FC_GLX_BadFBConfig:
            mErrorString = "FC_GLX_BadFBConfig";
            break;
        case FC_GLX_BadPbuffer:
            mErrorString = "FC_GLX_BadPbuffer";
            break;
        case FC_GLX_BadPixmap:
            mErrorString = "FC_GLX_BadPixmap";
            break;
        case FC_GLX_UnsupportedPrivateRequest:
            mErrorString = "FC_GLX_UnsupportedPrivateRequest";
            break;
        case FC_GLX_BadWindow:
            mErrorString = "FC_GLX_BadWindow";
            break;
        case FC_GLX_BadContextTag:
            mErrorString = "FC_GLX_BadContextTag";
            break;
        case FC_GLX_BadRenderRequest:
            mErrorString = "FC_GLX_BadRenderRequest";
            break;
        case FC_GLX_BadLargeRequest:
            mErrorString = "FC_GLX_BadLargeRequest";
            break;

        case FC_POSIX_BlockDevice:
            mErrorString = "FC_POSIX_BlockDevice";
            break;
        case FC_POSIX_CharacterDevice:
            mErrorString = "FC_POSIX_CharacterDevice";
            break;
        case FC_POSIX_Directory:
            mErrorString = "FC_POSIX_Directory";
            break;
        case FC_POSIX_FIFO_PIPE:
            mErrorString = "FC_POSIX_FIFO_PIPE";
            break;
        case FC_POSIX_Symlink:
            mErrorString = "FC_POSIX_Symlink";
            break;
        case FC_POSIX_RegularFile:
            mErrorString = "FC_POSIX_RegularFile";
            break;
        case FC_POSIX_Socket:
            mErrorString = "FC_POSIX_Socket";
            break;
        case FC_POSIX_Unknown:
            mErrorString = "FC_POSIX_Unknown";
            break;

        case FC_POSIX_EACCES:
            mErrorString = "FC_POSIX_EACCES";
            break;
        case FC_POSIX_EDQUOT:
            mErrorString = "FC_POSIX_EDQUOT";
            break;
        case FC_POSIX_EFAULT:
            mErrorString = "FC_POSIX_EFAULT";
            break;
        case FC_POSIX_EINVAL:
            mErrorString = "FC_POSIX_EINVAL";
            break;
        case FC_POSIX_ELOOP:
            mErrorString = "FC_POSIX_ELOOP";
            break;
        case FC_POSIX_EMLINK:
            mErrorString = "FC_POSIX_EMLINK";
            break;
        case FC_POSIX_ENAMETOOLONG:
            mErrorString = "FC_POSIX_ENAMETOOLONG";
            break;
        case FC_POSIX_ENOENT:
            mErrorString = "FC_POSIX_ENOENT";
            break;
        case FC_POSIX_ENOMEM:
            mErrorString = "FC_POSIX_ENOMEM";
            break;
        case FC_POSIX_ENOSPC:
            mErrorString = "FC_POSIX_ENOSPC";
            break;
        case FC_POSIX_ENOTDIR:
            mErrorString = "FC_POSIX_ENOTDIR";
            break;
        case FC_POSIX_EPERM:
            mErrorString = "FC_POSIX_EPERM";
            break;
        case FC_POSIX_EROFS:
            mErrorString = "FC_POSIX_EROFS";
            break;
        case FC_POSIX_EBADF:
            mErrorString = "FC_POSIX_EBADF";
            break;

        case FC_XLIB_NOTTHREADSAFE:
            mErrorString = "FC_XLIB_NOTTHREADSAFE";
            break;
        case FC_XLIB_XOPENDISPLAY:
            mErrorString = "FC_XLIB_XOPENDISPLAY";
            break;
#endif
    }
    fwrite(mErrorString, 1, strlen(mErrorString), eFileError);
}

void FcErrorClose() {
    if (eFileError)
        fclose(eFileError);
    eFileError = NULL;
}
