
#include "FcGL/FcGL_Control/FcGL_ProgramGenerator.h"
#include "FcGL/FcGL_Parser.h"
#include "FcGL/FcGL_Matrix/FcGL_Vec4.h"
#include "FcGL/FcGL_Matrix/FcGL_Vec8.h"

#include <malloc.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

#define CASHE_SIZE 1024000
#define RESERVE_SIZE 16
const char vertexShader[] = "#version 110"
                            "attribute vec2 vertex;"
                            "uniform mat4 MVP;"
                            "uniform vec4 mouse;"
                            "uniform vec2 window;"
                            "uniform vec2 time;"
                            "varying vec4 f_mouse;"
                            "varying vec2 f_window;"
                            "varying vec2 f_time;"
                            "void main(){"
                            "   f_mouse = mouse;"
                            "   f_window = window;"
                            "   f_time = time;"
                            "   gl_Position = MVP*vec4(vertex,0,1);"
                            "}";
const char fragmentShader[] = "#version 110\n"
                              "varying vec4 f_mouse;"
                              "varying vec2 f_window;"
                              "varying vec2 f_time;"
                              "uniform sampler2D textureID;"
                              "uniform sampler2D controlID;"
                              "void main(){"
                              "   float scale = 1.0 / min(f_window.x, f_window.y);"
                              "   vec2 xy = gl_FragCoord.xy * vec2(scale);"
                              "   vec2 mouse = f_mouse.xy * scale;"
                              "   gl_FragColor = color;"
                              "}";

static inline void floatTruncToChar_fast(GLubyte *text, GLfloat value) {
    int32_t i;
    GLfloat j;
    FcGL_Vec8_t vec_0, vec_1;
    FcGL_Vec4_t vec4;
    FcGL_Vec8_t data;
    for (i = 0, j = 1.f; i <= 7; j *= 10.f, i++)
        data.fdata[i] = j;
    value = value - (int32_t) value;
    vec_0 = FcGL_Vec8f_p00000000_init(value);
    vec_1 = FcGL_Vec8f_mul(vec_0, data);
    vec_0 = FcGL_Vec8f_mul(vec_0, data);
    vec_0 = FcGL_Vec8f_mulc(vec_0, 10.f);
    vec_1 = FcGL_Vec8_floatToInt(vec_1);
    vec_1 = FcGL_Vec8i_mulc(vec_1, 10);
    vec_0 = FcGL_Vec8f_addc(vec_0, 48.f);
    vec_0 = FcGL_Vec8_floatToInt(vec_0);
    vec_0 = FcGL_Vec8i_sub(vec_0, vec_1);
    text[0] = 48;
    text[1] = 46;
    for (i = 0; i <= 7; i++)
        text[i + 2] = vec_0.idata[i];
    text[i + 2] = 48;
}

static inline GLuint
screenPartition_lessThan(GLubyte *code, GLuint offset, const FcGL_Vec2_t scale, const GLubyte name) {
    code += offset;
    FCGL_type_bvec2(code);
    code[5] = ' ';
    code[6] = name;
    code[7] = *FCGL_operator_assignment;
    FCGL_function_lessThan(code + 8);
    code[16] = FCGL_operator_functionCall_start;
    FCGL_variables_gl_FragCoord(code + 17);
    code[29] = FCGL_operator_constructorStructureFieldSelector;
    FCGL_vectorComponents_vec2(code + 30);
    code[32] = *FCGL_operator_sequence;
    code[33] = fragmentShader[47];
    code[34] = fragmentShader[48];
    code[35] = fragmentShader[49];
    code[36] = fragmentShader[50];
    code[37] = fragmentShader[51];
    code[38] = fragmentShader[52];
    code[39] = fragmentShader[53];
    code[40] = fragmentShader[54];
    code[41] = *FCGL_operator_multiplication;
    FCGL_type_vec2(code + 42);
    code[46] = FCGL_operator_functionCall_start;
    floatTruncToChar_fast(code + 47, scale.f0);
    code[58] = *FCGL_operator_sequence;
    floatTruncToChar_fast(code + 59, scale.f1);
    code[70] = FCGL_operator_functionCall_end;
    code[71] = FCGL_operator_functionCall_end;
    code[72] = ';';
    return offset + 73;
}

