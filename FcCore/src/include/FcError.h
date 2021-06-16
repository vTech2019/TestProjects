//
// Created by human on 24.02.2021.
//

#ifndef _FCERROR_H
#define _FCERROR_H

#include <errno.h>

enum FcError {
    FC_NO_ERROR,


    FC_IO_EPERM = EPERM, //	Operation not permitted 	1
    FC_IO_ENOENT = ENOENT, //	No such file or directory 	2
    FC_IO_ESRCH = ESRCH, //	No such process 	3
    FC_IO_EINTR = EINTR, //	Interrupted function 	4
    FC_IO_EIO = EIO, //	I / O error 	5
    FC_IO_ENXIO = ENXIO, //	No such device or address 	6
    FC_IO_E2BIG = E2BIG, //	Argument list too long 	7
    FC_IO_ENOEXEC = ENOEXEC, //	Exec format error 	8
    FC_IO_EBADF = EBADF, //	Bad file number 	9
    FC_IO_ECHILD = ECHILD, //	No spawned processes 	10
    FC_IO_EAGAIN = EAGAIN, //	No more processes or not enough memory or maximum nesting level reached 	11
    FC_IO_ENOMEM = ENOMEM, //	Not enough memory 	12
    FC_IO_EACCES = EACCES, //	Permission denied 	13
    FC_IO_EFAULT = EFAULT, //	Bad address 	14
    FC_IO_EBUSY = EBUSY, //	Device or resource busy 	16
    FC_IO_EEXIST = EEXIST, //	File exists 	17
    FC_IO_EXDEV = EXDEV, //	Cross - device link 	18
    FC_IO_ENODEV = ENODEV, //	No such device 	19
    FC_IO_ENOTDIR = ENOTDIR, //	Not a directory 	20
    FC_IO_EISDIR = EISDIR, //	Is a directory 	21
    FC_IO_EINVAL = EINVAL, //	Invalid argument 	22
    FC_IO_ENFILE = ENFILE, //	Too many files open in system 	23
    FC_IO_EMFILE = EMFILE, //	Too many open files 	24
    FC_IO_ENOTTY = ENOTTY, //	Inappropriate I / O control operation 	25
    FC_IO_EFBIG = EFBIG, //	File too large 	27
    FC_IO_ENOSPC = ENOSPC, //	No space left on device 	28
    FC_IO_ESPIPE = ESPIPE, //	Invalid seek 	29
    FC_IO_EROFS = EROFS, //	Read - only file system 	30
    FC_IO_EMLINK = EMLINK, //	Too many links 	31
    FC_IO_EPIPE = EPIPE, //	Broken pipe 	32
    FC_IO_EDOM = EDOM, //		Math argument 	33
    FC_IO_ERANGE = ERANGE, //	Result too large 	34
    FC_IO_EDEADLK = EDEADLK, //	Resource deadlock would occur 	35
#ifdef MSVC
    FC_IO_EDEADLOCK = EDEADLOCK, //Same as EDEADLK for compatibility with older Microsoft C versions 	35
#endif
    FC_IO_ENAMETOOLONG = ENAMETOOLONG, // Filename too long 	36
    FC_IO_ENOLCK = ENOLCK, //	No locks available 	37
    FC_IO_ENOSYS = ENOSYS, //	Function not supported 	38
    FC_IO_ENOTEMPTY = ENOTEMPTY, //Directory not empty 	39
    FC_IO_EILSEQ = EILSEQ, //	Illegal byte sequence

#ifdef WIN32
    FC_IO_STRUNCATE = STRUNCATE, //String was truncated
#endif

    FC_PNG_NOTPNG,
    FC_PNG_CRCERROR,
    FC_PNG_UNSUPPORTED,


