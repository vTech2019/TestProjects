#pragma once

#ifndef __FCGL_PARSER_H__
#define __FCGL_PARSER_H__


#define gl_MaxLights 8
#define gl_MaxClipPlanes 6
#define gl_MaxTextureUnits 2
#define gl_MaxTextureCoords 2
#define gl_VertexAttribs 16
#define gl_MaxVertexUniformComponents 512
#define gl_MaxVaryingFloats 32
#define gl_MaxVertexTextureImageUnits 0
#define gl_MaxCombinedTextureImageUnits 2
#define gl_MaxTextureImageUnits 2
#define gl_MaxFragmentUniformComponents = 64
#define gl_MaxDrawBuffers 1
const char gl_shaderSelection[] = {"ifelse"};

#define FCGL_shaderSelection_if(ptr) (ptr)[0] = 'i', (ptr)[1] = 'f';
#define FCGL_shaderSelection_else(ptr) (ptr)[0] = 'e', (ptr)[1] = 'l', (ptr)[2] = 's', (ptr)[3] = 'e';

const char gl_shaderVariables[] = {
        "gl_Positiongl_PointSizegl_ClipVertexgl_FragColorgl_FragDatagl_FragDepthgl_FragCoordgl_FrontFacing"
};
const char gl_shaderVariablesLength[] = {
        11, 12, 13, 12, 11, 12, 12, 14
};
#define FCGL_variables_gl_Position(ptr) (ptr)[0] = gl_shaderVariables[0], (ptr)[1] = gl_shaderVariables[1], (ptr)[2] = gl_shaderVariables[2], (ptr)[3] = gl_shaderVariables[3], (ptr)[4] = gl_shaderVariables[4], (ptr)[5] = gl_shaderVariables[5], (ptr)[6] = gl_shaderVariables[6], (ptr)[7] = gl_shaderVariables[7], (ptr)[8] = gl_shaderVariables[8], (ptr)[9] = gl_shaderVariables[9], (ptr)[10] = gl_shaderVariables[10];
#define FCGL_variables_gl_PointSize(ptr) (ptr)[0] = gl_shaderVariables[11], (ptr)[1] = gl_shaderVariables[12], (ptr)[2] = gl_shaderVariables[13], (ptr)[3] = gl_shaderVariables[14], (ptr)[4] = gl_shaderVariables[15], (ptr)[5] = gl_shaderVariables[16], (ptr)[6] = gl_shaderVariables[17], (ptr)[7] = gl_shaderVariables[18], (ptr)[8] = gl_shaderVariables[19], (ptr)[9] = gl_shaderVariables[20], (ptr)[10] = gl_shaderVariables[21], (ptr)[11] = gl_shaderVariables[22];
#define FCGL_variables_gl_ClipVertex(ptr) (ptr)[0] = gl_shaderVariables[23], (ptr)[1] = gl_shaderVariables[24], (ptr)[2] = gl_shaderVariables[25], (ptr)[3] = gl_shaderVariables[26], (ptr)[4] = gl_shaderVariables[27], (ptr)[5] = gl_shaderVariables[28], (ptr)[6] = gl_shaderVariables[29], (ptr)[7] = gl_shaderVariables[30], (ptr)[8] = gl_shaderVariables[31], (ptr)[9] = gl_shaderVariables[32], (ptr)[10] = gl_shaderVariables[33], (ptr)[11] = gl_shaderVariables[34], (ptr)[12] = gl_shaderVariables[35];
#define FCGL_variables_gl_FragColor(ptr) (ptr)[0] = gl_shaderVariables[36], (ptr)[1] = gl_shaderVariables[37], (ptr)[2] = gl_shaderVariables[38], (ptr)[3] = gl_shaderVariables[39], (ptr)[4] = gl_shaderVariables[40], (ptr)[5] = gl_shaderVariables[41], (ptr)[6] = gl_shaderVariables[42], (ptr)[7] = gl_shaderVariables[43], (ptr)[8] = gl_shaderVariables[44], (ptr)[9] = gl_shaderVariables[45], (ptr)[10] = gl_shaderVariables[46], (ptr)[11] = gl_shaderVariables[47];
#define FCGL_variables_gl_FragData(ptr) (ptr)[0] = gl_shaderVariables[48], (ptr)[1] = gl_shaderVariables[49], (ptr)[2] = gl_shaderVariables[50], (ptr)[3] = gl_shaderVariables[51], (ptr)[4] = gl_shaderVariables[52], (ptr)[5] = gl_shaderVariables[53], (ptr)[6] = gl_shaderVariables[54], (ptr)[7] = gl_shaderVariables[55], (ptr)[8] = gl_shaderVariables[56], (ptr)[9] = gl_shaderVariables[57], (ptr)[10] = gl_shaderVariables[58];
#define FCGL_variables_gl_FragDepth(ptr) (ptr)[0] = gl_shaderVariables[59], (ptr)[1] = gl_shaderVariables[60], (ptr)[2] = gl_shaderVariables[61], (ptr)[3] = gl_shaderVariables[62], (ptr)[4] = gl_shaderVariables[63], (ptr)[5] = gl_shaderVariables[64], (ptr)[6] = gl_shaderVariables[65], (ptr)[7] = gl_shaderVariables[66], (ptr)[8] = gl_shaderVariables[67], (ptr)[9] = gl_shaderVariables[68], (ptr)[10] = gl_shaderVariables[69], (ptr)[11] = gl_shaderVariables[70];
#define FCGL_variables_gl_FragCoord(ptr) (ptr)[0] = gl_shaderVariables[71], (ptr)[1] = gl_shaderVariables[72], (ptr)[2] = gl_shaderVariables[73], (ptr)[3] = gl_shaderVariables[74], (ptr)[4] = gl_shaderVariables[75], (ptr)[5] = gl_shaderVariables[76], (ptr)[6] = gl_shaderVariables[77], (ptr)[7] = gl_shaderVariables[78], (ptr)[8] = gl_shaderVariables[79], (ptr)[9] = gl_shaderVariables[80], (ptr)[10] = gl_shaderVariables[81], (ptr)[11] = gl_shaderVariables[82];
#define FCGL_variables_gl_FrontFacing(ptr) (ptr)[0] = gl_shaderVariables[83], (ptr)[1] = gl_shaderVariables[84], (ptr)[2] = gl_shaderVariables[85], (ptr)[3] = gl_shaderVariables[86], (ptr)[4] = gl_shaderVariables[87], (ptr)[5] = gl_shaderVariables[88], (ptr)[6] = gl_shaderVariables[89], (ptr)[7] = gl_shaderVariables[90], (ptr)[8] = gl_shaderVariables[91], (ptr)[9] = gl_shaderVariables[92], (ptr)[10] = gl_shaderVariables[93], (ptr)[11] = gl_shaderVariables[94], (ptr)[12] = gl_shaderVariables[95], (ptr)[13] = gl_shaderVariables[96];

const char gl_typeQualifiers[] = {
        "constattributeuniformvaryinginoutinout"
};
const char gl_typeQualifiersLength[] = {
        5, 9, 7, 7, 2, 3, 5
};

