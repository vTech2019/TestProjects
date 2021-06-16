//
// Created by human on 04.04.2020.
//

#include "gl_mesh.h"
#include <stdio.h>

void gl_mesh_init_thread(struct gl_mesh_parameters* vertex_data, struct gl_mesh* mesh){

    if (vertex_data->return_number_vertices && vertex_data->return_number_indices){
        if(!mesh->m_vertexBuffer)
            glGenBuffers(1, &mesh->m_vertexBuffer);
        if(!mesh->m_indexCount)
            glGenBuffers(1, &mesh->m_indexBuffer);
        if (!mesh->m_VAO)
            glGenVertexArrays(1, &mesh->m_VAO);

        glBindVertexArray(mesh->m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data->return_vertices[0]) * vertex_data->return_number_vertices, vertex_data->return_vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_data->return_indices[0]) * vertex_data->return_number_indices, vertex_data->return_indices, GL_STATIC_DRAW);
        
        if (vertex_data->numberPositions){
            glEnableVertexAttribArray(vertex_data->indexProgramPosition);
            glVertexAttribPointer(vertex_data->indexProgramPosition, vertex_data->numberPositions, GL_FLOAT, GL_FALSE, vertex_data->offsetVertex * sizeof(float), (void *) (vertex_data->offsetVertexPosition * sizeof(GLfloat)));
        }
        if (vertex_data->activateColors) {
            glEnableVertexAttribArray(vertex_data->indexProgramColor);
            glVertexAttribPointer(vertex_data->indexProgramColor, vertex_data->activateColors, GL_FLOAT, GL_FALSE, vertex_data->offsetVertex * sizeof(float), (void *) (vertex_data->offsetColorPosition * sizeof(GLfloat)));
        }
        if (vertex_data->activateNormals) {
            glEnableVertexAttribArray(vertex_data->indexProgramNormal);
            glVertexAttribPointer(vertex_data->indexProgramNormal, vertex_data->activateNormals, GL_FLOAT, GL_FALSE, vertex_data->offsetVertex * sizeof(float), (void*)(vertex_data->offsetNormalPosition * sizeof(GLfloat)));
        }
        if (vertex_data->activateTexture){
            glEnableVertexAttribArray(vertex_data->indexProgramTexture);
            glVertexAttribPointer(vertex_data->indexProgramTexture, vertex_data->activateTexture, GL_FLOAT, GL_FALSE, vertex_data->offsetVertex * sizeof(float), (void *) (vertex_data->offsetTexturePosition * sizeof(GLfloat)) );
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        if (vertex_data->image_rgb) {
            gl_mesh_create2DTexture_RGB8_thread(mesh, vertex_data->image_rgb, vertex_data->width, vertex_data->height);
        }
        mesh->m_vertexCount = (int)vertex_data->return_number_vertices;
        mesh->m_indexCount = (int)vertex_data->return_number_indices;

    }
}
void gl_mesh_create2DTexture_RGB8_thread(struct gl_mesh* mesh, const GLbyte* image, GLuint width, GLuint height) {
    glGenTextures(1, &mesh->m_textureId);
    glBindTexture(GL_TEXTURE_2D, mesh->m_textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}
/*
struct gl_mesh gl_mesh_copy(const struct gl_mesh mesh) {
    struct gl_mesh copy = { 0 };
    GLint bufferVertexSize;
    GLint bufferIndexSize;
    GLint width, height, depth, format;
    glBindTexture(GL_TEXTURE_2D, mesh.m_textureId);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_DEPTH, &depth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);
    gl_mesh_create2DTexture_RGB8(&copy, NULL, width, height);
    glCopyImageSubData(mesh.m_textureId, GL_TEXTURE_2D, 0, 0, 0, 0, mesh.m_textureId, GL_TEXTURE_2D, 0, 0, 0, 0, width, height, depth);


    glGenBuffers(1, &copy.m_vertexBuffer);
    glGenBuffers(1, &copy.m_indexBuffer);
    glGenVertexArrays(1, &copy.m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.m_vertexBuffer);
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferVertexSize);
    glBindBuffer(GL_COPY_WRITE_BUFFER, copy.m_vertexBuffer);
    glBufferData(GL_COPY_WRITE_BUFFER, bufferVertexSize, NULL, GL_STATIC_DRAW);
    glCopyBufferSubData(GL_ARRAY_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferVertexSize);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.m_indexBuffer);
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferIndexSize);
    glBindBuffer(GL_COPY_WRITE_BUFFER, copy.m_indexBuffer);
    glBufferData(GL_COPY_WRITE_BUFFER, bufferIndexSize, NULL, GL_STATIC_DRAW);
    glCopyBufferSubData(GL_ELEMENT_ARRAY_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferIndexSize);

    glBindVertexArray(copy.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, copy.m_vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, copy.m_indexBuffer);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::PositionOffset);
    //glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)Vertex::ColorOffset);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)Vertex::TextureOffset);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    copy.m_vertexCount = mesh.m_vertexCount;
    copy.m_indexCount = mesh.m_indexCount;
}*/

void gl_mesh_free_thread(struct gl_mesh* mesh){
    if (mesh){
        mesh->m_indexCount = 0;
        mesh->m_textureId = 0;
        mesh->m_vertexCount = 0;
        if (mesh->m_textureId) glDeleteTextures(1, &mesh->m_textureId);
        if (mesh->m_vertexBuffer) glDeleteBuffers(1, &mesh->m_vertexBuffer);
        if (mesh->m_indexBuffer) glDeleteBuffers(1, &mesh->m_indexBuffer);
        if (mesh->m_VAO) glDeleteVertexArrays(1, &mesh->m_VAO);
        mesh->m_textureId = 0;
        mesh->m_VAO = 0;
        mesh->m_indexBuffer = 0;
        mesh->m_vertexBuffer = 0;
    }
}