static inline GLuint screenPartition_if_vec1(GLubyte *code, GLuint offset, GLubyte name, GLubyte vectorComponent) {
    code += offset;
    FCGL_shaderSelection_if(code);
    code[2] = FCGL_operator_functionCall_start;
    code[3] = name;
    code[4] = FCGL_operator_constructorStructureFieldSelector;
    code[5] = vectorComponent;// FCGL_vectorComponents_vec_x(code + offset + 5);
    code[6] = FCGL_operator_functionCall_end;
    code[7] = '{';
    return offset + 8;
}

static inline GLuint screenPartition_if_else_vec1(GLubyte *code, GLuint offset, GLubyte name, GLubyte vectorComponent,
                                                  const GLubyte *callTrue, GLuint callTrueSize,
                                                  const GLubyte *callFalse,
                                                  GLuint callFalseSize) {
    GLuint i;
    code += offset;
    FCGL_shaderSelection_if(code);
    code[2] = FCGL_operator_functionCall_start;
    code[3] = name;
    code[4] = FCGL_operator_constructorStructureFieldSelector;
    code[5] = vectorComponent; // FCGL_vectorComponents_vec_y(code + offset + 5);
    code[6] = FCGL_operator_functionCall_end;
    code[7] = '{';
    for (i = 0; i < callTrueSize; i++, code++)
        code[8] = callTrue[i];
    offset += i;
    code[8] = '}';
    FCGL_shaderSelection_else(code + 9);
    code[13] = '{';
    for (i = 0; i < callFalseSize; i++, code++)
        code[14] = callFalse[i];
    code[14] = '}';
    return offset + i + 15;
}

static inline GLuint screenPartition_else(GLubyte *code, GLuint offset, const GLubyte *callElse,
                                          const GLuint callElseSize) {
    GLuint i;
    code += offset;
    code[0] = '}';
    FCGL_shaderSelection_else(code + 1);
    code[5] = '{';
    for (i = 0; i < callElseSize; i++, code++)
        code[6] = callElse[i];
    code[6] = '}';
    return offset + i + 7;
}

#ifdef _MSC_VER
#include <intrin.h>
#pragma intrinsic(_BitScanForward)
#define lsb32 _BitScanForward
#else

static inline GLuint lsb32(GLuint *index, GLuint mask) {
    *index = 0;
    if (mask == 0) return 0;
    while (((mask >> *index) & 1) == 0)
        (*index)++;
    return 1;
}

#endif

//bsr
static inline GLuint msb32(GLuint x) {
    GLuint c = 0;
    if (x < 1) return 0;
    while (x >>= 1) c++;
    return c;
}

static inline GLuint setBits32(GLuint x, GLuint start, GLuint end) {
    while (start < end) {
        x |= 1 << start;
        start++;
    }
    return x;
}

static inline GLuint screenPartition_countBit(GLuint x) {
    x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
    x = (x & 0x00FF00FF) + ((x >> 8) & 0x00FF00FF);
    x = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF);
    return x;
}

static inline GLuint screenPartition_x(GLuint x) {
    GLuint i = 0, r = 0;
    GLuint x0, x1, x2, x3;
    for (i = 0; i < 16 && x; i += 4) {
        x0 = x & 1 ? 1 : 0;
        x1 = x & 4 ? 2 : 0;
        x2 = x & 16 ? 4 : 0;
        x3 = x & 64 ? 8 : 0;
        r += (x0 + x1 + x2 + x3) << i;
        x >>= 8;
    }
    return r;
}