#define FCGL_typeQualifier_const(ptr) (ptr)[0] = gl_typeQualifiers[0], (ptr)[1] = gl_typeQualifiers[1], (ptr)[2] = gl_typeQualifiers[2], (ptr)[3] = gl_typeQualifiers[3], (ptr)[4] = gl_typeQualifiers[4];
#define FCGL_typeQualifier_attribute(ptr) (ptr)[0] = gl_typeQualifiers[5], (ptr)[1] = gl_typeQualifiers[6], (ptr)[2] = gl_typeQualifiers[7], (ptr)[3] = gl_typeQualifiers[8], (ptr)[4] = gl_typeQualifiers[9], (ptr)[5] = gl_typeQualifiers[10], (ptr)[6] = gl_typeQualifiers[11], (ptr)[7] = gl_typeQualifiers[12], (ptr)[8] = gl_typeQualifiers[13];
#define FCGL_typeQualifier_uniform(ptr) (ptr)[0] = gl_typeQualifiers[14], (ptr)[1] = gl_typeQualifiers[15], (ptr)[2] = gl_typeQualifiers[16], (ptr)[3] = gl_typeQualifiers[17], (ptr)[4] = gl_typeQualifiers[18], (ptr)[5] = gl_typeQualifiers[19], (ptr)[6] = gl_typeQualifiers[20];
#define FCGL_typeQualifier_varying(ptr) (ptr)[0] = gl_typeQualifiers[21], (ptr)[1] = gl_typeQualifiers[22], (ptr)[2] = gl_typeQualifiers[23], (ptr)[3] = gl_typeQualifiers[24], (ptr)[4] = gl_typeQualifiers[25], (ptr)[5] = gl_typeQualifiers[26], (ptr)[6] = gl_typeQualifiers[27];
#define FCGL_typeQualifier_in(ptr) (ptr)[0] = gl_typeQualifiers[28], (ptr)[1] = gl_typeQualifiers[29];
#define FCGL_typeQualifier_out(ptr) (ptr)[0] = gl_typeQualifiers[30], (ptr)[1] = gl_typeQualifiers[31], (ptr)[2] = gl_typeQualifiers[32];
#define FCGL_typeQualifier_inout(ptr) (ptr)[0] = gl_typeQualifiers[33], (ptr)[1] = gl_typeQualifiers[34], (ptr)[2] = gl_typeQualifiers[35], (ptr)[3] = gl_typeQualifiers[36], (ptr)[4] = gl_typeQualifiers[37];

const char gl_types[] = {
        "voidboolintfloatvec2vec3vec4bvec2bvec3bvec4"\
    "ivec2ivec3ivec4mat2mat3mat4Sampler1DSampler2DSampler3D"\
    "SamplerCubeSampler1DShadowSampler2DShadow"
};
const char gl_typesLength[] = {
        4, 4, 3, 5, 4, 4, 4, 5, 5, 5, 5, 5, 5, 4, 4, 4, 9, 9, 9, 11, 15, 15
};

#define FCGL_type_void(ptr) (ptr)[0] = gl_types[0], (ptr)[1] = gl_types[1], (ptr)[2] = gl_types[2], (ptr)[3] = gl_types[3];
#define FCGL_type_bool(ptr) (ptr)[0] = gl_types[4], (ptr)[1] = gl_types[5], (ptr)[2] = gl_types[6], (ptr)[3] = gl_types[7];
#define FCGL_type_int(ptr) (ptr)[0] = gl_types[8], (ptr)[1] = gl_types[9], (ptr)[2] = gl_types[10];
#define FCGL_type_float(ptr) (ptr)[0] = gl_types[11], (ptr)[1] = gl_types[12], (ptr)[2] = gl_types[13], (ptr)[3] = gl_types[14], (ptr)[4] = gl_types[15];
#define FCGL_type_vec2(ptr) (ptr)[0] = gl_types[16], (ptr)[1] = gl_types[17], (ptr)[2] = gl_types[18], (ptr)[3] = gl_types[19];
#define FCGL_type_vec3(ptr) (ptr)[0] = gl_types[20], (ptr)[1] = gl_types[21], (ptr)[2] = gl_types[22], (ptr)[3] = gl_types[23];
#define FCGL_type_vec4(ptr) (ptr)[0] = gl_types[24], (ptr)[1] = gl_types[25], (ptr)[2] = gl_types[26], (ptr)[3] = gl_types[27];
#define FCGL_type_bvec2(ptr) (ptr)[0] = gl_types[28], (ptr)[1] = gl_types[29], (ptr)[2] = gl_types[30], (ptr)[3] = gl_types[31], (ptr)[4] = gl_types[32];
#define FCGL_type_bvec3(ptr) (ptr)[0] = gl_types[33], (ptr)[1] = gl_types[34], (ptr)[2] = gl_types[35], (ptr)[3] = gl_types[36], (ptr)[4] = gl_types[37];
#define FCGL_type_bvec4(ptr) (ptr)[0] = gl_types[38], (ptr)[1] = gl_types[39], (ptr)[2] = gl_types[40], (ptr)[3] = gl_types[41], (ptr)[4] = gl_types[42];
#define FCGL_type_ivec2(ptr) (ptr)[0] = gl_types[43], (ptr)[1] = gl_types[44], (ptr)[2] = gl_types[45], (ptr)[3] = gl_types[46], (ptr)[4] = gl_types[47];
#define FCGL_type_ivec3(ptr) (ptr)[0] = gl_types[48], (ptr)[1] = gl_types[49], (ptr)[2] = gl_types[50], (ptr)[3] = gl_types[51], (ptr)[4] = gl_types[52];
#define FCGL_type_ivec4(ptr) (ptr)[0] = gl_types[53], (ptr)[1] = gl_types[54], (ptr)[2] = gl_types[55], (ptr)[3] = gl_types[56], (ptr)[4] = gl_types[57];
#define FCGL_type_mat2(ptr) (ptr)[0] = gl_types[58], (ptr)[1] = gl_types[59], (ptr)[2] = gl_types[60], (ptr)[3] = gl_types[61];
#define FCGL_type_mat3(ptr) (ptr)[0] = gl_types[62], (ptr)[1] = gl_types[63], (ptr)[2] = gl_types[64], (ptr)[3] = gl_types[65];
#define FCGL_type_mat4(ptr) (ptr)[0] = gl_types[66], (ptr)[1] = gl_types[67], (ptr)[2] = gl_types[68], (ptr)[3] = gl_types[69];
#define FCGL_type_Sampler1D(ptr) (ptr)[0] = gl_types[70], (ptr)[1] = gl_types[71], (ptr)[2] = gl_types[72], (ptr)[3] = gl_types[73], (ptr)[4] = gl_types[74], (ptr)[5] = gl_types[75], (ptr)[6] = gl_types[76], (ptr)[7] = gl_types[77], (ptr)[8] = gl_types[78];
#define FCGL_type_Sampler2D(ptr) (ptr)[0] = gl_types[79], (ptr)[1] = gl_types[80], (ptr)[2] = gl_types[81], (ptr)[3] = gl_types[82], (ptr)[4] = gl_types[83], (ptr)[5] = gl_types[84], (ptr)[6] = gl_types[85], (ptr)[7] = gl_types[86], (ptr)[8] = gl_types[87];
#define FCGL_type_Sampler3D(ptr) (ptr)[0] = gl_types[88], (ptr)[1] = gl_types[89], (ptr)[2] = gl_types[90], (ptr)[3] = gl_types[91], (ptr)[4] = gl_types[92], (ptr)[5] = gl_types[93], (ptr)[6] = gl_types[94], (ptr)[7] = gl_types[95], (ptr)[8] = gl_types[96];
#define FCGL_type_SamplerCube(ptr) (ptr)[0] = gl_types[97], (ptr)[1] = gl_types[98], (ptr)[2] = gl_types[99], (ptr)[3] = gl_types[100], (ptr)[4] = gl_types[101], (ptr)[5] = gl_types[102], (ptr)[6] = gl_types[103], (ptr)[7] = gl_types[104], (ptr)[8] = gl_types[105], (ptr)[9] = gl_types[106], (ptr)[10] = gl_types[107];
#define FCGL_type_Sampler1DShadow(ptr) (ptr)[0] = gl_types[108], (ptr)[1] = gl_types[109], (ptr)[2] = gl_types[110], (ptr)[3] = gl_types[111], (ptr)[4] = gl_types[112], (ptr)[5] = gl_types[113], (ptr)[6] = gl_types[114], (ptr)[7] = gl_types[115], (ptr)[8] = gl_types[116], (ptr)[9] = gl_types[117], (ptr)[10] = gl_types[118], (ptr)[11] = gl_types[119], (ptr)[12] = gl_types[120], (ptr)[13] = gl_types[121], (ptr)[14] = gl_types[122];
#define FCGL_type_Sampler2DShadow(ptr) (ptr)[0] = gl_types[123], (ptr)[1] = gl_types[124], (ptr)[2] = gl_types[125], (ptr)[3] = gl_types[126], (ptr)[4] = gl_types[127], (ptr)[5] = gl_types[128], (ptr)[6] = gl_types[129], (ptr)[7] = gl_types[130], (ptr)[8] = gl_types[131], (ptr)[9] = gl_types[132], (ptr)[10] = gl_types[133], (ptr)[11] = gl_types[134], (ptr)[12] = gl_types[135], (ptr)[13] = gl_types[136], (ptr)[14] = gl_types[137];

