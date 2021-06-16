#ifndef __TRUETYPEGL_H__
#define __TRUETYPEGL_H__

#include "TrueTypeLibrary.h"

typedef struct _TrueTypeGL_t {
	float m_scaleMatrix[4][4];

}TrueTypeGL_t;

void TrueTypeGL_init(TrueTypeReader_t* m_library, TrueTypeGL_t* m_render);
void TrueTypeGL_draw(TrueTypeReader_t* m_library, TrueTypeGL_t* m_render, uint32_t id);
void TrueTypeGL_free(TrueTypeGL_t* m_render);

#endif