static inline GLuint screenPartition_y(GLuint y) {
    GLuint i = 0, r = 0;
    GLuint y0, y1, y2, y3;
    for (i = 0; i < 16 && y; i += 4) {
        y0 = y & (1 << 1) ? 1 : 0;
        y1 = y & (1 << 3) ? 2 : 0;
        y2 = y & (1 << 5) ? 4 : 0;
        y3 = y & (1 << 7) ? 8 : 0;
        r += (y0 + y1 + y2 + y3) << i;
        y >>= 8;
    }
    return r;
}

static inline FcGL_Vec2_t screenPartition_xy(GLuint x, GLuint y) {
    GLuint i = 0, xy = x | y;
    FcGL_Vec2_t r = {0, 0};
    do {
        r.ui0 |= ((xy & 1) |
                  ((xy & (1 << 2)) / 2) |
                  ((xy & (1 << 4)) / 4) |
                  ((xy & (1 << 6)) / 8)
        ) << i;
        r.ui1 |= (((xy & 2) / 2) |
                  ((xy & (1 << 3)) / 4) |
                  ((xy & (1 << 5)) / 8) |
                  ((xy & (1 << 7)) / 16)
        ) << i;
        xy >>= 8;
        i += 4;
    } while (xy);
    return r;
}

void screenPartition(GLubyte *code, GLuint numberControls, GLuint logMax) {
    GLuint i, j, j_x, j_y, m_block, offset = 0;
    GLfloat step = 1.0f;
    for (i = 0; i < logMax; i++)
        step *= 0.5;
    const GLuint i_end = 1 << (2 * logMax);
    const GLuint m_center = screenPartition_x(i_end) >> 1;

    const GLuint block_end = i_end / 4;

    for (m_block = 0; m_block < 4; m_block++) {
        if (m_block & 1) {
            FCGL_shaderSelection_else(code + offset);
            code[offset + 4] = '{';
            offset += 5;
        } else if (m_block == 2) {
            code[offset + 0] = '}';
            FCGL_shaderSelection_else(code + offset + 1);
            code[offset + 5] = '{';
            offset = screenPartition_if_vec1(code, offset + 6, 'c', 'x');
        }

        for (i = 0; i < block_end; i++) {
            FcGL_Vec2_t m_xy = screenPartition_xy(i, i);

            if (!(m_xy.ui0 & 1) & !(m_xy.ui1 & 1)) {
                m_xy.ui0 += (m_block & 1) * m_center;
                m_xy.ui1 += (m_block / 2) * m_center;

                j_y = 2 * m_center - m_xy.ui1;
                j_x = 2 * m_center - m_xy.ui0;

                lsb32(&j_x, j_x);
                lsb32(&j_y, j_y);

                j_x = j_y = min(j_x, j_y);
                const FcGL_Vec2_t m_end_scale = {(m_xy.ui0 + 1) * step, (m_xy.ui1 + 1) * step};
                FcGL_Vec2_t m_current_scale = {step * (1 << (j_x - 1)), step * (1 << (j_y - 1))};
                FcGL_Vec2_t m_next_step = {step * (1 << (j_x - 2)), step * (1 << (j_y - 2))};
                m_current_scale.f0 += step * (m_xy.ui0 & ((UINT32_MAX >> j_x) << j_x));
                m_current_scale.f1 += step * (m_xy.ui1 & ((UINT32_MAX >> j_y) << j_y));

                for (j = 0; (j < j_x) | (j < j_y); j++) {
                    if (j < j_y && j < j_x) {
                        offset = screenPartition_lessThan(code, offset, m_current_scale, 'c');
                        //code[offset++] = '\n';
                    }
                    if (j <= j_y) {
                        offset = screenPartition_if_vec1(code, offset, 'c', 'y');
                        //code[offset++] = '\n';
                        if (m_end_scale.f1 <= m_current_scale.f1)
                            m_current_scale.f1 -= m_next_step.f1,
                                    m_next_step.f1 *= 0.5f;
                        else if (m_end_scale.f1 >= m_current_scale.f1)
                            m_current_scale.f1 += m_next_step.f1,
                                    m_next_step.f1 *= 0.5f;
                    }
                    if (j < j_x) {
                        offset = screenPartition_if_vec1(code, offset, 'c', 'x');
                        //code[offset++] = '\n';
                        if (m_end_scale.f0 <= m_current_scale.f0)
                            m_current_scale.f0 -= m_next_step.f0,
                                    m_next_step.f0 *= 0.5f;
                        else if (m_end_scale.f0 >= m_current_scale.f0)
                            m_current_scale.f0 += m_next_step.f0,
                                    m_next_step.f0 *= 0.5f;
                    }
                }
            } else if (m_xy.ui0 & 1 & m_xy.ui1 & 1) {
                j_y = (m_center - m_xy.ui1) / 2;
                j_x = (m_center - m_xy.ui0) / 2;

                j_x = (m_center / 2 - j_x) * 2;
                j_y = (m_center / 2 - j_y) * 2;
                j = 4;
                do {
                    m_xy.ui0 = (i & ((1 << j) - 1)) == ((1 << (j - 1)) - 1);
                    j += 2;
                } while (i >= (1 << j));

                lsb32(&j_y, j_y);
                lsb32(&j_x, j_x);

                j = 2 * min(j_x, j_y) + m_xy.ui0;

                FCGL_shaderSelection_else(code + offset);
                code[offset + 4] = '{';
                offset += 5;
                j += offset;
                do {
                    code[offset++] = '}';
                } while (offset <= j);

                if (block_end - 1 != i) {
                    FCGL_shaderSelection_else(code + offset);
                    code[offset + 4] = '{';
                    offset += 5;
                }
                if (m_xy.ui0) {
                    offset = screenPartition_if_vec1(code, offset, 'c', 'x');
                }
            } else if (m_xy.ui0 & 1) {
                code[offset] = '}';
                FCGL_shaderSelection_else(code + offset + 1);
                code[offset + 5] = '{';
                code[offset + 6] = '}';
                code[offset + 7] = '}';
                offset += 8;
            } else if (m_xy.ui1 & 1) {
                FCGL_shaderSelection_else(code + offset);
                code[offset + 4] = '{';
                offset = screenPartition_if_vec1(code, offset + 5, 'c', 'x');
                code[offset++] = '}';
            }
        }
    }
    code[offset] = '}';
}


