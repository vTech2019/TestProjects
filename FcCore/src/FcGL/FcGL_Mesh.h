#pragma once

#ifndef __FCGL_MESH_H__
#define __FCGL_MESH_H__

#include "FcGL_Functions.h"

typedef struct _FcGL_Mesh_parameters_t {
    GLuint m_meshMode;
    GLuint m_vertexCount;
    GLuint m_vertexLength;
    GLuint m_vertexDataLength;

    GLuint m_vertexIndex;
    GLuint m_colorIndex;
    GLuint m_normalIndex;
    GLuint m_textureIndex;

    GLuint m_vertexOffsetPosition;
    GLuint m_colorOffsetPosition_rgba;
    GLuint m_normalOffsetPosition;
    GLuint m_textureOffsetPosition;


    void *m_return_data;
    GLuint m_return_sizeVertexBuffer;
    GLuint m_return_number_indices;

    GLbyte *m_image_rgb;
    GLuint m_width;
    GLuint m_height;
} FcGL_Mesh_parameters_t;

typedef struct _FcGL_Mesh_t {
    GLuint m_vertexCount;
    GLuint m_vertexLength;
    GLuint m_vertexDataLength;
    GLuint m_vertexIndex;
    GLuint m_vertexOffsetPosition;
    GLuint m_vertexBuffer;


    GLuint m_colorCount;
    GLuint m_normalCount;
    GLuint m_textureCount;
    GLuint m_indexCount;


    GLuint m_colorIndex;
    GLuint m_normalIndex;
    GLuint m_textureIndex;

    GLuint m_colorOffsetPosition_rgba;
    GLuint m_normalOffsetPosition;
    GLuint m_textureOffsetPosition;

    GLuint m_meshMode;
    GLuint m_textureId;
    GLuint m_indexBuffer;
} FcGL_Mesh_t;

void FcGL_Mesh_drawArrays_v(FcGL_Mesh_t *mesh);

FcGL_Mesh_t FcGL_Mesh(const FcGL_Mesh_parameters_t *parameters);

void FcGL_Mesh_free(FcGL_Mesh_t *mesh);

void FcGL_create2DTexture_R8(GLuint *textureId, const GLbyte *image, GLuint width, GLuint height);

void FcGL_create2DTexture_RGB8(GLuint *textureId, const GLbyte *image, GLuint width, GLuint height);

static inline void FcGL_bind2DTexture(GLuint textureId) { glBindTexture(GL_TEXTURE_2D, textureId); };

static inline void FcGL_rewrite2DTexture_Alpha(GLuint textureId, GLuint x, GLuint y,
                                               GLuint width, GLuint height, const GLubyte *data) {
    FcGL_bind2DTexture(textureId);
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_ALPHA, GL_UNSIGNED_BYTE, data);
};

static inline void FcGL_rewrite2DTexture_RGB(GLuint textureId, GLuint x, GLuint y,
                                             GLuint width, GLuint height, const GLubyte *data) {
    FcGL_bind2DTexture(textureId);
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
};
#endif