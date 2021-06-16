#include "FcGL_Mesh.h"

void FcGL_create2DTexture_RGB8(GLuint *textureId, const GLbyte *image, GLuint width, GLuint height) {
    glGenTextures(1, textureId);
    glBindTexture(GL_TEXTURE_2D, *textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void FcGL_create2DTexture_R8(GLuint *textureId, const GLbyte *image, GLuint width, GLuint height) {
    glGenTextures(1, textureId);
    glBindTexture(GL_TEXTURE_2D, *textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

FcGL_Mesh_t FcGL_Mesh(const FcGL_Mesh_parameters_t *parameters) {
    FcGL_Mesh_t mesh = {0};
    if (parameters->m_return_sizeVertexBuffer) {
        glGenBuffers(1, &mesh.m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.m_vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, parameters->m_return_sizeVertexBuffer, parameters->m_return_data, GL_STATIC_DRAW);
    }
    if (parameters->m_return_number_indices) {
        glGenBuffers(1, &mesh.m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * parameters->m_return_number_indices,
                     (char *) parameters->m_return_data + parameters->m_return_sizeVertexBuffer, GL_STATIC_DRAW);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if (parameters->m_image_rgb) {
        FcGL_create2DTexture_RGB8(&mesh.m_textureId, parameters->m_image_rgb, parameters->m_width,
                                  parameters->m_height);
    }
    mesh.m_vertexDataLength = parameters->m_vertexDataLength;
    mesh.m_vertexLength = parameters->m_vertexLength;
    mesh.m_vertexCount = parameters->m_vertexCount;
    mesh.m_colorCount = (parameters->m_colorOffsetPosition_rgba) ? parameters->m_vertexCount * 4 : 0;
    mesh.m_normalCount = (parameters->m_normalOffsetPosition) ? parameters->m_vertexCount : 0;
    mesh.m_textureCount = (parameters->m_textureOffsetPosition) ? parameters->m_vertexCount : 0;
    mesh.m_indexCount = parameters->m_return_number_indices;

    mesh.m_vertexIndex = parameters->m_vertexIndex;
    mesh.m_colorIndex = parameters->m_colorIndex;
    mesh.m_normalIndex = parameters->m_normalIndex;
    mesh.m_textureIndex = parameters->m_textureIndex;

    mesh.m_vertexOffsetPosition = parameters->m_vertexOffsetPosition;
    mesh.m_colorOffsetPosition_rgba = parameters->m_colorOffsetPosition_rgba;
    mesh.m_normalOffsetPosition = parameters->m_normalOffsetPosition;
    mesh.m_textureOffsetPosition = parameters->m_textureOffsetPosition;

    mesh.m_meshMode = parameters->m_meshMode;
    return mesh;
}

void FcGL_Mesh_drawArrays_v(FcGL_Mesh_t *mesh) {
    glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vertexBuffer);
    glEnableVertexAttribArray(mesh->m_vertexIndex);
    glVertexAttribPointer(mesh->m_vertexIndex, mesh->m_vertexLength, GL_FLOAT, GL_FALSE, mesh->m_vertexDataLength,
                          (const GLvoid *) mesh->m_vertexOffsetPosition);
    glDrawArrays(mesh->m_meshMode, 0, mesh->m_vertexCount);
}

void FcGL_Mesh_free(FcGL_Mesh_t *mesh) {
    if (mesh->m_textureId) glDeleteTextures(1, &mesh->m_textureId);
    if (mesh->m_vertexBuffer) glDeleteBuffers(1, &mesh->m_vertexBuffer);
    if (mesh->m_indexBuffer) glDeleteBuffers(1, &mesh->m_indexBuffer);
    memset(mesh, 0, sizeof(*mesh));
}