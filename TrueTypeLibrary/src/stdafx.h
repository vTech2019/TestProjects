
#ifndef  __STDAFX_T__
#define __STDAFX_T__
#ifdef _MSC_VER

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sal.h>
#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#endif
#endif

#ifndef _MSC_VER
#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#endif
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define _In_z_
#define _In_
#define _Inout_
#define _Out_
#define _Pre_maybenull_
#define _Post_invalid_
#define _Ret_maybenull_
#define _In_reads_bytes_(length)
#endif
#endif