void FcGL_ProgramGenerator_test(FcGL_ProgramGenerator_t *program, const FcGL_ProgramGenerator_options_t *options,
                                const FcGLWindow_t *window) {
    program->code = (GLubyte *) calloc(1, CASHE_SIZE * 384);
    if (!program->code) return;
    GLuint i, j, h, w, end_x, end_y, start_x, start_y;
    GLint width, height;
    GLuint logMax;
    FcGLWindow_getWindowSize(window, &width, &height);
    logMax = max(log2f(1024) + 1, log2f(14) + 1);

    screenPartition(program->code, options->numberControls, logMax);
    printf("%s\n", program->code);

}


FcGL_ProgramGenerator_t FcGL_GeneratorGUI(const FcGL_ProgramGenerator_options_t *options, const FcGLWindow_t *window) {
    GLuint i;
    GLint width, height;
    FcGL_ProgramGenerator_t generator;
    FcGLWindow_getWindowSize(window, &width, &height);
    generator.image = FcImage(width, height, FCIMAGE_RGBA);
    //for (i = 0; i < options->numberControls; i++){
    //	switch (options->typeControl[i].type) {
    //	case FcGL_Button_control:
    //		FcGL_Button(&options->typeControl[i].code.m_button, generator.image, window);
    //	}

    //}

    return generator;

}


