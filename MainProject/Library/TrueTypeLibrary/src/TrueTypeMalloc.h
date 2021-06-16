#ifndef __TRUETYPEMALLOC_H__
#define __TRUETYPEMALLOC_H__
#include "TrueTypeLibrary.h"
#include "TrueTypeSize.h"
#include <stdio.h>
#include <stdlib.h>

_Ret_maybenull_ TrueTypeReader_t* TrueTypeMalloc(_In_ TrueTypeSize_t* size);
void TrueTypeFree(_Pre_maybenull_ _Post_invalid_ TrueTypeReader_t* ptr);
#endif
