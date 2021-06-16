#include "TrueTypeGL.h"

const char vertexShader[] =
"attribute mediump vec2 Vertex;"
"uniform highp mat4 MVP;"
"uniform mediump vec2 cords[4];"
"varying mediump vec2 outTexCord;"
"void main() {"
"    outTexCord = Vertex * cords[3] + cords[2];"
"    gl_Position = MVP * vec4(Vertex * cords[1] + cords[0], 0.0, 1.0);"
"}";

const char fragmentShader[] =
"varying mediump vec2 outTexCord;"
"uniform lowp sampler2D tex0;"
"uniform mediump vec4 color;"
"uniform mediump vec2 params;"
"void main(void) {"
"    float tx = texture2D(tex0, outTexCord).r;"
"    float a = min((tx - params.x) * params.y, 1.0);"
"    gl_FragColor = vec4(color.rgb, a * color.a);"
"}";

/*
void TrueTypeGL_init(TrueTypeReader_t* m_library, TrueTypeGL_t* m_render) {



}

void TrueTypeGL_draw(TrueTypeReader_t* m_library, TrueTypeGL_t* m_render, uint32_t m_id) {



}

void TrueTypeGL_free(TrueTypeGL_t* m_render) {



}
 */