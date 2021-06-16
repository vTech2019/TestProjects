//
// Created by human on 03.03.2021.
//

#ifndef __FCCORE_H_
#define __FCCORE_H_

#include "FcGL/FcGLX.h"
#include "FcGL/FcWGL.h"


#ifdef __FCGLX_H_
typedef FcGLX_t FcGLFunctions_t;
#define FcCoreGL FcGLX
#define FcCoreGL_free FcGLX_free
#elif defined __FCWGL_H__
typedef FcWGL_t FcGLFunctions_t;
#define FcCoreGL FcWGL
#define FcCoreGL_free FcWGL_free
#endif

typedef struct FcCore_t {
    FcGLFunctions_t m_gl;
} FcCore_t;

static inline FcError_t FcCore_init(FcCore_t *core) {
    return FcCoreGL(&core->m_gl);
}

static inline FcError_t FcCore_free(FcCore_t *core) {
    FcCoreGL_free(&core->m_gl);
    FcErrorClose();
}

#endif //_FCCORE_H
