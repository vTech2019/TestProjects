#ifndef __TRUETYPEERRORS_H__
#define __TRUETYPEERRORS_H__
#include <stdint.h>

typedef int TrueTypeError_t;

enum e_TrueTypeError {
    e_TrueTypeCodeError_success,
    e_TrueTypeCodeError_fopen,
    e_TrueTypeCodeError_fseek,
    e_TrueTypeCodeError_ftell,
    e_TrueTypeCodeError_malloc,
    e_TrueTypeCodeError_read,
    e_TrueTypeCodeError_fclose,
    e_TrueTypeCodeError_notTrueType,
    e_TrueTypeCodeError_tableOutOfMemory,
    e_TrueTypeCodeError_MallocOutOfMemory,
    e_TrueTypeCodeError_tableChecksum,
    e_TrueTypeCodeError_parameterFunction
};

#endif