const char gl_identifiers_nondigit[] = {
        "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
};
const char gl_identifiers_digit[] = {
        "0123456789"
};
#define FCGL_vectorComponents_vec_x(ptr) (ptr)[0] = gl_identifiers_nondigit[24];
#define FCGL_vectorComponents_vec_y(ptr) (ptr)[0] = gl_identifiers_nondigit[25];
#define FCGL_vectorComponents_vec2(ptr) (ptr)[0] = gl_identifiers_nondigit[24], (ptr)[1] = gl_identifiers_nondigit[25];
#define FCGL_vectorComponents_vec3(ptr) (ptr)[0] = gl_identifiers_nondigit[24], (ptr)[1] = gl_identifiers_nondigit[25], (ptr)[2] = gl_identifiers_nondigit[26];
#define FCGL_vectorComponents_vec4(ptr) (ptr)[0] = gl_identifiers_nondigit[24], (ptr)[1] = gl_identifiers_nondigit[25], (ptr)[2] = gl_identifiers_nondigit[26], (ptr)[3] = gl_identifiers_nondigit[23];
const char gl_preprocessor[] = {
        "#define#undef#if#ifdef"
        "#ifndef#else#elif#endif#error"
        "#pragma#extension#version#line"
};
const char gl_preprocessorLength[] = {
        7, 6, 3, 6, 7, 5, 5, 6, 6, 7, 10, 8, 5
};
#define FCGL_preprocessor_define(ptr) (ptr)[0] = gl_preprocessor[0], (ptr)[1] = gl_preprocessor[1], (ptr)[2] = gl_preprocessor[2], (ptr)[3] = gl_preprocessor[3], (ptr)[4] = gl_preprocessor[4], (ptr)[5] = gl_preprocessor[5], (ptr)[6] = gl_preprocessor[6];
#define FCGL_preprocessor_undef(ptr) (ptr)[0] = gl_preprocessor[7], (ptr)[1] = gl_preprocessor[8], (ptr)[2] = gl_preprocessor[9], (ptr)[3] = gl_preprocessor[10], (ptr)[4] = gl_preprocessor[11], (ptr)[5] = gl_preprocessor[12];
#define FCGL_preprocessor_if(ptr) (ptr)[0] = gl_preprocessor[13], (ptr)[1] = gl_preprocessor[14], (ptr)[2] = gl_preprocessor[15];
#define FCGL_preprocessor_ifdef(ptr) (ptr)[0] = gl_preprocessor[16], (ptr)[1] = gl_preprocessor[17], (ptr)[2] = gl_preprocessor[18], (ptr)[3] = gl_preprocessor[19], (ptr)[4] = gl_preprocessor[20], (ptr)[5] = gl_preprocessor[21];
#define FCGL_preprocessor_ifndef(ptr) (ptr)[0] = gl_preprocessor[22], (ptr)[1] = gl_preprocessor[23], (ptr)[2] = gl_preprocessor[24], (ptr)[3] = gl_preprocessor[25], (ptr)[4] = gl_preprocessor[26], (ptr)[5] = gl_preprocessor[27], (ptr)[6] = gl_preprocessor[28];
#define FCGL_preprocessor_else(ptr) (ptr)[0] = gl_preprocessor[29], (ptr)[1] = gl_preprocessor[30], (ptr)[2] = gl_preprocessor[31], (ptr)[3] = gl_preprocessor[32], (ptr)[4] = gl_preprocessor[33];
#define FCGL_preprocessor_elif(ptr) (ptr)[0] = gl_preprocessor[34], (ptr)[1] = gl_preprocessor[35], (ptr)[2] = gl_preprocessor[36], (ptr)[3] = gl_preprocessor[37], (ptr)[4] = gl_preprocessor[38];
#define FCGL_preprocessor_endif(ptr) (ptr)[0] = gl_preprocessor[39], (ptr)[1] = gl_preprocessor[40], (ptr)[2] = gl_preprocessor[41], (ptr)[3] = gl_preprocessor[42], (ptr)[4] = gl_preprocessor[43], (ptr)[5] = gl_preprocessor[44];
#define FCGL_preprocessor_error(ptr) (ptr)[0] = gl_preprocessor[45], (ptr)[1] = gl_preprocessor[46], (ptr)[2] = gl_preprocessor[47], (ptr)[3] = gl_preprocessor[48], (ptr)[4] = gl_preprocessor[49], (ptr)[5] = gl_preprocessor[50];
#define FCGL_preprocessor_pragma(ptr) (ptr)[0] = gl_preprocessor[51], (ptr)[1] = gl_preprocessor[52], (ptr)[2] = gl_preprocessor[53], (ptr)[3] = gl_preprocessor[54], (ptr)[4] = gl_preprocessor[55], (ptr)[5] = gl_preprocessor[56], (ptr)[6] = gl_preprocessor[57];
#define FCGL_preprocessor_extension(ptr) (ptr)[0] = gl_preprocessor[58], (ptr)[1] = gl_preprocessor[59], (ptr)[2] = gl_preprocessor[60], (ptr)[3] = gl_preprocessor[61], (ptr)[4] = gl_preprocessor[62], (ptr)[5] = gl_preprocessor[63], (ptr)[6] = gl_preprocessor[64], (ptr)[7] = gl_preprocessor[65], (ptr)[8] = gl_preprocessor[66], (ptr)[9] = gl_preprocessor[67];
#define FCGL_preprocessor_version(ptr) (ptr)[0] = gl_preprocessor[68], (ptr)[1] = gl_preprocessor[69], (ptr)[2] = gl_preprocessor[70], (ptr)[3] = gl_preprocessor[71], (ptr)[4] = gl_preprocessor[72], (ptr)[5] = gl_preprocessor[73], (ptr)[6] = gl_preprocessor[74], (ptr)[7] = gl_preprocessor[75];
#define FCGL_preprocessor_line(ptr) (ptr)[0] = gl_preprocessor[76], (ptr)[1] = gl_preprocessor[77], (ptr)[2] = gl_preprocessor[78], (ptr)[3] = gl_preprocessor[79], (ptr)[4] = gl_preprocessor[80];

