#ifndef __TRUETYPEERRORS_H__
#define __TRUETYPEERRORS_H__

#ifndef ALIGNED64
#ifdef __GNUC__
#define ALIGNED64(str, x)str x __attribute__ ((aligned (64)))
#else
#define ALIGNED64(str, x) str __declspec(align(64)) x
#endif
#endif	   

#ifndef ALIGNED32
#ifdef __GNUC__
#define ALIGNED32(str, x)str x __attribute__ ((aligned (32)))
#else
#define ALIGNED32(str, x) str __declspec(align(32)) x
#endif
#endif

#ifndef ALIGNED16
#ifdef __GNUC__
#define ALIGNED16(str, x)str x __attribute__ ((aligned (16)))
#else
#define ALIGNED16(str, x) str __declspec(align(16)) x
#endif
#endif		  
#ifndef ALIGNED8
#ifdef __GNUC__
#define ALIGNED8(str, x) str x __attribute__ ((aligned (8)))
#else
#define ALIGNED8(str, x) str __declspec(align(8)) x
#endif
#endif	

#ifndef ALIGNED
#ifdef __GNUC__
#define ALIGNED(value, str, x) str x __attribute__ ((aligned(value)))
#else
#define ALIGNED(value, str, x) str __declspec(align(value)) x
#endif
#endif

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