    FC_THREAD_RUNNING,
    FC_THREAD_INCORRECT_VALUE,
    FC_THREAD_MAXIMUM_NUMBER_OF_THREADS_FOR_THIS_JOB_HAS_BEEN_REACHED,
    FC_THREAD_SYSTEM_CANNOT_ALLOW_THREAD_CREATION_IN_THIS_PROCESS_AT_THIS_TIME,
    FC_THREAD_THE_THREAD_SPECIFIED_COULD_NOT_BE_FOUND,
    FC_THREAD_THE_CALL_TIMES_OUT_BEFORE_THREAD_TERMINATED,

    FC_SEMAPHORE_ACCES_DENIED,
    FC_SEMAPHORE_EXIST,
    FC_SEMAPHORE_INCORRECT_VALUE,
    FC_SEMAPHORE_NAME_TO_LONG,
    FC_SEMAPHORE_NO_SUCH_PATH_OR_DIRECTORY,
    FC_SEMAPHORE_NO_SPACE_AVAILABLE,
    FC_SEMAPHORE_INTERRUPTED_FUNCTION_CALL,
    FC_SEMAPHORE_RESOURCE_BUSY,

    FC_MUTEX_INCORRECT_VALUE,
    FC_MUTEX_NO_MEMORY,
    FC_MUTEX_OBJECT_WAS_DESTROYED_NO_LONGER_EXISTS,
    FC_MUTEX_OBJECT_NO_LONGER_EXISTS_BECAUSE_THE_OWNER_IS_NOT_LONGER_RUNNING,
    FC_MUTEX_RESOURCE_DEADLOCK_AVOIDED,
    FC_MUTEX_RECURSIVE_ATTEMPT_REJECTED,
    FC_MUTEX_IS_NOT_CURRENTLY_HELD_BY_THE_CALLER,
    FC_MUTEX_CURRENTLY_OWNED_BY_ANOTHER_THREAD,
#ifdef WIN32
    FC_WINAPI_EXISTS,
    FC_WINAPI_PATH_NOT_FOUND,
    FC_WINAPI_UNKNOWN
#endif
#ifdef linux
    FC_GLX_LoadLibrary,
    FC_GLX_Version14IsRequired,
    FC_GLX_ARBCreateContextProfile,
    FC_GLX_FBConfigsNotFound,
    FC_GLX_ContextNotDebug,
    FC_GLX_ContextNotDirect,
    FC_GLX_MakeCurrent,
    FC_GLX_BadContext,
    FC_GLX_BadContextState,
    FC_GLX_BadCurrentDrawable,
    FC_GLX_BadCurrentWindow,
    FC_GLX_BadDrawable,
    FC_GLX_BadFBConfig,
    FC_GLX_BadPbuffer,
    FC_GLX_BadPixmap,
    FC_GLX_UnsupportedPrivateRequest,
    FC_GLX_BadWindow,
    FC_GLX_BadContextTag,
    FC_GLX_BadRenderRequest,
    FC_GLX_BadLargeRequest,

    FC_POSIX_BlockDevice,
    FC_POSIX_CharacterDevice,
    FC_POSIX_Directory,
    FC_POSIX_FIFO_PIPE,
    FC_POSIX_Symlink,
    FC_POSIX_RegularFile,
    FC_POSIX_Socket,
    FC_POSIX_Unknown,

    FC_POSIX_EACCES,
    FC_POSIX_EDQUOT,
    FC_POSIX_EFAULT,
    FC_POSIX_EINVAL,
    FC_POSIX_ELOOP,
    FC_POSIX_EMLINK,
    FC_POSIX_ENAMETOOLONG,
    FC_POSIX_ENOENT,
    FC_POSIX_ENOMEM,
    FC_POSIX_ENOSPC,
    FC_POSIX_ENOTDIR,
    FC_POSIX_EPERM,
    FC_POSIX_EROFS,
    FC_POSIX_EBADF,

    FC_XLIB_NOTTHREADSAFE,
    FC_XLIB_XOPENDISPLAY
#endif
};


typedef int FcError_t;

#define FcError(error) if (error) FcErrorOpen(error)

void FcErrorOpen(FcError_t error);

void FcErrorClose();

#endif //_FCERROR_H