const char gl_operators[] = {
        "()[].++--+-~!*/%+-<<>><><=>===!=&^|&&||?:=+=-=*=/=%=<<=>>=&=^=|=,"
};
const char gl_operatorsLength[] = {
        2, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 3, 3, 2,
        2, 2, 1
};
#define FCGL_operator_functionCall_start                        '(';
#define FCGL_operator_functionCall_end                          ')';
#define FCGL_operator_arraySubscripting_start                   '[';
#define FCGL_operator_arraySubscripting_end                     ']';
#define FCGL_operator_constructorStructureFieldSelector         '.';
#define FCGL_operator_postFixIncrement                          (gl_operators + 5);
#define FCGL_operator_postFixIncrement_length                   2;
#define FCGL_operator_postFixDecrement                          (gl_operators + 7);
#define FCGL_operator_postFixDecrement_length                   2;
#define FCGL_operator_prefixIncrement                           (gl_operators + 5);
#define FCGL_operator_prefixIncrement_length                    2;
#define FCGL_operator_prefixDecrement                           (gl_operators + 7);
#define FCGL_operator_prefixDecrement_length                    2;
#define FCGL_operator_unaryPlus                                 (gl_operators + 9);
#define FCGL_operator_unaryPlus_length                          1;
#define FCGL_operator_unaryMinus                                (gl_operators + 10);
#define FCGL_operator_unaryMinus_length                         1;
#define FCGL_operator_bitwiseNot                                (gl_operators + 11);
#define FCGL_operator_bitwiseNot_length                         1;
#define FCGL_operator_logicalNot                                (gl_operators + 12);
#define FCGL_operator_logicalNot_length                         1;
#define FCGL_operator_multiplication                            (gl_operators + 13);
#define FCGL_operator_multiplication_length                     1;
#define FCGL_operator_division                                  (gl_operators + 14);
#define FCGL_operator_division_length                           1;
#define FCGL_operator_modulo                                    (gl_operators + 15);
#define FCGL_operator_modulo_length                             1;
#define FCGL_operator_addition                                  (gl_operators + 16);
#define FCGL_operator_addition_length                           1;
#define FCGL_operator_subtraction                               (gl_operators + 17);
#define FCGL_operator_subtraction_length                        1;
#define FCGL_operator_bitwiseLeft                               (gl_operators + 18);
#define FCGL_operator_bitwiseLeft_length                        2;
#define FCGL_operator_bitwiseRight                              (gl_operators + 20);
#define FCGL_operator_bitwiseRight_length                       2;
#define FCGL_operator_less                                      (gl_operators + 22);
#define FCGL_operator_more                                      (gl_operators + 23);
#define FCGL_operator_assignment                                (gl_operators + 41);
#define FCGL_operator_assignment_length                         1;
#define FCGL_operator_sequence                                  (gl_operators + 64);

const char gl_functions[] = {
        "radiansdegreessincostanasinacosatanpowexplogexp2log2sqrtinversesqrt"\
    "abssignfloorceilfractmodminmaxclampmixstepsmoothsteplengthdistancedot"\
    "crossnormalizeftransformfaceforwardreflectrefractmatrixCompMultlessThan"\
    "lessThanEqualgraeterThangreaterThanEqualequalnotEqualanyallnottexture1D"\
    "texture1DProjtexture1DLodtexture1dProjLodtexture2Dtexture2DProjtexture2DLod"\
    "texture2DProjLodtexture3Dtexture3DProjtexture3DLodtexture3DProjLodtextureCube"\
    "textureCubeLodshadow1Dshadow2Dshadow1DProjshadow2DProjshadow1DLodshadow2DLod"\
    "shadow1DProjLodshadow2DProjLoddFdxdFdyfwidthnoise1noise2noise3noise4"
};
const char gl_functionsLength[] = {
        7, 7, 3, 3, 3, 4, 4, 4, 3, 3, 3, 4, 4, 4, 11, \
    3, 4, 5, 4, 5, 3, 3, 3, 5, 3, 4, 10, 6, 8, 3, \
    5, 9, 10, 11, 7, 7, 14, 8, \
    13, 11, 16, 5, 8, 3, 3, 3, 9, \
    13, 12, 16, 9, 13, 12, \
    16, 9, 13, 12, 16, 11, \
    14, 8, 8, 12, 12, 11, 11, \
    15, 15, 4, 4, 6, 6, 6, 6, 6
};

#define FCGL_function_radians(ptr) (ptr)[0] = gl_functions[0], (ptr)[1] = gl_functions[1], (ptr)[2] = gl_functions[2], (ptr)[3] = gl_functions[3], (ptr)[4] = gl_functions[4], (ptr)[5] = gl_functions[5], (ptr)[6] = gl_functions[6];
#define FCGL_function_degrees(ptr) (ptr)[0] = gl_functions[7], (ptr)[1] = gl_functions[8], (ptr)[2] = gl_functions[9], (ptr)[3] = gl_functions[10], (ptr)[4] = gl_functions[11], (ptr)[5] = gl_functions[12], (ptr)[6] = gl_functions[13];
#define FCGL_function_sin(ptr) (ptr)[0] = gl_functions[14], (ptr)[1] = gl_functions[15], (ptr)[2] = gl_functions[16];
#define FCGL_function_cos(ptr) (ptr)[0] = gl_functions[17], (ptr)[1] = gl_functions[18], (ptr)[2] = gl_functions[19];
#define FCGL_function_tan(ptr) (ptr)[0] = gl_functions[20], (ptr)[1] = gl_functions[21], (ptr)[2] = gl_functions[22];
#define FCGL_function_asin(ptr) (ptr)[0] = gl_functions[23], (ptr)[1] = gl_functions[24], (ptr)[2] = gl_functions[25], (ptr)[3] = gl_functions[26];
#define FCGL_function_acos(ptr) (ptr)[0] = gl_functions[27], (ptr)[1] = gl_functions[28], (ptr)[2] = gl_functions[29], (ptr)[3] = gl_functions[30];
#define FCGL_function_atan(ptr) (ptr)[0] = gl_functions[31], (ptr)[1] = gl_functions[32], (ptr)[2] = gl_functions[33], (ptr)[3] = gl_functions[34];
#define FCGL_function_pow(ptr) (ptr)[0] = gl_functions[35], (ptr)[1] = gl_functions[36], (ptr)[2] = gl_functions[37];
#define FCGL_function_exp(ptr) (ptr)[0] = gl_functions[38], (ptr)[1] = gl_functions[39], (ptr)[2] = gl_functions[40];
#define FCGL_function_log(ptr) (ptr)[0] = gl_functions[41], (ptr)[1] = gl_functions[42], (ptr)[2] = gl_functions[43];
#define FCGL_function_exp2(ptr) (ptr)[0] = gl_functions[44], (ptr)[1] = gl_functions[45], (ptr)[2] = gl_functions[46], (ptr)[3] = gl_functions[47];
#define FCGL_function_log2(ptr) (ptr)[0] = gl_functions[48], (ptr)[1] = gl_functions[49], (ptr)[2] = gl_functions[50], (ptr)[3] = gl_functions[51];
#define FCGL_function_sqrt(ptr) (ptr)[0] = gl_functions[52], (ptr)[1] = gl_functions[53], (ptr)[2] = gl_functions[54], (ptr)[3] = gl_functions[55];
#define FCGL_function_inversesqrt(ptr) (ptr)[0] = gl_functions[56], (ptr)[1] = gl_functions[57], (ptr)[2] = gl_functions[58], (ptr)[3] = gl_functions[59], (ptr)[4] = gl_functions[60], (ptr)[5] = gl_functions[61], (ptr)[6] = gl_functions[62], (ptr)[7] = gl_functions[63], (ptr)[8] = gl_functions[64], (ptr)[9] = gl_functions[65], (ptr)[10] = gl_functions[66];
#define FCGL_function_abs(ptr) (ptr)[0] = gl_functions[67], (ptr)[1] = gl_functions[68], (ptr)[2] = gl_functions[69];
#define FCGL_function_sign(ptr) (ptr)[0] = gl_functions[70], (ptr)[1] = gl_functions[71], (ptr)[2] = gl_functions[72], (ptr)[3] = gl_functions[73];
#define FCGL_function_floor(ptr) (ptr)[0] = gl_functions[74], (ptr)[1] = gl_functions[75], (ptr)[2] = gl_functions[76], (ptr)[3] = gl_functions[77], (ptr)[4] = gl_functions[78];
#define FCGL_function_ceil(ptr) (ptr)[0] = gl_functions[79], (ptr)[1] = gl_functions[80], (ptr)[2] = gl_functions[81], (ptr)[3] = gl_functions[82];
#define FCGL_function_fract(ptr) (ptr)[0] = gl_functions[83], (ptr)[1] = gl_functions[84], (ptr)[2] = gl_functions[85], (ptr)[3] = gl_functions[86], (ptr)[4] = gl_functions[87];
#define FCGL_function_mod(ptr) (ptr)[0] = gl_functions[88], (ptr)[1] = gl_functions[89], (ptr)[2] = gl_functions[90];
#define FCGL_function_min(ptr) (ptr)[0] = gl_functions[91], (ptr)[1] = gl_functions[92], (ptr)[2] = gl_functions[93];
#define FCGL_function_max(ptr) (ptr)[0] = gl_functions[94], (ptr)[1] = gl_functions[95], (ptr)[2] = gl_functions[96];
#define FCGL_function_clamp(ptr) (ptr)[0] = gl_functions[97], (ptr)[1] = gl_functions[98], (ptr)[2] = gl_functions[99], (ptr)[3] = gl_functions[100], (ptr)[4] = gl_functions[101];
#define FCGL_function_mix(ptr) (ptr)[0] = gl_functions[102], (ptr)[1] = gl_functions[103], (ptr)[2] = gl_functions[104];
#define FCGL_function_step(ptr) (ptr)[0] = gl_functions[105], (ptr)[1] = gl_functions[106], (ptr)[2] = gl_functions[107], (ptr)[3] = gl_functions[108];
#define FCGL_function_smoothstep(ptr) (ptr)[0] = gl_functions[109], (ptr)[1] = gl_functions[110], (ptr)[2] = gl_functions[111], (ptr)[3] = gl_functions[112], (ptr)[4] = gl_functions[113], (ptr)[5] = gl_functions[114], (ptr)[6] = gl_functions[115], (ptr)[7] = gl_functions[116], (ptr)[8] = gl_functions[117], (ptr)[9] = gl_functions[118];
#define FCGL_function_length(ptr) (ptr)[0] = gl_functions[119], (ptr)[1] = gl_functions[120], (ptr)[2] = gl_functions[121], (ptr)[3] = gl_functions[122], (ptr)[4] = gl_functions[123], (ptr)[5] = gl_functions[124],
#define FCGL_function_distance(ptr) (ptr)[0] = gl_functions[125], (ptr)[1] = gl_functions[126], (ptr)[2] = gl_functions[127], (ptr)[3] = gl_functions[128], (ptr)[4] = gl_functions[129], (ptr)[5] = gl_functions[130], (ptr)[6] = gl_functions[131], (ptr)[7] = gl_functions[132];
#define FCGL_function_dot(ptr) (ptr)[0] = gl_functions[133], (ptr)[1] = gl_functions[134], (ptr)[2] = gl_functions[135];
#define FCGL_function_cross(ptr) (ptr)[0] = gl_functions[136], (ptr)[1] = gl_functions[137], (ptr)[2] = gl_functions[138], (ptr)[3] = gl_functions[139], (ptr)[4] = gl_functions[140];
#define FCGL_function_normalize(ptr) (ptr)[0] = gl_functions[141], (ptr)[1] = gl_functions[142], (ptr)[2] = gl_functions[143], (ptr)[3] = gl_functions[144], (ptr)[4] = gl_functions[145], (ptr)[5] = gl_functions[146], (ptr)[6] = gl_functions[147], (ptr)[7] = gl_functions[148], (ptr)[8] = gl_functions[149];
#define FCGL_function_ftransform(ptr) (ptr)[0] = gl_functions[150], (ptr)[1] = gl_functions[151], (ptr)[2] = gl_functions[152], (ptr)[3] = gl_functions[153], (ptr)[4] = gl_functions[154], (ptr)[5] = gl_functions[155], (ptr)[6] = gl_functions[156], (ptr)[7] = gl_functions[157], (ptr)[8] = gl_functions[158], (ptr)[9] = gl_functions[159];
#define FCGL_function_faceforward(ptr) (ptr)[0] = gl_functions[160], (ptr)[1] = gl_functions[161], (ptr)[2] = gl_functions[162], (ptr)[3] = gl_functions[163], (ptr)[4] = gl_functions[164], (ptr)[5] = gl_functions[165], (ptr)[6] = gl_functions[166], (ptr)[7] = gl_functions[167], (ptr)[8] = gl_functions[168], (ptr)[9] = gl_functions[169], (ptr)[10] = gl_functions[170];
#define FCGL_function_reflect(ptr) (ptr)[0] = gl_functions[171], (ptr)[1] = gl_functions[172], (ptr)[2] = gl_functions[173], (ptr)[3] = gl_functions[174], (ptr)[4] = gl_functions[175], (ptr)[5] = gl_functions[176], (ptr)[6] = gl_functions[177];
#define FCGL_function_refract(ptr) (ptr)[0] = gl_functions[178], (ptr)[1] = gl_functions[179], (ptr)[2] = gl_functions[180], (ptr)[3] = gl_functions[181], (ptr)[4] = gl_functions[182], (ptr)[5] = gl_functions[183], (ptr)[6] = gl_functions[184];
#define FCGL_function_matrixCompMult(ptr) (ptr)[0] = gl_functions[185], (ptr)[1] = gl_functions[186], (ptr)[2] = gl_functions[187], (ptr)[3] = gl_functions[188], (ptr)[4] = gl_functions[189], (ptr)[5] = gl_functions[190], (ptr)[6] = gl_functions[191], (ptr)[7] = gl_functions[192], (ptr)[8] = gl_functions[193], (ptr)[9] = gl_functions[194], (ptr)[10] = gl_functions[195], (ptr)[11] = gl_functions[196], (ptr)[12] = gl_functions[197], (ptr)[13] = gl_functions[198];
#define FCGL_function_lessThan(ptr) (ptr)[0] = gl_functions[199], (ptr)[1] = gl_functions[200], (ptr)[2] = gl_functions[201], (ptr)[3] = gl_functions[202], (ptr)[4] = gl_functions[203], (ptr)[5] = gl_functions[204], (ptr)[6] = gl_functions[205], (ptr)[7] = gl_functions[206];
#define FCGL_function_lessThanEqual(ptr) (ptr)[0] = gl_functions[207], (ptr)[1] = gl_functions[208], (ptr)[2] = gl_functions[209], (ptr)[3] = gl_functions[210], (ptr)[4] = gl_functions[211], (ptr)[5] = gl_functions[212], (ptr)[6] = gl_functions[213], (ptr)[7] = gl_functions[214], (ptr)[8] = gl_functions[215], (ptr)[9] = gl_functions[216], (ptr)[10] = gl_functions[217], (ptr)[11] = gl_functions[218], (ptr)[12] = gl_functions[219];
#define FCGL_function_graeterThan(ptr) (ptr)[0] = gl_functions[220], (ptr)[1] = gl_functions[221], (ptr)[2] = gl_functions[222], (ptr)[3] = gl_functions[223], (ptr)[4] = gl_functions[224], (ptr)[5] = gl_functions[225], (ptr)[6] = gl_functions[226], (ptr)[7] = gl_functions[227], (ptr)[8] = gl_functions[228], (ptr)[9] = gl_functions[229], (ptr)[10] = gl_functions[230];
#define FCGL_function_greaterThanEqual(ptr) (ptr)[0] = gl_functions[231], (ptr)[1] = gl_functions[232], (ptr)[2] = gl_functions[233], (ptr)[3] = gl_functions[234], (ptr)[4] = gl_functions[235], (ptr)[5] = gl_functions[236], (ptr)[6] = gl_functions[237], (ptr)[7] = gl_functions[238], (ptr)[8] = gl_functions[239], (ptr)[9] = gl_functions[240], (ptr)[10] = gl_functions[241], (ptr)[11] = gl_functions[242], (ptr)[12] = gl_functions[243], (ptr)[13] = gl_functions[244], (ptr)[14] = gl_functions[245], (ptr)[15] = gl_functions[246];
#define FCGL_function_equal(ptr) (ptr)[0] = gl_functions[247], (ptr)[1] = gl_functions[248], (ptr)[2] = gl_functions[249], (ptr)[3] = gl_functions[250], (ptr)[4] = gl_functions[251];
#define FCGL_function_notEqual(ptr) (ptr)[0] = gl_functions[252], (ptr)[1] = gl_functions[253], (ptr)[2] = gl_functions[254], (ptr)[3] = gl_functions[255], (ptr)[4] = gl_functions[256], (ptr)[5] = gl_functions[257], (ptr)[6] = gl_functions[258], (ptr)[7] = gl_functions[259];
#define FCGL_function_any(ptr) (ptr)[0] = gl_functions[260], (ptr)[1] = gl_functions[261], (ptr)[2] = gl_functions[262];
#define FCGL_function_all(ptr) (ptr)[0] = gl_functions[263], (ptr)[1] = gl_functions[264], (ptr)[2] = gl_functions[265];
#define FCGL_function_not(ptr) (ptr)[0] = gl_functions[266], (ptr)[1] = gl_functions[267], (ptr)[2] = gl_functions[268];
#define FCGL_function_texture1D(ptr) (ptr)[0] = gl_functions[269], (ptr)[1] = gl_functions[270], (ptr)[2] = gl_functions[271], (ptr)[3] = gl_functions[272], (ptr)[4] = gl_functions[273], (ptr)[5] = gl_functions[274], (ptr)[6] = gl_functions[275], (ptr)[7] = gl_functions[276], (ptr)[8] = gl_functions[277];
#define FCGL_function_texture1DProj(ptr) (ptr)[0] = gl_functions[278], (ptr)[1] = gl_functions[279], (ptr)[2] = gl_functions[280], (ptr)[3] = gl_functions[281], (ptr)[4] = gl_functions[282], (ptr)[5] = gl_functions[283], (ptr)[6] = gl_functions[284], (ptr)[7] = gl_functions[285], (ptr)[8] = gl_functions[286], (ptr)[9] = gl_functions[287], (ptr)[10] = gl_functions[288], (ptr)[11] = gl_functions[289], (ptr)[12] = gl_functions[290];
#define FCGL_function_texture1DLod(ptr) (ptr)[0] = gl_functions[291], (ptr)[1] = gl_functions[292], (ptr)[2] = gl_functions[293], (ptr)[3] = gl_functions[294], (ptr)[4] = gl_functions[295], (ptr)[5] = gl_functions[296], (ptr)[6] = gl_functions[297], (ptr)[7] = gl_functions[298], (ptr)[8] = gl_functions[299], (ptr)[9] = gl_functions[300], (ptr)[10] = gl_functions[301], (ptr)[11] = gl_functions[302];
#define FCGL_function_texture1dProjLod(ptr) (ptr)[0] = gl_functions[303], (ptr)[1] = gl_functions[304], (ptr)[2] = gl_functions[305], (ptr)[3] = gl_functions[306], (ptr)[4] = gl_functions[307], (ptr)[5] = gl_functions[308], (ptr)[6] = gl_functions[309], (ptr)[7] = gl_functions[310], (ptr)[8] = gl_functions[311], (ptr)[9] = gl_functions[312], (ptr)[10] = gl_functions[313], (ptr)[11] = gl_functions[314], (ptr)[12] = gl_functions[315], (ptr)[13] = gl_functions[316], (ptr)[14] = gl_functions[317], (ptr)[15] = gl_functions[318];
#define FCGL_function_texture2D(ptr) (ptr)[0] = gl_functions[319], (ptr)[1] = gl_functions[320], (ptr)[2] = gl_functions[321], (ptr)[3] = gl_functions[322], (ptr)[4] = gl_functions[323], (ptr)[5] = gl_functions[324], (ptr)[6] = gl_functions[325], (ptr)[7] = gl_functions[326], (ptr)[8] = gl_functions[327];
#define FCGL_function_texture2DProj(ptr) (ptr)[0] = gl_functions[328], (ptr)[1] = gl_functions[329], (ptr)[2] = gl_functions[330], (ptr)[3] = gl_functions[331], (ptr)[4] = gl_functions[332], (ptr)[5] = gl_functions[333], (ptr)[6] = gl_functions[334], (ptr)[7] = gl_functions[335], (ptr)[8] = gl_functions[336], (ptr)[9] = gl_functions[337], (ptr)[10] = gl_functions[338], (ptr)[11] = gl_functions[339], (ptr)[12] = gl_functions[340];
#define FCGL_function_texture2DLod(ptr) (ptr)[0] = gl_functions[341], (ptr)[1] = gl_functions[342], (ptr)[2] = gl_functions[343], (ptr)[3] = gl_functions[344], (ptr)[4] = gl_functions[345], (ptr)[5] = gl_functions[346], (ptr)[6] = gl_functions[347], (ptr)[7] = gl_functions[348], (ptr)[8] = gl_functions[349], (ptr)[9] = gl_functions[350], (ptr)[10] = gl_functions[351], (ptr)[11] = gl_functions[352];
#define FCGL_function_texture2DProjLod(ptr) (ptr)[0] = gl_functions[353], (ptr)[1] = gl_functions[354], (ptr)[2] = gl_functions[355], (ptr)[3] = gl_functions[356], (ptr)[4] = gl_functions[357], (ptr)[5] = gl_functions[358], (ptr)[6] = gl_functions[359], (ptr)[7] = gl_functions[360], (ptr)[8] = gl_functions[361], (ptr)[9] = gl_functions[362], (ptr)[10] = gl_functions[363], (ptr)[11] = gl_functions[364], (ptr)[12] = gl_functions[365], (ptr)[13] = gl_functions[366], (ptr)[14] = gl_functions[367], (ptr)[15] = gl_functions[368];
#define FCGL_function_texture3D(ptr) (ptr)[0] = gl_functions[369], (ptr)[1] = gl_functions[370], (ptr)[2] = gl_functions[371], (ptr)[3] = gl_functions[372], (ptr)[4] = gl_functions[373], (ptr)[5] = gl_functions[374], (ptr)[6] = gl_functions[375], (ptr)[7] = gl_functions[376], (ptr)[8] = gl_functions[377];
#define FCGL_function_texture3DProj(ptr) (ptr)[0] = gl_functions[378], (ptr)[1] = gl_functions[379], (ptr)[2] = gl_functions[380], (ptr)[3] = gl_functions[381], (ptr)[4] = gl_functions[382], (ptr)[5] = gl_functions[383], (ptr)[6] = gl_functions[384], (ptr)[7] = gl_functions[385], (ptr)[8] = gl_functions[386], (ptr)[9] = gl_functions[387], (ptr)[10] = gl_functions[388], (ptr)[11] = gl_functions[389], (ptr)[12] = gl_functions[390];
#define FCGL_function_texture3DLod(ptr) (ptr)[0] = gl_functions[391], (ptr)[1] = gl_functions[392], (ptr)[2] = gl_functions[393], (ptr)[3] = gl_functions[394], (ptr)[4] = gl_functions[395], (ptr)[5] = gl_functions[396], (ptr)[6] = gl_functions[397], (ptr)[7] = gl_functions[398], (ptr)[8] = gl_functions[399], (ptr)[9] = gl_functions[400], (ptr)[10] = gl_functions[401], (ptr)[11] = gl_functions[402];
#define FCGL_function_texture3DProjLod(ptr) (ptr)[0] = gl_functions[403], (ptr)[1] = gl_functions[404], (ptr)[2] = gl_functions[405], (ptr)[3] = gl_functions[406], (ptr)[4] = gl_functions[407], (ptr)[5] = gl_functions[408], (ptr)[6] = gl_functions[409], (ptr)[7] = gl_functions[410], (ptr)[8] = gl_functions[411], (ptr)[9] = gl_functions[412], (ptr)[10] = gl_functions[413], (ptr)[11] = gl_functions[414], (ptr)[12] = gl_functions[415], (ptr)[13] = gl_functions[416], (ptr)[14] = gl_functions[417], (ptr)[15] = gl_functions[418];
#define FCGL_function_textureCube(ptr) (ptr)[0] = gl_functions[419], (ptr)[1] = gl_functions[420], (ptr)[2] = gl_functions[421], (ptr)[3] = gl_functions[422], (ptr)[4] = gl_functions[423], (ptr)[5] = gl_functions[424], (ptr)[6] = gl_functions[425], (ptr)[7] = gl_functions[426], (ptr)[8] = gl_functions[427], (ptr)[9] = gl_functions[428], (ptr)[10] = gl_functions[429],
#define FCGL_function_textureCubeLod(ptr) (ptr)[0] = gl_functions[430], (ptr)[1] = gl_functions[431], (ptr)[2] = gl_functions[432], (ptr)[3] = gl_functions[433], (ptr)[4] = gl_functions[434], (ptr)[5] = gl_functions[435], (ptr)[6] = gl_functions[436], (ptr)[7] = gl_functions[437], (ptr)[8] = gl_functions[438], (ptr)[9] = gl_functions[439], (ptr)[10] = gl_functions[440], (ptr)[11] = gl_functions[441], (ptr)[12] = gl_functions[442], (ptr)[13] = gl_functions[443];
#define FCGL_function_shadow1D(ptr) (ptr)[0] = gl_functions[444], (ptr)[1] = gl_functions[445], (ptr)[2] = gl_functions[446], (ptr)[3] = gl_functions[447], (ptr)[4] = gl_functions[448], (ptr)[5] = gl_functions[449], (ptr)[6] = gl_functions[450], (ptr)[7] = gl_functions[451];
#define FCGL_function_shadow2D(ptr) (ptr)[0] = gl_functions[452], (ptr)[1] = gl_functions[453], (ptr)[2] = gl_functions[454], (ptr)[3] = gl_functions[455], (ptr)[4] = gl_functions[456], (ptr)[5] = gl_functions[457], (ptr)[6] = gl_functions[458], (ptr)[7] = gl_functions[459];
#define FCGL_function_shadow1DProj(ptr) (ptr)[0] = gl_functions[460], (ptr)[1] = gl_functions[461], (ptr)[2] = gl_functions[462], (ptr)[3] = gl_functions[463], (ptr)[4] = gl_functions[464], (ptr)[5] = gl_functions[465], (ptr)[6] = gl_functions[466], (ptr)[7] = gl_functions[467], (ptr)[8] = gl_functions[468], (ptr)[9] = gl_functions[469], (ptr)[10] = gl_functions[470], (ptr)[11] = gl_functions[471];
#define FCGL_function_shadow2DProj(ptr) (ptr)[0] = gl_functions[472], (ptr)[1] = gl_functions[473], (ptr)[2] = gl_functions[474], (ptr)[3] = gl_functions[475], (ptr)[4] = gl_functions[476], (ptr)[5] = gl_functions[477], (ptr)[6] = gl_functions[478], (ptr)[7] = gl_functions[479], (ptr)[8] = gl_functions[480], (ptr)[9] = gl_functions[481], (ptr)[10] = gl_functions[482], (ptr)[11] = gl_functions[483];
#define FCGL_function_shadow1DLod(ptr) (ptr)[0] = gl_functions[484], (ptr)[1] = gl_functions[485], (ptr)[2] = gl_functions[486], (ptr)[3] = gl_functions[487], (ptr)[4] = gl_functions[488], (ptr)[5] = gl_functions[489], (ptr)[6] = gl_functions[490], (ptr)[7] = gl_functions[491], (ptr)[8] = gl_functions[492], (ptr)[9] = gl_functions[493], (ptr)[10] = gl_functions[494];
#define FCGL_function_shadow2DLod(ptr) (ptr)[0] = gl_functions[495], (ptr)[1] = gl_functions[496], (ptr)[2] = gl_functions[497], (ptr)[3] = gl_functions[498], (ptr)[4] = gl_functions[499], (ptr)[5] = gl_functions[500], (ptr)[6] = gl_functions[501], (ptr)[7] = gl_functions[502], (ptr)[8] = gl_functions[503], (ptr)[9] = gl_functions[504], (ptr)[10] = gl_functions[505];
#define FCGL_function_shadow1DProjLod(ptr) (ptr)[0] = gl_functions[506], (ptr)[1] = gl_functions[507], (ptr)[2] = gl_functions[508], (ptr)[3] = gl_functions[509], (ptr)[4] = gl_functions[510], (ptr)[5] = gl_functions[511], (ptr)[6] = gl_functions[512], (ptr)[7] = gl_functions[513], (ptr)[8] = gl_functions[514], (ptr)[9] = gl_functions[515], (ptr)[10] = gl_functions[516], (ptr)[11] = gl_functions[517], (ptr)[12] = gl_functions[518], (ptr)[13] = gl_functions[519], (ptr)[14] = gl_functions[520];
#define FCGL_function_shadow2DProjLod(ptr) (ptr)[0] = gl_functions[521], (ptr)[1] = gl_functions[522], (ptr)[2] = gl_functions[523], (ptr)[3] = gl_functions[524], (ptr)[4] = gl_functions[525], (ptr)[5] = gl_functions[526], (ptr)[6] = gl_functions[527], (ptr)[7] = gl_functions[528], (ptr)[8] = gl_functions[529], (ptr)[9] = gl_functions[530], (ptr)[10] = gl_functions[531], (ptr)[11] = gl_functions[532], (ptr)[12] = gl_functions[533], (ptr)[13] = gl_functions[534], (ptr)[14] = gl_functions[535];
#define FCGL_function_dFdx(ptr) (ptr)[0] = gl_functions[536], (ptr)[1] = gl_functions[537], (ptr)[2] = gl_functions[538], (ptr)[3] = gl_functions[539];
#define FCGL_function_dFdy(ptr) (ptr)[0] = gl_functions[540], (ptr)[1] = gl_functions[541], (ptr)[2] = gl_functions[542], (ptr)[3] = gl_functions[543];
#define FCGL_function_fwidth(ptr) (ptr)[0] = gl_functions[544], (ptr)[1] = gl_functions[545], (ptr)[2] = gl_functions[546], (ptr)[3] = gl_functions[547], (ptr)[4] = gl_functions[548], (ptr)[5] = gl_functions[549];
#define FCGL_function_noise1(ptr) (ptr)[0] = gl_functions[550], (ptr)[1] = gl_functions[551], (ptr)[2] = gl_functions[552], (ptr)[3] = gl_functions[553], (ptr)[4] = gl_functions[554], (ptr)[5] = gl_functions[555];
#define FCGL_function_noise2(ptr) (ptr)[0] = gl_functions[556], (ptr)[1] = gl_functions[557], (ptr)[2] = gl_functions[558], (ptr)[3] = gl_functions[559], (ptr)[4] = gl_functions[560], (ptr)[5] = gl_functions[561];
#define FCGL_function_noise3(ptr) (ptr)[0] = gl_functions[562], (ptr)[1] = gl_functions[563], (ptr)[2] = gl_functions[564], (ptr)[3] = gl_functions[565], (ptr)[4] = gl_functions[566], (ptr)[5] = gl_functions[567];
#define FCGL_function_noise4(ptr) (ptr)[0] = gl_functions[568], (ptr)[1] = gl_functions[569], (ptr)[2] = gl_functions[570], (ptr)[3] = gl_functions[571], (ptr)[4] = gl_functions[572], (ptr)[5] = gl_functions[573];

void printinfo() {
    long long i, j, c, k;
    for (j = 0, c = 0; j < sizeof(gl_functionsLength); j++) {
        printf("#define FCGL_function_");
        for (i = 0, k = c; i < gl_functionsLength[j]; i++)
            printf("%c", gl_functions[k++]);
        printf("(ptr)");
        for (i = 0; i < gl_functionsLength[j]; i++) {
            printf(" (ptr)[%I64d] = gl_functions[%I64d],", i, c++);
        }
        printf("\n");
    }
    for (j = 0, c = 0; j < sizeof(gl_operatorsLength); j++) {
        for (i = 0; i < gl_operatorsLength[j]; i++) {
            printf("%c", gl_operators[c++]);
        }
        printf("\n");
    }
    for (j = 0, c = 0; j < sizeof(gl_typesLength); j++) {
        printf("#define FCGL_type_");
        for (i = 0, k = c; i < gl_typesLength[j]; i++)
            printf("%c", gl_types[k++]);
        printf("(ptr)");
        for (i = 0; i < gl_typesLength[j]; i++) {
            if (i == gl_typesLength[j] - 1)
                printf(" (ptr)[%I64d] = gl_types[%I64d];", i, c++);
            else
                printf(" (ptr)[%I64d] = gl_types[%I64d],", i, c++);
        }
        printf("\n");
    }
    for (j = 0, c = 0; j < sizeof(gl_typeQualifiersLength); j++) {
        printf("#define FCGL_typeQualifier_");
        for (i = 0, k = c; i < gl_typeQualifiersLength[j]; i++)
            printf("%c", gl_typeQualifiers[k++]);
        printf("(ptr)");
        for (i = 0; i < gl_typeQualifiersLength[j]; i++) {
            if (i == gl_typeQualifiersLength[j] - 1)
                printf(" (ptr)[%I64d] = gl_typeQualifiers[%I64d];", i, c++);
            else
                printf(" (ptr)[%I64d] = gl_typeQualifiers[%I64d],", i, c++);
        }
        printf("\n");
    }
    for (j = 0, c = 0; j < sizeof(gl_preprocessorLength); j++) {
        printf("#define FCGL_preprocessor_");
        for (i = 0, k = c; i < gl_preprocessorLength[j]; i++)
            printf("%c", gl_preprocessor[k++]);
        printf("(ptr)");
        for (i = 0; i < gl_preprocessorLength[j]; i++) {
            if (i == gl_preprocessorLength[j] - 1)
                printf(" (ptr)[%I64d] = gl_preprocessor[%I64d];", i, c++);
            else
                printf(" (ptr)[%I64d] = gl_preprocessor[%I64d],", i, c++);
        }
        printf("\n");
    }
    for (j = 0, c = 0; j < sizeof(gl_shaderVariablesLength); j++) {
        printf("#define FCGL_variables_");
        for (i = 0, k = c; i < gl_shaderVariablesLength[j]; i++)
            printf("%c", gl_shaderVariables[k++]);
        printf("(ptr)");
        for (i = 0; i < gl_shaderVariablesLength[j]; i++) {
            if (i == gl_shaderVariablesLength[j] - 1)
                printf(" (ptr)[%I64d] = gl_shaderVariables[%I64d];", i, c++);
            else
                printf(" (ptr)[%I64d] = gl_shaderVariables[%I64d],", i, c++);
        }
        printf("\n");
    }
    i = 0;
}

#endif